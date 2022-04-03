pragma solidity >= 0.5.0 <0.7.0;
import "@aztec/protocol/contracts/ERC1724/ZkAssetMintable.sol";
import "@aztec/protocol/contracts/libs/NoteUtils.sol";
import "@aztec/protocol/contracts/interfaces/IZkAsset.sol";
import "./LoanUtilities.sol";

/*
  @dev Loan contract with confidentiality does the following things:
  
  1. A borrower can create a loan request with a confidential loan notional.
  2. A lender can request access to see the value of the loan notional.
  3. A lender can settle a loan request by transferring the notional to the borrower,
     the transfer notional should be confidential.
     The blockchain should verify that the notional amount and the settlement amount are equal.
  4. The borrower should be able to pay interest into an account that the lender can withdraw from.
     Any payments to the interest account should be confidential.
  5. The lender should be able to withdraw interest from the interest account as it accrues up to the last block time.
    The blockchain should verify the amount of interest the lender is withdrawing is correct,
    and the withdraw amount and the balance of the account should remain confidential.
  6. The lender should be able to mark a loan as defaulting if the interest account does not contain sufficient interest.
    The blockchain should validate that this is the case whilst keeping the total interest payed,
    the account balance and the loan’s notional confidential.
*/

/* Creating the Loan zkAsset
  1. As the loan is intended to be a fully private asset without a public equivalent,
     it will inherit from the reference EIP1724ZkAssetMintable.sol contract.
     In this case, the constructor is overridden with to create a fully private asset.
*/
contract Loan is ZkAssetMintable {

  using SafeMath for uint256;
  using NoteUtils for bytes;
  using LoanUtilities for LoanUtilities.LoanVariables;
  LoanUtilities.LoanVariables public loanVariables;

  // This token handles value transferof zkAsset
  // The ACE contract is approved to spend ERC20 tokens on behalf of the token owner.
  // ```await settlementToken.approve(aceContract.address, value);```
  IZkAsset public settlementToken;
  // [0] interestRate
  // [1] interestPeriod
  // [2] duration
  // [3] settlementCurrencyId
  // [4] loanSettlementDate
  // [5] lastInterestPaymentDate address public borrower;
  address public lender;
  address public borrower;

  // lender address to shared secret
  mapping(address => bytes) lenderApprovals;

  event LoanPayment(string paymentType, uint256 lastInterestPaymentDate);
  event LoanDefault();
  event LoanRepaid();

  // AZTEC Note
  struct Note {
    // note owner
    address owner;
    // hashed string of note's public key
    bytes32 noteHash;
  }

  // Returning to Note struct after taking data in bytes form essentially and encodes them
  function _noteCoderToStruct(bytes memory note) internal pure returns (Note memory codedNote) {
    // the function returns the owner and the hashed string of note's public key
      (address owner, bytes32 noteHash,) = note.extractNote();
      return Note(owner, noteHash );
  }

  // @dev constructor : constructing loan contract and set variables to loan
  constructor(
    bytes32 _notional, // the notional value of loan asset
    uint256[] memory _loanVariables, // interest rate, period and duration
    address _borrower, // borrower address
    address _aceAddress, // address of AZTEC cryptographic contract
    address _settlementCurrency // address of ERC20 token to be settled with
    // On note values, all AZTEC toolkits do logical tests.
    // A note must be made before a logical check can be performed.
    // The loan's notional must be recorded as a note in the loan's note registry in order for it to be kept private.
    // Because any note registry's starting supply is zero, the Mint Proof must be used to alter the overall supply and generate new notes in a private asset.
   ) public ZkAssetMintable(_aceAddress, address(0), 1, true, false) {
      loanVariables.loanFactory = msg.sender; // contract calling this constructor to be loanFactory variable
      loanVariables.notional = _notional; // notional amount of the loan
      loanVariables.id = address(this); // set the id to the address of the contract
      loanVariables.interestRate = _loanVariables[0];
      loanVariables.interestPeriod = _loanVariables[1];
      loanVariables.duration = _loanVariables[2];
      loanVariables.borrower = _borrower;
      borrower = _borrower;
      // settlementing ERC20 tokens with a zkAsset linked to the note of the settlement
      loanVariables.settlementToken = IZkAsset(_settlementCurrency);
      loanVariables.aceAddress = _aceAddress;
  }

  // requesting permission to view the loan
  function requestAccess() public {
    lenderApprovals[msg.sender] = '0x';
  }

  // approving lender loan to view request
  function approveAccess(address _lender, bytes memory _sharedSecret) public {
    lenderApprovals[_lender] = _sharedSecret;
  }

  // settling loan
  // loan ownership goes to the lender while settlement assets go to the borrower
  function settleLoan(
    bytes calldata _proofData,
    bytes32 _currentInterestBalance,
    address _lender
  ) external {
    // settlement should be an loan initalizer
    LoanUtilities.onlyLoanDapp(msg.sender, loanVariables.loanFactory);

    // it also validates bilteral swap proof that shows the settlement assets
    // that is equal to the price of multiplied assets of notional loan price amount.
    LoanUtilities._processLoanSettlement(_proofData, loanVariables);

    // the output of proof updates the retrospective note registries.
    // it destorys the takerBid note while creating makerBid note in the settlement zkNotes Asset Registry.
    // it also destroys the makerBid note while creating takerBid note in the loan zkNotes Asset Registry.

    // storing timestamp to calculate accured timestamp
    loanVariables.loanSettlementDate = block.timestamp;
    loanVariables.lastInterestPaymentDate = block.timestamp;
    loanVariables.currentInterestBalance = _currentInterestBalance;
    loanVariables.lender = _lender;
    lender = _lender;
  }

/*
  To construct the Mint Proof, it uses aztec.js library.

  In this scenario, the constructor of the loan ZkAsset is a smart contract.
  The owner of the ZkAsset note registry is that contract.
  This enables it to validate a proof and handle the transfer instructions that result inside ACE.
*/
  // minting new notional loan with a mint proof and adds them to the loan note registry
  function confidentialMint(uint24 _proof, bytes calldata _proofData) external {
    // Only loanDapp could mint this loan note
    LoanUtilities.onlyLoanDapp(msg.sender, loanVariables.loanFactory);
    // Only the owner of the note registry is permitted to call the ```confidentialMint``` method.
    require(msg.sender == owner, "only owner can call the confidentialMint() method");
    require(_proofData.length != 0, "proof invalid");
    // overide this function to change the mint method to msg.sender
    // mints the new AZTEC notes
    (bytes memory _proofOutputs) = ace.mint(_proof, _proofData, msg.sender);

    // newTotal equals to the ```confidentailTotalSupply``` note
    (, bytes memory newTotal, ,) = _proofOutputs.get(0).extractProofOutput();

    // mintedNotes are the newly minted notes
    (, bytes memory mintedNotes, ,) = _proofOutputs.get(1).extractProofOutput();

    // retreving the hash of confidentialTotalSupply public key and its note-specific metadata to extract new Note
    (,
    bytes32 noteHash,
    bytes memory metadata) = newTotal.extractNote();
    // emiting events for all output notes that represents note being created and added to the note registry
    logOutputNotes(mintedNotes);
    emit UpdateTotalMinted(noteHash, metadata);
  }

  // lender withdraw interest in the interest account
  // @param _proof1 : dividend_proof that shows accured interest is calculated correctly
  // @param _proof2 : join_split_proof that shows interest note with join-split operation has done correctly
  function withdrawInterest(
    bytes memory _proof1,
    bytes memory _proof2,
    uint256 _interestDurationToWithdraw
  ) public {
    // dividend proof used to prove ```NotionalNote = AccruedInterest * Ratio```
    (,bytes memory _proof1OutputNotes) = LoanUtilities._validateInterestProof(_proof1, _interestDurationToWithdraw, loanVariables);

    // ensuring that lender has not attempted to withdraw more funds than the actual accured interest
    require(_interestDurationToWithdraw.add(loanVariables.lastInterestPaymentDate) < block.timestamp, ' withdraw is greater than accrued interest');

    // using Join-Split proof to withdraw interest
    // it splits current interest balance into accured interest and remainder note
    // it passes on _processInterestWithdrawal with proof parameter ```_proof2```.
    // loanVariables is accured interest note
    (bytes32 newCurrentInterestNoteHash) = LoanUtilities._processInterestWithdrawal(_proof2, _proof1OutputNotes, loanVariables);

    // updating interest note and subtotal of interest to withdraw
    loanVariables.currentInterestBalance = newCurrentInterestNoteHash;

    // updating loan interest payment date with duration of amount to withdraw
    loanVariables.lastInterestPaymentDate = loanVariables.lastInterestPaymentDate.add(_interestDurationToWithdraw);

    emit LoanPayment('INTEREST', loanVariables.lastInterestPaymentDate);

  }

  // Borrower pay interest
  // @param _proofData : join_split_proof that validates interest note join-split operation has done correctly
  function adjustInterestBalance(bytes memory _proofData) public {
    // only borrower can adjust borrowing rate
    LoanUtilities.onlyBorrower(msg.sender,borrower);

    (bytes32 newCurrentInterestBalance) = LoanUtilities._processAdjustInterest(_proofData, loanVariables);

    // updating interest note after adjusting the value
    loanVariables.currentInterestBalance = newCurrentInterestBalance;
  }

  // Borrower repay loan
  // @param _proof1 : dividend_proof that validates accured interest with remaining interest has been calculated correctly
  // @param _proof2 : join_split_proof that join-split operation has executed correctly
  function repayLoan(
    bytes memory _proof1,
    bytes memory _proof2
  ) public {
    // ensuring only the borrower can repay the loan
    LoanUtilities.onlyBorrower(msg.sender, borrower);

    uint256 remainingInterestDuration = loanVariables.loanSettlementDate.add(loanVariables.duration).sub(loanVariables.lastInterestPaymentDate);

    // validate the following: ```repayment === accrued + remaining```
    (,bytes memory _proof1OutputNotes) = LoanUtilities._validateInterestProof(_proof1, remainingInterestDuration, loanVariables);

    // ensuring that loan is not already overdue
    require(loanVariables.loanSettlementDate.add(loanVariables.duration) < block.timestamp, 'loan has not matured');

    // process the payment by utilizing join-split technique to confidentially transfer repayment of loan and interest with the lender (recipient)
    LoanUtilities._processLoanRepayment(
      _proof2,
      _proof1OutputNotes,
      loanVariables
    );

    emit LoanRepaid();
  }

  // mark defaulting loan in which the interest account has less fund than the accrued interest
  // @param _proof1 : dividend proof to validate the accured interest
  // @param _proof2 : private range proof that validates the accured is greater than the available in the interest account.
  function markLoanAsDefault(bytes memory _proof1, bytes memory _proo~f2, uint256 _interestDurationToWithdraw) public {
    // ensuring that lender has withdrawn the amount less and equal than the actual accrued interest
    require(_interestDurationToWithdraw.add(loanVariables.lastInterestPaymentDate) < block.timestamp, 'withdraw is greater than accrued interest');
    LoanUtilities._validateDefaultProofs(_proof1, _proof2, _interestDurationToWithdraw, loanVariables);
    emit LoanDefault();
  }
}

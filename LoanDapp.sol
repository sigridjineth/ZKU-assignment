pragma solidity >= 0.5.0 <0.7.0;

import "@aztec/protocol/contracts/interfaces/IAZTEC.sol";
import "@aztec/protocol/contracts/libs/NoteUtils.sol";
import "@aztec/protocol/contracts/ERC1724/ZkAsset.sol";
import "./ZKERC20/ZKERC20.sol";
import "./Loan.sol";

contract LoanDapp is IAZTEC {
  using NoteUtils for bytes;

  event SettlementCurrencyAdded(
    uint id,
    address settlementAddress
  );

  event LoanApprovedForSettlement(
    address loanId
  );

  event LoanCreated(
    address id,
    address borrower,
    bytes32 notional,
    string borrowerPublicKey,
    uint256[] loanVariables,
    uint createdAt
  );

  event ViewRequestCreated(
    address loanId,
    address lender,
    string lenderPublicKey
  );

  event ViewRequestApproved(
    uint accessId,
    address loanId,
    address user,
    string sharedSecret
  );

  event NoteAccessApproved(
    uint accessId,
    bytes32 note,
    address user,
    string sharedSecret
  );

  address owner = msg.sender;
  address aceAddress;
  // address of loans objects
  address[] public loans;
  mapping(uint => address) public settlementCurrencies;

  uint24 MINT_PRO0F = 66049;
  uint24 BILATERAL_SWAP_PROOF = 65794;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }

  modifier onlyBorrower(address _loanAddress) {
    Loan loanContract = Loan(_loanAddress);
    require(msg.sender == loanContract.borrower());
    _;
  }

  // aceAddress refers to the address of AZTEC cryptographic engine contract
  constructor(address _aceAddress) public {
    aceAddress = _aceAddress;
  }

  // retreiving the registered settlement with zkAsset
  // it returns the address of the settlement ERC20 tokens that loans are paid with
  function _getCurrencyContract(uint _settlementCurrencyId) internal view returns (address) {
    require(settlementCurrencies[_settlementCurrencyId] != address(0), 'Settlement Currency is not defined');
    return settlementCurrencies[_settlementCurrencyId];
  }

  // generating the accessId
  function _generateAccessId(bytes32 _note, address _user) internal pure returns (uint) {
    return uint(keccak256(abi.encodePacked(_note, _user)));
  }

  // giving a permission to access note to those who has a shared secret
  // 1) generating an access id of the note
  // 2) then emitting the event that the note has been approved
  function _approveNoteAccess(
    bytes32 _note,
    address _userAddress,
    string memory _sharedSecret
  ) internal {
    uint accessId = _generateAccessId(_note, _userAddress);
    emit NoteAccessApproved(
      accessId,
      _note,
      _userAddress,
      _sharedSecret
    );
  }

  // creating loan using provided loan variables and saving it to Loans Array
  // @param _notional : loan notional rate from the borrower
  // @param _loanVariables : some settings with variables
  // @param _proofData : minting proof to mint new loan notes and stores itself to the note registry
  function _createLoan(
    bytes32 _notional,
    uint256[] memory _loanVariables,
    bytes memory _proofData
  ) private returns (address) {
    address loanCurrency = _getCurrencyContract(_loanVariables[3]);

    // creating a new loan instance
    Loan newLoan = new Loan(
      _notional,
      _loanVariables,
      msg.sender,
      aceAddress,
      loanCurrency
    );

    // address of new loan instance stored to the loans array
    loans.push(address(newLoan));
    Loan loanContract = Loan(address(newLoan));

    loanContract.setProofs(1, uint256(-1));

    // with mint proof, mint notes and stores in to the note registry while increasing total notes supply
    loanContract.confidentialMint(MINT_PROOF, bytes(_proofData));

    return address(newLoan);
  }

  // register new supported token as settlement for ZkAsset
  // only dApp owner can add a new settlement currency with corresponding contract address
  function addSettlementCurrency(uint _id, address _address) external onlyOwner {
    settlementCurrencies[_id] = _address;
    emit SettlementCurrencyAdded(_id, _address);
  }

  // borrower create a new loan with wrapper function
  function createLoan(
    bytes32 _notional,
    string calldata _viewingKey,
    string calldata _borrowerPublicKey,
    uint256[] calldata _loanVariables,
    // [0] interestRate
    // [1] interestPeriod
    // [2] loanDuration
    // [3] settlementCurrencyId
    bytes calldata _proofData
  ) external {
    address loanId = _createLoan(
      _notional,
      _loanVariables,
      _proofData
    );

    emit LoanCreated(
      loanId,
      msg.sender,
      _notional,
      _borrowerPublicKey,
      _loanVariables,
      block.timestamp
    );

    // borrower may be approved with note view permission
    _approveNoteAccess(
      _notional,
      msg.sender,
      _viewingKey
    );
  }

  // approving the spending of loan notional note and signals that the loan is ready to be settled with
  function approveLoanNotional(
    bytes32 _noteHash,
    bytes memory _signature,
    address _loanId
  ) public {
    Loan loanContract = Loan(_loanId);
    // allowing loan instance to spend note
    loanContract.confidentialApprove(_noteHash, _loanId, true, _signature);
    emit LoanApprovedForSettlement(_loanId);
  }

  // submiting a request to view the borrower's requested loan
  function submitViewRequest(address _loanId, string calldata _lenderPublicKey) external {
    emit ViewRequestCreated(
      _loanId,
      msg.sender,
      _lenderPublicKey
    );
  }

  // approving a lender's request to view the notional loan who has a shared secret with the borrower
  function approveViewRequest(
    address _loanId,
    address _lender,
    bytes32 _notionalNote,
    string calldata _sharedSecret
  ) external onlyBorrower(_loanId) {
    uint accessId = _generateAccessId(_notionalNote, _lender);

    emit ViewRequestApproved(
      accessId,
      _loanId,
      _lender,
      _sharedSecret
    );
  }

  event SettlementSuccesfull(
    address indexed from,
    address indexed to,
    address loanId,
    uint256 timestamp
  );

  struct LoanPayment {
    address from;
    address to;
    bytes notional;
  }

  mapping(uint => mapping(uint => LoanPayment)) public loanPayments;

  // settling the loan between borrower and lender
  function settleInitialBalance(
    address _loanId,
    bytes calldata _proofData,
    bytes32 _currentInterestBalance
  ) external {
    Loan loanContract = Loan(_loanId);
    loanContract.settleLoan(_proofData, _currentInterestBalance, msg.sender);
    emit SettlementSuccesfull(
      msg.sender,
      loanContract.borrower(),
      _loanId,
      block.timestamp
    );
  }

  // giving a note access permission to caller who owns the viewing key and a specified user who owns a shared key
  function approveNoteAccess(
    bytes32 _note,
    string calldata _viewingKey,
    string calldata _sharedSecret,
    address _sharedWith
  ) external {
    if (bytes(_viewingKey).length != 0) {
      _approveNoteAccess(
        _note,
        msg.sender,
        _viewingKey
      );
    }

    if (bytes(_sharedSecret).length != 0) {
      _approveNoteAccess(
        _note,
        _sharedWith,
        _sharedSecret
      );
    }
  }
}

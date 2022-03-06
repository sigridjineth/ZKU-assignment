// SPDX-License-Identifier: GPL-3.0

pragma solidity ^0.8.0;

import "@openzeppelin/contracts/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts/utils/cryptography/MerkleProof.sol";
import "@openzeppelin/contracts/utils/Counters.sol";
import "@openzeppelin/contracts/access/Ownable.sol";

contract SigridNFT is ERC721URIStorage, Ownable {
    mapping(address => mapping(string => uint256)) public claimed;
    mapping(address => bool) private admins;
    mapping(string => Cohort) public cohorts;

    using Counters for Counters.Counter;
    Counters.Counter private _tokenIdTracker;

    string contractBaseURI;
    bool allowsTransfers = false;

    /**
        @dev cohort: The contract is being able to mint NFTs in group with the given whitelisted addresses
     */
    struct Cohort {
        uint128 limit;
        uint128 tokenMinted;
        bytes32 merkleRoot;
        bytes32[] whitelistedAddresses;
    }

    /**
        @dev when claiming NFTs, the event is emitted
        that has receiver address, cohortId, and its index, and whether it is admin or not.
     */
    event Claim(
        address indexed _receiver,
        string indexed _cohortId,
        uint128 _cohortIndex,
        uint256 _contractIndex,
        bool _isAdmin
    );

    constructor(string memory _contractBaseURI)
        ERC721("Sigrid Jin NFT", "SIGJNFT")
    {
        admins[msg.sender] = true;
        contractBaseURI = _contractBaseURI;
    }

    modifier onlyAdmin() {
        require(admins[msg.sender] == true);
        _;
    }

    modifier limitCheck(string memory _cohortId, address to) {
        require(
            cohorts[_cohortId].tokenMinted < cohorts[_cohortId].limit,
            "Max tokens issued for cohort. sad."
        );
        require(
            claimed[to][_cohortId] == 0,
            "Address has already claimed token yeah."
        );
        _;
    }

    modifier merkleCheck(
        string memory _cohortId,
        bytes32[] memory _proof,
        address to
    ) {
        bytes32 leaf = keccak256(abi.encodePacked(to));
        require(
            MerkleProof.verify(_proof, cohorts[_cohortId].merkleRoot, leaf),
            "address not eligible for claim"
        );
        _;
    }

    function _baseURI() internal view virtual override returns (string memory) {
        return contractBaseURI;
    }

    /**
        @dev the tokenMinted id in struct cohort is automatically initialized to 0.
        After getting the index (starting from 0), the function increments the value by 1.
        The function uses abi.encodePacked to create uri with the tokenIndex that has been mentioned above.
        The tokenId is given by the library called "Counters", which increments the id by 1.
        Thanks to the power of openZeppelin, we can safely mint by using `_safeMint` that has been on openZeppelin implementation.
        After issuing the token, the function emits the 'Claim' event.
     */
    function issueToken(
        string memory _cohortId,
        address to,
        bool _isAdmin
    ) internal limitCheck(_cohortId, to) returns (uint256) {
        uint128 nextCohortTokenIndex = cohorts[_cohortId].tokenMinted;
        string memory _uri = string(
            abi.encodePacked(
                _cohortId,
                "-",
                uint2str(nextCohortTokenIndex),
                "/metadata.json"
            )
        );

        uint256 newTokenId = _tokenIdTracker.current();
        claimed[to][_cohortId] = newTokenId;

        _safeMint(to, newTokenId);
        emit Claim(to, _cohortId, nextCohortTokenIndex, newTokenId, _isAdmin);

        _setTokenURI(newTokenId, _uri);

        cohorts[_cohortId].tokenMinted = nextCohortTokenIndex + 1;
        _tokenIdTracker.increment();

        return newTokenId;
    }

    function uint2str(uint128 _i) internal pure returns (string memory str) {
        if (_i == 0) return "0";

        uint128 j = _i;
        uint128 length;
        while (j != 0) {
            length++;
            j /= 10;
        }

        bytes memory bstr = new bytes(length);
        uint128 k = length;
        j = _i;
        while (j != 0) {
            bstr[--k] = bytes1(uint8(48 + (j % 10)));
            j /= 10;
        }
        str = string(bstr);
        return str;
    }

    /**
        @dev this function allows the admin to airdrop the whitelisted address user.
     */

    function adminClaimToken(
        string memory _cohortId,
        bytes32[] memory _proof,
        address to
    ) external onlyAdmin merkleCheck(_cohortId, _proof, to) returns (uint256) {
        return issueToken(_cohortId, to, true);
    }

    function claimToken(string memory _cohortId, bytes32[] memory _proof)
        external
        merkleCheck(_cohortId, _proof, msg.sender)
        returns (uint256)
    {
        bytes32 leaf = keccak256(abi.encodePacked(msg.sender));
        require(
            MerkleProof.verify(_proof, cohorts[_cohortId].merkleRoot, leaf),
            "address not eligible for claim"
        );

        return issueToken(_cohortId, msg.sender, false);
    }

    function setAllowsTransfers(bool _allowsTransfers) external onlyAdmin {
        allowsTransfers = _allowsTransfers;
    }

    function createCohort(
        string memory _cohortId,
        uint128 _limit,
        bytes32 _merkleRoot,
        bytes32[] memory _whitelistedAddresses
    ) external onlyAdmin {
        require(
            cohorts[_cohortId].limit == 0,
            " Cohort already exists"
        );
        require(_limit > 0, "Limit must be greater than 0");
        Cohort memory cohort = Cohort(_limit, 0, _merkleRoot, _whitelistedAddresses);
        cohorts[_cohortId] = cohort;
    }

    function setMerkleRoot(string memory _cohortId, bytes32 _merkleRoot)
        external
        onlyAdmin
    {
        require(
            cohorts[_cohortId].limit > 0,
            "No cohort limit set"
        );
        cohorts[_cohortId].merkleRoot = _merkleRoot;
    }

    function setWhiteList(string memory _cohortId, bytes32[] memory _whitelistedAddresses, uint128 _limit) external onlyAdmin {
        require(
            cohorts[_cohortId].limit > 0,
            "No cohort limit set"
        );
        cohorts[_cohortId].whitelistedAddresses = _whitelistedAddresses;
        cohorts[_cohortId].limit = _limit;
    }

    function _getCohortDetails(string memory _cohortId) external view returns (bytes32[] memory, bytes32) {
        return(
            cohorts[_cohortId].whitelistedAddresses,
            cohorts[_cohortId].merkleRoot
        );
    }

    function updateAdmin(address _admin, bool isAdmin) external onlyOwner {
        admins[_admin] = isAdmin;
    }

    function _beforeTokenTransfer(
        address from,
        address to,
        uint256 tokenId
    ) internal virtual override {
        require(
            from == address(0) || to == address(0) || allowsTransfers,
            "Not allowed to transfer"
        );
        return super._beforeTokenTransfer(from, to, tokenId);
    }
}

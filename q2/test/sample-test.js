const { expect } = require("chai");
const { ethers } = require("hardhat");
const { keccak256 } = require("ethers/lib/utils");
const { MerkleTree } = require("merkletreejs");

async function test() {
  const address = "0x39D95dB2824c069018865824ee6FC0D7639d9359";

  const buf2hex = (x) => `0x${x.toString("hex")}`

  const SigridNFT =  await ethers.getContractFactory("SigridNFT");
  const sigridnft = await SigridNFT.deploy("www.thisissigrid.com");
  await sigridnft.deployed();
  // console.log('sigridnft', sigridnft);

  // check sigridnft balance is zero
  let balance = await sigridnft.balanceOf(address);
  expect(balance).to.equal(0);

  // create cohort details
  const leaves = [
    "0x39D95dB2824c069018865824ee6FC0D7639d9359",
    "0x01725BE700413D34bCC5e961de1d0C777d3A52F4",
  ].map((v) => keccak256(v));

  const tree = new MerkleTree(leaves, keccak256, { sort: true });
  const root = tree.getHexRoot();
  const limitNumber = 2;
  const cohortId = 1;

  console.log("before tx.")

  const tx = await sigridnft
    .createCohort(cohortId, limitNumber, root, leaves)
    .catch((err) => {
      console.log(err)
      throw err;
    });
  await tx.wait();
  console.log("tx1", tx);

  const response = { merkleRoot: root };
  // console.log(response);

  // check cohort details
  const data = await sigridnft._getCohortDetails(0);

  const leaves2 = data[0];
  const root2 = data[1];
  const ipfsHash = data[2];

  if (
    leaves.length < 1 ||
    root2 ===
      "0x0000000000000000000000000000000000000000000000000000000000000000"
  ) {
    console.log("something goes wrong");
  }

  const tree2 = new MerkleTree(leaves2, keccak256, { sort: true });
  const internalRoot = tree.getHexRoot();

  if (internalRoot !== root2) {
    return null;
  }

  const proof = tree2.getProof(keccak256(address)).map((x) => buf2hex(x.data));

  const tx2 = await sigridnft
    .adminClaimToken(cohortId, proof, address)
    .catch((err) => {
      console.log(err);
      return null;
    });

  await tx2.wait();
  console.log("tx2", tx2)

  balance = await sigridnft.balanceOf(address);
  expect(balance).to.equal(1);
}

test();

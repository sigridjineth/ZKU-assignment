# ZK University's first assignment
## Question 1
### Q1.
#### Q1.1
* check out the following file
```
./q1/merkle_root.circom
```
#### Q1.2
After trying to generate a trusted setup for Phase 2, I have encountered the following error.
It seems that the value that we have is far bigger than the constraints that we set using powers of tau, which is ```2**14 = 16,384```
![size_12](https://user-images.githubusercontent.com/41055141/156890383-852ff8a2-32bf-44ad-86bf-97a85897d3a9.png)

I fixed the error by increasing the size of a powers of tau to 14 which is bigger than the previous one.
![size_14](https://user-images.githubusercontent.com/41055141/156890449-c280c97a-c7ff-4797-8bf0-a4072757d192.png)

#### Q1.3
I think that using zero-knowledge proof here would require a lot of gas to compute, which means that creating the total looking of merkle tree would be inefficient especially for congested networks including Ethereum. [The smart contract that is in solidity pages](https://solidity-by-example.org/app/merkle-tree/) have a function to verify a given block in merkle tree by accepting tree nodes as a parameter. Meanwhile, there are plethora of projects that try to implement zk-Rollups in Layer 2 sidechains including Loopring that transactions are uploaded to Layer 2 sidechains together, and the verification data is uploaded to Layer 1 blockchain.

#### Q1.4
* checkout the following file
```
./q1/execute.sh
```

### Q2
* I have rendered the contract on the following file
```
./q2/contracts/SigridNFT.sol
```
* Here is the screenshots for deploying contracts and its gas fees.
![contract1](https://user-images.githubusercontent.com/41055141/156906856-62faed88-5784-4171-b4e8-93bbc9ef8923.png)
![contract2](https://user-images.githubusercontent.com/41055141/156906171-b06ad45c-35a2-4a88-871d-aff216bfaebe.png)

### Q3
1. Summarizes the key difference between SNARKs and STARKs.
* To begin with, the prover time and verification time does not have much difference between two methods. However, the given two methods are different in following ways. First of all, The algorithmic complexity of prover and verifier processing is different. Secondly, the size of proof varies. Thirdly, the SNARKs have a verfication key and a trusted setup that is derived from the trusted setup ceremony. Meanwhile, the STARKs does not need to have an additional trusted setup processes. We have explored the power of tau ceremony from zCash programs on Question 1. This means that the STARKs take additional edges on saving times and costs since it does not need to decipher .zkey files to verify and generate proofs.

2. How is the trusted setup process different between Groth16 and PLONK?
* Basically Speaking, Groth16 requires each trusted ceremonies for circuits. Meanwhile, PLONK does not require each ceremonies but only universal, the powers of tau ceremony is enough. This means that there is only one single trusted setup for the whole businesses unless they up to the given maximum size when setting single trusted setup. In addition, by making only universal setup, multiple parties are easy to participate in the trusted setup, which makes the trusted setup more secure than Groth16. [Reference](https://vitalik.ca/general/2019/09/22/plonk.html)

3. Give an idea of how we can apply ZK to create unique usage for NFTs.
* ZKPs are the missing piece of the jigsaw that will allow businesses to mint and exchange NFTs on public blockchains like Ethereum while maintaining their anonymity. For example, forcing Alice to reveal her customer's identify in public is a violation of her privacy. Anyone can see how much her clients are paying her because of it. The ZKPs would be important if Alice wanted to negotiate a private agreement to acquire NFTs. This is handled by a group known as [centrifuge](https://medium.com/centrifuge/bringing-privacy-to-non-fungible-tokens-a-recap-from-the-zokrates-workshop-at-zcon1-6d9ea8a74b7f).

4. Give an idea for DAO tooling with ZKP.
* Participants can decide to invest their pools to which projects privately, by hiding the details of a deal. This means that decentralized private investment could be done with ZKP.
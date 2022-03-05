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
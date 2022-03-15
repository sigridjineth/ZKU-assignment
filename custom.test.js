const hre = require('hardhat')
const { ethers, waffle } = hre
const { loadFixture } = waffle
const { expect } = require('chai')

const { utils } = ethers

const { toFixedHex } = require('../src/utils')

const Utxo = require('../src/utxo')
const { transaction, prepareTransaction } = require('../src/index')
const { Keypair } = require('../src/keypair')
const { encodeDataForBridge } = require('./utils')

const MERKLE_TREE_HEIGHT = 5
const l1ChainId = 1
const MINIMUM_WITHDRAWAL_AMOUNT = utils.parseEther(process.env.MINIMUM_WITHDRAWAL_AMOUNT || '0.05')
const MAXIMUM_DEPOSIT_AMOUNT = utils.parseEther(process.env.MAXIMUM_DEPOSIT_AMOUNT || '1')

describe('Custom Test ZKU', function() {
    this.timeout(20000);

    async function deploy(contractName, ...args) {
        const Factory = await ethers.getContractFactory(contractName)
        const instance = await Factory.deploy(...args)
        return instance.deployed()
    }

    async function fixture() {
        require('../scripts/compileHasher')
        
        // Merkle Tree Initialize
        const hasher = await deploy('Hasher')

        const merkleTreeWithHistory = await deploy(
            'MerkleTreeWithHistoryMock',
            MERKLE_TREE_HEIGHT,
            hasher.address,
        )

        await merkleTreeWithHistory.initialize()

        return { hasher, merkleTreeWithHistory }
    }

    // l1-l2 bridge mechanism
    async function fixtureTornadoNova() {
        require('../scripts/compileHasher')
        const [sender, gov, l1Unwrapper, multisig] = await ethers.getSigners()
        const verifier2 = await deploy('Verifier2')
        const verifier16 = await deploy('Verifier16')
        const hasher = await deploy('Hasher')

        const token = await deploy('PermittableToken', 'Wrapped ETH', 'WETH', 18, l1ChainId)
        await token.mint(sender.address, utils.parseEther('10000'))

        const amb = await deploy('MockAMB', gov.address, l1ChainId)
        const omniBridge = await deploy('MockOmniBridge', amb.address)

        /** @type {TornadoPool} */
        const tornadoPoolImpl = await deploy(
            'TornadoPool',
            verifier2.address,
            verifier16.address,
            MERKLE_TREE_HEIGHT,
            hasher.address,
            token.address,
            omniBridge.address,
            l1Unwrapper.address,
            gov.address,
            l1ChainId,
            multisig.address,
        )

        const { data } = await tornadoPoolImpl.populateTransaction.initialize(
            MINIMUM_WITHDRAWAL_AMOUNT,
            MAXIMUM_DEPOSIT_AMOUNT,
        )

        const proxy = await deploy(
            'CrossChainUpgradeableProxy',
            tornadoPoolImpl.address,
            gov.address,
            data,
            amb.address,
            l1ChainId,
        )
      
        const tornadoPool = tornadoPoolImpl.attach(proxy.address)
      
        await token.approve(tornadoPool.address, utils.parseEther('10000'))
      
        return { tornadoPool, token, proxy, omniBridge, amb, gov, multisig }
    }

    describe('zku Q3.2.2', () => {
        it('should estimate and print gas, deposit and withdraw ETH, given balances are correct', async() => {
            const { tornadoPool, token, omniBridge, merkleTreeWithHistory } = await loadFixture(fixture)

            // estimate gas of adding leaves to the merkle tree
            const gas = await merkleTreeWithHistory.estimateGas.insert(toFixedHex(1), toFixedHex(2));
            console.log("gas estimate", gas - 21000)

            // bridge tokens from L1 to L2
            const aliceKeypair = new Keypair() // contains private and public keys

            // Alice deposits into tornado pool
            const aliceDepositAmount = utils.parseEther('0.08')
            const aliceDepositUtxo = new Utxo({ amount: aliceDepositAmount, keypair: aliceKeypair })
            const { args, extData } = await prepareTransaction({
                tornadoPool,
                outputs: [aliceDepositUtxo],
            })

            const onTokenBridgedData = encodeDataForBridge({
                proof: args,
                extData,
              })
          
            const onTokenBridgedTx = await tornadoPool.populateTransaction.onTokenBridged(
                token.address,
                aliceDepositUtxo.amount,
                onTokenBridgedData,
            )

            // emulating bridge. first it sends tokens to omnibridge mock then it sends to the pool
            await token.transfer(omniBridge.address, aliceDepositAmount)
            const transferTx = await token.populateTransaction.transfer(tornadoPool.address, aliceDepositAmount)
  
            await omniBridge.execute([
                { who: token.address, callData: transferTx.data }, // send tokens to pool
                { who: tornadoPool.address, callData: onTokenBridgedTx.data }, // call onTokenBridgedTx
            ])

            // withdraws a part of his funds from the shielded pool, L2 to '0x1111111111111111111111111111111111111111'
            const aliceWithdrawAmount = utils.parseEther('0.05')
            const recipient = '0x1111111111111111111111111111111111111111'
            const aliceChangeUtxo = new Utxo({
                amount: aliceDepositAmount.sub(aliceWithdrawAmount),
                keypair: aliceKeypair,
            })
            await transaction({
                tornadoPool,
                inputs: [aliceDepositUtxo],
                outputs: [aliceChangeUtxo],
                recipient: recipient,
                isL1Withdrawal: true,
            })

            const recipientBalance = await token.balanceOf(recipient)
            expect(recipientBalance).to.be.equal(aliceWithdrawAmount)
            console.log("Recipient Balance is the following: ", recipientBalance)
      
            const omniBridgeBalance = await token.balanceOf(omniBridge.address)
            expect(omniBridgeBalance).to.be.equal(0)
            console.log("omniBridge Balance is the following: ", omniBridgeBalance)
      
            const tornadoPoolBalance = await token.balanceOf(tornadoPool.address)
            const expectedTokens = utils.parseEther('0.03')
            expect(tornadoPoolBalance).to.be.equal(expectedTokens)
            console.log("tornadoPool Balance is the following: ", tornadoPoolBalance)
        })
    })
})
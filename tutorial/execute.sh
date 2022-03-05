rm circuit.r1cs
rm circuit.sym
rm circuit_*
rm -r circuit_*
rm pot*
rm proof.json
rm public.json
rm verifier.sol
rm verification_key.json
rm vitness.wtns
rm parameters.key

circom circuit.circom --r1cs --wasm --sym --c

echo "Using nodejs"
cd circuit_js
node generate_witness.js circuit.wasm ../input.json witness.wtns

cp witness.wtns ../witness.wtns
cd ..

snarkjs powersoftau new bn128 12 pot12_0000.ptau -v
snarkjs powersoftau contribute pot12_0000.ptau pot12_0001.ptau --name="First contribution" -v -e="random text"

snarkjs powersoftau prepare phase2 pot12_0001.ptau pot12_final.ptau -v
snarkjs groth16 setup circuit.r1cs pot12_final.ptau circuit_0000.zkey
snarkjs zkey contribute circuit_0000.zkey circuit_0001.zkey --name="1st Contributor Name" -v -e="random text"
snarkjs zkey export verificationkey circuit_0001.zkey verification_key.json

snarkjs groth16 prove circuit_0001.zkey witness.wtns proof.json public.json

snarkjs groth16 verify verification_key.json public.json proof.json
# snarkjs zkey export solidityverifier multiplier2_0001.zkey verifier.sol
# snarkjs generatecall
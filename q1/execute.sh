#!/bin/bash

rm merkle.r1cs
rm merkle.sym
rm merkle_*
rm -r merkle_*
rm pot*
rm proof.json
rm public.json
rm verification_key.json
rm witness.wtns

# Compile the merkle circuit
# Not using c for my device
circom merkle.circom --r1cs --wasm --sym

# Compute the witness using WebAssembly
cd merkle_js
node generate_witness.js

cd ..
node merkle_root_js/generate_witness.js merkle_js/merkle.wasm input.json ../witness.wtns



# Start a new Powers of Tau ceremony
snarkjs powersoftau new bn128 14 pot12_0000.ptau -v

# Contribute to the ceremony
snarkjs powersoftau contribute pot12_0000.ptau pot12_0001.ptau --name="First contribution" -v -e="randomText"

# Phase 2
# Start the generation of phase 2
snarkjs powersoftau prepare phase2 pot12_0001.ptau pot12_final.ptau -v

# Generate a .zkey file that will contain the proving and verification keys together with all phase 2 contributions
snarkjs groth16 setup merkle_root.r1cs pot12_final.ptau merkle_root_0000.zkey

# Contribute to the phase 2 ceremony
snarkjs zkey contribute merkle_root_0000.zkey merkle_root_0001.zkey --name="1st Contributor Name" -v -e="randomText"

# Export the verification key
snarkjs zkey export verificationkey merkle_root_0001.zkey verification_key.json


# Generate proof
snarkjs groth16 prove merkle_0001.zkey witness.wtns proof.json public.json

# Verify proof
snarkjs groth16 verify verification_key.json public.json proof.json
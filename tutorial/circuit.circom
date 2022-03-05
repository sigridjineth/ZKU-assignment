// It is being used to specify the compiler verison.
pragma circom 2.0.0;

// use `template` keyword to define the shape of new circuit.
template Multiplier2() {
    // input signals which is private to verifier
    signal input x;
    signal input y;

    // output signal which is public to verifier
    signal output prod;

    // constriants. set the value of prod as the result of multiplying two values.
    prod <== x * y;
    // prod <-- x * y;
    // prod === x * y;
}

component main = Multiplier2();

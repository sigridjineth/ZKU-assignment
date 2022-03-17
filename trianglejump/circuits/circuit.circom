pragma circom 2.0.3;

include "../node_modules/circomlib/circuits/mimcsponge.circom";
include "../node_modules/circomlib/circuits/comparators.circom";

template Circuit() {
    signal input x1;
    signal input y1;
    signal input x2;
    signal input y2;
    signal input x3;
    signal input y3;

    signal input energy;

    signal output coordinate1;
    signal output coordinate2;
    signal output coordinate3;

    // if the tree points are not in the straight line, the condition works.
    // it goes when (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1) is the conditions.
    signal firstCase;
    firstCase <== (y2 - y1) * (x3 - x2);

    signal secondCase;
    secondCase <== (y3 - y2) * (x2 - x1);

    component isNotTriangle = IsEqual();
    
    isNotTriangle.in[0] <== firstCase;
    isNotTriangle.in[1] <== secondCase;
    assert(isNotTriangle.out == 0);

    /*
        check (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) is less than (energy)^2
    */

    // (x1 - x2) * (x1 - x2)
    signal firstXSquare;
    firstXSquare <== (x1 - x2) * (x1 - x2);

    // (y1 - y2) * (y1 - y2)
    signal firstYSquare;
    firstYSquare <== (y1 - y2) * (y1 - y2);

    component firstDistCompare = LessThan(64);
    
    firstDistCompare.in[0] <== firstXSquare + firstYSquare;
    firstDistCompare.in[1] <== energy * energy;
    assert(firstDistCompare.out == 1);

    /*
        check (x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2) is less than (energy)^2
    */

    // (x3 - x2) * (x3 - x2)
    signal secondXSquare;
    secondXSquare <== (x3 - x2) * (x3 - x2);

    // (y3 - y2) * (y3 - y2)
    signal secondYSquare;
    secondYSquare <== (y3 - y2) * (y3 - y2);

    component SecondDistCompare = LessThan(64);
    
    SecondDistCompare.in[0] <== secondXSquare + secondYSquare;
    SecondDistCompare.in[1] <== energy * energy;
    assert(SecondDistCompare.out == 1);

    /*
        Using MiMCSponge(x1, y1) = coordinate1 and coordinate2 is the following.
    */
    component firstMimcCoordinate = MiMCSponge(2, 220, 1);
    component secondMimcCoordinate = MiMCSponge(2, 220, 1);
    component thirdMimcCoordinate = MiMCSponge(2, 220, 1);

    firstMimcCoordinate.ins[0] <== x1;
    firstMimcCoordinate.ins[1] <== y1;
    firstMimcCoordinate.k <== 0;

    secondMimcCoordinate.ins[0] <== x2;
    secondMimcCoordinate.ins[1] <== y2;
    secondMimcCoordinate.k <== 0;

    thirdMimcCoordinate.ins[0] <== x3;
    thirdMimcCoordinate.ins[1] <== y3;
    thirdMimcCoordinate.k <== 0;

    coordinate1 <== firstMimcCoordinate.outs[0];
    coordinate2 <== secondMimcCoordinate.outs[0];
    coordinate3 <== thirdMimcCoordinate.outs[0];
}

component main = Circuit();
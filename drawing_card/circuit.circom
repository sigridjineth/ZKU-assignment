pragma circom 2.0.0;

include "./node_modules/circomlib/circuits/mimcsponge.circom";
include "./node_modules/circomlib/circuits/comparators.circom";

/*
    check whether the given number is within the range
*/

template checkInRange() {
    signal input number;
    signal input beginningOfRange;
    signal input endingOfRange;

    signal output out;

    // starting lower bound
    // e.g. 14 is greater than 13.
    // the output is 1 if true else 0
    component lowThreshold = GreaterEqThan(64);
    lowThreshold.in[0] <== number;
    lowThreshold.in[1] <== beginningOfRange;

    // ending upper bound
    // e.g. 14 is less than 25. Thus, it is a club.
    // the output is 1 if true else 0
    component highThreshold = LessThan(64);
    highThreshold.in[0] <== number;
    highThreshold.in[1] <== endingOfRange;

    // two outputs should be 1 both if it is in range
    // otherwise it is 0
    out <== lowThreshold.out * highThreshold.out;
}

template whichSuitsItBelongsTo() {
    signal input number;
    
    signal output suite[4];

    component spades = checkInRange();
    spades.number <== number;
    spades.beginningOfRange <== 0;
    spades.endingOfRange <== 13;
    suite[0] <== spades.out;

    component clubs = checkInRange();
    clubs.number <== number;
    clubs.beginningOfRange <== 13;
    clubs.endingOfRange <== 26;
    suite[1] <== clubs.out;

    component diamonds = checkInRange();
    diamonds.number <== number;
    diamonds.beginningOfRange <== 26;
    diamonds.endingOfRange <== 39;
    suite[2] <== diamonds.out;

    component hearts = checkInRange();
    hearts.number <== number;
    hearts.beginningOfRange <== 39;
    hearts.endingOfRange <== 52;
    suite[3] <== hearts.out;
}

template checkWhetherGivenTwoNumbersAreSameSuit() {
    signal input firstCard;
    signal input secondCard;
    signal input seed;

    signal output hashedCard;

    assert(firstCard >= 0);
    assert(firstCard < 52);
    assert(secondCard >= 0);
    assert(secondCard < 52);

    component firstCardSuitCandidates = whichSuitsItBelongsTo();
    firstCardSuitCandidates.number <== firstCard;

    component secondCardSuiteCandidates = whichSuitsItBelongsTo();
    secondCardSuiteCandidates.number <== secondCard;

    for (var i = 0; i < 4; i++) {
        firstCardSuitCandidates.suite[i] === secondCardSuiteCandidates.suite[i];
    }

    // Hashing the card value with a secret seed so that it could be ensured that the card's value is not revealed at all.
    component mimc = MiMCSponge(2, 220, 1);
    mimc.ins[0] <== firstCard;
    mimc.ins[1] <== seed;
    mimc.k <== 1;

    hashedCard <== mimc.outs[0];
}

component main = checkWhetherGivenTwoNumbersAreSameSuit();
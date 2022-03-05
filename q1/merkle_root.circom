pragma circom 2.0.0;

include "../node_modules/circomlib/circuits/mimcsponge.circom";

template merkleRoot(n) {
    signal input leaves[n];
    signal output merkleRoot;
    var k = 0;
    var totalNodeCounts = n * 2 - 1;

    component treeNodes[totalNodeCounts];
    var hashes[totalNodeCounts];

    for (var i = 0; i < n; i++) {
        treeNodes[i] = MiMCSponge(1, 220, 1);
        treeNodes[i].ins[0] <== leaves[i];
        treeNodes[i].k <== k;
        hashes[i] = treeNodes[i].outs[0];
    }

    for (var i = 2; i < totalNodeCounts; i += 2) {
        var parentNode = i / 2 + n - 1;
        treeNodes[parentNode] = MiMCSponge(2, 220, 1);
        treeNodes[parentNode].ins[0] <== hashes[i - 2];
        treeNodes[parentNode].ins[1] <== hashes[i - 1];
        treeNodes[parentNode].k <== k;
        hashes[parentNode] = treeNodes[i].outs[0];
    }

    merkleRoot <== treeNodes[totalNodeCounts - 1].outs[0];
}

component main {
    public [leaves]
} = merkleRoot(8);
#include <stdio.h>
#include "linkedlist.h"
#include "blockchain.h"

int main() {
    Block* blockchain = NULL;
    initializeBlockchain(&blockchain);

    printf("===== Blockchain After Initialization =====\n");
    displayBlockchain(blockchain);

    Block* block1 = createBlock(1, "Block 1 Data", blockchain->hash);
    insertBlock(&blockchain, block1);

    printf("\n===== Blockchain After Inserting Block 1 =====\n");
    displayBlockchain(blockchain);

    Block* block2 = createBlock(2, "Block 2 Data", block1->hash);
    insertBlock(&blockchain, block2);

    printf("\n===== Blockchain After Inserting Block 2 =====\n");
    displayBlockchain(blockchain);

    printf("\n===== Validating Blockchain =====\n");
    validateChain(blockchain);
    return 0;
}
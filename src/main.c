#include <stdio.h>
#include "linkedlist.c"
#include "blockchain.c"
#include "ledger.c"

int main() {
    // Initialize the blockchain
    Block* blockchain = NULL;
    initializeBlockchain(&blockchain);

    // Display the blockchain after initialization
    printf("===== Blockchain After Initialization =====\n");
    displayBlockchain(blockchain);

    // Create and insert a new block
    Block* block1 = createBlock(1, "Block 1 Data", blockchain->hash);
    insertBlock(&blockchain, block1);

    // Display the blockchain after inserting the first block
    printf("\n===== Blockchain After Inserting Block 1 =====\n");
    displayBlockchain(blockchain);

    // Create and insert another block
    Block* block2 = createBlock(2, "Block 2 Data", block1->hash);
    insertBlock(&blockchain, block2);

    // Display the blockchain after inserting the second block
    printf("\n===== Blockchain After Inserting Block 2 =====\n");
    displayBlockchain(blockchain);

    // Validate the blockchain
    printf("\n===== Validating Blockchain =====\n");
    if (validateChain(blockchain)) {
        printf("Blockchain is valid!\n");
    } else {
        printf("Blockchain is invalid!\n");
    }

    // Load the blockchain from the binary ledger file
    printf("\n===== Loading Blockchain from Ledger =====\n");
    Block* loadedBlockchain = loadBlockchainFromFile("blockchain_ledger.bin");
    if (loadedBlockchain) {
        printf("Blockchain loaded successfully!\n");
        displayBlockchain(loadedBlockchain);
    } else {
        printf("Failed to load blockchain from file.\n");
    }

    // Free the memory used by the blockchain
    freeBlockchain(blockchain);
    freeBlockchain(loadedBlockchain);

    return 0;
}
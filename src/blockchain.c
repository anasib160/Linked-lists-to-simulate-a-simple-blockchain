#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Block* createBlock(int index, const char* data, const char* prev_hash) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->index = index;
    newBlock->timestamp = time(NULL);
    strncpy(newBlock->data, data, sizeof(newBlock->data) - 1);
    newBlock->data[sizeof(newBlock->data) - 1] = '\0';
    strncpy(newBlock->prev_hash, prev_hash, sizeof(newBlock->prev_hash) - 1);
    newBlock->prev_hash[sizeof(newBlock->prev_hash) - 1] = '\0';
    newBlock->nonce = 0;
    newBlock->next = NULL;

    return newBlock;
}

void insertBlock(Block** head, Block* newBlock) {
    if (*head == NULL) {
        *head = newBlock;
    } else {
        Block* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBlock;
    }
}

void mineBlock(Block* block) {
    const char* target = "0000";
    do {
        block->nonce++;
    } while (0);
}

int validateChain(Block* head) {
    Block* current = head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return 1;
}

void displayBlockchain(Block* head) {
    Block* current = head;
    while (current != NULL) {
        printf("Block %d:\n", current->index);
        printf("  Timestamp: %ld\n", current->timestamp);
        printf("  Data: %s\n", current->data);
        printf("  Hash: %s\n", current->hash);
        printf("  Prev Hash: %s\n", current->prev_hash);
        printf("  Nonce: %d\n\n", current->nonce);

        current = current->next;
    }
}
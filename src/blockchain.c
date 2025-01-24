#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <openssl/sha.h> //  SHA-256 howa wahd algoritm li ki7ssb hashing (bwhd formule dmath mhm bla manmrdo rasna hahya library wajda)


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

void calculHash(Block * block){
    char melang[1024]; 
    snprintf(melang, sizeof(melang), "%s%d%s", block->data,    //kan 8alto data o nonce o prev_hash kmlin f melang
                                              block->nonce,
                                             block->prev_hash);

    unsigned char hash[SHA256_DIGEST_LENGTH];    // unsigned : binary data
    SHA256_CTX sha256; //context li aykn fih hash kan declariwh

    SHA256_Init(&sha256); // kan initializiwh

    SHA256_Update(&sha256, melang, strlen(melang)); // kan7to fih dik melang li drna

    SHA256_Final(hash, &sha256); // whahowa wajd o kan7toh f hash


    //db dik hash rah binary donc 8ssa n7wloh decimal haka :
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {  
        sprintf(&block->hash[i * 2], "%02x", hash[i]); 
    }
    block->hash[SHA256_DIGEST_LENGTH * 2] = '\0';
}


void mineBlock(Block* block) {
    int difficulty = 4; 
    char target[difficulty + 1];
    memset(target, '0', difficulty); 

    block->nonce = 0; 
    do {
        calculHash(block); 
        block->nonce++;    
    } while (strncmp(block->hash, target, difficulty) != 0); 
}


int validateChain(Block* block) {
    Block* current = block;
    while (current->next != NULL ) {
        current = current->next;
    }
    mineBlock(block);
    insertBlock(block,current);
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

// Exemple:

int main() {
    Block block;
    block.nonce = 1234;
    strcpy(block.data, "Sample Block Dat");
    strcpy(block.prev_hash, "0000000000000000000000000000000000000000000000000000000000000000");

    calculHash(&block);
    printf("Block Hash: %s\n", block.hash);

    return 0;
}
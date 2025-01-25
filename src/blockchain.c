#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/sha.h> //  SHA-256 howa wahd algoritm li ki7ssb hashing (bwhd formule dmath mhm bla manmrdo rasna hahya library wajda)

void calculHash(Block * block);
void mineBlock(Block* block);

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
    calculHash(newBlock);
    return newBlock;
}

void insertBlock(Block** head, Block* newBlock) {
    if (head == NULL) {
        printf("Erreur \n");
        return;
    }

    if (*head == NULL) {
        *head = newBlock;
    } else {
        Block* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        mineBlock(newBlock);
        temp->next = newBlock;
    }
    
}


void calculHash(Block * block){
    char melang[1024]; 
    snprintf(melang, sizeof(melang), "%s%d%s", block->data,    
                                              block->nonce,
                                             block->prev_hash);

    unsigned char hash[SHA256_DIGEST_LENGTH];    
    SHA256_CTX sha256; 

    SHA256_Init(&sha256); 

    SHA256_Update(&sha256, melang, strlen(melang)); 

    SHA256_Final(hash, &sha256); 


    
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

    if (block == NULL) {
        printf("Blockchain is empty!\n");
        return 0;
    }

    char zerostring[65];
    memset(zerostring,'0',64);
    zerostring[64] = '\0';
    if(strncmp(block->prev_hash,zerostring,64) != 0){
        printf("Theres No genesis Block");
        return 0 ; 
    }

    while (block->next != NULL ) {
        if(strncmp(block->hash , block->next->prev_hash, 64) != 0 ){
            printf("The block is not valid !");
            return 0;
        }
        block = block->next;
    }
    printf("The block is valid");
    return 1 ;
}
void displayBlockchain(Block* head) {
    Block* current = head; 

    printf("===== Blockchain =====\n");
    while (current) {
        printf("Bloc #%d\n", current->index);
        printf("Timestamp: %ld\n", current->timestamp);
        printf("Data: %s\n", current->data);
        printf("Nonce: %d\n", current->nonce);
        printf("Previous Hash: %s\n", current->prev_hash);
        printf("Hash: %s\n", current->hash);
        printf("----------------------\n");

        current = current->next; 
    }
}

void initializeBlockchain(Block** head) {
    Block* genesisBlock = (Block*)malloc(sizeof(Block));
    if (!genesisBlock) {
        printf("Erreur : allocation mémoire échouée \n");
        return;
    }

    genesisBlock->index = 0;
    genesisBlock->timestamp = time(NULL); 
    strncpy(genesisBlock->data, "Genesis Block", sizeof(genesisBlock->data) - 1); 
    genesisBlock->data[sizeof(genesisBlock->data) - 1] = '\0'; 
    strncpy(genesisBlock->prev_hash ,"0000000000000000000000000000000000000000000000000000000000000000000",70);
    genesisBlock->nonce = 0; 
    genesisBlock->next = NULL;

    calculHash(genesisBlock);
    *head = genesisBlock;

    printf("Genesis Block créé.\n");
}

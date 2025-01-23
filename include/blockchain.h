#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <time.h>

typedef struct Block {
    int index;                
    time_t timestamp;         
    char data[256];           
    char hash[64];            
    char prev_hash[64];      
    int nonce;                
    struct Block* next;       
} Block;

Block* createBlock(int index, const char* data, const char* prev_hash);
void insertBlock(Block** head, Block* newBlock);
void mineBlock(Block* block);
int validateChain(Block* head);
void displayBlockchain(Block* head);

#endif 
#include <stdio.h>
#include <string.h>
#include "ledger.h"
#include "blockchain.h"

void saveBlockchainToFile(const Block* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    const Block* current = head;
    while (current) {
        LedgerEntry entry;
        entry.index = current->index;
        entry.timestamp = current->timestamp;
        strncpy(entry.data, current->data, sizeof(entry.data) - 1);
        entry.data[sizeof(entry.data) - 1] = '\0';
        strncpy(entry.hash, current->hash, sizeof(entry.hash) - 1);
        entry.hash[sizeof(entry.hash) - 1] = '\0';
        strncpy(entry.prev_hash, current->prev_hash, sizeof(entry.prev_hash) - 1);
        entry.prev_hash[sizeof(entry.prev_hash) - 1] = '\0';
        entry.nonce = current->nonce;

        fwrite(&entry, sizeof(LedgerEntry), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Blockchain sauvegardée dans le fichier : %s\n", filename);
}

Block* loadBlockchainFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    Block* head = NULL;
    Block* previous = NULL;

    LedgerEntry entry;
    while (fread(&entry, sizeof(LedgerEntry), 1, file)) {
        Block* newBlock = (Block*)malloc(sizeof(Block));
        newBlock->index = entry.index;
        newBlock->timestamp = entry.timestamp;
        strncpy(newBlock->data, entry.data, sizeof(newBlock->data) - 1);
        newBlock->data[sizeof(newBlock->data) - 1] = '\0';
        strncpy(newBlock->hash, entry.hash, sizeof(newBlock->hash) - 1);
        newBlock->hash[sizeof(newBlock->hash) - 1] = '\0';
        strncpy(newBlock->prev_hash, entry.prev_hash, sizeof(newBlock->prev_hash) - 1);
        newBlock->prev_hash[sizeof(newBlock->prev_hash) - 1] = '\0';
        newBlock->nonce = entry.nonce;
        newBlock->next = NULL;

        if (!head) {
            head = newBlock;
        } else {
            previous->next = newBlock;
        }
        previous = newBlock;
    }

    fclose(file);
    printf("Blockchain chargée depuis le fichier : %s\n", filename);
    return head;
}
int main(){

    return 0 ;
}
#include <stdio.h>
#include <openssl/sha.h>
#ifndef LEDGER_H
#define LEDGER_H
#define MAX_DATA_SIZE 256

typedef struct LedgerEntry {
    int index;
    long timestamp;
    char data[MAX_DATA_SIZE];
    char hash[SHA256_DIGEST_LENGTH * 2 + 1];
    char prev_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    int nonce;
} LedgerEntry;

#endif 

int main(){

    return 0 ;
}
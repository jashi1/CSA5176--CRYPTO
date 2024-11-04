#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK_SIZE 16  
#define NUM_BLOCKS 4  
void AES_encrypt(unsigned char* input, unsigned char* output) {
   
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ 0xAA; 
    }
}
void print_hex(unsigned char* data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

void introduce_error(unsigned char* ciphertext, int block_index, int byte_index) {
    ciphertext[block_index * BLOCK_SIZE + byte_index] ^= 0xFF; 
}

int main() {
  
    unsigned char plaintext[NUM_BLOCKS][BLOCK_SIZE] = {
        "Block 1 Data!!",
        "Block 2 Data!!",
        "Block 3 Data!!",
        "Block 4 Data!!"
    };

    unsigned char ciphertext[NUM_BLOCKS][BLOCK_SIZE];

    for (int i = 0; i < NUM_BLOCKS; i++) {
        AES_encrypt(plaintext[i], ciphertext[i]);
    }

    printf("Ciphertext (before error):\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        print_hex(ciphertext[i], BLOCK_SIZE);
    }

    introduce_error((unsigned char*)ciphertext, 1, 2); 

    printf("Ciphertext (after error):\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        print_hex(ciphertext[i], BLOCK_SIZE);
    }

    return 0;
}


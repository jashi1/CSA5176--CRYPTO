#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 16   
#define Rb 0x87        
void print_hex(const unsigned char *buffer, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}
void left_shift_one_bit(unsigned char *input, unsigned char *output) {
    int carry = 0;
    for (int i = BLOCK_SIZE - 1; i >= 0; --i) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;
    }
}

void xor_with_rb(unsigned char *block) {
    block[BLOCK_SIZE - 1] ^= Rb;
}

void generate_cmac_subkeys(const unsigned char *key, unsigned char *K1, unsigned char *K2) {
   
    unsigned char L[BLOCK_SIZE] = {0};    
    unsigned char temp[BLOCK_SIZE] = {0};
 
    left_shift_one_bit(L, K1);
    if (L[0] & 0x80) { 
        xor_with_rb(K1);
    }

    left_shift_one_bit(K1, K2);
    if (K1[0] & 0x80) {  
        xor_with_rb(K2);
    }
}

int main() {
    
    unsigned char key[BLOCK_SIZE] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x16, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };

    unsigned char K1[BLOCK_SIZE] = {0};
    unsigned char K2[BLOCK_SIZE] = {0};

    generate_cmac_subkeys(key, K1, K2);

    
    printf("Subkey K1: ");
    print_hex(K1, BLOCK_SIZE);
    printf("Subkey K2: ");
    print_hex(K2, BLOCK_SIZE);
    return 0;
}


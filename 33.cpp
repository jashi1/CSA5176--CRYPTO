#include <stdio.h>
#include <stdint.h>
int IP[] = { 
    58, 50, 42, 34, 26, 18, 10,  2, 
    60, 52, 44, 36, 28, 20, 12,  4, 
    62, 54, 46, 38, 30, 22, 14,  6, 
    64, 56, 48, 40, 32, 24, 16,  8, 
    57, 49, 41, 33, 25, 17,  9,  1, 
    59, 51, 43, 35, 27, 19, 11,  3, 
    61, 53, 45, 37, 29, 21, 13,  5, 
    63, 55, 47, 39, 31, 23, 15,  7 
};
int FP[] = { 
    40,  8, 48, 16, 56, 24, 64, 32, 
    39,  7, 47, 15, 55, 23, 63, 31, 
    38,  6, 46, 14, 54, 22, 62, 30, 
    37,  5, 45, 13, 53, 21, 61, 29, 
    36,  4, 44, 12, 52, 20, 60, 28, 
    35,  3, 43, 11, 51, 19, 59, 27, 
    34,  2, 42, 10, 50, 18, 58, 26, 
    33,  1, 41,  9, 49, 17, 57, 25 
};
int E[] = { 
    32,  1,  2,  3,  4,  5, 
     4,  5,  6,  7,  8,  9, 
     8,  9, 10, 11, 12, 13, 
    12, 13, 14, 15, 16, 17, 
    16, 17, 18, 19, 20, 21, 
    20, 21, 22, 23, 24, 25, 
    24, 25, 26, 27, 28, 29, 
    28, 29, 30, 31, 32,  1 
};
int P[] = { 
    16,  7, 20, 21, 
    29, 12, 28, 17, 
     1, 15, 23, 26, 
     5, 18, 31, 10, 
     2,  8, 24, 14, 
    32, 27,  3,  9, 
    19, 13, 30,  6, 
    22, 11,  4, 25 
};
uint64_t permute(uint64_t input, int* table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output |= ((input >> (64 - table[i])) & 0x01) << (n - i - 1);
    }
    return output;
}

// Simple left rotation function for key scheduling
uint64_t rotate_left(uint64_t input, int shifts, int n) {
    return ((input << shifts) | (input >> (n - shifts))) & ((1ULL << n) - 1);
}

// DES encryption function (with decryption option)
uint64_t des(uint64_t input, uint64_t key, int decrypt) {
    // Initial permutation
    uint64_t permuted_block = permute(input, IP, 64);

    // Divide into left and right halves
    uint32_t left = permuted_block >> 32;
    uint32_t right = permuted_block & 0xFFFFFFFF;

    // Perform 16 rounds (simplified, no key schedule)
    for (int round = 0; round < 16; round++) {
        uint32_t expanded_right = permute(right, E, 48); // Expansion permutation
        uint32_t sbox_output = expanded_right ^ (uint32_t)(key & 0xFFFFFFFF); // Simplified S-box substitution

        // Swap and combine
        uint32_t new_right = left ^ sbox_output;
        left = right;
        right = new_right;
    }

    // Combine left and right
    uint64_t combined = ((uint64_t)right << 32) | left;

    // Final permutation
    uint64_t result = permute(combined, FP, 64);

    return result;
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;  // Example plaintext
    uint64_t key = 0x133457799BBCDFF1;      
    printf("Plaintext: %016lX\n", plaintext);
    uint64_t ciphertext = des(plaintext, key, 0);  // Encrypt
    printf("Ciphertext: %016lX\n", ciphertext);
    uint64_t decrypted_text = des(ciphertext, key, 1);  // Decrypt
    printf("Decrypted text: %016lX\n", decrypted_text);

    return 0;
}


#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16 // Block size of 16 bytes (128 bits)

// Simulate simple XOR encryption for ECB (only for demonstration)
void encryptECB(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

void decryptECB(unsigned char* ciphertext, unsigned char* plaintext, unsigned char* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i];
    }
}

// CBC mode encryption
void encryptCBC(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key, unsigned char* iv) {
    unsigned char block[BLOCK_SIZE];
    
    // XOR IV with first plaintext block
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = plaintext[i] ^ iv[i];
    }
    encryptECB(block, ciphertext, key); // Encrypt the first block
    
    // Process subsequent blocks (for simplicity, assuming 2 blocks of plaintext)
    for (int i = 1; i < 2; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = plaintext[i * BLOCK_SIZE + j] ^ ciphertext[(i - 1) * BLOCK_SIZE + j];
        }
        encryptECB(block, &ciphertext[i * BLOCK_SIZE], key);
    }
}

// CBC mode decryption
void decryptCBC(unsigned char* ciphertext, unsigned char* plaintext, unsigned char* key, unsigned char* iv) {
    unsigned char block[BLOCK_SIZE];

    // Decrypt the first block and XOR with IV
    decryptECB(ciphertext, block, key);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = block[i] ^ iv[i];
    }

    // Process subsequent blocks
    for (int i = 1; i < 2; i++) {
        decryptECB(&ciphertext[i * BLOCK_SIZE], block, key);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] = block[j] ^ ciphertext[(i - 1) * BLOCK_SIZE + j];
        }
    }
}

// Simulate an error in a ciphertext block (flip a byte)
void introduceError(unsigned char* ciphertext, int blockIndex, int byteIndex) {
    ciphertext[blockIndex * BLOCK_SIZE + byteIndex] ^= 0xFF; // Flip the bits of the byte at byteIndex in blockIndex
}

int main() {
    unsigned char plaintext[2 * BLOCK_SIZE] = "PlaintextBlock1PlaintextBlock2";
    unsigned char ciphertext[2 * BLOCK_SIZE];
    unsigned char decryptedtext[2 * BLOCK_SIZE];
    unsigned char key[BLOCK_SIZE];

    memcpy(key, "encryptionkey123", BLOCK_SIZE); // Copy the key as 16 bytes

    printf("Original Plaintext: %s\n", plaintext);

    // ECB Mode
    printf("\n--- ECB Mode ---\n");
    encryptECB(plaintext, ciphertext, key);
    introduceError(ciphertext, 0, 0); // Introduce an error in the first byte of the first block

    printf("Ciphertext (ECB mode): ");
    for (int i = 0; i < 2 * BLOCK_SIZE; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");
    decryptECB(ciphertext, decryptedtext, key);
    printf("Decrypted text (ECB mode): %s\n", decryptedtext);
    printf("\n--- CBC Mode ---\n");
    encryptCBC(plaintext, ciphertext, key);
    introduceError(ciphertext, 0, 0); 
    printf("Ciphertext (CBC mode): ");
    for (int i = 0; i < 2 * BLOCK_SIZE; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    decryptCBC(ciphertext, decryptedtext, key, iv);
    printf("Decrypted text (CBC mode): %s\n", decryptedtext);

    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16  // AES block size in bytes

// Dummy AES encryption function
void AES_encrypt(unsigned char* input, unsigned char* output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ 0xAA; // Simple XOR operation for demo
    }
}

// Function to pad the plaintext using 1 followed by 0's
void pad_plaintext(unsigned char* plaintext, int *length) {
    int pad_length = BLOCK_SIZE - (*length % BLOCK_SIZE);
    plaintext[*length] = 0x80;  // 1 followed by zeros
    for (int i = 1; i < pad_length; i++) {
        plaintext[*length + i] = 0x00;
    }
    *length += pad_length;
}

// ECB Mode Encryption
void ECB_encrypt(unsigned char* plaintext, unsigned char* ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i);
    }
}

// CBC Mode Encryption
void CBC_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* iv, int length) {
    unsigned char temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] = plaintext[i] ^ iv[i];  // XOR with IV
    }
    AES_encrypt(temp, ciphertext);

    for (int i = BLOCK_SIZE; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plaintext[i + j] ^ ciphertext[i - BLOCK_SIZE + j]; // XOR with previous ciphertext
        }
        AES_encrypt(temp, ciphertext + i);
    }
}

// CFB Mode Encryption
void CFB_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* iv, int length) {
    unsigned char temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] = iv[i];
    }

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        AES_encrypt(temp, temp);  // Encrypt the IV or previous block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ temp[j];  // XOR with plaintext
            temp[j] = ciphertext[i + j];  // Shift the ciphertext to be the next IV
        }
    }
}

// Function to display data in hexadecimal format
void print_hex(unsigned char* data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    // Example plaintext (not a multiple of block size)
    unsigned char plaintext[] = "This is an example message.";
    unsigned char iv[BLOCK_SIZE] = {0x00};  
    int plaintext_len = strlen((char*)plaintext);

    unsigned char padded_plaintext[64];  
    memcpy(padded_plaintext, plaintext, plaintext_len);
    pad_plaintext(padded_plaintext, &plaintext_len);

    unsigned char ciphertext_ecb[64] = {0};
    unsigned char ciphertext_cbc[64] = {0};
    unsigned char ciphertext_cfb[64] = {0};

    ECB_encrypt(padded_plaintext, ciphertext_ecb, plaintext_len);
    printf("ECB Mode Ciphertext:\n");
    print_hex(ciphertext_ecb, plaintext_len);

    CBC_encrypt(padded_plaintext, ciphertext_cbc, iv, plaintext_len);
    printf("CBC Mode Ciphertext:\n");
    print_hex(ciphertext_cbc, plaintext_len);

    CFB_encrypt(padded_plaintext, ciphertext_cfb, iv, plaintext_len);
    printf("CFB Mode Ciphertext:\n");
    print_hex(ciphertext_cfb, plaintext_len);

    return 0;
}


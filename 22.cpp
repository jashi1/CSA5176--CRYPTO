#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 
#define KEY_SIZE 10 
uint8_t sdesEncrypt(uint8_t input, uint8_t key) {
   
    return input ^ key;
}

uint8_t binaryStringToByte(const char* binaryString) {
    uint8_t byte = 0;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        byte <<= 1;
        byte |= (binaryString[i] - '0');
    }
    return byte;
}

void byteToBinaryString(uint8_t byte, char* binaryString) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        binaryString[i] = (byte & 1) ? '1' : '0';
        byte >>= 1;
    }
    binaryString[BLOCK_SIZE] = '\0';
}

void cbcEncryptDecrypt(const char* plaintextBin, const char* keyBin, const char* ivBin) {
    uint8_t key = binaryStringToByte(keyBin);
    uint8_t iv = binaryStringToByte(ivBin);
    char binaryOutput[BLOCK_SIZE + 1]; 
    size_t plaintextLength = strlen(plaintextBin);
    
    printf("Ciphertext:\n");
    for (size_t i = 0; i < plaintextLength; i += BLOCK_SIZE) {
       
        char block[BLOCK_SIZE + 1] = {0};
        strncpy(block, plaintextBin + i, BLOCK_SIZE);
        
        uint8_t plaintextBlock = binaryStringToByte(block);
        
        if (i == 0) {
            plaintextBlock ^= iv; 
        } else {
            plaintextBlock ^= iv; 
        }
        
        uint8_t ciphertextBlock = sdesEncrypt(plaintextBlock, key);
        
        byteToBinaryString(ciphertextBlock, binaryOutput);
        printf("%s ", binaryOutput);
        
        iv = ciphertextBlock; 
    }

    printf("\n\nDecrypted Plaintext:\n");
    
    iv = binaryStringToByte(ivBin);
    
    for (size_t i = 0; i < plaintextLength; i += BLOCK_SIZE) {
     
        char block[BLOCK_SIZE + 1] = {0};
        strncpy(block, plaintextBin + i, BLOCK_SIZE);
        
        uint8_t ciphertextBlock = binaryStringToByte(block);
        
        uint8_t decryptedBlock = sdesEncrypt(ciphertextBlock, key);
        
        uint8_t plaintextBlock = decryptedBlock ^ iv;

        byteToBinaryString(plaintextBlock, binaryOutput);
        printf("%s ", binaryOutput);
        
        iv = ciphertextBlock; 
    }
}

int main() {
    
    const char* plaintextBin = "0000000100100011"; 
    const char* keyBin = "1010000010"; 
    const char* ivBin = "10101010"; 

    printf("Plaintext: %s\n", plaintextBin);
    printf("Key: %s\n", keyBin);
    printf("IV: %s\n", ivBin);
    
    cbcEncryptDecrypt(plaintextBin, keyBin, ivBin);

    return 0;
}


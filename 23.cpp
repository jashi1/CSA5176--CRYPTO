#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 
#define KEY_SIZE 10  
#define NUM_ROUNDS 10

uint8_t sdesEncrypt(uint8_t input, uint8_t key) {
    
    return input ^ key;
}

uint8_t sdesDecrypt(uint8_t input, uint8_t key) {
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
void counterModeEncryptDecrypt(const char* plaintextBin, const char* keyBin) {
    uint8_t key = binaryStringToByte(keyBin);
    uint8_t counter = 0; 
    char binaryOutput[BLOCK_SIZE + 1]; 

    for (int i = 0; i < strlen(plaintextBin); i += BLOCK_SIZE) {
        uint8_t plaintextBlock = binaryStringToByte(plaintextBin + i);
        uint8_t encryptedCounter = sdesEncrypt(counter, key);
        uint8_t ciphertextBlock = plaintextBlock ^ encryptedCounter;
        byteToBinaryString(ciphertextBlock, binaryOutput);
        printf("Ciphertext Block: %s\n", binaryOutput);
        counter++; 
    }

    counter = 0;

    printf("Decrypted Plaintext:\n");
    for (int i = 0; i < strlen(plaintextBin); i += BLOCK_SIZE) {
        uint8_t ciphertextBlock = binaryStringToByte(plaintextBin + i); 
        uint8_t encryptedCounter = sdesDecrypt(counter, key);
        uint8_t decryptedBlock = ciphertextBlock ^ encryptedCounter;
        byteToBinaryString(decryptedBlock, binaryOutput);
        printf("Decrypted Block: %s\n", binaryOutput);
        counter++; 
    }
}

int main() {

    const char* plaintextBin = "0011100001001111";
    const char* keyBin = "1010000010"; 

    printf("Plaintext: %s\n", plaintextBin);
    printf("Key: %s\n", keyBin);
    
    counterModeEncryptDecrypt(plaintextBin, keyBin);

    return 0;
}


#include <stdio.h>
#include <string.h>
unsigned long desRoundFunction(unsigned long data, unsigned long subkey) {
    return (data ^ subkey); 
}
unsigned long desDecrypt(unsigned long ciphertext, unsigned long subkeys[16]) {
    unsigned long data = ciphertext;
    for (int i = 15; i >= 0; i--) {
        data = desRoundFunction(data, subkeys[i]);
    }
    return data;
}
void generateSubkeys(unsigned long key, unsigned long subkeys[16]) {
    for (int i = 0; i < 16; i++) {
        subkeys[i] = key ^ (i + 1);
    }
}
int main() {
    unsigned long key = 0xAABB09182736CCDD; 
    unsigned long ciphertext = 0xD4E6B48F; 
    unsigned long subkeys[16];
    generateSubkeys(key, subkeys);
    unsigned long plaintext = desDecrypt(ciphertext, subkeys);
    printf("Decrypted plaintext: %lX\n", plaintext);
    return 0;
}


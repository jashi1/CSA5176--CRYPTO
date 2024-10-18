#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encryptVigenere(char plaintext[], int key[], int keyLength) {
    int i;
    int textLength = strlen(plaintext);
    printf("Encrypted Text: ");
    for (i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int ptChar = plaintext[i] - base;
            int shift = key[i % keyLength]; 
            int encryptedChar = (ptChar + shift) % 26;
            printf("%c", encryptedChar + base);
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; 
    int keyLength = sizeof(key) / sizeof(key[0]);
    encryptVigenere(plaintext, key, keyLength);
    return 0;
}

Output:
Encrypted Text: beok bjfp owwny

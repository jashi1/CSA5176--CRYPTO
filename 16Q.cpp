#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_LEN 1000
char commonLetters[] = "etaoinshrdlcumwfgypbvkjxqz";
void frequencyAnalysis(char ciphertext[], int freq[]) {
    int i;
    int length = strlen(ciphertext);
    for (i = 0; i < 26; i++) {
        freq[i] = 0;
    }
    for (i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = tolower(ciphertext[i]); 
            freq[ch - 'a']++;
        }
    }
}
void mapCiphertext(char ciphertext[], int freq[], char mapping[]) {
    int i, j;
    int sortedFreq[26];
    char sortedLetters[26];
    for (i = 0; i < 26; i++) {
        sortedFreq[i] = freq[i];
        sortedLetters[i] = 'a' + i;
    }
    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (sortedFreq[i] < sortedFreq[j]) {
                int tempFreq = sortedFreq[i];
                sortedFreq[i] = sortedFreq[j];
                sortedFreq[j] = tempFreq;
                char tempLetter = sortedLetters[i];
                sortedLetters[i] = sortedLetters[j];
                sortedLetters[j] = tempLetter;
            }
        }
    }
    for (i = 0; i < 26; i++) {
        mapping[sortedLetters[i] - 'a'] = commonLetters[i];
    }
}
void decryptCiphertext(char ciphertext[], char mapping[]) {
    int i;
    int length = strlen(ciphertext);
    
    printf("Decrypted Text: ");
    for (i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char mappedChar = mapping[tolower(ciphertext[i]) - 'a'];
            printf("%c", isupper(ciphertext[i]) ? toupper(mappedChar) : mappedChar);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}
int main() {
    char ciphertext[MAX_TEXT_LEN];
    int freq[26];
    char mapping[26];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LEN, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; 
    frequencyAnalysis(ciphertext, freq);
    mapCiphertext(ciphertext, freq, mapping);
    decryptCiphertext(ciphertext, mapping);
    return 0;
}

//OUTPUT:
Enter the ciphertext: hello
Decrypted Text: taeeo

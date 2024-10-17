#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to generate the monoalphabetic substitution based on a shift
void generateMonoAlphabeticSubstitution(char* substitution, int shift) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[i] = (char)((i + shift) % ALPHABET_SIZE + 'A');
    }
}

// Function to encrypt the plaintext using polyalphabetic substitution
void encrypt(char* plaintext, char* key, char* ciphertext) {
    int textLength = strlen(plaintext);
    int keyLength = strlen(key);
    
    for (int i = 0, j = 0; i < textLength; i++) {
        char currentChar = plaintext[i];

        // Ignore non-alphabetic characters
        if (!isalpha(currentChar)) {
            ciphertext[i] = currentChar;
            continue;
        }

        // Convert to uppercase
        currentChar = toupper(currentChar);
        int keyShift = toupper(key[j % keyLength]) - 'A';
        
        // Generate monoalphabetic substitution
        char substitution[ALPHABET_SIZE];
        generateMonoAlphabeticSubstitution(substitution, keyShift);

        // Encrypt the character
        ciphertext[i] = substitution[currentChar - 'A'];
        
        // Move to the next character in the key
        j++;
    }
    ciphertext[textLength] = '\0'; // Null-terminate the ciphertext
}

int main() {
    char plaintext[100];
    char key[100];
    char ciphertext[100];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    encrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}


Output:
Enter plaintext: ADD
Enter key: OR
Ciphertext: OUR

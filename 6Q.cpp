#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to compute the modular multiplicative inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Return -1 if no modular inverse exists
}

// Function to decrypt the affine cipher
void decryptAffine(const char *ciphertext, int a, int b) {
    int m = ALPHABET_SIZE;
    int a_inv = modInverse(a, m);
    
    if (a_inv == -1) {
        printf("No modular inverse exists for a = %d\n", a);
        return;
    }

    printf("Decrypted plaintext: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];

        if (c >= 'A' && c <= 'Z') {
            // Apply the decryption formula
            int P = (a_inv * ((c - 'A' - b + m) % m)) % m;
            printf("%c", P + 'A');
        } else {
            printf("%c", c); // Preserve non-alphabet characters
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "YOUR_CIPHERTEXT_HERE"; // Replace with your actual ciphertext
    int a = 3; // Example value for a (must be coprime with 26)
    int b = 1; // Example value for b

    printf("Ciphertext: %s\n", ciphertext);
    decryptAffine(ciphertext, a, b);

    return 0;
}


Output:
	Ciphertext: YOUR_CIPHERTEXT_HERE
Decrypted plaintext: ZNPO_JLWCBOGBQG_CBOB

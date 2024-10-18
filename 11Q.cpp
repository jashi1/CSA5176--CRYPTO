#include <stdio.h>
#include <string.h>

#define SIZE 2 // Size of the Hill cipher matrix

int key[SIZE][SIZE] = {{9, 4}, {5, 7}}; // Hill cipher key matrix
int inv_key[SIZE][SIZE] = {{0, 0}, {0, 0}}; // To store the inverse key matrix

// Function to encrypt the plaintext using Hill cipher
void encryptHill(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += SIZE) {
        int block[SIZE] = {0}; // Store current block of plaintext
        for (int j = 0; j < SIZE; j++) {
            if (i + j < len) {
                block[j] = plaintext[i + j] - 'a'; // Convert to 0-25
            }
        }
        // Encrypt the block
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i / SIZE * SIZE + j] = (key[j][0] * block[0] + key[j][1] * block[1]) % 26 + 'a'; // Encrypt and convert back to character
        }
    }
    ciphertext[len] = '\0'; // Null-terminate ciphertext
}

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // If not found
}

// Function to calculate the inverse key matrix
void inverseKey() {
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    determinant = (determinant + 26) % 26; // Ensure positive determinant
    int detInv = modInverse(determinant, 26); // Find inverse of determinant

    inv_key[0][0] = (key[1][1] * detInv) % 26;
    inv_key[0][1] = (-key[0][1] * detInv + 26) % 26;
    inv_key[1][0] = (-key[1][0] * detInv + 26) % 26;
    inv_key[1][1] = (key[0][0] * detInv) % 26;
}

int main() {
    char plaintext[] = "meetmeattheusualplaceattentratherthaneight";
    char ciphertext[100];

    encryptHill(plaintext, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    inverseKey(); // Calculate inverse key matrix
    return 0;
}

OUTPUT:-
Ciphertext: ukixukydromeiwszxwiokunukhfgydblvkljdpsejm

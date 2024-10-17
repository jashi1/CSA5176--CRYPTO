#include <stdio.h>
#include <stdlib.h>

#define SIZE 2  // Size of the key matrix

// Function to calculate the modulo inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;  // If no modular inverse exists
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[SIZE][SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

// Function to get the adjugate (cofactor matrix) of a 2x2 matrix
void adjugateMatrix(int matrix[SIZE][SIZE], int adj[SIZE][SIZE]) {
    adj[0][0] = matrix[1][1];
    adj[0][1] = -matrix[0][1];
    adj[1][0] = -matrix[1][0];
    adj[1][1] = matrix[0][0];
}

// Function to encrypt a block of text
void encrypt(const char *text, int key[SIZE][SIZE], char *ciphertext) {
    int len = 0;
    while (text[len] != '\0') len++;

    for (int i = 0; i < len; i += SIZE) {
        for (int row = 0; row < SIZE; row++) {
            int sum = 0;
            for (int col = 0; col < SIZE; col++) {
                sum += key[row][col] * (text[i + col] - 'A');
            }
            ciphertext[i / SIZE * SIZE + row] = (sum % 26 + 26) % 26 + 'A'; // Ensure positive
        }
    }
    ciphertext[len] = '\0';  // Null-terminate the string
}

// Function to decrypt a block of text
void decrypt(const char *ciphertext, int key[SIZE][SIZE], char *plaintext) {
    int det = determinant(key);
    int detInverse = modInverse(det, 26);
    
    if (detInverse == -1) {
        printf("Matrix is not invertible. Decryption is not possible.\n");
        return;
    }

    int adj[SIZE][SIZE];
    adjugateMatrix(key, adj);

    // Multiply the adjugate matrix by the modular inverse of the determinant
    int inverseKey[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inverseKey[i][j] = (adj[i][j] * detInverse) % 26;
            if (inverseKey[i][j] < 0) inverseKey[i][j] += 26;  // Ensure positive values
        }
    }

    int len = 0;
    while (ciphertext[len] != '\0') len++;

    for (int i = 0; i < len; i += SIZE) {
        for (int row = 0; row < SIZE; row++) {
            int sum = 0;
            for (int col = 0; col < SIZE; col++) {
                sum += inverseKey[row][col] * (ciphertext[i + col] - 'A');
            }
            plaintext[i / SIZE * SIZE + row] = (sum % 26 + 26) % 26 + 'A'; // Ensure positive
        }
    }
    plaintext[len] = '\0';  // Null-terminate the string
}

int main() {
    int key[SIZE][SIZE] = {{3, 3}, {2, 5}};  // Key matrix

    char plaintext[100];
    char ciphertext[100];
    char decryptedText[100];

    printf("Enter plaintext (only uppercase letters): ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}


Output:
Enter plaintext (only uppercase letters): MUST
Encrypted Text: SUHB
Decrypted Text: MUST

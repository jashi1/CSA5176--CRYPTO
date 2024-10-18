#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char playfairMatrix[SIZE][SIZE]; // Playfair matrix

// Function to create Playfair matrix from a key
void createPlayfairMatrix(const char *key) {
    int k = 0;
    int charExists[26] = {0}; // To track used characters
    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c >= 'A' && c <= 'Z' && !charExists[c - 'A']) {
            if (c == 'J') c = 'I'; // Treat I and J as the same
            playfairMatrix[k / SIZE][k % SIZE] = c;
            charExists[c - 'A'] = 1;
            k++;
        }
    }
    // Fill the matrix with remaining letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!charExists[c - 'A']) {
            if (c == 'J') continue; // Skip J
            playfairMatrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}

// Function to print the Playfair matrix
void printPlayfairMatrix() {
    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", playfairMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to encrypt the plaintext using the Playfair cipher
void encryptPlayfair(const char *plaintext) {
    char processedText[100] = {0};
    int k = 0;

    // Prepare the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);
        if (c == ' ') continue; // Skip spaces
        if (c == 'J') c = 'I'; // Treat I and J as the same
        processedText[k++] = c;
    }
    processedText[k] = '\0';

    // Form digraphs
    char digraphs[50][3]; // Maximum of 25 digraphs
    int digraphIndex = 0;
    
    for (int i = 0; i < k; i += 2) {
        if (i + 1 < k) {
            if (processedText[i] == processedText[i + 1]) { // Same letter
                digraphs[digraphIndex][0] = processedText[i];
                digraphs[digraphIndex][1] = 'X'; // Insert filler
                digraphs[digraphIndex][2] = '\0';
                digraphIndex++;
                i--; // Check the same letter again
            } else {
                digraphs[digraphIndex][0] = processedText[i];
                digraphs[digraphIndex][1] = processedText[i + 1];
                digraphs[digraphIndex][2] = '\0';
                digraphIndex++;
            }
        } else {
            digraphs[digraphIndex][0] = processedText[i];
            digraphs[digraphIndex][1] = 'X'; // Filler for odd length
            digraphs[digraphIndex][2] = '\0';
            digraphIndex++;
        }
    }

    // Encrypt digraphs
    printf("Encrypted Message: ");
    for (int i = 0; i < digraphIndex; i++) {
        char a = digraphs[i][0];
        char b = digraphs[i][1];

        int rowA, colA, rowB, colB;
        // Find positions of a and b in the matrix
        for (rowA = 0; rowA < SIZE; rowA++) {
            for (colA = 0; colA < SIZE; colA++) {
                if (playfairMatrix[rowA][colA] == a) break;
            }
            if (colA < SIZE) break; // Found
        }
        for (rowB = 0; rowB < SIZE; rowB++) {
            for (colB = 0; colB < SIZE; colB++) {
                if (playfairMatrix[rowB][colB] == b) break;
            }
            if (colB < SIZE) break; // Found
        }

        // Apply Playfair cipher rules
        if (rowA == rowB) {
            printf("%c%c", playfairMatrix[rowA][(colA + 1) % SIZE], playfairMatrix[rowB][(colB + 1) % SIZE]);
        } else if (colA == colB) {
            printf("%c%c", playfairMatrix[(rowA + 1) % SIZE][colA], playfairMatrix[(rowB + 1) % SIZE][colB]);
        } else {
            printf("%c%c", playfairMatrix[rowA][colB], playfairMatrix[rowB][colA]);
        }
    }
    printf("\n");
}

int main() {
    char key[100];
    char plaintext[100];

    printf("Enter the keyword for Playfair cipher (without spaces): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; // Remove newline character from input

    createPlayfairMatrix(key);
    printPlayfairMatrix();

    printf("Enter the plaintext message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline character from input

    encryptPlayfair(plaintext);

    return 0;
}
OUTPUT:-
Output
Enter the keyword for Playfair cipher (without spaces): i am a student
Playfair Matrix:
I A M S T
U D E N B
C F G H K
L O P Q R
V W X Y Z
Enter the plaintext message to encrypt: Standing
Encrypted Message: TISDUAEH

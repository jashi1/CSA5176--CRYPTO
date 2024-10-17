#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

char playfairMatrix[5][5]; // Playfair matrix

// Function to create Playfair matrix from a key
void createPlayfairMatrix(char *key) {
    int k = 0;
    int charExists[26] = {0}; // to track used characters
    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c >= 'A' && c <= 'Z' && !charExists[c - 'A']) {
            if (c == 'J') c = 'I'; // treat I and J as the same
            playfairMatrix[k / 5][k % 5] = c;
            charExists[c - 'A'] = 1;
            k++;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!charExists[c - 'A']) {
            if (c == 'J') continue; // skip J
            playfairMatrix[k / 5][k % 5] = c;
            k++;
        }
    }
}

// Function to prepare the message by handling duplicate letters
void prepareMessage(char *msg, char *output) {
    int j = 0;
    for (int i = 0; msg[i] != '\0'; i++) {
        char c = toupper(msg[i]);
        if (c == ' ') continue; // ignore spaces
        if (c == 'J') c = 'I'; // treat I and J as the same
        output[j++] = c;
        if (msg[i + 1] != '\0' && c == toupper(msg[i + 1])) {
            output[j++] = 'X'; // insert 'X' between duplicate letters
        }
    }
    output[j] = '\0'; // null-terminate the output
}

// Function to encrypt the message using Playfair cipher
void encryptPlayfair(char *msg, char *ciphertext) {
    char prepared[MAX_LEN];
    prepareMessage(msg, prepared);
    
    for (int i = 0; prepared[i] != '\0'; i += 2) {
        char a = prepared[i];
        char b = (prepared[i + 1] != '\0') ? prepared[i + 1] : 'X'; // pair with X if odd
        
        int rowA, colA, rowB, colB;
        // Find positions in the matrix
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (playfairMatrix[r][c] == a) {
                    rowA = r; colA = c;
                }
                if (playfairMatrix[r][c] == b) {
                    rowB = r; colB = c;
                }
            }
        }

        if (rowA == rowB) { // Same row
            ciphertext[i] = playfairMatrix[rowA][(colA + 1) % 5];
            ciphertext[i + 1] = playfairMatrix[rowB][(colB + 1) % 5];
        } else if (colA == colB) { // Same column
            ciphertext[i] = playfairMatrix[(rowA + 1) % 5][colA];
            ciphertext[i + 1] = playfairMatrix[(rowB + 1) % 5][colB];
        } else { // Rectangle swap
            ciphertext[i] = playfairMatrix[rowA][colB];
            ciphertext[i + 1] = playfairMatrix[rowB][colA];
        }
    }
    ciphertext[strlen(prepared)] = '\0'; // null-terminate the ciphertext
}

int main() {
    char key[] = "M F H I J K U N O P Q Z V W X Y E L A R G D S T B C";
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[MAX_LEN];

    createPlayfairMatrix(key);
    encryptPlayfair(message, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}


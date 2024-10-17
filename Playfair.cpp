#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]);
void formatPlaintext(char plaintext[], char formattedText[]);
void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col);
void encryptPair(char keyMatrix[SIZE][SIZE], char pair[], char result[]);
int removeDuplicatesAndPrepareKey(char key[]);
void replaceJWithI(char *text);
void printMatrix(char matrix[SIZE][SIZE]);
int main() {
    char key[30], plaintext[100], formattedText[100];
    char keyMatrix[SIZE][SIZE];
    char encryptedText[100] = "";
    int i;
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    if (removeDuplicatesAndPrepareKey(key) == 0) {
        createKeyMatrix(key, keyMatrix);
        printf("\nGenerated 5x5 Key Matrix:\n");
        printMatrix(keyMatrix);
        printf("\nEnter the plaintext: ");
        fgets(plaintext, sizeof(plaintext), stdin);
        plaintext[strcspn(plaintext, "\n")] = '\0';
        formatPlaintext(plaintext, formattedText);
        printf("\nEncrypted message: ");
        for (i = 0; i < strlen(formattedText); i += 2) {
            char pair[3] = {formattedText[i], formattedText[i + 1], '\0'};
            char encryptedPair[3];
            encryptPair(keyMatrix, pair, encryptedPair);
            strcat(encryptedText, encryptedPair);
        }
        printf("%s\n", encryptedText);
    } else {
        printf("Invalid input! Please enter a valid keyword.\n");
    }
    return 0;
}
int removeDuplicatesAndPrepareKey(char key[]) {
    int i, j, k = 0;
    int used[26] = {0};
    replaceJWithI(key);
    for (i = 0; key[i] != '\0'; ++i) {
        if (isalpha(key[i])) {
            key[i] = toupper(key[i]);
            if (!used[key[i] - 'A']) {
                key[k++] = key[i];
                used[key[i] - 'A'] = 1;
            }
        }
    }
    key[k] = '\0'; 
    return (k > 0) ? 0 : -1;
}
void createKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int used[26] = {0};
    int i, j, k = 0;
    char letter = 'A';
    for (i = 0; key[i] != '\0'; ++i) {
        if (key[i] == 'J') key[i] = 'I'; 
        used[key[i] - 'A'] = 1;
    }
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (key[k] != '\0') {
                keyMatrix[i][j] = key[k++];
            } else {
                while (used[letter - 'A'] || letter == 'J') letter++;
                keyMatrix[i][j] = letter++;
            }
        }
    }
}
void formatPlaintext(char plaintext[], char formattedText[]) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; ++i) {
        char letter = toupper(plaintext[i]);
        if (isalpha(letter)) {
            if (letter == 'J') letter = 'I'; 
            formattedText[j++] = letter;
            if (j % 2 == 1 && formattedText[j - 1] == letter) {
                formattedText[j++] = 'X'; 
            }
        }
    }
    if (j % 2 == 1) formattedText[j++] = 'X';
    formattedText[j] = '\0'; 
}
void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char keyMatrix[SIZE][SIZE], char pair[], char result[]) {
    int row1, col1, row2, col2;
    findPosition(keyMatrix, pair[0], &row1, &col1);
    findPosition(keyMatrix, pair[1], &row2, &col2);
    if (row1 == row2) {
        result[0] = keyMatrix[row1][(col1 + 1) % SIZE];
        result[1] = keyMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) { 
        result[0] = keyMatrix[(row1 + 1) % SIZE][col1];
        result[1] = keyMatrix[(row2 + 1) % SIZE][col2];
    } else { 
        result[0] = keyMatrix[row1][col2];
        result[1] = keyMatrix[row2][col1];
    }
    result[2] = '\0'; 
}
void replaceJWithI(char *text) {
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        if (toupper(text[i]) == 'J') {
            text[i] = 'I';
        }
    }
}
void printMatrix(char matrix[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

Output:
Enter the keyword: ADD

Generated 5x5 Key Matrix:
A D B C E
F G H I K
L M N O P
Q R S T U
V W X Y Z

Enter the plaintext: ARE YOU

Encrypted message: BVSWBZZYNYSZ

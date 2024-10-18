#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 100
void hill_encrypt(char *plaintext, int key[][MAX_SIZE], int key_size) {
    int i, j, k, sum;
    int len = strlen(plaintext);
    int ciphertext[MAX_SIZE] = {0};

    for (i = 0; i < len; i += key_size) {
        for (j = 0; j < key_size; j++) {
            sum = 0;
            for (k = 0; k < key_size; k++) {
                sum += key[j][k] * (plaintext[i + k] - 'a');
            }
            ciphertext[i + j] = sum % 26;
        }
    }
    printf("Encrypted ciphertext: ");
    for (i = 0; i < len; i++) {
        printf("%c", ciphertext[i] + 'a'); 
    }
    printf("\n");
}
int main() {
    char plaintext[MAX_SIZE];
    int key[MAX_SIZE][MAX_SIZE];
    int key_size, i, j;
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    key_size = 2;
    printf("Enter %dx%d key matrix for Hill cipher:\n", key_size, key_size);
    for (i = 0; i < key_size; i++) {
        for (j = 0; j < key_size; j++) {
            scanf("%d", &key[i][j]);
        }
    }
    hill_encrypt(plaintext, key, key_size);
    return 0;
}
Output:
Enter plaintext: help
Enter 2x2 key matrix for Hill cipher:
3
3
4
5
Encrypted ciphertext: hwap

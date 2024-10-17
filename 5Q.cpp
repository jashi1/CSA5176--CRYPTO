#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

// Function to check if 'a' is coprime to 26
int isCoprime(int a) {
    int gcd = 1;
    for (int i = 1; i <= a && i <= 26; i++) {
        if (a % i == 0 && 26 % i == 0) {
            gcd = i;
        }
    }
    return gcd == 1;
}

// Function to encrypt using the affine Caesar cipher
char affineEncrypt(char plaintext, int a, int b) {
    if (plaintext < 'A' || plaintext > 'Z') {
        return plaintext; // Non-alphabet characters remain unchanged
    }
    return (char)(((a * (plaintext - 'A') + b) % ALPHABET_SIZE) + 'A');
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter plaintext (uppercase A-Z): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    printf("Enter value of a (must be coprime to 26): ");
    scanf("%d", &a);

    // Check if a is coprime to 26
    if (!isCoprime(a) || a < 1 || a > 25) {
        printf("Value of a is not allowed. It must be coprime to 26 and between 1 and 25.\n");
        return 1;
    }
    printf("Enter value of b (0-25): ");
    scanf("%d", &b);
    if (b < 0 || b >= 26) {
        printf("Value of b is not allowed. It must be between 0 and 25.\n");
        return 1;
    }
    printf("Ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ciphertext = affineEncrypt(plaintext[i], a, b);
        putchar(ciphertext);
    }
    putchar('\n');
    return 0;
}

Output:
	Enter plaintext (uppercase A-Z): ADD
Enter value of a (must be coprime to 26): 1
Enter value of b (0-25): 16
Ciphertext: QTT

#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void findFactors(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            printf("Found a factor: %d\n", i);
            printf("Corresponding factor: %d\n", n / i);
            return;
        }
    }
    printf("No factors found for %d\n", n);
}

int main() {
    int n, e, plaintextBlock;

    
    printf("Enter the modulus n: ");
    scanf("%d", &n);

    printf("Enter the public key e: ");
    scanf("%d", &e);

    printf("Enter a known plaintext block: ");
    scanf("%d", &plaintextBlock);

    int commonFactor = gcd(plaintextBlock, n);
    
    if (commonFactor > 1) {
        printf("The plaintext block %d has a common factor with n: %d\n", plaintextBlock, commonFactor);
        printf("Using this common factor, we can factor n.\n");
        
        printf("Finding factors of n...\n");
        findFactors(n);
    } else {
        printf("The plaintext block %d does not have a common factor with n.\n", plaintextBlock);
    }

    return 0;
}


#include <stdio.h>
#include <math.h>

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void encryptMessage(const char *message, long long e, long long n) {
    printf("Encrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
  
        int m = message[i] - 'A'; 
        if (m >= 0 && m <= 25) {
            long long encrypted = modExp(m, e, n);
            printf("%lld ", encrypted);
        } else {
            printf("Invalid character: %c ", message[i]);
        }
    }
    printf("\n");
}

int main() {
    char message[100];
    long long e = 65537;
    long long n = 3233;  

    printf("Enter a message (uppercase letters only): ");
    scanf("%s", message);

    encryptMessage(message, e, n);

    return 0;
}


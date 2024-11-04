#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int extendedGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int modInverse(int e, int phi) {
    int x, y;
    int gcd = extendedGCD(e, phi, &x, &y);
    if (gcd != 1) {
        return -1; 
    }
    return (x % phi + phi) % phi; 
}

void findPrimes(int n, int *p, int *q) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            int j = n / i;
            
            int isPrime1 = 1, isPrime2 = 1;
            for (int k = 2; k * k <= i; k++) {
                if (i % k == 0) {
                    isPrime1 = 0;
                    break;
                }
            }
            for (int k = 2; k * k <= j; k++) {
                if (j % k == 0) {
                    isPrime2 = 0;
                    break;
                }
            }
            if (isPrime1 && isPrime2) {
                *p = i;
                *q = j;
                return;
            }
        }
    }
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;
    
    // Find the prime factors p and q
    findPrimes(n, &p, &q);
    
    if (p == 0 || q == 0) {
        printf("Failed to find prime factors of n = %d\n", n);
        return 1;
    }
    int phi = (p - 1) * (q - 1);
    
    int d = modInverse(e, phi);
    
    if (d == -1) {
        printf("No modular inverse found. d does not exist.\n");
    } else {
        printf("Public Key: (e = %d, n = %d)\n", e, n);
        printf("Private Key: (d = %d)\n", d);
        printf("Factors: p = %d, q = %d\n", p, q);
        printf("f(n) = %d\n", phi);
    }
    
    return 0;
}


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
uint32_t hash_message(const char *message) {
    uint32_t hash = 0;
    while (*message) {
        hash = (hash << 5) + *message++; 
    }
    return hash;
}
uint32_t generate_random_k() {
    return rand() % 1000 + 1; 
}
void dsa_sign(const char *message, uint32_t private_key, uint32_t p, uint32_t q, uint32_t g, uint32_t *r, uint32_t *s) {
    uint32_t k = generate_random_k();  
    uint32_t hash = hash_message(message);  
    *r = (g * k) % p; 
    *s = ((hash + private_key * (*r)) * k) % q;  

    printf("DSA Signature: (r = %u, s = %u) [Random k = %u]\n", *r, *s, k);
}
uint32_t rsa_sign(const char *message, uint32_t private_key, uint32_t n) {
    uint32_t hash = hash_message(message); 
    return (hash ^ private_key) % n; 
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    const char *message = "Hello, DSA vs RSA!";
    uint32_t private_key = 31;  // Simplified private key for both DSA and RSA
    uint32_t p = 1019;  // A prime number for DSA (used in mod operations)
    uint32_t q = 509;   // Another prime number for DSA
    uint32_t g = 2;     // Base for DSA (typically a primitive root mod p)

    uint32_t r1, s1, r2, s2;

    printf("Message: %s\n", message);

    // Generate two DSA signatures (new random 'k' for each signature)
    dsa_sign(message, private_key, p, q, g, &r1, &s1);  // First DSA signature
    dsa_sign(message, private_key, p, q, g, &r2, &s2);  // Second DSA signature (with new k)

    printf("\nComparing DSA Signatures:\n");
    printf("First Signature:  r = %u, s = %u\n", r1, s1);
    printf("Second Signature: r = %u, s = %u\n", r2, s2);

    if (r1 != r2 || s1 != s2) {
        printf("DSA: Signatures are different due to unique random 'k'.\n");
    } else {
        printf("DSA: Signatures are identical.\n");
    }

    // Simulate RSA signature generation (same signature for the same message)
    uint32_t rsa_n = 3233;  // RSA modulus (simplified)
    uint32_t rsa_signature1 = rsa_sign(message, private_key, rsa_n);
    uint32_t rsa_signature2 = rsa_sign(message, private_key, rsa_n);

    printf("\nRSA Signatures:\n");
    printf("First RSA Signature: %u\n", rsa_signature1);
    printf("Second RSA Signature: %u\n", rsa_signature2);

    if (rsa_signature1 == rsa_signature2) {
        printf("RSA: Signatures are identical for the same message.\n");
    } else {
        printf("RSA: Signatures are different.\n");
    }

    return 0;
}


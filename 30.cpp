#include <stdio.h>
#include <stdint.h>
#include <string.h>
uint64_t encrypt(uint64_t block, uint64_t key) {
    return block ^ key;
}
uint64_t CBC_MAC(uint64_t key, uint64_t block) {
    uint64_t mac = encrypt(block, key);
    return mac;
}
void attack_CBC_MAC(uint64_t key, uint64_t X) {
    uint64_t T = CBC_MAC(key, X);
    printf("T = MAC(K, X): %llu\n", T);
    uint64_t second_block = X ^ T;
    uint64_t intermediate = encrypt(X, key); 
    uint64_t final_mac = encrypt(intermediate ^ second_block, key);  

    printf("CBC-MAC for the two-block message (X || (X ? T)): %llu\n", final_mac);
}

int main() {
    uint64_t key = 0x123456789ABCDEF0;
    uint64_t X = 0x1122334455667788; 
    attack_CBC_MAC(key, X);
    return 0;
}


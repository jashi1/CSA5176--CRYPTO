#include <stdio.h>
unsigned long extract24Bits(unsigned long block, int start) {
    return (block >> (28 - start - 24)) & 0xFFFFFF; 
}
void generateSubkeys(unsigned long key, unsigned long subkeys[16]) {
    unsigned long leftHalf, rightHalf;
    leftHalf = (key >> 28) & 0xFFFFFFF;
    rightHalf = key & 0xFFFFFFF;
    for (int i = 0; i < 16; i++) {
        leftHalf = (leftHalf << 1) & 0xFFFFFFF;
        rightHalf = (rightHalf << 1) & 0xFFFFFFF;
        unsigned long left24 = extract24Bits(leftHalf, 0);  
        unsigned long right24 = extract24Bits(rightHalf, 0);
        subkeys[i] = (left24 << 24) | right24;
    }
}
int main() {
    unsigned long key = 0xAABB09182736CCDD; 
    unsigned long subkeys[16];
    generateSubkeys(key, subkeys);
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: %lX\n", i+1, subkeys[i]);
    }
    return 0;
}

OUTPUT:-
Subkey 1: 12345678ABCDEF
Subkey 2: 23456789BCDEFA
Subkey 3: 3456789ACDEFAB
Subkey 4: 456789ABDEFABC
Subkey 5: 56789ABCDEABC1
Subkey 6: 6789ABCDEABF12
Subkey 7: 789ABCDEABC234
Subkey 8: 89ABCDEABC3456
Subkey 9: 9ABCDEABC45678
Subkey 10: ABCDEABC56789A
Subkey 11: BCDEABC6789ABC
Subkey 12: CDEABC789ABCDE
Subkey 13: DEABC89ABCDEF1
Subkey 14: EABC9ABCDEFF12
Subkey 15: ABCABCDEFFF234
Subkey 16: BCDEFFFFF3456

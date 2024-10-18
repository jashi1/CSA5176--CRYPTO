#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_LEN 1000
void decryptAdditive(char ciphertext[], int key) {
    int i;
    int length = strlen(ciphertext);
    for (i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int ctChar = ciphertext[i] - base;
            int decryptedChar = (ctChar - key + 26) % 26;
            printf("%c", decryptedChar + base);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}
int main() {
    char ciphertext[MAX_TEXT_LEN];
    int i, numShifts = 10;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LEN, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    printf("\nTop possible plaintexts using all shifts:\n");
    for (i = 0; i < numShifts; i++) {
        printf("Shift %d: ", i);
        decryptAdditive(ciphertext, i);
    }
    return 0;
}
/*OUTPUT:-
Enter the ciphertext: hello
Top possible plaintexts using all shifts:
Shift 0: hello
Shift 1: gdkkn
Shift 2: fcjjm
Shift 3: ebiil
Shift 4: dahhk
Shift 5: czggj
Shift 6: byffi
Shift 7: axeeh
Shift 8: zwddg
Shift 9: yvccf/*

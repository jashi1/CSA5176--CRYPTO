#include <stdio.h>
#include <string.h>
#include <ctype.h>
void caesarCipher(char text[], int shift) {
    int i;
    char ch;

    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isupper(ch)) {
            text[i] = (ch + shift - 'A') % 26 + 'A';
        }
        else if (islower(ch)) {
            text[i] = (ch + shift - 'a') % 26 + 'a';
        }
    }
}
int main() {
    char text[100];
    int shift;
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the shift (1-25): ");
    scanf("%d", &shift);
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value! Please enter a number between 1 and 25.\n");
        return 1;
    }
    caesarCipher(text, shift);
    printf("Encrypted message: %s\n", text);
    return 0;
}


OUTPUT: -
Enter a string to encrypt: HELLO WORLD
Enter the shift (1-25): 3
Encrypted message: KHOOR ZRUOG

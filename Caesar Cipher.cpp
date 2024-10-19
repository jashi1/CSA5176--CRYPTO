#include <stdio.h>
#include <ctype.h>
void caesarCipher(char text[], int k) {
    char ch;
    int i = 0;
    while (text[i] != '\0') {
        ch = text[i];
        if (isupper(ch)) {
            text[i] = ((ch - 'A' + k) % 26) + 'A';
        }
        else if (islower(ch)) {
            text[i] = ((ch - 'a' + k) % 26) + 'a';
        }
        i++;
    }
}
int main() {
    char text[100];
    int k;
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift value (1-25): ");
    scanf("%d", &k);
    caesarCipher(text, k);
    printf("Encrypted message: %s\n", text);
    return 0;
}


OUTPUT:-
Enter a message: WELCOME TO MY SESSION
Enter shift value (1-25): 3
Encrypted message: ZHOFRPH WR PB VHVVLRQ

#include <stdio.h>
#include <string.h>
#include <ctype.h>
void substitutionCipher(char text[], char key[]) {
    int i;
    char ch;
    char cipher[26];
    for (i = 0; i < 26; ++i) {
        cipher[i] = tolower(key[i]);  
    }
    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isupper(ch)) {
            text[i] = toupper(cipher[ch - 'A']); 
        }
        else if (islower(ch)) {
            text[i] = cipher[ch - 'a'];  
        }
    }
}
int main() {
    char text[100];
    char key[] = "QWERTYUIOPLKJHGFDSAZXCVBNM"; 
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    substitutionCipher(text, key);
    printf("Encrypted message: %s\n", text);
    return 0;
}

output:
Enter a string to encrypt: keyword
Encrypted message: ltnvgsr

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void createSubstitutionAlphabet(const char *keyword, char *substitution) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char c = toupper(keyword[i]);
        if (isalpha(c) && !used[c - 'A']) {
            substitution[index++] = c;
            used[c - 'A'] = 1;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            substitution[index++] = c;
        }
    }
    substitution[index] = '\0'; 
}

int main() {
    char keyword[100];
    char substitution[ALPHABET_SIZE + 1];

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0; 

    createSubstitutionAlphabet(keyword, substitution);

    printf("Substitution alphabet: %s\n", substitution);

    return 0;
}

Output:
	Enter the keyword: ADD
Substitution alphabet: ADBCEFGHIJKLMNOPQRSTUVWXYZ

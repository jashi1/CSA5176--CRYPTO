#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 256

// Function to perform frequency analysis
void frequencyAnalysis(char *ciphertext, int *freq) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) { // Check if character is printable
            freq[(unsigned char)ciphertext[i]]++;
        }
    }
}

// Function to find the most frequent character
void findMostFrequent(int *freq, char *mostFreq, int *maxFreq) {
    *maxFreq = 0;
    *mostFreq = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > *maxFreq) {
            *maxFreq = freq[i];
            *mostFreq = (char)i;
        }
    }
}

int main() {
    char ciphertext[] = "53††305)6*‡:482)4†.J†806*48†‡(60))85;J:8*+*8†83(88)*:†46(88‡96*?;)8*†(485)5*†2:*+(496*2(3*—4)†8‡9[8*4069285;)6†8†4†1(9:48081;8*11;48†5;4†528806*81(‡9:48;(88;4(‡734;48)4†161;:18$;†?;";
    int freq[ALPHABET_SIZE] = {0};
    char mostFreqChar;
    int maxFreq;

    // Perform frequency analysis
    frequencyAnalysis(ciphertext, freq);

    // Find the most frequent character
    findMostFrequent(freq, &mostFreqChar, &maxFreq);

    printf("Most frequent character in ciphertext: '%c' with frequency: %d\n", mostFreqChar, maxFreq);
    printf("Guess: Map '%c' to 'E'\n", mostFreqChar); // Assuming we map the most frequent character to 'E'

    return 0;
}


Output:
	Most frequent character in ciphertext: '8' with frequency: 29
Guess: Map '8' to 'E'

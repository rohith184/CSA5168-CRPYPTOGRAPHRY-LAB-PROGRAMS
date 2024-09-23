#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decrypt(char *ciphertext, int shift) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                ciphertext[i] = 'A' + (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            } else {
                ciphertext[i] = 'a' + (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            }
        }
    }
}
void countLetterFrequency(char *text, int *frequency) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i])) {
                frequency[text[i] - 'A']++;
            } else {
                frequency[text[i] - 'a']++;
            }
        }
    }
}
int findShiftValue(int *frequency) {
    int maxFrequency = 0;
    int shift = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            shift = (ALPHABET_SIZE - i) % ALPHABET_SIZE;
        }
    }
    return shift;
}

int main() {
    char ciphertext[1000];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    size_t len = strlen(ciphertext);
    if (len > 0 && ciphertext[len - 1] == '\n') {
        ciphertext[len - 1] = '\0';
    }

    int letterFrequency[ALPHABET_SIZE] = {0};
    countLetterFrequency(ciphertext, letterFrequency);

    int shift = findShiftValue(letterFrequency);

    printf("Possible plaintexts in order of likelihood:\n");
    for (int i = 0; i < 10; i++) {
        char decryptedText[1000];
        strcpy(decryptedText, ciphertext);
        decrypt(decryptedText, shift);
        printf("%d. %s\n", i + 1, decryptedText);
        shift = (shift + 1) % ALPHABET_SIZE; 
    }

    return 0;
}


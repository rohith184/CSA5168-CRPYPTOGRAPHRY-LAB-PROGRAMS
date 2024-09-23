#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_RESULTS 10

const float english_frequency[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202,
    0.0609, 0.0697, 0.0015, 0.0077, 0.0402, 0.0241, 0.0675,
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276,
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007
};
void calculate_frequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[tolower(ciphertext[i]) - 'a']++;
        }
    }
}
void decrypt(const char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = 'A' + (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            } else {
                plaintext[i] = 'a' + (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
}

// Function to perform frequency analysis and display possible plaintexts
void frequency_attack(const char *ciphertext) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    // Calculate chi-square values for each possible shift
    float chi_square_values[ALPHABET_SIZE] = {0};
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        float chi_square = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int shifted_index = (i + shift) % ALPHABET_SIZE;
            chi_square += ((frequency[shifted_index] - english_frequency[i]) * 
                           (frequency[shifted_index] - english_frequency[i])) / 
                           english_frequency[i];
        }
        chi_square_values[shift] = chi_square;
    }
    printf("Top %d possible plaintexts:\n", MAX_RESULTS);
    for (int i = 0; i < MAX_RESULTS; i++) {
        char plaintext[strlen(ciphertext) + 1];
        decrypt(ciphertext, plaintext, i);
        printf("%d: %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[1000];
    strcpy(ciphertext, "WZV YJHMT"); 
    printf("Ciphertext: %s\n", ciphertext);
    
    frequency_attack(ciphertext);

    return 0;
}

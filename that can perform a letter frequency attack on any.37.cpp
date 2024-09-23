#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26 
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

float calculate_chi_square(const int *frequency, const float *expected_frequency) {
    float chi_square = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        chi_square += ((frequency[i] - expected_frequency[i]) * (frequency[i] - expected_frequency[i])) / expected_frequency[i];
    }
    return chi_square;
}

void decrypt(const char *ciphertext, char *plaintext, const int *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = toupper('a' + key[ciphertext[i] - 'A']);
            } else {
                plaintext[i] = 'a' + key[ciphertext[i] - 'a'];
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}

void frequency_attack(const char *ciphertext, int num_results) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    float chi_square_values[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int shifted_frequency[ALPHABET_SIZE] = {0};
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            shifted_frequency[j] = frequency[(j + i) % ALPHABET_SIZE];
        }
        chi_square_values[i] = calculate_chi_square(shifted_frequency, english_frequency);
    }

    int sorted_keys[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_keys[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (chi_square_values[sorted_keys[i]] > chi_square_values[sorted_keys[j]]) {
                int temp = sorted_keys[i];
                sorted_keys[i] = sorted_keys[j];
                sorted_keys[j] = temp;
            }
        }
    }

    printf("Top %d possible plaintexts:\n", num_results);
    for (int i = 0; i < num_results; i++) {
        char plaintext[strlen(ciphertext) + 1];
        decrypt(ciphertext, plaintext, sorted_keys + i);
        printf("%d. %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int num_results;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &num_results);

    frequency_attack(ciphertext, num_results);

    return 0;
}

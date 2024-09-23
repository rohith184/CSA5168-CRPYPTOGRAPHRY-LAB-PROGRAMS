#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void affine_encrypt(char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char current_char = plaintext[i];
        if (current_char >= 'A' && current_char <= 'Z') {
            ciphertext[i] = ((a * (current_char - 'A') + b) % ALPHABET_SIZE) + 'A';
        } else if (current_char >= 'a' && current_char <= 'z') {
            ciphertext[i] = ((a * (current_char - 'a') + b) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = current_char; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}

int main() {
    char plaintext[256];
    char ciphertext[256];
    int a, b;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }

    printf("Enter value for a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter value for b: ");
    scanf("%d", &b);

    affine_encrypt(plaintext, a, b, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

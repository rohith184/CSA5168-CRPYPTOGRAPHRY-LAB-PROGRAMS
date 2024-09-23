#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *plaintext, char *key) {
    int i;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            
            plaintext[i] = ((plaintext[i] - 'A' + (key[i] - 'A')) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            
            plaintext[i] = ((plaintext[i] - 'a' + (key[i] - 'A')) % 26) + 'a';
        }
    }
}

int main() {
    char plaintext[256];
    char key[256];
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    int i;
    int len = strlen(plaintext);
    int key_len = strlen(key);
    for (i = 0; i < len; i++) {
        if (plaintext[i] == '\n') {
            plaintext[i] = '\0';
            break;
        }
    }
    for (i = 0; i < key_len; i++) {
        if (key[i] == '\n') {
            key[i] = '\0';
            break;
        }
    }
    encrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

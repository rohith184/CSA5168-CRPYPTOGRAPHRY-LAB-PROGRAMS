#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes
#define KEY_SIZE 8   // Key size in bytes

void ecb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key);
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv);
void cfb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv);
void xor_blocks(uint8_t *out, const uint8_t *in1, const uint8_t *in2);

void simple_encrypt(const uint8_t *input, const uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

int main() {
    uint8_t key[KEY_SIZE + 1] = "12345678";
    uint8_t plaintext[BLOCK_SIZE * 2 + 1] = "ABCDEFGH12345678";
    uint8_t ciphertext[BLOCK_SIZE * 2];
    uint8_t decrypted[BLOCK_SIZE * 2];
    
    printf("ECB Mode:\n");
    ecb_encrypt(plaintext, ciphertext, key);
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE * 2; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n\n");

    printf("CBC Mode:\n");
    uint8_t iv[BLOCK_SIZE + 1] = "00000000";
    cbc_encrypt(plaintext, ciphertext, key, iv);
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE * 2; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n\n");

    printf("CFB Mode:\n");
    memset(ciphertext, 0, sizeof(ciphertext));
    cfb_encrypt(plaintext, ciphertext, key, iv);
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE * 2; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE * 2; i += BLOCK_SIZE) {
        simple_encrypt(plaintext + i, key, ciphertext + i);
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv) {
    uint8_t previous_block[BLOCK_SIZE];
    
    memcpy(previous_block, iv, BLOCK_SIZE);
    
    for (int i = 0; i < BLOCK_SIZE * 2; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, previous_block, ciphertext + i);
        simple_encrypt(ciphertext + i, key, ciphertext + i);
        memcpy(previous_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv) {
    uint8_t feedback[BLOCK_SIZE];
    
    memcpy(feedback, iv, BLOCK_SIZE);

    for (int i = 0; i < BLOCK_SIZE * 2; i += BLOCK_SIZE) {
        simple_encrypt(feedback, key, feedback);
        xor_blocks(plaintext + i, feedback, ciphertext + i);
        memcpy(feedback + BLOCK_SIZE - BLOCK_SIZE / 2 , ciphertext + i , BLOCK_SIZE / 2);
     }
}

void xor_blocks(uint8_t *out, const uint8_t *in1, const uint8_t *in2) {
   for (int i = 0; i < BLOCK_SIZE; ++i) {
       out[i] = in1[i] ^ in2[i];
   }
}

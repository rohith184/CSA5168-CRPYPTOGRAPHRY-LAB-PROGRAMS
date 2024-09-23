#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define AES_BLOCK_SIZE 16
void xor_blocks(unsigned char *out, const unsigned char *in1, const unsigned char *in2) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}

void aes_encrypt(const unsigned char *key, const unsigned char *input, unsigned char *output) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; 
    }
}

void cbc_mac(unsigned char *mac, const unsigned char *key, const unsigned char *message, size_t len) {
    unsigned char iv[AES_BLOCK_SIZE] = {0}; 
    unsigned char block[AES_BLOCK_SIZE];

    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        memcpy(block, message + i, AES_BLOCK_SIZE);
        xor_blocks(block, block, iv); 
        aes_encrypt(key, block, iv); k
    }
    memcpy(mac, iv, AES_BLOCK_SIZE);
}

int main() {
    unsigned char key[AES_BLOCK_SIZE + 1] = "0123456789abcdef"; 
    unsigned char message[AES_BLOCK_SIZE + 1] = "oneblockmsg1234"; 
    unsigned char mac[AES_BLOCK_SIZE];
    unsigned char new_message[2 * AES_BLOCK_SIZE];
    unsigned char new_mac[AES_BLOCK_SIZE];
    cbc_mac(mac, key, message, AES_BLOCK_SIZE);
    printf("CBC MAC for one-block message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");
    xor_blocks(new_message + AES_BLOCK_SIZE, message, mac); 
    memcpy(new_message, message, AES_BLOCK_SIZE);

    cbc_mac(new_mac, key, new_message, 2 * AES_BLOCK_SIZE);
    printf("CBC MAC for two-block message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", new_mac[i]);
    }
    printf("\n");

    return 0;
}

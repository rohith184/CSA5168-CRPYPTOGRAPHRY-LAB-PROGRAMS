#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DES_BLOCK_SIZE 8 // DES operates on 64-bit blocks
#define KEY_SIZE 8       // DES key size (64 bits)
static const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9 ,1,
    59 ,51 ,43 ,35 ,27 ,19 ,11 ,3,
    61 ,53 ,45 ,37 ,29 ,21 ,13 ,5,
    63 ,55 ,47 ,39 ,31 ,23 ,15 ,7
};
static const int IP_INV[64] = {
    40, 8 ,48 ,16 ,56 ,24 ,64 ,32 ,
    39 ,7 ,47 ,15 ,55 ,23 ,63 ,31 ,
    38 ,6 ,46 ,14 ,54 ,22 ,62 ,30 ,
    37 ,5 ,45 ,13 ,53 ,21 ,61 ,29 ,
    36 ,4 ,44 ,12 ,52 ,20 ,60 ,28 ,
    35 ,3 ,43 ,11 ,51 ,19 ,59 ,27 ,
    34 ,2 ,42 ,10 ,50 ,18 ,58 ,26 ,
    33 ,1 ,41 ,9 ,49 ,17 ,57 ,25
};
void des_encrypt(uint8_t *input_block,uint8_t *output_block,uint8_t *key);
void des_decrypt(uint8_t *input_block,uint8_t *output_block,uint8_t *key);
void initial_permutation(uint8_t *block);
void inverse_initial_permutation(uint8_t *block);

int main() {
    uint8_t key[KEY_SIZE + 1] = "12345678"; // Key with null terminator
    uint8_t plaintext[DES_BLOCK_SIZE + 1] = "ABCDEFGH"; // Plaintext with null terminator
    uint8_t ciphertext[DES_BLOCK_SIZE];
    uint8_t decryptedtext[DES_BLOCK_SIZE];

    printf("Plaintext: %s\n", plaintext);
    des_encrypt((uint8_t *)plaintext, ciphertext, (uint8_t *)key);
    
    printf("Ciphertext: ");
    for (int i =0; i < DES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    des_decrypt(ciphertext,decryptedtext,key);
    
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}

void des_encrypt(uint8_t *input_block,uint8_t *output_block,uint8_t *key) {
   initial_permutation(input_block);
   inverse_initial_permutation(input_block);
   memcpy(output_block,input_block,DES_BLOCK_SIZE);
}

void des_decrypt(uint8_t *input_block,uint8_t *output_block,uint8_t *key) {
   initial_permutation(input_block);
   inverse_initial_permutation(input_block);
   memcpy(output_block,input_block,DES_BLOCK_SIZE);
}

void initial_permutation(uint8_t *block) {
   uint8_t temp[DES_BLOCK_SIZE] = {0};
   for (int i =0; i <64; i++) {
       temp[i/8] |= ((block[(IP[i]-1)/8] >> (7 - ((IP[i]-1) %8))) &1) << (7 - (i %8));
   }
   memcpy(block,temp,DES_BLOCK_SIZE);
}

void inverse_initial_permutation(uint8_t *block) {
   uint8_t temp[DES_BLOCK_SIZE] = {0};
   for (int i =0; i <64; i++) {
       temp[i/8] |= ((block[(IP_INV[i]-1)/8] >> (7 - ((IP_INV[i]-1) %8))) &1) << (7 - (i %8));
   }
   memcpy(block,temp,DES_BLOCK_SIZE);
}

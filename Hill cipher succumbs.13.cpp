#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
#define MOD 26

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + MOD) % MOD;
}

void inverseMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int invDet = modInverse(det, MOD);
    if (invDet == -1) {
        printf("Inverse does not exist\n");
        exit(1);
    }
    inverse[0][0] = (matrix[1][1] * invDet) % MOD;
    inverse[0][1] = (-matrix[0][1] * invDet + MOD) % MOD;
    inverse[1][0] = (-matrix[1][0] * invDet + MOD) % MOD;
    inverse[1][1] = (matrix[0][0] * invDet) % MOD;
}

int charToNum(char c) {
    return c - 'A';
}

char numToChar(int num) {
    return num + 'A';
}

void decryptHill(char *ciphertext, int keyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    inverseMatrix(keyMatrix, inverse);
    
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE];
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = charToNum(ciphertext[i + j]);
        }
        
        int decryptedBlock[MATRIX_SIZE];
        for (int j = 0; j < MATRIX_SIZE; j++) {
            decryptedBlock[j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                decryptedBlock[j] += inverse[j][k] * block[k];
            }
            decryptedBlock[j] = (decryptedBlock[j] % MOD + MOD) % MOD;
        }
        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = numToChar(decryptedBlock[j]);
        }
    }
}

int main() {
    char ciphertext[] = "teja";
    
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {2, 3},
        {1, 4}
    };
    
    decryptHill(ciphertext, keyMatrix);
    printf("Decrypted text: %s\n", ciphertext);
    
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <ctype.h>
void createKeyMatrix(char key[], char matrix[5][5]) {
    int used[26] = {0};
    int k = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            if (c == 'J') c = 'I'; 
            used[c - 'A'] = 1;
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A'] && c != 'J') { 
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
}
void decryptPlayfair(char message[], char key[]) {
    char matrix[5][5];
    createKeyMatrix(key, matrix);
    char preparedMessage[100];
    int len = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        char c = toupper(message[i]);
        if (c >= 'A' && c <= 'Z') {
            preparedMessage[len++] = c;
        }
    }
    if (len % 2 != 0) {
        preparedMessage[len++] = 'X';
    }
    preparedMessage[len] = '\0';
    for (int i = 0; i < len; i += 2) {
        char c1 = preparedMessage[i];
        char c2 = preparedMessage[i + 1];
        int r1, c1_index, r2, c2_index;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (matrix[j][k] == c1) {
                    r1 = j;
                    c1_index = k;
                }
                if (matrix[j][k] == c2) {
                    r2 = j;
                    c2_index = k;
                }
            }
        }
        if (r1 == r2) {
            printf("%c%c", matrix[r1][(c1_index + 4) % 5], matrix[r2][(c2_index + 4) % 5]);
        } else if (c1_index == c2_index) { 
            printf("%c%c", matrix[(r1 + 4) % 5][c1_index], matrix[(r2 + 4) % 5][c2_index]);
        } else { 
            printf("%c%c", matrix[r1][c2_index], matrix[r2][c1_index]);
        }
    }
    printf("\n");
}
int main() {
    char message[] =
        "KXJEYUREBEZWEHEWR "
        "YTUHEYFSKREHEGOYFI "
        "WTTTUOLKSYCAJPOBOT "
        "EIZONTXBYBNTGONEYC "
        "UZWRGDSONSXBOUYWR "
        "HEBAAHYUSEDQ";
    char key[] =
        "PLAYFIREXMBCDGHKN "
        "OQSTUVWZ";
    decryptPlayfair(message, key);
    return 0;
}

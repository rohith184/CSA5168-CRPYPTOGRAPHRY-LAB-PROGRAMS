#include <stdio.h>
#include <string.h>
#include <ctype.h>
char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I'; 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char a, char b) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);
    if (row1 == row2) {
        printf("%c%c", matrix[row1][(col1 + 1) % 5], matrix[row2][(col2 + 1) % 5]);
    } else if (col1 == col2) {
        printf("%c%c", matrix[(row1 + 1) % 5][col1], matrix[(row2 + 1) % 5][col2]);
    } else {
        printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
    }
}
void prepareMessage(char message[], char preparedMessage[]) {
    int len = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            preparedMessage[len++] = toupper(message[i]);
        }
    }
    preparedMessage[len] = '\0';
    if (len % 2 != 0) {
        preparedMessage[len++] = 'X';
    }
    preparedMessage[len] = '\0';
}
void encryptMessage(char message[]) {
    char preparedMessage[100];
    prepareMessage(message, preparedMessage);

    for (int i = 0; i < strlen(preparedMessage); i += 2) {
        encryptPair(preparedMessage[i], preparedMessage[i + 1]);
    }
    printf("\n");
}
int main() {
    char message[100];
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    printf("Encrypted message: ");
    encryptMessage(message);
    return 0;
}

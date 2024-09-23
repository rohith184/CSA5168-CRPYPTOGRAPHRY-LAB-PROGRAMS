#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
char affine_encrypt(char p, int a, int b) {
    if (p >= 'a' && p <= 'z') {
        return (char) (((a * (p - 'a') + b) % 26) + 'a');
    } else if (p >= 'A' && p <= 'Z') {
        return (char) (((a * (p - 'A') + b) % 26) + 'A');
    } else {
        return p; 
    }
}
int main() {
    int a, b, i;
    char plaintext[100];
    printf("Enter value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);
    if (gcd(a, 26) != 1) {
        printf("Error: a must be coprime with 26.\n");
        return 1;
    }
    printf("Enter plaintext: ");
    scanf(" %[^\n]%*c", plaintext); 
    printf("Ciphertext: ");
    for (i = 0; plaintext[i] != '\0'; i++) {
        printf("%c", affine_encrypt(plaintext[i], a, b));
    }
    printf("\n");

    return 0;
}

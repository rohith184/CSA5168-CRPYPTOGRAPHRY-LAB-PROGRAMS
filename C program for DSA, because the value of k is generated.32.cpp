#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void ecdsa_sign(const char *message, char *signature) {
    int k = rand() % 100; 
    snprintf(signature, 100, "ECDSA_Signature(%s, k=%d)", message, k);
}


void rsa_sign(const char *message, char *signature) {
    snprintf(signature, 100, "RSA_Signature(%s)", message);
}

int main() {
    srand(time(0));
    char message[] = "Hello, this is a test message.";
    char ecdsa_signature[100];
    char rsa_signature[100];
    ecdsa_sign(message, ecdsa_signature);
    printf("First ECDSA Signature: %s\n", ecdsa_signature);

    ecdsa_sign(message, ecdsa_signature);
    printf("Second ECDSA Signature: %s\n", ecdsa_signature);

    rsa_sign(message, rsa_signature);
    printf("RSA Signature: %s\n", rsa_signature);

    return 0;
}


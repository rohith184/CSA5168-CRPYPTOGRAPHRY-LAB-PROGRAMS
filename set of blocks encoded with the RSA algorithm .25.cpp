#include <stdio.h>
#include <math.h>
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a, int m) {
    int m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}
void commonFactorAttack(int n, int e, int blocks[], int num_blocks) {
    int common_factor = 0;
    for (int i = 0; i < num_blocks; i++) {
        for (int j = i + 1; j < num_blocks; j++) {
            if (gcd(blocks[i], n) != 1 && gcd(blocks[j], n) != 1) {
                common_factor = gcd(blocks[i], n);
                break;
            }
        }
        if (common_factor) break;
    }

    if (common_factor) {
        int p = common_factor;
        int q = n / p;
        int phi = (p - 1) * (q - 1);
        int d = modInverse(e, phi);

        printf("Factors of n: p = %d, q = %d\n", p, q);
        printf("Euler's totient function phi(n) = %d\n", phi);
        printf("Private key d = %d\n", d);

        printf("Plaintext blocks: ");
        for (int i = 0; i < num_blocks; i++) {
            int plaintext = pow(blocks[i], d) - (int)(blocks[i] / pow(blocks[i], d) * n);
            printf("%d ", plaintext);
        }
        printf("\n");
    } else {
        printf("No common factor found.\n");
    }
}

int main() {
    int n = 3233; 
    int e = 17;   
    int blocks[] = {1791, 123, 2509, 1281}; 
    int num_blocks = sizeof(blocks) / sizeof(blocks[0]);

    commonFactorAttack(n, e, blocks, num_blocks);

    return 0;
}


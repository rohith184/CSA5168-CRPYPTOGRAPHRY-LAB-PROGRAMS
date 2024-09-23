#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
void findAffineKeys(int freq1, int freq2, int plain1, int plain2) {
    int a, b;
    int a_inv;
    int diff1 = (freq1 - freq2 + 26) % 26;
    int diff2 = (plain1 - plain2 + 26) % 26;
    printf("Finding possible keys...\n");
    for (a = 1; a < 26; a++) {
        if (gcd(a, 26) != 1) {
            continue; 
        }
        a_inv = modInverse(a, 26);
        if (a_inv != -1) {
            int found = 0;
            for (b = 0; b < 26; b++) {
                if ((a * (plain1 - plain2) + b) % 26 == diff1) {
                    found = 1;
                    printf("Possible key found: a = %d, b = %d\n", a, b);
                }
            }
            if (found) {
                continue;
            }
        }
    }
}
int main() {
    int mostFrequent = 1;  
    int secondMostFrequent = 20; 
    int mostFrequentPlain = 4;  
    int secondMostFrequentPlain = 19; 
    findAffineKeys(mostFrequent, secondMostFrequent, mostFrequentPlain, secondMostFrequentPlain);
    return 0;
}

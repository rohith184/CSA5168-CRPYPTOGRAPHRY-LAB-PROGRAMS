#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}
int main() {
    int keyLength = 25;
    unsigned long long totalPossibleKeys = factorial(keyLength);
    printf("Total possible keys (without considering identical encryption results): %llu\n", totalPossibleKeys);
    unsigned long long effectivelyUniqueKeys = totalPossibleKeys / keyLength;
    printf("Effectively unique keys (considering identical encryption results): %llu\n", effectivelyUniqueKeys);
    double log2TotalPossibleKeys = log2((double)totalPossibleKeys);
    double log2EffectivelyUniqueKeys = log2((double)effectivelyUniqueKeys);
    printf("Total possible keys as a power of 2: 2^%.2f\n", log2TotalPossibleKeys);
    printf("Effectively unique keys as a power of 2: 2^%.2f\n", log2EffectivelyUniqueKeys);

    return 0;
}


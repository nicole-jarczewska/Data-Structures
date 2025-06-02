#include "include/HashFunctions.hpp"

int hashMod(int key, int size){
    return key % size;
}

int fibonacci(int key, int size){
    const unsigned int F = 2654435769U; // 2^32 / 1.6180339887 stala fibonacciego
    return (key * F) % size;
}

int fibonacci2(int key, int size) {
    const uint32_t A = 2654435769u; // Knuth's constant (≈ 2^32 / φ)
    uint32_t unsigned_key = static_cast<uint32_t>(key);
    uint32_t hash = unsigned_key * A;

    int shift = 32 - __builtin_clz(static_cast<uint32_t>(size - 1));

    return static_cast<int>(hash >> (32 - shift));
}

int bitMix(int key, int size) {
    uint32_t x = static_cast<uint32_t>(key);
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return static_cast<int>(x % size);
}

int countDigits(long long n) {
    int count = 0;
    do {
        count++;
        n /= 10;
    } while (n > 0);
    return count;
}

int square(int key, int size) {
    __int128 squared = (__int128)key * key;

    // Count digits of squared number
    long long temp = squared;
    int totalDigits = 0;
    while (temp > 0) {
        totalDigits++;
        temp /= 10;
    }

    int extractDigits = 3;
    int shift = (totalDigits - extractDigits) / 2;
    if (shift < 0) shift = 0;

    // Shift divisor
    __int128 divisor = 1;
    for (int i = 0; i < shift; ++i) divisor *= 10;

    __int128 mod10 = 1;
    for (int i = 0; i < extractDigits; ++i) mod10 *= 10;

    __int128 reduced = (squared / divisor) % mod10;
    return static_cast<int>(reduced % size);
}
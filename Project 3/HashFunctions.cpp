#include "include/HashFunctions.hpp"

int hashMod(int key, int size){
    return key % size;
}

int hashMult(int key, int size){
    double A = 0.6180339887; // A constant
    return size * (key * A - int(key * A));
}

int hashCuckoo(int key, int size){
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11

#define TRUE    1
#define FALSE   0

typedef int BOOL;


/* Data will be stored in Hash Table */
typedef struct tagKeyValue{
    char* key;
    char* value;
}KeyValuePair;

/* GLOBAL Hash Table */
KeyValuePair* hashTable[TABLE_SIZE];

int HashFunction(char* key)
{
    int length;
    int i, total;

    length = strlen(key);

    total = 0;
    for (i = 0; i < length; ++i)
        total += (int) key[i];// Each character's ASCII table index will be summed-up

    // Obtain an index between [0..(TABLE_SIZE-1)]
    return (total % TABLE_SIZE);
}

BOOL DoHashingWithLinearProbing(KeyValuePair* data)
{
    int index;
    int step = 1;

    index = HashFunction(data->key);

    // Check whether the index is occupied or not
    // If it is occupied APPLY linear probing!
    // Check the next slot in a CIRCULAR FASHION!
    while (0 != hashTable[index] && step != TABLE_SIZE) {
        index = (index + 1) % TABLE_SIZE;
        ++step;
    }

    // We FOUND an empty slot
    if (0 == hashTable[index]) {
        hashTable[index] = data;
        return TRUE;
    } else // The table was FULL! We could NOT find an empty slot!
        return FALSE;
}

BOOL DoHashingWithQuadraticProbing(KeyValuePair* data)
{
    int index;
    int step = 1;
    double loadFactor = 0.0;

    index = HashFunction(data->key);
    loadFactor = (double)itemCount / TABLE_SIZE;

    // Check whether the index is occupied or not
    // If it is occupied APPLY linear probing!
    // Check the next slot in a CIRCULAR FASHION!
    while (loadFactor < 0.5 && 0 != hashTable[index]) {
        index = (index + (step * step)) % TABLE_SIZE;
        ++step;
    }

    // We FOUND an empty slot
    if (0 == hashTable[index]) {
        hashTable[index] = data;
        ++itemCount;
        return TRUE;
    } else { // The table is at least HALF FULL!
        //It means quadratic may fail to find an empty place!
        printf("Table's load factor is %lf and it is bigger than or equal to 0.5!\n", loadFactor);
        printf("Quadratic probing can not be applied while load factor is equal to or bigger than 0.5!\n");
        return FALSE;
    }
}

int main()
{

}

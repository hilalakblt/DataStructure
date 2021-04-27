#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE  11

/* This is the data that we will store in a hash table! */
typedef struct tagStudent {
    int id;
    char* name;
    char* surname;// This will be our key!
}Student;

/* This is the structure to implement separate chaining */
typedef struct tagSingleLinkedList {
    Student* data;
    struct tagSingleLinkedList* next;
}SLL;

void DoHashingWithLinearProbing(SLL** pTable, Student* pData)
{
    int index;

    index = HashFunction(pData->surname);
    pTable[index] = AddFront(pTable[index], pData);
}

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

/* SINGLE LINKED LIST RELATED FUNCTION IMPLEMENTATIONS  */

SLL* AddFront(SLL* list, Student* data)
{
    SLL* pNewItem;

    pNewItem = (SLL*) malloc(sizeof(SLL));
    if (0 == pNewItem) {
        fprintf(stderr, "Cannot Allocate memory!!!\n");
        exit(EXIT_FAILURE);
    }
    pNewItem->data = data;
    pNewItem->next = list;

    return  pNewItem;
}

int main()
{
    SLL* hashTable[TABLE_SIZE];
    //SLL** hashTable = malloc(TABLE_SIZE * sizeof(SLL*));
    int i, dataCount;

    for (i = 0; i < TABLE_SIZE; ++i)
        hashTable[i] = 0;
}

#include <stdio.h>
#include <stdlib.h>

// recordType
struct RecordType
{
    int id;
    char name;
    int order;
	
	// next pointer
    struct RecordType* next;
};

// hashType
struct HashType
{
    struct RecordType* head;
};

// compute the hash function
int hash(int x, int tableSize)
{
    return (x % tableSize);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");

    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);

        *ppData = calloc(dataSz, sizeof(struct RecordType));

        if (*ppData == NULL)
        {
            printf ("Cannot allocate memory\n");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return (dataSz);
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;

    printf ("\nRecords:\n");

    for (i = 0; i < dataSz; ++i)
    {
        printf ("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }

    printf ("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType* record, int tableSize)
{
    int index = hash(record->id, tableSize);

    if (hashTable[index].head == NULL)
    {
        hashTable[index].head = record;
    }
    else
    {
        struct RecordType* currentRecord = hashTable[index].head;

        while (currentRecord->next != NULL)
        {
            currentRecord = currentRecord->next;
        }

        currentRecord->next = record;
    }
}

// display records in the hash structure
void displayRecordsInHash(struct HashType* hashTable, int tableSize)
{
    int i;
    struct RecordType* currentRecord;

    for (i = 0; i < tableSize; ++i)
    {
        printf ("Index %d -> ", i);

        if (hashTable[i].head == NULL)
        {
            printf ("NULL\n");
        }
        else
        {
            currentRecord = hashTable[i].head;

            while (currentRecord != NULL)
            {
                printf ("%d, %c, %d -> ", currentRecord->id, currentRecord->name, currentRecord->order);
                currentRecord = currentRecord->next;
            }

            printf ("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // initialize the hash table
    int hashTableSize =11;

    struct HashType* hashTable = (struct HashType*) malloc(sizeof(struct HashType) * hashTableSize);

    for (int i = 0; i < hashTableSize; i++)
	{
        hashTable[i].head = NULL;
    }

    // insert record to hash table
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    // display thr contents of table
    displayRecordsInHash(hashTable, hashTableSize);

    free(pRecords);
    
    return (0);
}
#include <stdio.h>
#include <stdlib.h>

enum Type { EMPTY, ACTIVE, DELETED };

typedef struct _entry {
	enum Type type;
	int key;
} Entry;

typedef struct _hash_set {
	int currSize;
	int maxSize;
	Entry* arr;
} HashSet;

int isPrime(int num) {
	int i;
	for (i = 2; i * i <= num; i++) {
		if (num % i == 0)
			return 0;
	}
	return 1;
}

int nextPrime(int num) {
	while (!isPrime(num)) {
		num++;
	}
	return num;
}

Entry* initEntryList(int size) {
	Entry* entry = malloc(sizeof(Entry) * size);
	int i;
	for (i = 0; i < size; i++)
		entry[i].type = EMPTY;
	return entry;
}

HashSet* initHashSet(int size) {
	HashSet* hs = malloc(sizeof(HashSet));
	hs->arr = initEntryList(size);
	hs->currSize = 0;
	hs->maxSize = size;
	return hs;
}

void freeHashSet(HashSet* hs) {
	free(hs->arr);
	free(hs);
}

int hash(HashSet* hs, int key, int probes) {
	return ((key % hs->maxSize) + probes * probes) % hs->maxSize;
}

int find(HashSet* hs, int key) {
	int probes = 0;
	int hashVal = hash(hs, key, probes);
	while (hs->arr[hashVal].type == DELETED || (hs->arr[hashVal].type == ACTIVE && hs->arr[hashVal].key != key)) {
		probes++;
		hashVal = hash(hs, key, probes);
	}
	if (hs->arr[hashVal].type == EMPTY) {
		return 0;
	}
	return 1;
}

HashSet* insert(HashSet* hs, int key) {
	int probes = 0;
	int hashVal = hash(hs, key, probes);
	while (hs->arr[hashVal].type == ACTIVE) {
		probes++;
		hashVal = hash(hs, key, probes);
	}

	hs->arr[hashVal].type = ACTIVE;
	hs->arr[hashVal].key = key;

	hs->currSize++;

	if (hs->currSize * 2 >= hs->maxSize) {
		HashSet* old = hs;
		hs = initHashSet(nextPrime(old->maxSize * 2));
		int i;
		for (i = 0; i < old->maxSize; i++) {
			if (old->arr[i].type == ACTIVE) {
				insert(hs, old->arr[i].key);
			}
		}
		freeHashSet(old);
	}

	return hs;
}

void delete(HashSet* hs, int key) {
	int probes = 0;
	int hashVal = hash(hs, key, probes);
	while (hs->arr[hashVal].type == DELETED || (hs->arr[hashVal].type == ACTIVE && hs->arr[hashVal].key != key)) {
		probes++;
		hashVal = hash(hs, key, probes);
	}
	if (hs->arr[hashVal].type == ACTIVE) {
		hs->arr[hashVal].type = DELETED;
	}
}

int main(void) {
	HashSet* hs = initHashSet(7);
	hs = insert(hs, 190);
	hs = insert(hs, 1311);
	hs = insert(hs, 689);
	hs = insert(hs, 92);
	hs = insert(hs, 87);
	hs = insert(hs, 69);
	hs = insert(hs, 420);
	if (find(hs, 92)) puts("YES 1");
	if (!find(hs, 88)) puts("YES 2");
	if (find(hs, 689)) puts("YES 3");
	delete(hs, 689);
	delete(hs, 190);
	delete(hs, 1311);
	if (!find(hs, 689)) puts("YES 4");
	if (find(hs, 92)) puts("YES 5");
	if (!find(hs, 1311)) puts("YES 6");
	delete(hs, 92);
	if (!find(hs, 92)) puts("YES 7");
	return 0;
}

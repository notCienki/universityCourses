#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define ALPHABET_SIZE 26

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    unsigned int smallest = idx;
    unsigned int left = 2 * idx + 1;
    unsigned int right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != (unsigned int)idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct Letter {
    char c;
    int freq;
};

int compareLetters(const void* a, const void* b) {
    const struct Letter* l1 = (const struct Letter*)a;
    const struct Letter* l2 = (const struct Letter*)b;
    
    if (l1->freq != l2->freq)
        return l2->freq - l1->freq;
    return l1->c - l2->c;
}

struct MinHeapNode* buildHuffmanTree(int freq[]) {
    struct Letter letters[ALPHABET_SIZE];
    int letterCount = 0;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > 0) {
            letters[letterCount].c = 'a' + i;
            letters[letterCount].freq = freq[i];
            letterCount++;
        }
    }
    
    qsort(letters, letterCount, sizeof(struct Letter), compareLetters);
    
    struct MinHeapNode** trees = malloc(letterCount * sizeof(struct MinHeapNode*));
    int treeCount = letterCount;
    
    for (int i = 0; i < letterCount; i++) {
        trees[i] = newNode(letters[i].c, letters[i].freq);
    }
    
    while (treeCount > 1) {
        struct MinHeapNode* right = trees[treeCount - 1];
        struct MinHeapNode* left = trees[treeCount - 2];
        
        struct MinHeapNode* newTree = newNode('$', left->freq + right->freq);
        newTree->left = left;
        newTree->right = right;
        
        treeCount--;
        trees[treeCount - 1] = newTree;
        
        int j = treeCount - 1;
        while (j > 0 && trees[j]->freq > trees[j-1]->freq) {
            struct MinHeapNode* temp = trees[j];
            trees[j] = trees[j-1];
            trees[j-1] = temp;
            j--;
        }
    }
    
    struct MinHeapNode* root = trees[0];
    free(trees);
    return root;
}

void storeCodes(struct MinHeapNode* root, int arr[], int top, char* huffmanCodes[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, huffmanCodes);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffmanCodes);
    }

    if (!root->left && !root->right) {
        char* code = (char*)malloc(top + 1);
        for (int i = 0; i < top; i++) {
            code[i] = arr[i] + '0';
        }
        code[top] = '\0';
        huffmanCodes[root->data - 'a'] = code;
    }
}

int main() {
    int freq[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        scanf("%d", &freq[i]);
    }

    int n;
    scanf("%d", &n);
    if (n > 1000000) {
        return 1;
    }

    struct MinHeapNode* root = buildHuffmanTree(freq);

    char* huffmanCodes[ALPHABET_SIZE] = {NULL};
    int arr[MAX_TREE_HT], top = 0;
    
    storeCodes(root, arr, top, huffmanCodes);

    char* text = (char*)malloc((n + 1) * sizeof(char));
    scanf("%s", text);
    
    for (int i = 0; i < n; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            if (huffmanCodes[text[i] - 'a'] != NULL) {
                printf("%s", huffmanCodes[text[i] - 'a']);
            }
        }
    }
    printf("\n");

    free(text);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (huffmanCodes[i] != NULL) {
            free(huffmanCodes[i]);
        }
    }

    return 0;
}

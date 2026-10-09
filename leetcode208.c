
#include <stdlib.h>
#include <stdbool.h>

typedef struct TrieNode {
    struct TrieNode* children[26];
    bool isEnd;
} TrieNode;

typedef struct {
    TrieNode* root;
} Trie;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)calloc(1, sizeof(TrieNode));
    return node;
}

Trie* trieCreate() {
    Trie* obj = (Trie*)malloc(sizeof(Trie));
    obj->root = createNode();
    return obj;
}

void trieInsert(Trie* obj, char* word) {
    TrieNode* curr = obj->root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (curr->children[index] == NULL) {
            curr->children[index] = createNode();
        }

        curr = curr->children[index];
    }

    curr->isEnd = true;
}

bool trieSearch(Trie* obj, char* word) {
    TrieNode* curr = obj->root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (curr->children[index] == NULL) {
            return false;
        }

        curr = curr->children[index];
    }

    return curr->isEnd;
}

bool trieStartsWith(Trie* obj, char* prefix) {
    TrieNode* curr = obj->root;

    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';

        if (curr->children[index] == NULL) {
            return false;
        }

        curr = curr->children[index];
    }

    return true;
}

void freeNode(TrieNode* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        freeNode(node->children[i]);
    }

    free(node);
}

void trieFree(Trie* obj) {
    if (obj == NULL) {
        return;
    }

    freeNode(obj->root);
    free(obj);
}

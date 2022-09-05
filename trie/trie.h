#ifndef __TRIE_NODE_H__
#define __TRIE_NODE_H__

typedef struct _TrieNode *TrieNode;

// Crea y devulve un nodo de tipo trie
TrieNode createTrieNode();

// Inserta un string en el trie
void insertTrie(TrieNode root, char* s);

// Verifica si el string está en el trie o no
char checkPresent(TrieNode root, char* key);

// Destruye el trie
void destroyTrie(TrieNode root);

#endif
#ifndef __TRIE_NODE_H__
#define __TRIE_NODE_H__

typedef struct _TrieNode *TrieNode;

//TODO: cambiar nombre en todas las funciones para que empiecen con trie_...

// Crea y devulve un nodo de tipo trie
TrieNode trie_createNode();

// Inserta un string en el trie
void trie_insert(TrieNode root, char* s);

// Verifica si el string está en el trie o no
int trie_checkPresent(TrieNode root, char* key);

// Destruye el trie
void trie_destroy(TrieNode root);

#endif
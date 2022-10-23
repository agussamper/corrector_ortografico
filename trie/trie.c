#include "trie.h"

#include <stdlib.h>

// Estructura de un Trie Node
struct _TrieNode { 
  // Store address of a character
  struct _TrieNode* trie[26];

  // isEnd sirve para comprobar si
  // el nodo representa el ultimo caracter
  // un string o no
  char isEnd;
};
 
TrieNode createTrieNode() {
	TrieNode trie = malloc(sizeof(struct _TrieNode));
  for (int i = 0; i < 26; i++) { 
    trie->trie[i] = NULL;
  }
  trie->isEnd = 0;
	return trie;
}

void insertTrie(TrieNode root, char* s) {
  TrieNode temp = root;
  
  for (int i = 0; s[i] != '\0'; i++) {
    if (temp->trie[s[i]-'a'] == NULL) 
      temp->trie[s[i]-'a'] = createTrieNode();
      
    temp = temp->trie[s[i]-'a'];
  }

  // Marca el ultimo caracter del
  // string a true
  temp->isEnd = 1;
}
 
char checkPresent(TrieNode root, char* key) {

  for (int i = 0; key[i] != '\0'; i++) {
 
    // Si el caracter actual no esta
    // presente en el trie
    if (root->trie[key[i]-'a'] == NULL)
        return 0;
 
    root = root->trie[key[i]-'a'];
	}
  if (root->isEnd == 1)
      return 1;
 
  return 0;
}

void aux_destroyTrie(TrieNode root) {
  if (root == NULL)
    return;
  for (int i = 0; i < 26; i++) {
    if (root->trie[i] != NULL) {
      aux_destroyTrie(root->trie[i]);
      free(root->trie[i]);
    }
  }
}

void destroyTrie(TrieNode root) {
  aux_destroyTrie(root);
  free(root);
}
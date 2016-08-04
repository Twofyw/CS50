/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */


#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

typedef struct node
{
    bool isWord;
    struct node* children[27];
}
node;

node* root;
void unloadNode(node* cnode);
unsigned int count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* cnode = root;
    for (int i = 0, l = strlen(word); i < l; i++) {
        int idx;
        if (word[i] == '\'') {
            idx = 26;
        } else {
            idx = tolower(word[i]) - 97;
        }
        
        if (cnode->children[idx] != NULL)
        {
        cnode = cnode->children[idx];
        }
        else
        {
            return false;
        }
    }
    if (cnode->isWord == true) {
        return true;
    } else {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    root = calloc(1, sizeof(node));
    
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL) {
        printf("Dictionary missing\n");
        return false;
    }

    char word[LENGTH + 1];
    
    // + 2 = "\n" + "\0"
    for (fgets(word, LENGTH + 2, fp); feof(fp) == 0; fgets(word, LENGTH + 2, fp)) {
        node* cnode = root;
        
        // - 1 = - "\n"
        for (int i = 0,l = strlen(word) - 1; i < l; i++) {
            int idx;
            if (word[i] == '\'') {
                idx = 26;
            } else {
                idx = word[i] - 97;
            }
            
            if (cnode->children[idx] == NULL) {
                cnode->children[idx] = calloc(1, sizeof(node));
            }
            cnode = cnode->children[idx];
        }
        cnode->isWord = true;
        count++;
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unloadNode(root);
    return true;
}

void unloadNode(node* cnode) {
    if (cnode->isWord == false) {
        for (int i = 0; i < 27; i++) {
            if (cnode->children[i] != NULL) {
                unloadNode(cnode->children[i]);
            }
        }
    }
    free(cnode);
}
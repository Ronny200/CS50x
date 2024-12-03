// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads ` into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // 打开字典
    FILE *source = fopen(dictionary, 'r');
    if (source == NULL)
    {
        return false;
    }

    // 读取字典单词
    unsigned int head;
    char *word = malloc(siezeof(LENGTH + 1));
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return false;
    }

    while(fcanf(source, "%s", word) != EOF)
    {
        head = hash(word);
        strcpy(new_node->word, word);
        if (table[head] == NULL)
        {
            new_node->next = NULL;
            table[head]->next = new_node;
            continue;
        }
        new_node->next = table[head]->next;
        table[head]->next = new_node;
    }

    //释放
    fclose(source);
    free(word);
    free(new_node);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

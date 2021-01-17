#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define NUM_LETTERS ((int)26)

typedef struct node
{
    char letter;
    long unsigned int count;
    struct node *children[NUM_LETTERS];
    bool EOW;
} node;

node *new_node(char C);
node *Trie();
void insert(node *head, char *word);
void initTrie(node *head);
void print(node *root, char *word);
void print_r(node *root, char *word);

node *Trie()
{
    node *Node = (node *)malloc(sizeof(node));
    if (Node == NULL)
    {
        return NULL;
    }
    Node->count = 0;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        Node->children[i] = NULL;
    }
    return Node;
}

node *new_node(char C)
{
    node *Node = (node *)malloc(sizeof(node));
    if (Node == NULL)
    {
        return NULL;
    }
    Node->letter = C;
    Node->count = 0;
    Node->EOW = false;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        Node->children[i] = NULL;
    }
    return Node;
}

void insert(node *head, char *word)
{
    node *temp = head;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (temp->children[word[i] - 'a'] == NULL)
        {
            temp->children[word[i] - 'a'] = new_node(word[i]);
        }
        temp = temp->children[word[i] - 'a'];
    }
    temp->EOW = true;
    temp->count++;
}

void initTrie(node *head)
{
    char c = getc(stdin);
    char *word;
    word = (char *)malloc(sizeof(char));
    while (c != EOF)
    {
        if (isalpha(c))
        {
            c = tolower(c);
            int len = strlen(word);
            word = (char *)realloc(word, (len + 2) * sizeof(char));
            word[len] = c;
            word[len + 1] = '\0';
        }
        if (c == ' ' || c == '\t' || c == '\n')
        {
            insert(head, word);
            free(word);
            word = (char *)malloc(sizeof(char));
        }
        c = getc(stdin);
    }
    free(word);
}

void print(node *root, char *word)
{
    char *str;
    if (root == NULL)
    {
        return;
    }
    if (root->EOW)
    {
        printf("%s %lu\n", word, root->count);
    }
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        str = (char *)malloc(strlen(word) + 2);
        strcpy(str,word);
        str[strlen(word)] = ('a' + i);
        str[strlen(word) + 1] = '\0';
        print(root->children[i], str);
        free(str);
    }
    free(root);
}

void print_r(node *root, char *word)
{
    char *str;
    if (root == NULL)
    {
        return;
    }
    if (root->EOW)
    {
        printf("%s %lu\n", word, root->count);
    }
    for (int i = NUM_LETTERS-1; i >= 0; i--)
    {
        str = (char *)malloc(strlen(word) + 2);
        strcpy(str,word);
        str[strlen(word)] = ('a' + i);
        str[strlen(word) + 1] = '\0';
        print_r(root->children[i], str);
        free(str);
    }
    free(root);
}

int main(int argc, char *argv[])
{
    node *root = Trie();
    initTrie(root);
    char *word = (char *)malloc(sizeof(char));
    if (argc == 2 && *argv[1] == 'r')
    {
        print_r(root, word);
    }
    else
    {
        print(root, word);
    }
    free(word);
}
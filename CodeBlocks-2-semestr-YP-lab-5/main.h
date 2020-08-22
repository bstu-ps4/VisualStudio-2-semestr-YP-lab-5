#ifndef _MAIN_H_
    #define _MAIN_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct LIST
    {
        struct LIST* next;
        char symbol;
        int counter;
    };

    struct ArrayElement
    {
        char symbol;
        int counter;
        char* code;
    };

    struct NodeTree
    {
        struct NodeTree* top;
        struct NodeTree* left;
        struct NodeTree* right;
        char symbol;
        int counter;
        char* code;
    };

    struct NodeTree* createTree(char symbol, int counter, char* code);
    void addingTree(struct NodeTree* node, char symbol, int counter, char* code);
    void Shannon_Fano(
        struct NodeTree* node,
        struct ArrayElement* array,
        int end,
        int start,
        char* vetka,
        char* fullvetka
    );
    void list_print(struct LIST* node);
    struct LIST* list_addNode(struct LIST* node, char symbol);
    int list_length(struct LIST* node);
    struct LIST* list_clean(struct LIST* node);
    void array_print(struct ArrayElement* array, int length);
    void array_bubbleSort(struct ArrayElement* array, int length);
#endif // _MAIN_H_

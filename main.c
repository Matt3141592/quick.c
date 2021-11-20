//
//  main.c
//  quick.c
//
//  Created by Matthew Lee on 16/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int x;
    struct node *next;
}node;

node *quick(node *list);
void freelist(node *list);

int main(void)
{
    srand((int)time(0));
    int m = 1000;
    
    node *sort = NULL;
    for (int i = 0; i < m; i++)
    {
        node *n = malloc(sizeof(node));
        n -> next = sort;
        sort = n;
    }
    
    clock_t begin = clock();
    for (int j = 0; j < 100000; j++)
    {
        node *start = sort;
        
        for (int i = 0; i < m; i++)
        {
            sort -> x = (rand() & 131071);
            sort = sort -> next;
        }
        sort = quick(start);
    }
    
    printf("%f\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
    
    /*for (int i = 0; i < m; i++)
    {
        printf("%d\n", sort -> x);
        sort = sort -> next;
    }*/
    freelist(sort);
}

node *quick(node *list)
{
    if (list == NULL)
        return NULL;
    node *piv = list;
    node *smaller = NULL;
    node *larger = NULL;
    list = list -> next;
    
    // divides the list about the pivot into two lists
    while (list != NULL)
    {
        node *next = list -> next;
        if (list -> x >= piv -> x)
        {
            list -> next = larger;
            larger = list;
        }
        else
        {
            list -> next = smaller;
            smaller = list;
        }
        list = next;
    }
    
    // recursively sorts the two lists
    smaller = quick(smaller);
    larger = quick(larger);
    
    // combining the two lists and the pivot
    piv -> next = larger;
    node *temp = smaller;
    
    if (temp != NULL)
    {
        while (temp -> next != NULL)
            temp = temp -> next;
        temp -> next = piv;
    }
    else
        smaller = piv;
    return smaller;
}

// frees the memory used for the linked list
void freelist(node *list)
{
    node *prev = list;
    while (list != NULL)
    {
        list = list -> next;
        free(prev);
        prev = list;
    }
}

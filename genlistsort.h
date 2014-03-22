/**************************************************************************
 *
 * Title:          genlistsort.h
 * Description:    Header for the generic linked list sort
 * Author:         rafoid
 * Date:           3/21/2014
 * Licensed under GPL v.2
 *
 ***************************************************************************/

ifndef HDR_genlistsort_H
#define HDR_genlistsort_H

typedef struct gen_list_node
{
    struct gen_list_node *next;
    void *data;
} gen_list_node_t;

typedef struct gen_tree_node
{
    struct gen_tree_node *left;
    struct gen_tree_node *right;
    void *data;
    int size;
} gen_tree_node_t;

/*
typedef struct test_data_ptr
{
    int size;
    int area;
    int volume;
    char *name;
} tdp;

typedef struct test_list_node
{
    struct test_list_node *next;
    tdp *data;
} tl;
*/
#endif /* HDR_genlistsort_H */

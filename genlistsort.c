/**************************************************************************
 *
 * Title:          genlistsort.c
 * Description:    Implements the sorting of generic linked list using 
 *                    max-heap sort algorithm
 * Author:         rafoid
 * Date:           3/21/2014
 * Licensed under GPL v.2
 *
 ***************************************************************************/
#include <stdio.h>
#include <time.h>
#include "genlistsort.h"
#include "string.h"

/* possible scenarios:
 * 1) cur node replaces root
 * 2) cur node goes to the left
 * 3) cur node goes to the right
 */
void
add_node(gen_tree_node_t *n, gen_tree_node_t *t, int (*cmp_func)())
{
    gen_tree_node_t *c, tmp;

    while (1)
        {
        if (!t)
            break;

        t->size++;
        if ((*cmp_func)(n->data, t->data) < 0)
            {
            void *data = t->data;
            t->data = n->data;
            n->data = data;
            }

        if (t->left)
            {
            if (t->right)
                t = t->left->size < t->right->size ? t->left : t->right;
            else
                {
                t->right = n;
                break;
                }
            }
        else
            {
            t->left = n;
            break;
            }
        }
}

/* pick the root node and return it.
 * percolate data node from the smallest child all the way down to the bottom of
 * the heap
 */
void
get_node(gen_tree_node_t *n, gen_tree_node_t **t, int (*cmp_func)())
{
    gen_tree_node_t *cur_root, *left, *right, *dir, **root = t;

    cur_root = *t;
    n->data = cur_root->data;

    while (1)
        {
        if (!cur_root)
            break;

        left = cur_root->left;
        right = cur_root->right;

        if (left)
            {
            if (right)
                dir = (*cmp_func)(left->data, right->data) < 0 ? left : right;
            else
                dir = left;
            }
        else
            {
            if (right)
                dir = right;
            else
                break;
            }

        cur_root->data = dir->data;
        if (!dir->left && !dir->right)
            {
            if (dir == left)
                cur_root->left = NULL;
            else
                cur_root->right = NULL;
            }
        cur_root = dir;
        }
    t = root;
}

/* uses  min-heap sort algorithm.
 * original list is destroyed and replaced with the sorted one (least to
 * greatest order)
 */
void
sort_gen_list(void *list, void (*cmp_func))
{
    gen_list_node_t *l = list;
    gen_tree_node_t t, *mem, *root, *new_node;
    int i = 0, tree_size = 1;

    if (!l)
        return;

    /* how many elements in the list */
    while (l)
        {
        i++;
        l = l->next;
        }

    /* allocate the generic heap tree */
    mem = (gen_tree_node_t *) malloc (sizeof(gen_tree_node_t)*i);
    root = mem;

    /* add root node */
    root->left = NULL;
    root->right = NULL;
    root->data = ((gen_list_node_t *)list)->data;
    root->size = 0;

    /* add all linked list nodes to the heap tree */
    l = ((gen_list_node_t *)list)->next;
    while (l)
        {
        new_node = root+tree_size;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->data = l->data;
        new_node->size = 0;
        add_node(new_node, root, cmp_func);
        l = l->next;
        tree_size++;
        }

    /* read the nodes back into the list */
    l = list;
    while (l)
        {
        get_node(&t, &root, cmp_func);
        l->data = t.data;
        l = l->next;
        }

    free(mem);
    list = l;
}

/* Example of using the sort.
 * Just uncomment everything below, compile and run.
 * It is fully operation and also tests the sort
 */
int
compare_nodes_by_size(tdp *d1, tdp *d2)
{
    return d1->size - d2->size;
}

int
compare_nodes_by_area(tdp *d1, tdp *d2)
{
    return d1->area - d2->area;
}

int
compare_nodes_by_volume(tdp *d1, tdp *d2)
{
    return d1->volume - d2->volume;
}

int
compare_nodes_by_name(tdp *d1, tdp *d2)
{
    return strcmp(d1->name, d2->name);
}

#define LST_SZ  19

int
main(int argc, char **argv)
{
    tdp node[LST_SZ];
    tl list[LST_SZ];
    int i;
    char a, b, names[LST_SZ][3];

    srand(time(NULL));

    for (i = 0; i < LST_SZ; i++)
        {
        node[i].size = rand() % 20;
        node[i].area = rand() % 20;
        node[i].volume = rand() % 20;
        a = 97 + (rand() % 26);
        b = 97 + (rand() % 26);
        sprintf(names[i], "%c%c\0", a, b);
        node[i].name = names[i];
        list[i].data = &node[i];
        }

    for (i = 0; i < LST_SZ - 1; i++)
        list[i].next = &list[i + 1];
    list[LST_SZ - 1].next = NULL;

    printf("Original list:\n");
    for (i = 0; i<LST_SZ; i++)
        {
        printf("\t%3d, ", list[i].data->size);
        printf("%3d, ", list[i].data->area);
        printf("%3d, ", list[i].data->volume);
        printf("%3s\n", list[i].data->name);
        }

    printf("Order by size:\n\t");
    sort_gen_list(&list, (*compare_nodes_by_size));
    for (i = 0; i<LST_SZ; i++)
        printf("%d,", list[i].data->size);
    printf("\n");

    printf("Order by area:\n\t");
    sort_gen_list(&list, (*compare_nodes_by_area));
    for (i = 0; i<LST_SZ; i++)
        printf("%d,", list[i].data->area);
    printf("\n");

    printf("Order by volume:\n\t");
    sort_gen_list(&list, (*compare_nodes_by_volume));
    for (i = 0; i<LST_SZ; i++)
        printf("%d,", list[i].data->volume);

    printf("Order by name:\n\t");
    sort_gen_list(&list, (*compare_nodes_by_name));
    for (i = 0; i<LST_SZ; i++)
        printf("%s,", list[i].data->name);
    printf("\n");

    return 0;
}
*/

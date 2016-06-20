/* 
 * File:   huffman.h
 * Author: madp
 *
 * Created on May 17, 2016, 2:38 PM
 */

#ifndef HUFFMAN_H
#define	HUFFMAN_H

//Array size
#define SIZE 255

//Options to sort the array
#define ORDER_BY_CHARACTER 0
#define ORDER_BY_OCCURRENTE 1

//Constant indicating that the node is not a leaf node
#define NODE_TYPE_NON_LEAF -2

#include <stdlib.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct _huffnode huffnode;
    
    struct _huffnode{
        int character;
        int occurrence;
        huffnode* left;
        huffnode* right;
        
    };

    
    huffnode* huffnode_new(int character);
    int huffnode_delete(huffnode* node);
    
    int huffman_encode(const char* filename);
    
//    hufflist_node* hufflist_node_create();
//    hufflist* hufflist_count(const char* filename);
//    int hufflist_print(hufflist* list);

#ifdef	__cplusplus
}
#endif

#endif	/* HUFFMAN_H */


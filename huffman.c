/* 
 * File:   huffman.h
 * Author: madp
 *
 * Created on May 17, 2016, 2:38 PM
 */
#include "huffman.h"

huffnode* huffnode_new(int character){
    huffnode* node = (huffnode*) malloc(sizeof(huffnode));
    node->character = character;
    node->occurrence = 1;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

int huffnode_delete(huffnode* node){
    if(node->left)
        huffnode_delete(node->left);
    if(node->right)
        huffnode_delete(node->right);
    node->character = 0;
    node->occurrence = 0;
    free(node);
    
    return 0;
}

int huffman_print(huffnode** heap, FILE* file){
    if(heap){
        int i;
        for(i = 0; i < SIZE; i++){
            if(!heap[i])
                return EXIT_SUCCESS;
            else{
                fprintf(file, "Character: %c\n Occurrence: %d\n\n", 
                        heap[i]->character, heap[i]->occurrence);
            }
        }
    }
    return EXIT_SUCCESS;
}

int huff_count(huffnode** nodes){
    int r = 0, i;
    for (i = 0; i < SIZE; i++){
        if(!nodes[i])
            break;
        r += nodes[i]->occurrence;
    }
    return r;
}

 int huff_concat(huffnode** nodes, huffnode* least, huffnode* least2){
     int i = 0;
     
     //if you don't have two nodes there's nothing to concatenate.
     if(!least || !least2){
         fprintf(stdout, "Can't concatenate a single node.\n");
         return 0;
     }
     
     huffnode* new_node = huffnode_new(NODE_TYPE_NON_LEAF);
     new_node->occurrence = least->occurrence + least2->occurrence;
     
     //Check which node has lower occurrence and add it to left, the other one is
     //added to the right.
     if(least->occurrence > least2->occurrence){
         new_node->left = least2;
         new_node->right = least;
     } else{
         new_node->right = least;         
         new_node->left = least2;
     }
     
     while(nodes[i]){
         i++;
     }
     nodes[i] = new_node;
     
     return 0;
     
 }

huffnode* huff_get_least(huffnode** heap){
    int i, pos = 0, final = SIZE-1;
    huffnode* aux = heap[0];
    if(!heap[0]){
        fprintf(stdout, "The structure is empty, not removing anything.\n");
        return NULL;
    }
    for(i = 0; i < SIZE; i++){        
        //If array has ended.
        if (!heap[i]) {
            final = i - 1;
            break;
        } else if (heap[i]->occurrence < aux->occurrence) {
            //Get the node with least occurrence.
            aux = heap[i];
            pos = i;
        }
    }
    //After get node with least occurrence, remove it and rearrange the array.
    heap[pos] = heap[final];
    heap[final] = NULL;
    
    return aux;
}

int huffman_encode(const char* filename){
    huffnode *aux = NULL, *aux2 = NULL;
    FILE* file = fopen(filename, "r");
    if(!file){
        fprintf(stderr, "Failed to open file %s\n", filename);
        return EXIT_FAILURE;
    }
    FILE* debug = fopen("/home/madp/NetBeansProjects/huffmancode/debug.txt", "w");
    if(!debug){
        fprintf(stderr, "Failed to open debug\n");
        return EXIT_FAILURE;
    }
    
    huffnode* heap[SIZE];
    int c, i, hahaha = 0;
    
    //For some reason, if I don't do this I get a segmentation fault.
    for(i = 0; i < SIZE; i++){
        heap[i] = NULL;
    }
    
    //Read file and get the occurrence of each character.
    c = fgetc(file);    
    while(c != EOF){
        for (i = 0; i < SIZE; i++){
            if(!heap[i]){
                heap[i] = huffnode_new(c);
                break;
            } else if(heap[i]->character == c){
                heap[i]->occurrence++;
                break;
            }
        }
        c = fgetc(file);
        hahaha++;
    }
    
    huffman_print(heap, debug);    
    fprintf(debug, "\nArray total occurrences after each concatenation:\n");
    i = 0;
    //Turn nodes in a huffman tree.
    while(heap[1]){
        i++;
        aux = huff_get_least(heap);
        aux2 = huff_get_least(heap);
        huff_concat(heap, aux, aux2);
        fprintf(debug, "Count %d: %d\n", i, huff_count(heap));
    }

	fprintf(debug, "hahaha = %d\n", hahaha);
    fprintf(debug, "array = %d\n", heap[0]->occurrence);
    
    //Clean up what has been used and ends.
    for(i = 0; i < SIZE; i++){
        if(heap[i])
            huffnode_delete(heap[i]);
    }
    return EXIT_SUCCESS;
    
}

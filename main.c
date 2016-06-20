/* 
 * File:   main.c
 * Author: madp
 *
 * Created on May 17, 2016, 2:37 PM
 */

#include "huffman.h"

/*
 * 
 */
int main(int argc, char** argv) {
    huffman_encode(argv[1]);
    
    return (EXIT_SUCCESS);
}


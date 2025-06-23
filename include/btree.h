/*
** EREN TURKOGLU, 2025
** sqlite
** File description:
** btree
*/

#ifndef INCLUDED_BTREE_H
    #define INCLUDED_BTREE_H

    #include "main.h"

// Each node will correspond to one page
// Internal nodes will point to their children by storing the page number that stores the child
typedef enum { NODE_INTERNAL, NODE_LEAF } NodeType;

//Every node will store what type of node it is, whether or not it is the root node,
// and a pointer to its parent (to allow finding a node’s siblings).
/*
 * Common Node Header Layout
*/ 
extern const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
extern const uint32_t NODE_TYPE_OFFSET = 0;
extern const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
extern const uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
extern const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
extern const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
extern const uint32_t COMMON_NODE_HEADER_SIZE =
    NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

// leaf nodes need to store how many “cells” they contain. A cell is a key/value pair
/*
 * Leaf Node Header Layout
*/
extern const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
extern const uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
extern const uint32_t LEAF_NODE_HEADER_SIZE =
    COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;

// The body of a leaf node is an array of cells. Each cell is a key followed by a value (a serialized row).
/*
* Leaf Node Body Layout
*/
extern const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
extern const uint32_t LEAF_NODE_KEY_OFFSET = 0;
extern const uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;
extern const uint32_t LEAF_NODE_VALUE_OFFSET =
    LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
extern const uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
extern const uint32_t LEAF_NODE_SPACE_FOR_CELLS =
    LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;

#endif

/* -------------------------------------------------------------------------- **
**                                                                            **
** MIT License                                                                **
** Copyright (c) 2025 Eren TURKOGLU                                           **
**                                                                            **
** Permission is hereby granted, free of charge, to any person obtaining a    **
** copy of this software and associated documentation files (the "Software"), **
** to deal in the Software without restriction, including without limitation  **
** the rights to use, copy, modify, merge, publish, distribute, sublicense,   **
** and/or sell copies of the Software, and to permit persons to whom the      **
** Software is furnished to do so, subject to the following conditions:       **
**                                                                            **
** The above copyright notice and this permission notice shall be included in **
** all copies or substantial portions of the Software.                        **
**                                                                            **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    **
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    **
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        **
** DEALINGS IN THE SOFTWARE.                                                  **
**                                                                            **
** -------------------------------------------------------------------------- */

/*NEACSU ADRIAN - 314CD*/

#include "tree.h"

extern Tree* Init(unsigned char** data, unsigned int size,
 unsigned int factor, Type position, int level, Coord coord)
{
    Tree* tree = (Tree*) malloc(sizeof(Tree));

    tree->imageSize = size;
    tree->data = data;
    tree->level = level;
    tree->topRight = tree->topLeft = NULL;
    tree->botRight = tree->botLeft = NULL; 
    tree->nodeType = 0;
    tree->position = position;
    tree->coord = coord;

    if (tree->position == Root) {
        calculateRoot(tree);
    } else {
        calculateTreeNode(tree);
    }

    if (tree->mean > factor)
        tree->nodeType = 0;
    else tree->nodeType = 1;

    return tree;
}

extern Tree* verifyTree(Tree* root, unsigned char** data,
 unsigned int size, unsigned int factor, Type position, int level, Coord coord)
{
    if (root == NULL) {
        root = Init(data, size, factor, position, level, coord);
    }

    if (root->nodeType == 0) {

        Coord cor;
        cor.iStart = root->coord.iStart;
        cor.iEnd = (root->coord.iEnd+root->coord.iStart)/2;
        cor.jStart = root->coord.jStart;
        cor.jEnd = (root->coord.jEnd+root->coord.jStart)/2;
        root->topLeft = verifyTree(root->topLeft, root->data,
         root->imageSize, factor, TopLeft, root->level+1, cor);

        cor.iStart = root->coord.iStart;
        cor.iEnd = (root->coord.iEnd+root->coord.iStart)/2;
        cor.jStart = (root->coord.jEnd+root->coord.jStart)/2;
        cor.jEnd = root->coord.jEnd;
        root->topRight = verifyTree(root->topRight, root->data,
         root->imageSize, factor, TopRight, root->level+1, cor);

        cor.iStart = (root->coord.iEnd+root->coord.iStart)/2;
        cor.iEnd = root->coord.iEnd;
        cor.jStart = (root->coord.jEnd+root->coord.jStart)/2;
        cor.jEnd = root->coord.jEnd;
        root->botRight = verifyTree(root->botRight, root->data,
         root->imageSize, factor, BotRight, root->level+1, cor);

        cor.iStart = (root->coord.iEnd+root->coord.iStart)/2;
        cor.iEnd = root->coord.iEnd;
        cor.jStart = root->coord.jStart;
        cor.jEnd = (root->coord.jEnd+root->coord.jStart)/2;
        root->botLeft = verifyTree(root->botLeft, root->data,
         root->imageSize, factor, BotLeft, root->level+1, cor);
    }
    return root;
}

extern Tree* freeTree(Tree* tree)
{
    if (tree == NULL) return NULL;

    tree->topLeft = freeTree(tree->topLeft);
    tree->topRight = freeTree(tree->topRight);
    tree->botRight = freeTree(tree->botRight);
    tree->botLeft = freeTree(tree->botLeft);
    free(tree);
    return NULL;
}

extern Tree* compressRoot(Tree* root)
{
    for (int i = 0; i < root->imageSize * root->imageSize * 3; i+=3) {
        (*root->data)[i] = root->color.red;
        (*root->data)[i+1] = root->color.green;
        (*root->data)[i+2] = root->color.blue;
    }

    return root;
}

extern Tree* compressTreeNode(Tree* root)
{
    for (int i = root->coord.iStart; i < root->coord.iEnd; i++) {
        for (int j = root->coord.jStart; j < root->coord.jEnd; j+=3) {
            (*root->data)[i * root->imageSize * 3 +j] = root->color.red;
            (*root->data)[i * root->imageSize * 3+j+1] = root->color.green;
            (*root->data)[i * root->imageSize * 3 +j+2] = root->color.blue;
        }
    }
    
    return root;
}

extern Tree* calculateRoot(Tree* tree)
{
    unsigned long long red = 0, green = 0, blue = 0;
    for (int i = 0; i < tree->imageSize * tree->imageSize * 3; i+=3) {
        red += (*tree->data)[i];
        green += (*tree->data)[i+1];
        blue += (*tree->data)[i+2];
    }

    tree->color.red = red /
     (tree->imageSize * tree->imageSize);
    tree->color.green = green /
     (tree->imageSize * tree->imageSize);
    tree->color.blue = blue /
     (tree->imageSize * tree->imageSize);

    red = 0, green = 0, blue = 0;
    for (int i = 0; i < tree->imageSize * tree->imageSize * 3; i+=3) {
        red += (tree->color.red - (*tree->data)[i]) *
         (tree->color.red - (*tree->data)[i]);
        green += (tree->color.green - (*tree->data)[i+1]) *
         (tree->color.green - (*tree->data)[i+1]);
        blue += (tree->color.blue - (*tree->data)[i+2]) *
         (tree->color.blue - (*tree->data)[i+2]);
    }

    tree->mean = (red+green+blue) / 
     (tree->imageSize * tree->imageSize * 3);
    return tree;
}

extern Tree* calculateTreeNode(Tree* tree)
{   
    unsigned long long red = 0, green = 0, blue = 0;
    int size = tree->coord.iEnd-tree->coord.iStart;
    
    for (int i = tree->coord.iStart; i < tree->coord.iEnd; i++) {
        for (int j = tree->coord.jStart; j < tree->coord.jEnd; j+=3) {
            red += (*tree->data)[i * tree->imageSize * 3 + j];
            green += (*tree->data)[i * tree->imageSize * 3 + j+1];
            blue += (*tree->data)[i * tree->imageSize * 3 + j+2];
        }
    }
    
    tree->color.red = red / (size * size);
    tree->color.green = green / (size * size);
    tree->color.blue = blue / (size * size);

    red = 0, green = 0, blue = 0;
    for (int i = tree->coord.iStart; i < tree->coord.iEnd; i++) {
        for (int j = tree->coord.jStart; j < tree->coord.jEnd; j+=3) {
            int tempRed = tree->color.red -
             (*tree->data)[i * tree->imageSize * 3 +j];
            
            int tempGreen = tree->color.green -
             (*tree->data)[i * tree->imageSize * 3 +j+1];

            int tempBlue = tree->color.blue -
             (*tree->data)[i * tree->imageSize * 3 +j+2];

            red += tempRed * tempRed;
            green += tempGreen * tempGreen;
            blue += tempBlue * tempBlue;
        }
    }

    tree->mean = (red + green + blue) / (size * size * 3);
    return tree;
}

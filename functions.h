/*NEACSU ADRIAN - 314CD*/

#include "queue.h"

// Functie pentru a gasi nr de frunze din arbore
int findLeaves(Tree* root)
{
    if (root == NULL) return 0;

    if (root->nodeType == 0) {
        return findLeaves(root->topLeft) +
         findLeaves(root->topRight) +
         findLeaves(root->botRight) +
         findLeaves(root->botLeft);

    } else {
        return 1;
    }
    return 0;
}

// Functie pentru gasirea nivelului maxim din arbore
void findMaxLevel(Tree* root, int* level)
{
    if (root == NULL) return;

    if (root->level > *level) *level = root->level;

    findMaxLevel(root->topLeft, level);
    findMaxLevel(root->topRight, level);
    findMaxLevel(root->botRight, level);
    findMaxLevel(root->botLeft, level);

    return;
}

// Functie pentru gasirea marimei relative maxime
void findMaxSize(Tree* root, int* leaf)
{
    if (root == NULL) return;

    if (root->level < *leaf && root->nodeType == 1) 
        *leaf = root->level;

    findMaxSize(root->topLeft, leaf);
    findMaxSize(root->topRight, leaf);
    findMaxSize(root->botRight, leaf);
    findMaxSize(root->botLeft, leaf);

    return;
}

// Functie folosita la task2 pentru printarea arborelui
void printTree(Tree* root, FILE* out)
{
    if (root == NULL) return;

    Queue* queue = createQueue();
    Tree* current;
    enqueue(queue, root);

    while(!isQueueEmpty(queue)) {
        current = front(queue);
        dequeue(queue);
        if (current != NULL) {
            if (current->nodeType == 0) {
                fwrite(&current->nodeType, 
                 sizeof(unsigned char), 1, out);
                printf("%d ", current->nodeType);
            } else {
                    printf("{");
                    fwrite(&current->nodeType, 
                     sizeof(unsigned char), 1, out);
                    fwrite(&current->color.red, 
                     sizeof(unsigned char), 1, out);
                    fwrite(&current->color.green, 
                     sizeof(unsigned char), 1, out);
                    fwrite(&current->color.blue, 
                     sizeof(unsigned char), 1, out);
            }
            enqueue(queue, current->topLeft);
            enqueue(queue, current->topRight);
            enqueue(queue, current->botRight);
            enqueue(queue, current->botLeft);
        }
    }
    destroyQueue(queue);
}

// creaza un nou nod in arbore
Tree* createTreeNode(unsigned char** data, int size,
 Coord coord, Type position)
{
    Tree* tree = (Tree*) malloc(sizeof(Tree));
    tree->botLeft = tree->botRight =
    tree->topLeft = tree->topRight = NULL;
    tree->coord = coord;
    tree->position = position;
    tree->data = data;
    tree->imageSize = size;

    return tree;
}

// creaza arborele cu informatile din fisierul binar
Tree* createTreeFromFile(FILE* input, unsigned char** data,
 int size, Coord coord, Type position)
{
    Tree* tree = createTreeNode(data, size, coord, position);
    Queue* queue = createQueue();
    Tree* current;
    enqueue(queue, tree);
    
    while(!isQueueEmpty(queue)) {
        current = front(queue);
        dequeue(queue);
        fread (&current->nodeType, 
         sizeof(unsigned char), 1, input);

        if (current != NULL && current->nodeType == 1) {
            fread(&current->color.red, 
             sizeof(unsigned char), 1, input);
            fread(&current->color.green,
             sizeof(unsigned char), 1, input);
            fread(&current->color.blue,
             sizeof(unsigned char), 1, input);
        }

        if (current->nodeType == 0) {
            Coord cor;

            cor.iStart = current->coord.iStart;
            cor.iEnd = (current->coord.iEnd +
             current->coord.iStart)/2;

            cor.jStart = current->coord.jStart;
            cor.jEnd = (current->coord.jEnd +
             current->coord.jStart)/2;

            current->topLeft = createTreeNode(data, size,
             cor, TopLeft);

            cor.iStart = current->coord.iStart;
            cor.iEnd = (current->coord.iEnd +
             current->coord.iStart)/2;

            cor.jStart = (current->coord.jEnd +
             current->coord.jStart)/2;
            cor.jEnd = current->coord.jEnd;

            current->topRight = createTreeNode(data, size,
             cor, TopRight);

            cor.iStart = (current->coord.iEnd +
             current->coord.iStart)/2;
            cor.iEnd = current->coord.iEnd;

            cor.jStart = (current->coord.jEnd +
             current->coord.jStart)/2;
            cor.jEnd = current->coord.jEnd;

            current->botRight = createTreeNode(data, size,
             cor, BotRight);

            cor.iStart = (current->coord.iEnd +
             current->coord.iStart)/2;
            cor.iEnd = current->coord.iEnd;

            cor.jStart = current->coord.jStart;
            cor.jEnd = (current->coord.jEnd +
             current->coord.jStart)/2;

            current->botLeft = createTreeNode(data, size,
             cor, BotLeft);

            enqueue(queue, current->topLeft);
            enqueue(queue, current->topRight);
            enqueue(queue, current->botRight);
            enqueue(queue, current->botLeft);
        }
    }

    destroyQueue(queue);
    return tree;
}

// genereaza poza cu ajutorul arborelui
void createPPM(Tree* root)
{
    if (root == NULL) return;

    if (root->nodeType == 0) {
        createPPM(root->topLeft);
        createPPM(root->topRight);
        createPPM(root->botRight);
        createPPM(root->botLeft);
    }

    if (root->nodeType == 1) {
        if (root->position == Root) {
            compressRoot(root);
        } else {
            compressTreeNode(root);
        }
    }
    return;
}

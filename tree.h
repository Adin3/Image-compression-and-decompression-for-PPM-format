/*NEACSU ADRIAN - 314CD*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// arata pozitia nodului respectiv
typedef enum Type {
    Root,
    TopLeft,
    TopRight,
    BotRight,
    BotLeft,
} Type;

// culoarea RGB atribuita nodului dupa calcularea variabilei mean
typedef struct Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Color;

// coordonate ce corespund unei sectiuni din matricea
// liniarizata unsigned char* data si atribuite unui nod
typedef struct Coord {
    unsigned int iStart;
    unsigned int iEnd;
    unsigned int jStart;
    unsigned int jEnd;
} Coord;

// Structura Arbore
// unsigned char** data - pointer la matricea liniarizata data
// unsigned int imageSize - dimensiunea absoluta a imaginii
// unsigned char nodeType - tipul nodului (0-Nod intern, 1-Nod frunza)
// unsigned long long mean - factorul care decide tipul nodului
// Color color - culoarea nodului
// Coord coord - coordonate ce corespund unui segment din matrice
// Type position - pozitia nodului
// struct Tree "-" - reprezinta copii nodului
typedef struct Tree {
unsigned char** data; 
unsigned int imageSize;
unsigned char nodeType;
unsigned long long mean;
Color color;
Coord coord;
Type position;
int level;

struct Tree *topRight;
struct Tree *topLeft;
struct Tree *botRight;
struct Tree *botLeft;
} Tree;

// Initializarea nodului
extern Tree* Init(unsigned char** data, unsigned int size,
 unsigned int factor, Type position, int level, Coord coord);

// Se verifica daca se imparte in alte 4 noduri
extern Tree* verifyTree(Tree* root, unsigned char** data, unsigned int size,
 unsigned int factor, Type position, int level, Coord coord);

// in cazul in care arborele are doar un nod
// radacina va fi compresata si imaginea va contine doar
// culoarea radacinii
extern Tree* compressRoot(Tree* root);

// nodul e compresat, si sectiunea din matrice 
// primeste culoarea nodului
extern Tree* compressTreeNode(Tree* root);

// calculeaza mean pentru radacina
extern Tree* calculateRoot(Tree* tree);

// calculeaza mean pentru nod
extern Tree* calculateTreeNode(Tree* tree);

// dealoca memoria din intregului arbore
extern Tree* freeTree(Tree* tree);

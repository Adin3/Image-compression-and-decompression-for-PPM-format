/*NEACSU ADRIAN - 314CD*/

#include "functions.h"
#define REALLY_BIG_NUMBER 10000000

int main(int argc, char **argv)
{   
    if (1 >= argc) {
        printf("Ai uitat sa pui argumente -_-");
        return -1;
    }

    if (strcmp(argv[1],"-c1") == 0) {
        int factor = atoi(argv[2]);

        // Se citesc din fisier datele
        FILE* ppmInput, *out;
        ppmInput = fopen(argv[3], "rb");
        out = fopen(argv[4], "w");

        char* imageFormat = (char*)
         malloc(10 * sizeof(char));
        fscanf(ppmInput, "%s", imageFormat);

        int imageHeight, imageWidth;
        fscanf(ppmInput, "%d %d", &imageWidth, &imageHeight);

        int maxImageColor;
        fscanf(ppmInput, "%d", &maxImageColor);
        unsigned char c;
        fread(&c, sizeof(unsigned char), 1, ppmInput);

        unsigned char* data = (unsigned char*)
         malloc(3 * imageHeight * imageWidth * sizeof(unsigned char));
        fread(data, sizeof(unsigned char),
         3 * imageHeight * imageWidth, ppmInput);
        //-----------------------------

        // Se creaza arborele
        Coord coords;
        coords.iStart = 0;
        coords.iEnd = imageHeight;
        coords.jStart = 0;
        coords.jEnd = imageWidth * 3;
        Tree* tree = Init(&data, imageHeight,
         factor, 0, 0, coords);

        tree = verifyTree(tree, tree->data,
         tree->imageSize, factor, 0, 0, coords);
        //-----------------------------

        // Cerinta1
        int nrLeaves = findLeaves(tree);
        int maxLevel = 0; findMaxLevel(tree, &maxLevel);
        int minLeaf = REALLY_BIG_NUMBER; findMaxSize(tree, &minLeaf);

        fprintf(out, "%d\n", maxLevel + 1);
        fprintf(out, "%d\n", nrLeaves);
        if (minLeaf == 0)
        fprintf(out, "%d\n", tree->imageSize);
        else
        fprintf(out, "%d\n", tree->imageSize/(2 << (minLeaf-1)));
        //-----------------------------

        // Se dealoca memoria
        fclose(ppmInput);
        fclose(out);
        free(data);
        free(imageFormat);
        tree = freeTree(tree);
        //-----------------------------

    } else if (strcmp(argv[1], "-c2") == 0) {
        int factor = atoi(argv[2]);

        // Se citesc din fisier datele
        FILE* ppmInput, *out;
        ppmInput = fopen(argv[3], "rb");
        out = fopen(argv[4], "wb");

        char* imageFormat = (char*) malloc(10 * sizeof(char));
        fscanf(ppmInput, "%s", imageFormat);

        int imageHeight, imageWidth;
        fscanf(ppmInput, "%d %d", &imageWidth, &imageHeight);

        int maxImageColor;
        fscanf(ppmInput, "%d", &maxImageColor);

        unsigned char c;
        fread(&c, sizeof(unsigned char), 1, ppmInput);

        unsigned char* data = (unsigned char*)
         malloc(3 * imageHeight * imageWidth * sizeof(unsigned char));
        fread(data, sizeof(unsigned char),
         3 * imageHeight * imageWidth, ppmInput);
        //-----------------------------

        // Se creaza arborele
        Coord coords;
        coords.iStart = 0;
        coords.iEnd = imageHeight;
        coords.jStart = 0;
        coords.jEnd = imageWidth * 3;
        Tree* tree = Init(&data, imageHeight,
         factor, 0, 0, coords);
        
        tree = verifyTree(tree, tree->data,
         tree->imageSize, factor, 0, 0, coords);
        //-----------------------------


        // Se scrie arborele in fisier
        fwrite(&tree->imageSize, sizeof(int), 1, out);
        printTree(tree, out);
        //-----------------------------

        // Se dealoca memoria
        fclose(ppmInput);
        fclose(out);
        free(data);
        free(imageFormat);
        tree = freeTree(tree);
        //-----------------------------

    } else if (strcmp(argv[1], "-d") == 0) {
        // Se citeste din fisier dimensiunea
        FILE* input, *ppm_output;
        input = fopen(argv[2], "rb");
        ppm_output = fopen(argv[3], "wb");

        int size;
        fread(&size, sizeof(int), 1, input);
        //-----------------------------

        // Se creaza arborele dupa structura din fiser
        Coord coord;
        coord.iStart = 0;
        coord.iEnd = size;
        coord.jStart = 0;
        coord.jEnd = size * 3;
        unsigned char* data = (unsigned char*)
         calloc(size * size * 3, sizeof(unsigned char));

        Tree* tree = createTreeFromFile(input, &data,
         size, coord, Root);
        //-----------------------------

        // Se creaza imaginea
        createPPM(tree); //unsigned char data se modifica
        fprintf(ppm_output, "%s\n", "P6\0");
        fprintf(ppm_output, "%d %d\n", size, size);
        fprintf(ppm_output, "%d", 255);
        unsigned char c = '\n';
        fwrite(&c, sizeof(unsigned char), 1, ppm_output);
        fwrite((*tree->data), sizeof(unsigned char),
         tree->imageSize * tree->imageSize * 3, ppm_output);
        //-----------------------------

        // Se dealoca memoria
        fclose(input);
        fclose(ppm_output);
        free(data);
        tree = freeTree(tree);
        //-----------------------------
    }
    return 0;
}

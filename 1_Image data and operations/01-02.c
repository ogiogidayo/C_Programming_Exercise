#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertToBinary(unsigned char *img, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        img[i] = (img[i] < 128) ? 0 : 255;
    }
}

int main() {
    char inputFilename[] = "cat001.pgm";
    char outputFilename[] = "catbin.pgm";

    FILE *inputFile = fopen(inputFilename, "rb");
    if (inputFile == NULL) {
        perror("file not found");
        return 1;
    }

    char format[3];
    int width, height, maxVal;
 
    fscanf(inputFile, "%s %d %d %d\n", format, &width, &height, &maxVal);

    unsigned char *img = (unsigned char *)malloc(width * height);

    fread(img, sizeof(unsigned char), width * height, inputFile);
    fclose(inputFile);

    convertToBinary(img, width, height);

    FILE *outputFile = fopen(outputFilename, "wb");
    if (outputFile == NULL) {
        perror("output file not found");
        free(img);
        return 1;
    }

    fprintf(outputFile, "P5\n%d %d\n%d\n", width, height, maxVal);
    fwrite(img, sizeof(unsigned char), width * height, outputFile);

    fclose(outputFile);
    free(img);

    return 0;
}

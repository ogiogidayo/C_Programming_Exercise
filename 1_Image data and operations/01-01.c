#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error>\n");
        return 1;
    }

    char magicNumber[3];
    int width, height, maxPixelValue;
    char line[100];

    if (!fgets(line, sizeof(line), fp) || sscanf(line, "%2s", magicNumber) != 1) {
        fprintf(stderr, "MagicNumber not found\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] != '#') {
            break;
        }
    }

    if (sscanf(line, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "width & height not found\n");
        fclose(fp);
        return 1;
    }

    if (!fgets(line, sizeof(line), fp) || sscanf(line, "%d", &maxPixelValue) != 1) {
        fprintf(stderr, "Maximum pixel value not found\n");
        fclose(fp);
        return 1;
    }

    printf("MagicNumber: %s\n", magicNumber);
    printf("Image width: %d\n", width);
    printf("Image height: %d\n", height);
    printf("Maximum pixel value: %d\n", maxPixelValue);

    fclose(fp);
    return 0;
}

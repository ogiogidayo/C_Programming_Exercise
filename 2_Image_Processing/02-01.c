#include <stdio.h>
#include <stdlib.h>

typedef struct _bitmap {
    char format;
    int width;
    int height;
    unsigned char *rmap;
    unsigned char *gmap;
    unsigned char *bmap;
} Bitmap;

Bitmap *loadPpm(char *name) {
    FILE *file = fopen(name, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    Bitmap *bmp = (Bitmap *)malloc(sizeof(Bitmap));
    if (bmp == NULL) {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }

    fscanf(file, "P%c\n", &bmp->format);
    int ch;
    while ((ch = fgetc(file)) == '#') {
        while (fgetc(file) != '\n');
    }
    ungetc(ch, file);
    fscanf(file, "%d %d\n", &bmp->width, &bmp->height);

    int imageSize = bmp->width * bmp->height * 3;
    bmp->rmap = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
    bmp->gmap = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
    bmp->bmap = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
    if (bmp->rmap == NULL || bmp->gmap == NULL || bmp->bmap == NULL) {
        printf("Error allocating memory.\n");
        free(bmp->rmap);
        free(bmp->gmap);
        free(bmp->bmap);
        free(bmp);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < imageSize; i++) {
        fread(&bmp->rmap[i], 1, 1, file);
        fread(&bmp->gmap[i], 1, 1, file);
        fread(&bmp->bmap[i], 1, 1, file);
    }

    fclose(file);
    return bmp;
}

void savePpm(char *name, Bitmap *bmp) {
    FILE *file = fopen(name, "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "P%c\n", bmp->format);
    fprintf(file, "# comment\n");
    fprintf(file, "%u %u\n", bmp->width, bmp->height);

    int imageSize = bmp->width * bmp->height * 3;
    for (int i = 0; i < imageSize; i++) {
        fwrite(&bmp->rmap[i], 1, 1, file);
        fwrite(&bmp->gmap[i], 1, 1, file);
        fwrite(&bmp->bmap[i], 1, 1, file);
    }

    fclose(file);
}

int main(void) {
    Bitmap *bmp;
    bmp = loadPpm("cat001.ppm");
    if (bmp == NULL) {
        printf("Failed to load PPM file.\n");
        return 1;
    }

    savePpm("catout.ppm", bmp);

    free(bmp->rmap);
    free(bmp->gmap);
    free(bmp->bmap);
    free(bmp);

    return 0;
}
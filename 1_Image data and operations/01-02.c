#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp_i, *fp_o;
    char *input_file = "cat001.pgm";
    char *output_file = "catbin.pgm";
    char head1[255], head2[255];
    int w, h, mpv, i;

    if ((fp_i = fopen(input_file, "rb")) == NULL)
    {
        printf("Cannot open", input_file);
        exit(1);
    }

    if (fgets(head1, 255, fp_i) == NULL || fgets(head2, 255, fp_i) == NULL ||
        fscanf(fp_i, "%d %d", &w, &h) != 2 || fscanf(fp_i, "%d", &mpv) != 1) 
    {
        printf("ERROR\n");
        fclose(fp_i);
        exit(1);
    }

    int v = w * h;
    unsigned char *imageData = (unsigned char *)malloc(v * sizeof(unsigned char));
    if (imageData == NULL) 
    {
        printf("ERROR\n");
        fclose(fp_i);
        exit(1);
    }

    if (fread(imageData, sizeof(unsigned char), v, fp_i) != v) 
    {
        printf("ERROR!3\n");
        fclose(fp_i);
        free(imageData);
        exit(1);
    }

    for (i = 0; i < v; i++)
     {
        if (imageData[i] < 128) 
        {
            imageData[i] = 0;
        } 
        else 
        {
            imageData[i] = 255;
        }
    }

    if ((fp_o = fopen(output_file, "wb")) == NULL) 
    {
        printf("Cannot open the outputfile!\n", output_file);
        fclose(fp_i);
        free(imageData);
        exit(1);
    }

    fprintf(fp_o, "%s%s", head1, head2);
    fprintf(fp_o, "%d %d\n", w, h);
    fprintf(fp_o, "%d\n", mpv);

    if (fwrite(imageData, sizeof(unsigned char), v, fp_o) != v) 
    {
        printf("ERROR!4\n");
    }

    fclose(fp_i);
    fclose(fp_o);
    free(imageData);

    return 0;
}

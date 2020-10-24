/*********************************************************************************
 * Christopher Medlin
 * Program 07
 *
 * Provides several image manipulation tools for images stored as ASCII text.
 *
 * Alternative description: ImageMagick but bad
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Image {
    int* pixels;
    int size;
} Image;

/*
 * Used for abstracting pointer arithmetic. 
 *
 * If row and col are within the bounds of the image (less than size), then
 * return the pixel at (row, col). Otherwise, return 0 (this comes in handy in
 * the remove red eye operation, as we might end up checking pixels out of
 * bounds)
 */
int getPixel(Image *img, int row, int col) {
    int size = img->size;

    if (row >= size || col >= size || row < 0 || col < 0) {
        return 0;
    }
    return *(img->pixels + size*row + col);
}

/*
 * Same as getPixel for but manipulating the pixel at (row, col)
 */
void setPixel(Image *img, int row, int col, int val) {
    int size = img->size;

    if (row < size && col < size && row >= 0 && col >= 0) {
        *(img->pixels + size*row + col) = val; 
    }
}

/*
 * Changes every white pixel to a black pixel and every black pixel to a white
 * pixel.
 */
void invert(Image *img) {
    int i = 0, j = 0;

    for (i; i < img->size; i++) {
        for (j = 0; j < img->size; j++) {
            setPixel(img, i, j, !getPixel(img, i, j));
        }
    }
}

/*
 * If dir is 'V', flip the image across a vertical axis. Otherwise, flip it
 * horizontally.
 */
void flip(Image *img, char dir) {
    int i = 0, j = 0;
    int tmp;

    for (i; i < img->size; i++) {
        for (j = 0; j < img->size / 2; j++) {
            if (dir == 'V') {
                tmp = getPixel(img, i, j);
                   setPixel(img, i, j, getPixel(img, i, img->size - j));
                setPixel(img, i, img->size - j, tmp);
            } else {
                tmp = getPixel(img, j, i);
                setPixel(img, j, i, getPixel(img, img->size - j, i));
                setPixel(img, img->size - j, i, tmp);
            }
        }
    }
}

/*
 * Returns 1 if the pixel at the specified row and column is a black pixel
 * surrounded by white pixels; 0 otherwise.
 */
int isRedEye(Image *img, int row, int col) {
    int i = row - 1, j = col - 1;

    // iterate through the 3x3 region surrounding the pixel at (col, row) and
    // check for any black pixel that isn't (col, row) itself
    for (i; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++) {
            if (getPixel(img, i, j) && (i != row || j != col)) {
                return 0;
            }
        }
    }
    
    // for the function to return true, (col, row) must be black
    return getPixel(img, row, col);
}

/*
 * Removes any black pixel surrounded by white pixels from the given image
 */
void rmRedEye(Image *img) {
    int i = 0, j = 0;

    for (i; i < img->size; i++) {
        for (j = 0; j < img->size; j++) {
            if (isRedEye(img, i, j)) {
                setPixel(img, i, j, 0);
            }
        }
    }
}

/*
 * Prints each pixel in the image as '*' or ' '.
 */
void printImage(Image *img) {
    int i = 0, j = 0;

    for (i; i < img->size; i++) {
        for (j = 0; j < img->size; j++) {
            printf("%c", getPixel(img, i, j) ? '*' : ' ');
        }
        printf("\n");
    }
}

/*
 * Safely parses the size found at the start of the file, returning -1 if an
 * invalid integer is found. Otherwise, the size is returned.
 */
int getSize() {
    char numString[9];
    char **end;

    if (!fgets(numString, 9, stdin)) return -1;
    return strtol(numString, end, 10);
} 

int main(int argc, char *argv[]) {
    int i = 0, j = 0;
    char c;
    Image img;

    img.size = getSize();
    if (!img.size) return 1;

    // allocate pixels
    img.pixels = (int*) malloc(sizeof(int) * img.size * img.size);

    for (i = 0; i < img.size; i++) {
        // size + 1 to count the newlines at the end of each row
        for (j = 0; j <= img.size; j++) {
            c = getchar();

            switch (c) {
                case '*':
                    setPixel(&img, i, j, 1);
                    break;
                case ' ':
                    setPixel(&img, i, j, 0);
                    break;
                case '\n':
                    break;
                default:
                    return 1;
            }
        }
    }

    // if EOF has not been reached yet, then the file is bigger than the size,
    // and is improperly formatted
    if (getchar() != EOF) {
        return 1;
    }

    // start at 1 to ignore program name
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "inv")) {
            invert(&img);
        } else if (!strcmp(argv[i], "flip")) {
            // to avoid accessing memory outside of argv
            if (i < argc - 1) {
                i++;
                if (!strcasecmp(argv[i], "V")) {
                    flip(&img, 'V');                   
                } else if (!strcasecmp(argv[i], "H")) {
                    flip(&img, 'H');
                } else {
                    return 1;
                }
            } else {
                return 1;
            }
        } else if (!strcmp(argv[i], "redeye")) {
            rmRedEye(&img);
        } else if (argv[i][0] == '<') {
            break;
        } else {
            return 1;
        }
    }

    printImage(&img);
    free(img.pixels);
    return 0;
}

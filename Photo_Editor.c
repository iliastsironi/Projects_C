/* Compile with 
 gcc -Wall -g hw3a.c -o hw3a -lhw3 -L. 
*/
/* Ilias Tsironis. 11/01/2018
 * Photoshop program that can change grayscale, luminocity, print and save an image */

#include "hw3a.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function that prints the image
void print_image (int height, int width, int max_size, pixelT array[IMG_SIZE][IMG_SIZE]) {
	
	int i, k;
	
	printf("\n");
	for(i = 0; i < 20; i++) {
		printf("=");
		if (i == 9) {
			printf(" IMAGE ");
		}
	}
	printf("\n");
	printf("%d %d %d\n", width, height, max_size);
	
	for (i = 0; i < height; i++) {
		for (k = 0; k < width; k++) {
			printf("%d ", array[i][k].red);
			printf("%d ", array[i][k].green);
			printf("%d ", array[i][k].blue);
		}
		printf("\n");
	}
	
	for (i = 0; i < 27; i++) {
		printf("=");
	}
	printf("\n\n");
	printf("\n#\n");
}

// Function that change luminocity 
void luminocity (pixelT array[][IMG_SIZE], int width, int height, int maxsizeRGB, float variation) {
	
	int i, k;
	int red, green, blue;
	
	for (i = 0; i < height; i++) {
		for (k = 0; k < width; k++) {
			red = array[i][k].red * variation;
			green = array[i][k].green * variation;
			blue = array[i][k].blue * variation;
			if (red > maxsizeRGB ) {
				red = maxsizeRGB;
			}
			if (green > maxsizeRGB ) {
				green = maxsizeRGB;
			}
			if (blue > maxsizeRGB ) {
				blue = maxsizeRGB;
			}
			array[i][k].red = red;
			array[i][k].green = green;
			array[i][k].blue = blue;
		}
	}
}

// Function that convert the image to black & white
void grayscale (pixelT array[][IMG_SIZE], int width, int height) {
	
	int i, k;
	float gray;
	
	for (i = 0; i < height; i++) {
		for (k = 0; k < width; k++) {
			gray = (array[i][k].red * 0.3) + (array[i][k].green * 0.59) + (array[i][k].blue * 0.11);
			array[i][k].red = gray;
			array[i][k].green = gray;
			array[i][k].blue = gray;
		}
	}
}

// Function that duplicates the pixel of the image
int duplicate (pixelT array[][IMG_SIZE], int *widthP, int *heightP) {
	
	int i, k;
	int height, width;
	height = *heightP;
	width = *widthP;
	
	if ( (2 * height > IMG_SIZE) || (2 * (height + 1) > IMG_SIZE) || (2 * width > IMG_SIZE)
		|| (2 * (width + 1) > IMG_SIZE)) {
		return 0;
	}
	for ( i = height - 1; i > -1; i--) {
		for( k = width - 1; k > -1; k--) {
			array[2 * i][2 * k].red = array[i][k].red;
			array[2 * i][2 * k].green = array[i][k].green;
			array[2 * i][2 * k].blue = array[i][k].blue;
			
			array[(2*i) + 1][2 * k].red = array[i][k].red;
			array[(2*i) + 1][2 * k].green = array[i][k].green;
			array[(2*i) + 1][2 * k].blue = array[i][k].blue;
			
			array[2 * i][(2*k) + 1].red = array[i][k].red;
			array[2 * i][(2*k) + 1].green = array[i][k].green;
			array[2 * i][(2*k) + 1].blue = array[i][k].blue;
			
			array[(2*i) + 1][(2*k) + 1].red = array[i][k].red;
			array[(2*i) + 1][(2*k) + 1].green = array[i][k].green;
			array[(2*i) + 1][(2*k) + 1].blue = array[i][k].blue;
		}
	}
	*heightP = 2 * height;
	*widthP = 2 * width;
	return 1;
}

// Function that rotate the image at 90 degrees
void rotation (pixelT array[][IMG_SIZE], int *width, int *height) {
	
	int i, j;
	int swap;
	pixelT swap_array[IMG_SIZE][IMG_SIZE];
	
	for (i = 0; i < *height; i++) {
		for (j = 0; j < *width; j++) {
			swap_array[i][j] = array[i][j];
		}
	}
	
	swap = *height;
	*height = *width;
	*width = swap;
	
	for(i = 0; i < *height; i++) {
		for(j = 0; j < *width; j++) {
			array[i][j] = swap_array[*width - 1 - j][i]; 
		}
	}
	
}

int main (int argc, char *argv[]) {
	
	int height, width, max_size, loop;
	char choice;
	char file_path[PATH_SIZE], save_path[PATH_SIZE] = {};
	int *heightP, *widthP, *maxsizeP;
	int load_return, save_return, dupl_return;
	float variation;
	pixelT pixel_image[IMG_SIZE][IMG_SIZE];
	

	heightP = &height;
	widthP = &width;
	maxsizeP = &max_size;
	
	do {
		printf("Enter image path: ");
		fgets(file_path, PATH_SIZE, stdin);
		scanf("%d %d %d", widthP, heightP, maxsizeP);
		
		for (loop = 0; loop < PATH_SIZE; loop++) {
			if (file_path[loop] == '\n') {
				file_path[loop] = '\0';
			}
		}
		load_return = load_image(file_path, pixel_image, widthP, heightP, maxsizeP);
		
		if (load_return == 0) {
			printf("\nInvalid path!\n");
		}
	} while (load_return != 1);
	printf("\nLoad OK!");
	
	printf("\n#\n");
	
//	print_image(height, width, max_size, pixel_image);
	
	do {
		printf("\nEnter option:\n");
		printf("\tPrint image to screen: (P/p)\n");
		printf("\tLoad another image: (L/l)\n");
		printf("\tSave image: (S/s)\n");
		printf("\tChange luminocity: (U/u)\n");
		printf("\tConvert to grayscale: (G/g)\n");
		printf("\tDuplicate size: (D/d)\n");
		printf("\tRotate: (R/r)\n");
		printf("\tQuit: (Q/q)\n");
		scanf(" %c", &choice);
		
		switch (choice) {
		
			case 'p': case 'P': {
				print_image(height, width, max_size, pixel_image);
				break;
			}
		
			case 'l': case 'L': {
				do {
					printf("\nEnter image path: ");
					fgets(file_path, PATH_SIZE, stdin);
					scanf("%d %d %d", widthP, heightP, maxsizeP);
					
					
					for (loop = 0; loop < PATH_SIZE; loop++) {
						if (file_path[loop] == '\n') {
							file_path[loop] = '\0';
						}
					}
					
					load_return = load_image(file_path, pixel_image, widthP, heightP, maxsizeP);
					if (load_return == 0) {
						printf("\nInvalid path!\n");
					}
				} while (load_return != 1);
				printf("\nLoad OK!\n");
				printf("\n#\n");
				break;
			}
		
			case 's': case 'S': {
				do {
					printf("\nEnter image path: ");
					fgets(save_path, PATH_SIZE, stdin);
					
					for (loop = 0; loop < PATH_SIZE; loop++) {
						if (save_path[loop] == '\n') {
							save_path[loop] = '\0';
						}
					}
					
					save_return = save_image(save_path, pixel_image, width, height, max_size);
					if (save_return == 0) {
						printf("\nInvalid path!\n");
					}
				} while(save_return != 1);
				printf("\nSave OK!");
				printf("\n#\n");
				break;
			}
			case 'u': case 'U': {
				do {
					printf("\nEnter luminocity factor: ");
					scanf("%f", &variation);
					
					if( variation <= 0 || variation > 2) {
						printf("\nFactor should be between (0,2]\n");
					}
				} while ((variation <= 0) || (variation > 2));
				
				luminocity(pixel_image, width, height, max_size, variation);
				printf("\nLuminocity OK!");
				printf("\n#\n");
				break;
			}
			case 'g': case'G': {
				grayscale(pixel_image, width, height);
				printf("\nGrayscale OK!");
				printf("\n#\n");
				break;
			}
			
			case 'd': case'D': {
				dupl_return = duplicate(pixel_image, widthP, heightP);
				if ( dupl_return == 1) {
					printf("\nDuplication OK!");
					printf("\n#\n");
				}
				else if ( dupl_return == 0) {
					printf("\nDuplication NOT OK!");
					printf("\n#\n");
				}
				break;
			}
			case 'r': case'R': {
				rotation(pixel_image, widthP, heightP);
				printf("\nRotation OK!");
				printf("\n#\n");
				break;
			}	
		}
	} while (choice != 'q' && choice != 'Q');
	
	return 0;
}

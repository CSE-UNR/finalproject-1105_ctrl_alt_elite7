//Authors: Jeremy Atwell and Raveena Cheema
//Due Date: 5/7/24
//Purpose: Create a program that allows the user to upload an image of any size and edit it

#include <stdio.h>

#define MAX_SIZE 500

void load_image(int image[MAX_SIZE][MAX_SIZE], int *rows, int *cols);
void display_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols);
void edit_image(int image[MAX_SIZE][MAX_SIZE], int *rows, int *cols);
void save_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols);
void crop_image(int image[MAX_SIZE][MAX_SIZE], int *rows, int *cols);
void dim_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols);
void brighten_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols);

int main() {
    int image[MAX_SIZE][MAX_SIZE];
    int rows = 0, cols = 0;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Load image\n");
        printf("2. Display image\n");
        printf("3. Edit image\n");
        printf("0. Exit\n");
        printf("Choose from one of the options above: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                load_image(image, &rows, &cols);
                break;
            case 2:
                display_image(image, rows, cols);
                break;
            case 3:
                edit_image(image, &rows, &cols);
                break;
            case 0:
                printf("\nGoodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

void load_image(int image[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    char filename[50];
    char imageArray[MAX_SIZE + 1];
    int col = 0;
    int row = 0;
    FILE *file;
    int i, j;

    printf("What is the name of the image file? ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while(fgets(imageArray, MAX_SIZE, file) != NULL){
    	int col = 0;
    	for(int i = 0; imageArray[i] != '\0'; i++){
    		 if (imageArray[i] != '\n') {
    		image[row][col] = imageArray[i] - '0';
    		col++;
    		}
    	} 
    	if(col>*cols){
    	*cols = col;
    	}
    	row++;
    }
    *rows = row;
    
    fclose(file);
    printf("Image loaded successfully.\n");
    }
    
void display_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols) {

    int i,j;
    printf("Image:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            switch (image[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf(".");
                    break;
                case 2:
                    printf("o");
                    break;
                case 3:
                    printf("O");
                    break;
                case 4:
                    printf("0");
                    break;
                default:            
                    break;
            }
        }
        printf("\n");
    }
}

void edit_image(int image[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    int choice;
    do {
        printf("\nEdit Menu:\n");
        printf("1. Crop\n");
        printf("2. Dim\n");
        printf("3. Brighten\n");
        printf("4. Save edited image\n");
        printf("5. Return to main menu\n");
        printf("Choose from one of the options above: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                crop_image(image, rows, cols);
                break;
            case 2:
                dim_image(image, *rows, *cols);
                break;
            case 3:
                brighten_image(image, *rows, *cols);
                break;
            case 4:
                save_image(image, *rows, *cols);
                break;
            case 5:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void save_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    char filename[50];
    FILE *file;
    int i, j;

    printf("Enter the filename to save the edited image: ");
    scanf("%s", filename);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d %d\n", rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(file, "%d ", image[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Edited image saved successfully.\n");
}

void crop_image(int image[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    int start_row, end_row, start_col, end_col;
    int new_rows, new_cols;

    printf("\nThe image you want to crop is %d x %d.\n", *rows, *cols);
    printf("The row and column values start in the upper lefthand corner.\n\n");

    printf("Which column do you want to be the new left side? ");
    scanf("%d", &start_col);
    printf("\nWhich column do you want to be the new right side? ");
    scanf("%d", &end_col);
    printf("\nWhich row do you want to be the new top? ");
    scanf("%d", &start_row);
    printf("\nWhich row do you want to be the new bottom? ");
    scanf("%d", &end_row);

    new_rows = end_row - start_row + 1;
    new_cols = end_col - start_col + 1;

    int cropped_image[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            cropped_image[i][j] = image[start_row + i][start_col + j];
        }
    }

    *rows = new_rows;
    *cols = new_cols;

    printf("\nImage cropped successfully.\n");
}

void dim_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (image[i][j] > 0) {
                image[i][j]--;
            }
        }
    }
    printf("\nImage dimmed successfully.\n");
}

void brighten_image(int image[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (image[i][j] < 4) {
                image[i][j]++;
            }
        }
    }
    printf("\nImage brightened successfully.\n");
}

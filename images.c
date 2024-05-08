// Authors: Jeremy Atwell and Raveena Cheema
// Due Date: 05/7/24
// Purpose: Create a program that allows the user to edit images

#include <stdio.h>

#define MAX_SIZE 500

void load_image(int image[MAX_SIZE][MAX_SIZE], int *size);
void display_image(int image[MAX_SIZE][MAX_SIZE], int size);
void edit_image(int image[MAX_SIZE][MAX_SIZE], int size);
void save_image(int image[MAX_SIZE][MAX_SIZE], int size);
void crop_image(int image[MAX_SIZE][MAX_SIZE], int *size);
void dim_image(int image[MAX_SIZE][MAX_SIZE], int size);
void brighten_image(int image[MAX_SIZE][MAX_SIZE], int size);

int main(){

	int image[MAX_SIZE][MAX_SIZE]; 
	int size = 0;
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
                load_image(image, &size);
                
                break;
            case 2:
                display_image(image, size);
                break;
            case 3:
                edit_image(image, size);
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

void load_image(int image[MAX_SIZE][MAX_SIZE], int *size) {
    char filename[50];
    FILE *file;
    int i, j;

    printf("What is the name of the image file? ");
    scanf(" %s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    //fscanf(file, "%d", size);

    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            fscanf(file, "%d", &image[i][j]);
        }
    }
	printf("first value: %d", image[0][0]);
    fclose(file);
    printf("Image loaded successfully.\n");
}

void display_image(int image[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;

   printf("Image:\n");
   for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            printf( "%d", image[i][j]);
        }
    }
   // for (i = 0; i < MAX_SIZE; i++) {
    //    for (j = 0; j < MAX_SIZE; j++) {
      //      switch (image[i][j]) {
        //        case 0:
          //          printf(" ");
            //        break;
              //  case 1:
                //    printf(".");
                 //   break;
               // case 2:
               //     printf("o");
               //     break;
               // case 3:
               //     printf("O");
               //     break;
              //  case 4:
              //      printf("0");
              //      break;
              //  default:
              //     printf(" ");
         // 	     break;
        //    }
       // }
       printf("\n");	
    //}
}

void edit_image(int image[MAX_SIZE][MAX_SIZE], int size) {
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
                crop_image(image, &size);
                break;
            case 2:
                dim_image(image, size);
                break;
            case 3:
                brighten_image(image, size);
                break;
            case 4:
                save_image(image, size);
                break;
            case 5:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void save_image(int image[MAX_SIZE][MAX_SIZE], int size) {
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

    fprintf(file, "%d\n", size);

    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            fprintf(file, "%d ", image[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Edited image saved successfully.\n");
}

void crop_image(int image[MAX_SIZE][MAX_SIZE], int *size) {
    int new_size;
    int start_row, start_col;
    
    printf("Enter the size of the new cropped image: ");
    scanf("%d", &new_size);
    
    printf("Enter the starting row and column for cropping (0-indexed): ");
    scanf("%d %d", &start_row, &start_col);
    
    if (start_row < 0 || start_row >= *size || start_col < 0 || start_col >= *size ||
        start_row + new_size > *size || start_col + new_size > *size) {
        printf("Invalid crop dimensions. Please try again.\n");
        return;
    }
    
    *size = new_size;
    
    int i, j;
    for (i = 0; i < new_size; i++) {
        for (j = 0; j < new_size; j++) {
            image[i][j] = image[start_row + i][start_col + j];
        }
    }
    
    printf("Image cropped successfully.\n");
}

void dim_image(int image[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            if (image[i][j] > 0) {
                image[i][j]--;
            }
        }
    }
    printf("Image dimmed successfully.\n");
}

void brighten_image(int image[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            if (image[i][j] < 4) {
                image[i][j]++;
            }
        }
    }
    printf("Image brightened successfully.\n");
}

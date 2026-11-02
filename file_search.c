#include <stdio.h>
#include <stdlib.h>
#include "movies.h"
#include "file_operations.h"

void menu(void){
  /* this function is the core user loop*/
  /* the menu first asks the user if they want to process a file or exit*/
  /* if the user chooses to process a file, a new menu is presented to the user */

  int outer_input = 0;
  int inner_intput = 0;
  do{
    printf("\n");
    printf("1. Select file to process\n");
    printf("2. Exit the program\n");
    printf("\n");
    printf("Enter a choice from 1 or 2: ");
    scanf("%d", &outer_input);
    switch(outer_input){
      case 1:
        // sub menu that handles user choices regarding file processing 
        int break_loop = 0;
        do{
          printf("\n");
          printf("Which file you want to process?\n");
          printf("Enter 1 to pick the largest file\n");
          printf("Enter 2 to pick the smallest file\n");
          printf("Enter 3 to specify the name of a file\n");
          printf("\n");
          printf("Enter a choice from 1 to 3: ");
          scanf("%d", &inner_intput);
              
          switch(inner_intput){
            case 1:
              //largest file
              char *file_path_longest = malloc(1024*sizeof(char));                    
              find_file(&file_path_longest, LARGEST);
              processMovieFile(file_path_longest);
              free(file_path_longest);
              break_loop = 1;
              break;
            case 2:
              //smallest file
              char *file_path_shortest = malloc(1024*sizeof(char)); 
              find_file(&file_path_shortest, SMALLEST);
              processMovieFile(file_path_shortest);
              free(file_path_shortest);
              break_loop = 1;
              break;
            case 3:
              //user chosen file
              char *user_file = malloc(1024*sizeof(char));
              printf("Enter the complete file name: ");
              scanf("%s", user_file);
              int check_file = check_file_exists(&user_file);
              if (check_file == 1){
                printf("The file %s was not found. Try again\n", user_file);
              }else{
                processMovieFile(user_file);
                break_loop = 1;
              } 
              free(user_file);
              break;
            default:
              break;
          }
        } while(break_loop != 1);
        break;
      case 2:
        break;
      default:
        printf("You entered an incorrect choice. Try again.\n");
        break;
    }
  } while (outer_input != 2);    
}



int main(void) {
  menu();


  return 0;
}


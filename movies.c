#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "movies.h"
#include "file_operations.h"

void process_movie(char * directory_path, movieObj_t *movie){
  /* this function accepts a movie linked list*/
  /* this function loops over the linked list and writes the movie title to the relevant year.txt file*/
  
    char *file_path = malloc(500*sizeof(char));
    make_file_path(&file_path, directory_path, movie->year);
    char write_string[500];
    sprintf(write_string, "%s\n", movie->title);   
    write_file(file_path, write_string);
}

void processMovieFile(char* filePath){
  // This function is borrowed from the course material and has since been adapted to match the assignment reqs
  // Citation: OSU CS 374 - https://canvas.oregonstate.edu/courses/2061291/assignments/10618930  - (C)2026
  // Accessed on 10.24.26
  printf("Now processing the chosen file named %s\n", filePath);
  char *directory_path = malloc(500*sizeof(char));
  make_directory(&directory_path);
  printf("Created directory with name %s\n", directory_path);
  
  char *currLine = NULL;
  size_t len = 0;
  // Open the specified file for reading only
  FILE *movieFile = fopen(filePath, "r");
  //Read the file line by line
  char *segment;
  movieObj_t *newMovie;
  int count = 0;

  while(getline(&currLine, &len, movieFile) != -1)
  {
    count++;
    newMovie = malloc(sizeof(movieObj_t));
    //get the movie title
    segment = strtok(currLine,",");
    newMovie->title = strdup(segment);

    //get the movie year
    segment = strtok(NULL, ",");
    newMovie->year = atoi(segment);

    if(strstr(newMovie->title, "Title") == NULL){
      //generate a new movie struct object
      process_movie(directory_path, newMovie);
    } 
    free(newMovie);    
    
  }
  free(directory_path);
  // Free the memory allocated by getline for currLine
  free(currLine);
  // Close the file
  fclose(movieFile);
  
}

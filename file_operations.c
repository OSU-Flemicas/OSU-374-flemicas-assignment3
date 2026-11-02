#include <time.h> //needed so the random generator actually comes up with a new number each time
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "file_operations.h"

int check_file_exists(char **file_path){
  // this function is used to ensure files the user enters exist
  int check_file = open(*file_path, O_RDWR, 0600);
  if (check_file == -1){
    //file doesn't exist
    return 1;
  }else{
    close(check_file);
    return 0;
  }
}

void make_directory(char **directory_name){
  //this function generates a directory per the assignment requirements, it updates the value of the directory_name variable passed into it
  srand(time(0)); 
  sprintf(*directory_name, "flemicas.movies.%d", rand() % 99999);
  mkdir(*directory_name, 0750);
}

void make_file_path(char **file_path, char *directory_name, int year){
  //this function generates a file path per the assignment requirements and updates the variable passed into it
  sprintf(*file_path, "./%s/%d.txt",  directory_name, year);
}

void write_file(char* file_path, char *write_string){
  //this function accepts a file path and a string. It opens the file and writes the string at the end of the file
  int file_open = open(file_path, O_RDWR | O_CREAT, 0640);
  lseek(file_open, 0, SEEK_END);
  int file_write = write(file_open, write_string, strlen(write_string));
  close(file_open);
}

void find_file(char **file_path, lookup type){
  //this function is used to find the largest or smallest file depending on the look up type. It updates the file_path variable passed into it
  DIR* directory;
  struct dirent *entry;
  struct stat entryStat;
  char temp_file_path[500];
  char directory_path[50] = ".";
  long int largest_file = 0;
  long int smallest_file = 99999;
  
  directory = opendir(directory_path);

  while((entry = readdir(directory)) != NULL){
    if(entry->d_type == 8){
      if(strstr(entry->d_name, "movies_") != NULL){
        sprintf(temp_file_path, "%s/%s", directory_path, entry->d_name);
        stat(temp_file_path, &entryStat);
        if (type == LARGEST){
          if(entryStat.st_size > largest_file){
            largest_file = entryStat.st_size;
            sprintf(*file_path, "%s", temp_file_path);
          }
        }else if(type == SMALLEST){
          if(entryStat.st_size < smallest_file){
            smallest_file = entryStat.st_size;
            sprintf(*file_path, "%s", temp_file_path);
          }
        }        
      }
    }
  }   
  
  closedir(directory);
}
#ifndef MOVIES_H
#define MOVIES_H

typedef struct movieObj movieObj_t;

typedef struct movieObj{
    char *title;
    int year;
} movieObj_t;

void process_movie(char * directory_path, movieObj_t *movie);

void processMovieFile(char* filePath);

#endif
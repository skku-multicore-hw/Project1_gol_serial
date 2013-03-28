




#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <sys/time.h>
#define Parameter 6
char ***Make_3D_Cube(int dim);
char ****Make_3D_Cube_2(int dim);
char *** Analysis_file(char* filename,int *parameter);
void Make_output_life(char*** Cube,int dim);
void Print_time(char* string,struct timeval *start_time);
void game_of_life(char* filename);


#endif

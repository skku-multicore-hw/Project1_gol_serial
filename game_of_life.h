




#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#define Parameter 6
char ***Make_3D_Cube(int dim);
char *** Analysis_file(char* filename,int *parameter);
void Make_output_life(char*** Cube);
void game_of_life(char* filename);


#endif

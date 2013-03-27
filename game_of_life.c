




#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>

// This function will return parameter and 3D_seed cell
char*** Analysis_file(char* filename, int* parameters){

	FILE *pFile_in;
	char ch;
	char buf[10];
	int par=0,n=0;

	if((pFile_in = fopen("input.life","r")) == NULL){
		printf("file open error!\n");
		exit(1);
	}

	while(1){
		ch=fgetc(pFile_in);
		if(ch == '\n'){
			parameters[par] = atoi(buf);
			break;
		}
		else if(ch == ' '){
			parameters[par++] = atoi(buf);
			n = 0;
		}
		else buf[n++] = ch;
	}

	return NULL;
}


void game_of_life(char* filename){

	int parameters[Parameter];
	char ***Cube;
	int i;

	Cube = Analysis_file(filename,parameters);

// This Line test parameters
// parameters[0] length
// parameters[1] D1
// parameters[2] D2
// parameters[3] L1
// parameters[4] L2
// parameters[5] Step
/*
	for(i=0;i<Parameter;i++) printf("%d\n",parameters[i]);
*/
	return ;
}


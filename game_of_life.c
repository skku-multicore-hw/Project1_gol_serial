




#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


// This function will return parameter and 3D_seed cell
char*** Analysis_file(char* filename, int* parameters){

	int nFile_in;
	int len;
	char temp[10];
	char *buf;
	int par=0,n=0,m=0;

	char ***Return_Cube;

	if((nFile_in = open(filename,O_RDONLY)) < 0){
		printf("file open error!\n");
		exit(1);
	}

	len = lseek(nFile_in,0,SEEK_END);
	buf = (char *)malloc(sizeof(char)*len);
	lseek(nFile_in,0,SEEK_SET);
	read(nFile_in,buf,len);

	while(1){
		if(buf[n] == '\n'){
			parameters[par++] = atoi(temp);
			n++;
			break;
		}
		else if(buf[n] == ' '){
			parameters[par++] = atoi(temp);
			m = 0;
		}
		else  temp[m++]= buf[n];
		n++;
	}

	printf("%d\n",n);

	return NULL;
}


void game_of_life(char* filename){

	int parameters[Parameter];
	char ***Cube;
//	int i;

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


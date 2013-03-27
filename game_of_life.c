




#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>



// This function will return parameter and 3D_seed cell
char*** Analysis_file(char* filename, int* parameters){

	int nFile_in;
	int len;
	char temp[10];
	char *buf;
	int par=0,n=0,m=0;

	char ***Return_Cube;
	int dim,i,j,k;

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
	dim = parameters[0];

	Return_Cube = (char***)malloc(dim*sizeof(char**));
	for(i=0;i<dim;i++){
		Return_Cube[i] = (char**)malloc(dim*sizeof(char*));
	}

	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			Return_Cube[i][j] = (char*)malloc(dim*sizeof(char));
		}
	}

	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			for(k=0;k<dim;k++){
				while(1){
					if(buf[n] == '0'){
						Return_Cube[i][j][k] = 0;
						n++;
						break;
					}
					else if(buf[n] == '1'){
						Return_Cube[i][j][k] = 1;
						n++;
						break;
					}
					else n++;
				}
			}
		}
	}

	return Return_Cube;
}


void game_of_life(char* filename){

	int parameters[Parameter];
	char ***Cube;
//	int i,j,k;

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
//This Line test Cube
/*
	for(i=0;i<parameters[0];i++){
		for(j=0;j<parameters[0];j++){
			for(k=0;k<parameters[0];k++){
				printf("Cube[%d][%d][%d] is ",i,j,k);
				printf("%4d : " ,Cube[i][j][k]);
				printf("0x%p",&Cube[i][j][k]);
				printf("\n");
			}
		}
	}
*/


	return ;
}


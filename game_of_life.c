




#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>



//This function will return 3D_Cube
char ***Make_3D_Cube(int dim){
	char ***Make_Cube;
	int i,j;

	Make_Cube = (char***)malloc(dim*sizeof(char**));
	for(i=0;i<dim;i++){
		Make_Cube[i] = (char**)malloc(dim*sizeof(char*));
	}
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			Make_Cube[i][j] = (char*)malloc(dim*sizeof(char));
		}
	}
	return Make_Cube;
}
char ****Make_3D_Cube_2(int dim){
	char ****Make_Cube;
	int i,j,k;

	Make_Cube = (char****)malloc(2*sizeof(char***));
	for(i=0;i<2;i++){
		Make_Cube[i] = (char***)malloc(dim*sizeof(char**));
	}
	for(i=0;i<2;i++){
		for(j=0;j<dim;j++){
			Make_Cube[i][j] = (char**)malloc(dim*sizeof(char*));
		}
	}
	for(i=0;i<2;i++){
		for(j=0;j<dim;j++){
			for(k=0;k<dim;k++){
				Make_Cube[i][j][k] = (char*)malloc(dim*sizeof(char));
			}
		}
	}
	return Make_Cube;
}
// This function will return parameters and 3D_seed cell
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
	Return_Cube = Make_3D_Cube(dim);


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
//This function will make output.life
void Make_output_life(char*** Cube,int dim){

	return ;
}

void Print_time(char* string,struct timeval *start_time){

	struct timeval end_time, result_time;
	gettimeofday(&end_time,NULL);
	timersub(&end_time,start_time,&result_time);
	fprintf(stderr,"%s Elapsed Time  : %ld(usec)\n",string,1000000*(result_time.tv_sec) + (result_time.tv_usec));

	return ;
}

void game_of_life(char* filename){

	int parameters[Parameter];
	char ***Cube;
	struct timeval start_time;
//	int i,j,k;

	gettimeofday(&start_time,NULL);
	Cube = Analysis_file(filename,parameters);
	Print_time("Initialize",&start_time);

//	Make_output_life(Cube,parameters[0]);
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


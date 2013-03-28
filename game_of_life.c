




#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define Parameter 6



//This function will return two 3D_Cube Even,Odd
char ****Make_3D_Cube(int dim){
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
char ****Analysis_file(char* filename, int* parameters){

	int nFile_in;
	int len;
	char temp[10];
	char *buf;
	int par=0,n=0,m=0;

	char ****Return_Cube;
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
			memset(temp,0,sizeof(char)*10);
			m = 0;
		}
		else  temp[m++]= buf[n];
		n++;
	}
	for(i=0;i<Parameter;i++){
		printf("parameters[%d] = %d\n",i,parameters[i]);
	}

	dim = parameters[0];
	Return_Cube = Make_3D_Cube(dim);


	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			for(k=0;k<dim;k++){
				while(1){
					if(buf[n] == '0'){
						Return_Cube[0][i][j][k] = 0;
						n++;
						break;
					}
					else if(buf[n] == '1'){
						Return_Cube[0][i][j][k] = 1;
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
void Make_output_life(char**** Cube, int dim, int nEorO){
	int nFile_out;
	int i,j,k;
	char string[20];

	if((nFile_out = open("output.life",O_WRONLY|O_TRUNC|O_CREAT,0664)) < 0){
		printf("file open error!\n");
		exit(1);
	}

	for(i=0;i<dim;i++){
		sprintf(string,"cell(x,y,%d)\n",i);
		write(nFile_out,string,strlen(string));
		for(j=0;j<dim;j++){
			for(k=0;k<dim;k++){
				if(Cube[nEorO][i][j][k]) write(nFile_out,"1",strlen("1"));
				else write(nFile_out,"0",strlen("0"));
				if(k==dim-1){
					write(nFile_out,"\n",strlen("\n"));
				}
			}
		}
	}
	return ;
}
//This function will Print time
void Print_time(char* string,struct timeval *start_time){

	struct timeval end_time, result_time;
	gettimeofday(&end_time,NULL);
	timersub(&end_time,start_time,&result_time);
	fprintf(stderr,"%s Elapsed Time  : %ld(usec)\n",string,1000000*(result_time.tv_sec) + (result_time.tv_usec));

	return ;
}

void game_of_life(char* filename){

	int parameters[Parameter];
	char ****Cube;
	struct timeval start_time;
//	int i,j,k;
	int nEorO=0;

	gettimeofday(&start_time,NULL);
	Cube = Analysis_file(filename,parameters);
	Print_time("Initialize",&start_time);

	gettimeofday(&start_time,NULL);
	nEorO = process_main(parameters,Cube);
	Print_time("Processing",&start_time);

	gettimeofday(&start_time,NULL);
	Make_output_life(Cube,parameters[0],nEorO);
	Print_time("Making output.life",&start_time);
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
				printf("Cube[0][%d][%d][%d] is ",i,j,k);
				printf("%4d : " ,Cube[0][i][j][k]);
				printf("0x%p",&Cube[0][i][j][k]);
				printf("\n");
			}
		}
	}

*/

	return ;
}


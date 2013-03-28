#include <stdio.h>
#include <stdlib.h>
#include "process.h"

/*
#define AXIS 10 			//less than 23 !!!!!!!!!!!!!!!!!!!!!!!!
#define AXISX AXIS
#define AXISY AXIS
#define AXISZ AXIS
#define STEPS 100

#define D1 5
#define D2 17
#define L1 7
#define L2 15
*/
int AXIS;
int AXISZ;
int AXISY;
int AXISX;
int STEPS;
int D1;
int D2;
int L1;
int L2;

//char odd;					//use for vector select e) vector[odd][i][j][k]
char even;
char ****vector;

void vector_init();
void vector_generate();
void vector_print();
void pixel_judg(int, int, int);
void pixel_kill(int, int, int);
void pixel_live(int, int, int);
char ****Make_3D_Cube_2(int);

/* Initialize vector space */
void vector_init() {
	int i, j, k, o;
	/*for (o = 0; o < 2; o++) {
		for (i = 0; i < AXISZ; i++) {
			for (j = 0; j < AXISY; j++) {
				vector[o][i][j] = malloc(sizeof(int)*AXISX);
				vector[o][i][j] = malloc(sizeof(int)*AXISX);
			}
		}
	}
*/
		for (i = 0; i < AXISZ; i++) {
			for (j = 0; j < AXISY; j++) {
				for (k = 0; k < AXISX; k++) {
					vector[0][i][j][k] = 1;
				}
			}
		}
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

/* Generate 1 step */
void vector_generate() {
	int i, j, k;

	for (i = 0; i < AXISZ; i++) {
		for (j = 0; j < AXISY; j++) {
			for (k = 0; k < AXISX; k++) {
				pixel_judg(i,j,k);
			}
			//printf("\n");
		}
		//printf("\n");
	}
}

/* Print last step vector */
void vector_print(char**** cube) {
	int i, j, k;
	printf("\n\n");

	for (i = 0; i < AXISZ; i++) {
		for (j = 0; j < AXISY; j++) {
			for (k = 0; k < AXISX; k++) {
				if (cube[even][i][j][k] == 1)
					printf(" %c", '1');
				else
					printf(" %c", '0');
			}
			printf("\n");
		}
		printf("\n");
	}
}

/* Judge pixel kill or live */
void pixel_judg(int i, int j, int k) {
	int a, b, c;
	int a_sta = 0, b_sta = 0, c_sta = 0;
	int a_end = 3, b_end = 3, c_end = 3;
	int n = 0;

	if (i == 0) a_sta++;
	if (i == AXISZ-1) a_end--;
	if (j == 0) b_sta++;
	if (j == AXISY-1) b_end--;
	if (k == 0) c_sta++;
	if (k == AXISX-1) c_end--;


		for (a = a_sta; a < a_end; a++) {
			for (b = b_sta; b < b_end; b++) {
				for (c = c_sta; c < c_end; c++) {
					if (vector[even][i+a-1][j+b-1][k+c-1] == 1) n++;
				}
			}
		}

	if (vector[even][i][j][k] == 1){			//judge live pixel
		n--;
		//printf("%d ",n);

		if (n < D1 || n > D2) pixel_kill(i, j, k);
		else pixel_live(i, j, k);
	}

	else if (vector[even][i][j][k] == 0){		//judge dead pixel
		//printf("(%d) ",n);
		if (n > L1 && n < L2) pixel_live(i, j, k);
		else pixel_kill(i, j, k);
	}
	else printf("ERROR\n");

}

/* Pixel kill */
void pixel_kill(int i, int j, int k) {
	vector[odd][i][j][k] = 0;
}

/* Pixel live */
void pixel_live(int i, int j, int k) {
	vector[odd][i][j][k] = 1;
}


char**** process_main(int* parameters, char**** cube) {
	int i, j;
	AXIS  = parameters[0];
	D1    = parameters[1];
	D2    = parameters[2];
	L1    = parameters[3];
	L2    = parameters[4];
	STEPS = parameters[5];

	// parameters[0] length
	// parameters[1] D1
	// parameters[2] D2
	// parameters[3] L1
	// parameters[4] L2
	// parameters[5] Step

	AXISZ = AXIS;
	AXISY = AXIS;
	AXISX = AXIS;

	vector = cube;

	odd = 1;
	even = 0;

	for (i = 0; i < STEPS; i++){
		vector_generate();
		//printf("\n STEPS = %d odd = %d even = %d \n",i+1,odd,even);
		if (odd) {
			odd--;
			even++;
		}
		else {
			odd++;
			even--;
		}
	}
/*
	for (i = 0; i < AXISZ; i++) {			//free memory
		for (j = 0; j < AXISY; j++) {
			free(vector[0][i][j]);
			free(vector[1][i][j]);

		}
	}
*/
	return vector;
}
/*
void main(){
	char**** cube;
	int parameters[6];

	vector = Make_3D_Cube_2(10);

	cube = process_main(parameters, vector);
	vector_print(cube);
}
*/

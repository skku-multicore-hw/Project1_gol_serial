#include <stdio.h>
#include <stdlib.h>
#include "process.h"


int AXIS;
int AXISZ;
int AXISY;
int AXISX;
int STEPS;
int D1;
int D2;
int L1;
int L2;

int odd;					//use for vector select e) vector[odd][i][j][k]
int even;
char ****vector;

void vector_generate();
void pixel_judg(int, int, int);
void pixel_kill(int, int, int);
void pixel_live(int, int, int);
int process_main(int* parameters, char**** cube);


/* Generate 1 step */
void vector_generate() {
	int i, j, k;

	for (i = 0; i < AXISZ; i++) {
		for (j = 0; j < AXISY; j++) {
			for (k = 0; k < AXISX; k++) {
				pixel_judg(i,j,k);
			}
		}
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
		printf("%d ",n);

		if (n < D1 || n > D2) pixel_kill(i, j, k);
		else pixel_live(i, j, k);
	}

	else if (vector[even][i][j][k] == 0){		//judge dead pixel
		printf("(%d) ",n);
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


int process_main(int* parameters, char**** cube) {
	int i/*, j*/;
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
		printf("\n STEPS = %d odd = %d even = %d \n",i+1,odd,even);
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
	cube =vector;
	return (int)even;
}
/*
void main(){
	char**** cube;
	int parameters[6];
	parameters[0] =10;
	parameters[1] =5;
	parameters[2] =17;
	parameters[3] =10;
	parameters[4] =15;
	parameters[5] =100;

	odd = 1;
	even = 0;

	vector = Make_3D_Cube_2(parameters[0]);
	vector_init();

	even = process_main(parameters, vector);
	vector_print(cube);
}
*/

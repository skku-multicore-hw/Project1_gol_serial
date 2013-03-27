





#include "main.h"

int main(int argc, char** argv){

	struct timeval start_time, end_time, result_time;

	if(argc != 2){
		printf("Usage : %s [Seed file Name] \n", argv[0]);

		return 1;
	}
	printf("Running game of life by openMP\n");

	gettimeofday(&start_time, NULL);

	game_of_life(argv[1]);

	gettimeofday(&end_time,NULL);
	timersub(&end_time,&start_time,&result_time);

	fprintf(stderr,"Elapsed Time  : %ld(usec)\n",	1000000*(result_time.tv_sec) + (result_time.tv_usec));

	return 0;
}

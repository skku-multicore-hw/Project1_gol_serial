





#include "main.h"

int main(int argc, char** argv){

	struct timeval start_time;

	if(argc != 2){
		printf("Usage : %s [Seed file Name] \n", argv[0]);

		return 1;
	}
	printf("Running game of life by Serialized Program \n");

	gettimeofday(&start_time, NULL);
	game_of_life(argv[1]);
	Print_time("Program Total",&start_time);

	return 0;
}

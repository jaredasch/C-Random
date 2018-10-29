#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int randint(){
	int *rand_int = malloc(8);
	int fd_rand = open("/dev/random", O_RDONLY);
	if(fd_rand == -1){
		printf("%s\n", strerror(errno));
	}
	read(fd_rand, rand_int, 8);
	close(fd_rand);
	free(rand_int);
	return *rand_int;
}

int main(){
	int *random_nums = malloc(10 * sizeof(int));
	printf("Generating Random Numbers:\n");
	for(int i = 0; i < 10; i++){
		random_nums[i] = randint();
		printf("\trandom %d: %d\n", i, random_nums[i]);
	}

	printf("Writing numbers to file...\n\n");
	int fd_out = open("random_ints", O_WRONLY | O_CREAT, 0777);
	write(fd_out, random_nums, 10 * sizeof(int));
	close(fd_out);

	printf("Reading numbers from file...\n\n");
	int *new_random_nums = malloc(10 * sizeof(int));
	int fd_in = open("random_ints", O_RDONLY);
	read(fd_in, new_random_nums, 10 * sizeof(int));
	
	printf("Printing random numbers loaded from file\n");
	for(int i = 0; i < 10; i++){
		printf("\trandom %d: %d\n", i, new_random_nums[i]);
	}

	return 0;
}
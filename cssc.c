#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aol.h"

/*
 * Creator of spiral staircases
 * v0.1
 * 26.02.2020
 * by ASZ
 */

int main(int argc, char *argv[]) {
	char input[256], *tok;
	double angle = 0.0;
	spiral_ladder sl;	
	size_t bytes;
	FILE *out;

	if (argc != 2) {
		fprintf(stderr, "usage: cssc <detail-name>\n");
		return 0;
	}

	printf("Enter 2 radii (the first is the General radius of the ladder, the second is the radius of the Central rod) (separate the values with spaces): ");
	fgets(input, 256, stdin);
	tok = strtok(input, " \n");
	for (int i = 0; i < 2 && tok; i++) {
		if (is_int(tok))
			sl.rads[i] = atof(tok);	
		tok = strtok(NULL, " \n");
	}

	printf("Enter the number of steps in full rotation: ");
	fgets(input, 256, stdin);
	if (is_int(input))
		sl.count = atoi(input);	

	if (sl.count > 0)
		angle = (double)(360/sl.count);

	printf("\n== Check\n\t* Main radius %f\n\t* Rod radius %f\n\t* Angle %f\n", sl.rads[0], sl.rads[1], angle);

	strcat(argv[1], ".ssco");
	out = fopen(argv[1], "w");
	if (!out) {
		fprintf(stderr, "error: file not recorded\n");
		return 0;
	}
	bytes = fwrite(&sl, sizeof(sl), 1, out);
	fclose(out);

	printf("\n== Write [%d / 1] %d%%\n", bytes, (bytes/1)*100);
	return 0;
}

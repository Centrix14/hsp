#include <stdio.h>
#include <string.h>
#include "aol.h"

/*
 * Cubic object reader
 * v0.2
 * 26.02.2020
 * by ASZ
 */

int main(int argc, char *argv[]) {
	spiral_ladder sl;	
	FILE *src;
	flat apartment;
	stairs ladder;
	size_t bytes;
	char *type;

	if (argc != 2) {
		fprintf(stderr, "usage: cor <read-file-name>\n");
		return 0;
	}

	printf("== Readable file %s\n", argv[1]);

	src = fopen(argv[1], "r");
	if (!src) {
		fprintf(stderr, "No such file \'%s\'\n", argv[1]);	
		return 0;
	}

	strtok(argv[1], ".");
	type = strtok(NULL, ".");

	if (!strcmp(type, "sco")) {
		bytes = fread(&apartment, sizeof(apartment), 1, src);

		printf("== Result [%d / 1] %d%%\n\n== Content\n", bytes, (bytes/1)*100);
	
		for (int i = 0; i < 4; i++) {
			if (i < 3)
				printf("\tSize [O%c]: %f\n", 'X'+i, apartment.size[i]);
			else
				printf("\tDesign size plane: %s\n", apartment.face);
		}
	}
	else if (!strcmp(type, "slo")) {
		bytes = fread(&ladder, sizeof(stairs), 1, src);	

		printf("== Result [%d / 1] %d%%\n\n== Content\n", bytes, (bytes/1)*100);

		printf("\tAbsolute OX %f\tAbsolute OY %f\n", ladder.size[0]*ladder.count, ladder.size[1]*ladder.count);
		for (int i = 0; i < 3; i++) {
			if (i < 2)
				printf("\tStep size [O%c]: %f\n", 'X'+i, ladder.size[i]);
			else
				printf("\tNumber of stages: %d\n", ladder.count);
		}
	}
	else if (!strcmp(type, "ssco")) {
		bytes = fread(&sl, sizeof(spiral_ladder), 1, src);

		printf("== Result [%d / 1] %d%%\n\n== Content\n", bytes, (bytes/1)*100);

		printf("\tMain radius %f mm\n\tRod radius %f mm\n\tCount %d\n\tAngle %f\n", sl.rads[0], sl.rads[1], sl.count, (double)360/sl.count);
	}

	fclose(src);
	return 0;
}

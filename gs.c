#include <stdio.h>
#include <string.h>
#include "aol.h"

/*
 * Generate Specification
 * v0.2
 * 26.02.2020
 * by ASZ
 */

int main(int argc, char *argv[]) {
	spiral_ladder sl;	
	FILE *output, *arg;	
	char *name, *type;
	flat apart;
	stairs ladder;

	if (argc < 3) {
		fprintf(stderr, "usage: gs <output-file-name> <input-file-name>...\n");
		return 0;
	}

	output = fopen(argv[1], "w");

	for (int i = 2; i < argc; i++) {
		arg = fopen(argv[i], "r");	
		if (!arg) {
			fprintf(stderr, "Can\'t open \'%s\'\n", argv[i]);	
			continue;
		}

		name = strtok(argv[i], ".");
		type = strtok(NULL, ".");

		fprintf(output, "== %s\n", name);

		if (!strcmp(type, "sco")) {
			fread(&apart, sizeof(flat), 1, arg);

			for (int j = 0; j < 4; j++)	{
				if (j < 3)
					fprintf(output, "\t* Cube size by [O%c] %f mm\n", 'X'+j, apart.size[j]);
				else
					fprintf(output, "\t* Design side plane is [%s]\n", apart.face);
			}
		}
		else if (!strcmp(type, "slo")) {
			fread(&ladder, sizeof(stairs), 1, arg);

			for (int j = 0; j < 3; j++) {
				if (j < 2)
					fprintf(output, "\t* Step size by [O%c] %f mm\n", 'X'+j, ladder.size[j]);
				else
					fprintf(output, "\t* Count %d \n", ladder.count);
			}
		}
		else if (!strcmp(type, "ssco")) {
			fread(&sl, sizeof(spiral_ladder), 1, arg);

			fprintf(output, "\t* Main radius %f mm\n\t* Rod radius %f mm\n\t* Count %d\n\t* Angle %f\n", sl.rads[0], sl.rads[1], sl.count, (double)360/sl.count);
		}
		fclose(arg);
	}

	fclose(output);
	return 0;	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aol.h"

/*
 * Creator of the cubic object
 * v0.2
 * 26.02.2020
 * by ASZ
 */

int main(int argc, char *argv[]) {
	char input[256], *tok = "";
	FILE *output_file;
	flat apartment;
	size_t bytes;

	if (argc != 2) {
		fprintf(stderr, "usage: cfo <detail-name>\n");
		return 0;
	}

	printf("Enter the size of the apartment [lwh / xyz] (separated by a space): ");
	fgets(input, 256, stdin);

	tok = strtok(input, " \n");
	for (int i = 0; i < 3 && tok; i++) {
		if (is_int(tok))
			apartment.size[i] = strtod(tok, NULL);

		tok = strtok(NULL, " \n");
	}

	printf("Enter the design side plane (XY, XZ, YZ): ");
	gets(apartment.face);

	printf("\n== Check\n");
	for (int i = 0; i < 4; i++) {
		if (i < 3)
			printf("The dimensions of the apartment are set [O%c]: %f\n", 'X'+i, apartment.size[i]);
		else
			printf("Design side plane: %s", apartment.face);
	}

	strcat(argv[1], ".sco")
	output_file = fopen(argv[1], "w");
	bytes = fwrite(&apartment, sizeof(apartment), 1, output_file);
	fclose(output_file);

	printf("\n== Write [%d / 1] %d%%\n", bytes, (bytes / 1)*100);
	return 0;
}

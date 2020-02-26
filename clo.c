#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aol.h"

/*
 * Creator of the ladder object
 * v0.2
 * 26.02.2020
 * By ASZ
 */

int main(int argc, char *argv[]) {
	char input[4], *tok = "";
	FILE *output, *src;
	stairs ladder;
	flat apart;
	size_t bytes;

	if (argc != 2) {
		fprintf(stderr, "usage: clo <detail-name>\n");
		return 0;
	}

	printf("== Ways\n	[1] Create by sizes\n	[2] Create by cube object\n");
	do {
		printf("Select the way: ");		
		fgets(input, 4, stdin);
	} while (input[0] != '1' && input[0] != '2');

	if (input[0] == '1') {
		printf("\nEnter sizes (separated by space): ");	
		fgets(input, 256, stdin);

		tok = strtok(input, " \n");
		for (int i = 0; i < 2 && tok; i++) {
			if (is_int(tok))
				ladder.size[i] = strtod(tok, NULL);
			tok = strtok(NULL, " \n");
		}

		printf("Enter count of the stairs: ");
		fgets(input, 256, stdin);
		ladder.count = atoi(del_sym(input, '\n'));
	}
	else {
		printf("Enter cube file name: ");
		fgets(input, 256, stdin);

		src = fopen(del_sym(input, '\n'), "r");
		if (!src) {
			fprintf(stderr, "No such file \'%s\'", input);
			return 0;
		}
		bytes = fread(&apart, sizeof(flat), 1, src);
		fclose(src);

		printf("== Read [%d / 1] %d%%\n\n", bytes, (bytes / 1)*100);

		do {
			printf("Enter count of the steps: ");
			fgets(input, 256, stdin);
		} while (!is_int(del_sym(input, '\n')));
		ladder.count = atoi(del_sym(input, '\n'));

		do {
			printf("Enter separate type (hotizontal / vertical / all / fill) [h / v / a / f]: ");
			fgets(input, 256, stdin);
		} while (input[0] != 'h' && input[0] != 'v' && input[0] != 'a' && input[0] != 'f');

		if (input[0] == 'h') {
			ladder.size[0] = apart.size[0] / ladder.count; /* OX */
			ladder.size[1] = apart.size[2] / 2 / ladder.count; /* OZ */
		}
		else if (input[0] == 'v') {
			ladder.size[0] = apart.size[0] / 2 / ladder.count;
			ladder.size[1] = apart.size[2] / ladder.count;
		}
		else if (input[0] == 'a') {
			ladder.size[0] = apart.size[0] / 2 / ladder.count;
			ladder.size[1] = apart.size[2] / 2 / ladder.count;
		}
		else {
			ladder.size[0] = apart.size[0];
			ladder.size[1] = apart.size[2];
		}
	}

	printf("\n== Check\n");
	printf("\tAbsolute OX %f\tAbsolute OY %f\n", ladder.size[0]*ladder.count, ladder.size[1]*ladder.count);
	for (int i = 0; i < 3; i++) {
		if (i < 2)
			printf("\tStep size [O%c] %f\n", 'X'+i, ladder.size[i]);	
		else
			printf("\tSteps count: %d\n", ladder.count);	
	}

	strcat(argv[1], ".slo");
	output = fopen(argv[1], "w");
	bytes = fwrite(&ladder, sizeof(stairs), 1, output);
	fclose(output);

	printf("== Write [%d / 1] %d%%\n", bytes, (bytes / 1)*100);
	return 0;
}

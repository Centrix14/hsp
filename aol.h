#ifndef __FLAT_OBJECT_HEADER_INCLUDED__
#define __FLAT_OBJECT_HEADER_INCLUDED__

typedef struct _flat {
	double size[3];	
	char face[8];
} flat;

typedef struct _stairs {
	double size[2];
	int count;
} stairs;

typedef struct _sl {
	double rads[2];
	int count;
} spiral_ladder;

int is_int(char*);
char *del_sym(char*, int);

#endif

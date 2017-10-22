#include <stdio.h>
#include <stdlib.h>
#define N 255

struct package {
	int x;
	char string[255];
	float y;
	};

int main(int argc, char *argv[]) {
	FILE *fp;
	if ((argc == 1) || (!(fopen(argv[1], "rb")))) {
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	fp = fopen(argv[1], "rb");
	struct package pack;
	
	int i = 0;
	while(fread(&pack, sizeof(struct package), 1, fp)) {
		printf("%d %s %f\n", pack.x, pack.string, pack.y);
		i++;
	}
	printf("File size: %lu bytes\n", i*sizeof(pack));

	fclose(fp);
	return 0;
}

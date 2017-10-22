#include "fann.h"
#include <stdio.h>
#include <string.h>

int i;
char answer[30];
void train(char *, char *);

int main(int argc, char* argv[])
{
	if (argc < 4)
		return 1;
	if (fopen("classify.net", "r") == NULL) {
		printf("train file not found\nwould you like to train?\n");
		printf("filename or 'no'\n");
		scanf("%s", answer);
		if (strcmp(answer, "no") != 0)
			train(answer, "classify.net");
		return 0;
	}

 	struct fann *tt = fann_create_from_file("classify.net");
	float input[3];
	for (i = 1; i <= 3; i++)
		input[i-1] = (float) *argv[i]-'0';
	
 	float *output = fann_run(tt, input);
	printf("%.lf\n", *output);
 	return 0;
}

void train(char *fromwhere, char *towhere) {
	struct fann *tt = fann_create_standard(2, 3, 1);
	fann_train_on_file(tt, fromwhere, 200, 1, 0.01);
	fann_save(tt, towhere);
	printf("finished\n");
	fann_destroy(tt);
}

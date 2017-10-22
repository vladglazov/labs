#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000
#define T 256
unsigned char *tape;
char *lpos, *rpos;
int i, c, tp, beginin, t = T;
typedef char* position;

int get(position); /* returns data */

int main(int argc, char const *argv[])
{
	FILE *fp;
	fp = fopen("input.txt", "r");		
	char *commands[N];

	for (i = 0; i < N; i++)
		commands[i] = (char*) malloc (sizeof(char) * N); 
	/* commands tape */
	tape = (unsigned char*) malloc(sizeof(char) * t);
	for (i = 0; i < T; i++)
		tape[i] = 0;
	/* write command */
	i = 0;
	while(fscanf(fp, "%s", commands[i]) == 1)
		i++;
	c = i, i = 0;
	while (i < c) {
		if (strstr("movl", commands[i]))
			tp--;
		else if (strstr("movr", commands[i]))
			tp++;
		else if (strstr("inc", commands[i])) {
			if (tape[tp] == 255) {
				printf("warning overflow\n");
				tape[tp] = 0;
			} else 
				++(tape[tp]);
		} else if (strstr("dec", commands[i]))
			--(tape[tp]);
		else if (strstr("print", commands[i]))
			printf("%d\n", tape[tp]);
		else if (strstr("printc", commands[i]))
			printf("%c\n", tape[tp]);
		else if (strstr("get", commands[i]))
			scanf("%c", &tape[tp]);
		else if (strstr("begin", commands[i]))
			if (tape[tp] == 0)
				while (!strstr("end", commands[i]))
					i++;
			else
				beginin = i;
		else if (strstr("end", commands[i]) && tape[tp] != 0)
			i = beginin;
		/* handle movr to the rightmost side of tape */
		if (tp >= T) {
			t += T;
			tape = realloc(tape, sizeof(char) * t);
		/* handle movl to the leftmost side of tape */
		} else if (tp < 0) {
			t += T;
			tape = realloc(tape, sizeof(char) * t);
			memcpy(tape, tape+T, sizeof(char) * T);
		}


		i++;

	}

	fclose(fp);
	return 0;
}
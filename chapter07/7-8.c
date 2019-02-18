/*
 * Exercise 7-8. Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>

#define LINE       81                  /* characters per line */
#define PAGEBREAK  3840                /* characters per page ~ 500 word/page */

/* functions */
int  pagecount(FILE *);
void printcover(char *, int);

int pagecount(FILE *f)
{
	int count = 0;

	while (getc(f) != EOF) 
		count++;
	return (count < PAGEBREAK) ? 1 : count / PAGEBREAK;
}

void printcover(char *s, int n)
{
	int i;

	printf("************************\n");
	printf("File name: %s\n", s);
	printf("Page count: %i\n", n);
	printf("************************\n");

	for (i = 4; i <= (PAGEBREAK / LINE); ++i)   /* i = 4 to skip above lines */
		printf("\n");
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char *prog = argv[0];
	int pages, c;

	while (--argc > 0)
		if ((fp = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
			exit(EXIT_FAILURE);
		} else {
			pages = pagecount(fp);
			rewind(fp);                   /* rewind input stream */
			printcover(*argv, pages);
			while ((c = getc(fp)) != EOF) /* print file */
				fprintf(stdout, "%c", c);
			fclose(fp);
		}
	exit(EXIT_SUCCESS);
}
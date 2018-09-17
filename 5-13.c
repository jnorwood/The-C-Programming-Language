/*
 * Exercise 5-13. Write the program tail. Which prints the last n lines of its
 * input. By default, n is set to 10, let us say, but it can be changed by an
 * optional argument so that
 *
 * 	tail -n
 *
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or value of n.  Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program of section 5.6, not in a two-dimensional array of fixed size.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES   5000      /* max #lines to be stored */
#define MAXLEN     1000      /* max length of any input line */
#define MEMORYSIZE 10000     /* storage for memory[] */
#define N          10        /* default value of last lines to print */

/* function declerations */
int  readlines(char *lineptr[], int nlines, char *p);
int  getLine(char *, int);
int  isDigitStr(char *s[]);

/* global variables */
char *lineptr[MAXLINES];    /* pointers to text lines */

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *p)
{
	int len, nlines, usedMemory;
	char line[MAXLEN];

	usedMemory = 0;
	nlines = 0;
	while ((len = getLine(line, MAXLEN)) > 0)
		if (nlines >= maxlines || MEMORYSIZE - usedMemory < len)
			return -1;
		else {
			line[len - 1] = '\0';   /* delete newline character */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;               /* increment pointer */
			usedMemory += len;      /* track memory usage */
		}
	return nlines;
}

/* getLine: get line into s, return length of s -- pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}
	if ( c == '\n') {
		*s++ = c;
		++len;
	}
	*s = '\0';
	return len;
}

/* isDigitStr: check if string is made of positive integers characters. Return
 * 1 if true; 0 if false */
int isDigitStr(char *s[])
{
	int i;

		for (i = 0; (*s)[i]; ++i)   /* omitted '\0', since s is a pointer */
			if (!isdigit((*s)[i]))
				return 0;
	return 1;
}

int main(int argc, char *argv[])
{
	int nlines;                   /* number of input lines read */
	char memory[MEMORYSIZE];      /* stored lines */
	int type;                     /* type of argument operator */
	int i;                        /* index variable */
	int n;                        /* cli argument value of n */

	while (--argc > 0) {
		type = *(++argv)[0];
		switch (type) {
		case ('-'):
			n = *++argv[0];
			if (isDigitStr(argv)) {
				n = atoi(*argv);
				argc = 0;         /* signal to exit loop */
			}
			else {
				n = 0;            /* signal invalid value */
				argc =0;
			}
			break;
		default:
			n = 0;                /* signal invalid input */
			argc = 0;
			break;
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES, memory)) >= 0) {
		if (n <= 0 || n > nlines) /* check input or value of argument */
			n = N;                /* default to N, if unreasonable */
		for (i = 0; i < n; ++i)
			printf("%s\n", lineptr[(nlines - n) + i]);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
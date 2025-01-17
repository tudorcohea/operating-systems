/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>

static int data[] = {10, 20, 30, 40};	/* stored in .data section (rw-) */

static void exec_do_nothing(void)	/* stored in .text section (r-x) */
{
}

static void do_write(const char *msg, void *address, int value)
{
	puts(msg);
	* (int *) address = value;
}

/*
	cum avem acces la un array de int-uri 

	((int *)arr)[10]
	(*(int *)arr + 10)
	*(int *)(arr + sizeof(int) * 10)
*/

/*
	char *f = malloc(100 * sizeof(int))
	char *f = malloc(100 * sizeof(*f))
	-> mai buna asta a doua pentru ca daca schimb
	tipul de date nu mai trebuie schimbat si in parateza 

*/

/*

	int **matrix, n, m;
	matrix = malloc(n * sizeof(*matrix));
	for (int i = 0; i < ; i++) {
		matrix[i] = malloc(m * sizeof(**matrix));
	}

*/
static void do_read(const char *msg, void *address)
{
	int p;

	puts(msg);
	p = * (int *) address;
	(void) p;
}

static void do_exec(const char *msg, void *address)
{
	void (*f)(void) = (void (*)(void)) address;

	puts(msg);
	f();
}

int main(void)
{
	do_read("reading from .data section", &data[0]);
	do_write("writing to .data section", &data[0], 77);

	do_read("reading from .text section", exec_do_nothing);
	do_exec("executing .text section", exec_do_nothing);

	/* These won't work due to permission issues. */
	//do_exec("executing .data section", &data[0]);
	//do_write("writing to .text section", exec_do_nothing, 77);
	//do_read("reading from NULL", NULL);

	return 0;
}

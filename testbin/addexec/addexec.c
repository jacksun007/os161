/*
 * Simple program to add two numbers (given in as arguments). Used to
 * test argument passing to child processes.
 *
 * Intended for the basic system calls assignment; this should work
 * once execv() argument handling is implemented.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char *argv[])
{
  	char progname[] = "add";
	char * args[4];

	if (argc != 3) {
		errx(1, "Usage: addexec num1 num2");
	}

	args[0] = progname;
	args[1] = argv[1];
	args[2] = argv[2];
	args[3] = NULL;
	execv("testbin/add", args);
	warnx("execv");
	return 0;
}

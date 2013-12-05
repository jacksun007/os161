/*
 * console.c
 *
 * Tests basic functionalities within stdio.h and err.h
 * This should work once read() and write() system calls are complete. However,
 * you should try testbin/printf first.
 *
 * Kuei (Jack) Sun
 * E-mail: <kuei.sun@utoronto.ca>
 *
 * University of Toronto, 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

void printstring(const char * str) {
    size_t len = strlen(str);
    int actual = write(STDOUT_FILENO, str, len);
    if ( actual < 0 )
        err(1, "write");
    if ( actual != (int)len )
        warnx("return value of write does not equal to input length\n");
}

int
main() {
    char ch;
    
    printf("1. writing to stdout... ");
    printstring("hello world!\n");
 
    printf("2. writing to stderr... ");
    warnx("false warning!");
    
    printf("3. reading from stdin...\n");
    printf("Press Enter: ");
    ch = getchar();
    if ( ch != '\n' && ch != '\r' ) {
        printf("fail to read newline or carriage return from stdin "
               "(got 0x%x)\n", (unsigned)ch);
    }
    else {
        printf("passed.\n");
    }
    
    printf("Press Backspace: ");
    ch = getchar();
    if ( ch == '\b' || ch == 127 ) {
        printf("passed.\n");
    }
    else {
        printf("fail to read backspace or delete from stdin "
               "(got 0x%x)\n", (unsigned)ch);    
    }
    
    printf("Press 6: ");
    if ( (ch = getchar()) != '6' ) {
        printf("fail to read the 6 from stdin (got 0x%x)\n", (unsigned)ch);
    }
    else {
        printf("passed.\n");
    }
    
	return 0;
}

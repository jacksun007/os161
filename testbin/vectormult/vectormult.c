/* vectormult1.c 
 *    Test program to do modulo vector multiplication on two large arrays.
 *
 *    Intended to stress virtual memory system and copy-on-write implementation.
 *
 *    Once the VM system assignment is complete your system should be
 *    able to survive this.
 */

#include <unistd.h>
#include <stdio.h>
#include <err.h>

#define Dim 8192
#define RIGHT  5591040		/* correct answer */

int A[Dim];
int B[Dim];

#define NR_CHILDREN 20

int
main()
{
        int sum = 0;
        int child = 0;
        int i;
        int pid_list[NR_CHILDREN];

        /* first initialize the vectors */
        for (i = 0; i < Dim; i++) {
                A[i] = i;
                B[i] = Dim - i;
        }

        while (child < NR_CHILDREN) {
                int pid = fork();
                if (pid < 0) {
                        warn("fork");
                        return 1;
                }
                if (pid == 0) { /* multiply the vectors */
                        for (i = 0; i < Dim; i++) {
                                sum += A[i] * B[i];
                                sum &= 0xffffff;
                        }
                        if (sum != RIGHT) {
                                printf("sum = %d\n", sum);
                                return 1;
                        }
                        return 0;
                }
                pid_list[child++] = pid;
        }
        for (i = 0; i < NR_CHILDREN; i++) {
                int status;
                if (waitpid(pid_list[i], &status, 0) < 0) {
                        warn("waitpid");
                        return 1;
                }
                if (status != 0) {
                        warnx("child %d failed\n", i);
                        return 1;
                }
        }
        printf("Passed.\n");
        return 0;
}

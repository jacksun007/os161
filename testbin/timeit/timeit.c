/*
 * timeit.c
 * 
 * Checks how much time it takes to run a specified program NUM times
 *
 * Kuei Sun <kuei.sun@utoronto.ca>
 *
 * University of Toronto, 2016
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct timespec
{
        time_t        tv_sec;
        unsigned long tv_nsec;
};

static int 
runprogram(int nruns, char * args[])
{
        int i;

        printf("running %s %d times...\n", args[0], nruns);
        for (i = 0; i < nruns; ++i) {
                pid_t pid;

                if ((pid = fork()) == 0) {
                        execv(args[0], args);
                        warn("execv");
                        _exit(-1);
                }
                else if (pid > 0) {
                        int x; 
                        if (waitpid(pid, &x, 0) < 0) {
                                warn("waitpid");
                        return -1;
                        }

                        /* don't care */
                        (void)x;
                }
                else
                {
                        warn("fork");
                        return -1;
                }
        }
        
        return 0;
}

void
print_timepsec(const char * msg, struct timespec * ts)
{
        printf("%s %d.%09lu seconds\n", msg, ts->tv_sec, ts->tv_nsec);
}

int
usage(void)
{
        printf("usage: timeit NUM PROG [ARGS...]\n");
        _exit(-1);
}

int
main(int argc, const char * argv[])
{
        struct timespec before, after;
        time_t ret;
        int nruns = 0;

        if (argc < 3) {
                usage();
        }
        
        nruns = atoi(argv[1]);
        if (nruns <= 0) {
                printf("timeit: NUM must be greater than 0\n");
                usage();
        }
        
        ret = __time(&before.tv_sec, &before.tv_nsec);
        if (ret != before.tv_sec) {
                printf("timeit: failed. inconsistent seconds returned\n");
                return -1;
        }
        print_timepsec("before:", &before);
        
        if (runprogram(nruns, (char **)(argv+2)) < 0) {
                printf("timeit: failed. cannot run program %d times\n", nruns);
                return -1;
        }
    
        after.tv_sec = __time(NULL, &after.tv_nsec);
        print_timepsec("after: ", &after);
        
        if ((after.tv_sec  <  before.tv_sec) ||
           ((after.tv_sec  == before.tv_sec) && 
            (after.tv_nsec <= before.tv_nsec))) {
                printf("timeit: failed. time after <= time before\n");
                return -1;
        }
        else {
                ret = time(NULL);
                if (ret < after.tv_sec) {
                        printf("timeit: failed. %d < time after\n", ret);
                        return -1;
                }
        }
        
        printf("timeit: all tests passed\n");
        return 0;
}


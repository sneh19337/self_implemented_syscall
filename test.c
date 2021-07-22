#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include<sys/wait.h>
#include<time.h>
#include <sys/resource.h>
#include<errno.h>
#include<string.h>


int fib(int n);
        int main()
        {
        int pid;
        long s_runtime;

        double start_time,end_time;
        double time;
        int ze=0;
        int fo=40;
        int i;
        struct timespec start, stop;

        printf("Time taken without soft realtime guarantees:\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        //start_time =  clock();
            i = 0;
            while (i < 5) {
            if(fork() == 0)
            {
            //end_time=clock();
            //time =(-1)*(end_time- start_time)/(CLOCKS_PER_SEC);
                 clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
            double results = 10000+(stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
            printf("Processes %d: %f sec\n", i + 1, results);
            exit(0);
            }
                i++;
            }
            if (i > 0) {
                do {
                    wait(NULL);
                    i--;
                } while (i > 0);
            }
            

        printf("Time taken with soft realtime guarantees:\n");
       // start_time = clock();
       clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            i = 0;
            while (i < 5) {
            if(fork() == 0)
            {
                if (i == 0) {
                    s_runtime = 400000000;
                } else {
                    if (i == 1) {
                        s_runtime = 300000000;
                    } else {
                        if (i == 2) {
                            s_runtime = 200000000;
                        } else {
                            if (i == 3) {
                                s_runtime = 100000000;
                            } else {
                            if(i==4)
                                    {s_runtime = 50000000;}
                                    else {
                                s_runtime = ze;
                            }
                            }
                        }
                    }
                }
            long tmp = syscall(440,getpid(), s_runtime);
            printf("Error No.: %d\n\n", errno);
            printf("Error :%s\n",strerror(errno));
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
            double results =10000+ (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
            //end_time=clock();
            //time =(-1)*(end_time- start_time)/(CLOCKS_PER_SEC);
            printf("Processes %d: %f sec\n", i + 1, results);
            exit(0);
            }
                i++;
            }
            if (i > 0) {
                do {
                    wait(NULL);
                    i--;
                } while (i > 0);
            }


        return 0;

        }
        
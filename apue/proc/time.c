#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/times.h>

static void pr_times(clock_t, struct tms*, struct tms*);
static void do_cmd(const char *);


/*根据 status的至判断得到子进程推出的状态*/
void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("子进程正常终止, exit status = %d\n",
        WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("子进程异常终止, signal number = %d%s\n",
        WTERMSIG(status),
    #ifdef WCOREDUMP //如果定义了 WCOREDUMP宏会产生终止进程的core文件
        WCOREDUMP(status) ? "(core file generated)":"");
    #else
        "");
    #endif
    
    else if(WIFSTOPPED(status))
        printf("子进程停止, singal number = %d\n",
        WSTOPSIG(status));
}

int main(int argc, char const *argv[])
{
    int i;

    setbuf(stdout, NULL);
    for(i=1;i<argc;i++)
        do_cmd(argv[i]);

    return 0;
}

static void do_cmd(const char *cmd)
{
    struct tms tmsstart, tmsend;
    clock_t start, end;
    int status;

    printf("\n command: %s\n",cmd);

    start = times(&tmsstart);

    status = system(cmd);

    end = times(&tmsend);

    pr_times(end-start, &tmsstart, &tmsend);
    pr_exit(status);
}

static void
pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck =0;
    if(clktck == 0)
        clktck = sysconf(_SC_CLK_TCK);
    
    printf(" real: %7.2f\n",real /(double)clktck);
    printf(" user: %7.2f\n",
        (tmsend->tms_utime - tmsstart->tms_utime)/(double) clktck);
    printf(" sys: %7.2f\n",
        (tmsend->tms_stime - tmsstart->tms_stime)/(double) clktck);
    printf(" child user: %7.2f\n",
        (tmsend->tms_cutime - tmsstart->tms_cutime)/(double) clktck);
    printf(" child sys: %7.2f\n",
        (tmsend->tms_cstime - tmsstart->tms_cstime)/(double) clktck);
}

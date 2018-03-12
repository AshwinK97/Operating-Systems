#define _POSIX_SOURCE

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
  int status;
  pid_t pid;

  pid = fork();

  if(pid == 0){
    execvp("./process", NULL);
  } else if(pid < 0){
    status = -1;
  } else {
    sleep(5);
    kill(pid, SIGSTOP);
    sleep(10);
    kill(pid, SIGCONT);

    if(waitpid(pid, &status, 0) != pid){
      status = -1;
    }

    printf("%d\n", status);
  }

  return 0;
}
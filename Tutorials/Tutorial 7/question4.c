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
  }

  sleep(5);
  kill(pid, SIGSTOP);
  sleep(10);
  kill(pid, SIGCONT);

  waitpid(pid, &status, NULL);

  return 0;
}
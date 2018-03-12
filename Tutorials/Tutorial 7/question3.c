#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
  pid_t pid = fork();
  int status;

  if (pid == 0){
    execvp("./process", NULL);
  } else if(pid < 0){
    status = -1;
  } else {
    sleep(5);
    kill(pid, SIGINT);
  }

  return 0;
}
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

  if (pid == 0){
    execvp("./process", NULL);
  }

  sleep(5);
  kill(pid, SIGINT);
}
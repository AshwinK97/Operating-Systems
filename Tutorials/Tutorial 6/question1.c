#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILE1 "child1.txt"
#define FILE2 "child2.txt"

int main() {
	pid_t pid1, pid2;
	char buffer[20];

	if ((pid1 = fork()) == 0) { // child 1
		sleep(1);
		FILE *fp = fopen(FILE1, "r");
		fgets(buffer, 20, fp);
		fclose(fp);
		printf("%s\n", buffer);
	} 
	else {
		if ((pid2 = fork()) == 0) { // child 2
			sleep(1);
			FILE *fp = fopen(FILE2, "r");
			fgets(buffer, 20, fp);
			fclose(fp);
			printf("%s\n", buffer);
		} 
		else { // parent
			FILE *fp1 = fopen(FILE1, "w");
			FILE *fp2 = fopen(FILE2, "w");
			fprintf(fp1, "child 1");
			fprintf(fp2, "child 2");
			fclose(fp1);
			fclose(fp2);
			printf("I am the parent\n");
			
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	
}

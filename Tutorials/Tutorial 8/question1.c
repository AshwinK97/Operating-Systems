#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INFILE "processes_tree.txt"

struct proc {
  char parent[256];
  char name[256];
  int priority;
  int memory;
};

struct proc_tree {
  struct proc data;
  struct proc_tree *left;
  struct proc_tree *right;
};

struct proc_tree *addNode(struct proc *node, struct proc_tree *tree){
  if (tree == NULL){
    tree = malloc(sizeof(struct proc_tree));
    tree->data = *node;
  } else {
    struct proc *current_node = &tree->data;
    char* current_parent = current_node->parent;

    // Make a recursive system to add nodes based on parent
    // data in current node and new node
  }

  return tree;
}

void read_file(struct proc_tree *tree) {
	FILE *fp = fopen(INFILE, "r");
	char line[255];
	char *token;
	struct proc *node;

	while(fgets(line, sizeof(line), fp) != NULL) {	

		// allocate new proc struct
		node = malloc(sizeof(struct proc));

		// get parent
		token = strtok(NULL, ",");
		strcpy(node->parent, token);

		// get name
		token = strtok(line, ",");
		strcpy(node->name, token);
		
		// get priority
		token = strtok(NULL, ",");
		sscanf(token, "%d", &node->priority);

		// get runtime
		token = strtok(NULL, "\n");
		sscanf(token, "%d", &node->memory);
		
		// add to binary tree
    addNode(node, tree);
	}
}

int main(void)
{
  struct proc_tree *tree;


  return 0;
}

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

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

void print_node(struct proc *node) {
	printf("%s\n", "----------------");
	printf("Parent: %s\n", node->parent);
	printf("Name: %s\n", node->name);
	printf("Priority: %d\n", node->priority);
	printf("Memory: %d\n", node->memory);
	printf("%s\n", "----------------");
	printf("\n");
}

void print_tree(struct proc_tree *tree) {
	if (tree != NULL) {
		struct proc *node = &tree->data;
		print_node(node);
		print_tree(tree->left);
		print_tree(tree->right);
	}
}

void addNode(struct proc *node, struct proc_tree **tree) {
	if (*tree == NULL) {
		struct proc_tree *temp = malloc(sizeof(struct proc_tree));
		temp->data = *node;
		temp->left = NULL;
		temp->right = NULL;
		*tree = temp;
		return;
	}
	
	struct proc *current_node = &(*tree)->data;

	if (strcmp(current_node->name, node->parent) <= 0)
		addNode(node, &(*tree)->left);
	else
		addNode(node, &(*tree)->right);	
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
		token = strtok(line, ",");
		strcpy(node->parent, token);

		// get name
		token = strtok(NULL, ",");
		strcpy(node->name, token);

		// get priority
		token = strtok(NULL, ",");
		sscanf(token, "%d", &node->priority);

		// get runtime
		token = strtok(NULL, "\n");
		sscanf(token, "%d", &node->memory);

		// add to binary tree
		print_node(node);
		addNode(node, &tree);
	}
}

int main() {
	struct proc_tree *tree;
	tree = NULL;
	read_file(tree);
	//print_node(&tree->data);
	print_tree(tree);

	return 0;
}

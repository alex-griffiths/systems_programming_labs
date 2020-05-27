#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int word_count(char *file_name);

int main(int argsc, char **argsv) {
	char *file_name;
	if (argsc < 2) {
		perror("word count missing arguments");
	} else {
		file_name = argsv[1];
	}
	
	FILE *fp = fopen(file_name, "r");
	if (!fp) die("fopen failed");
	
	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_length;
	
	while ((line_length = getline(&line, &line_cap, fp)) != -1) {
		
	}
}

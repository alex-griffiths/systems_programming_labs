#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

struct stat show_stat_info(char *, struct stat *);
void do_ls(char []);

void main(int argc, char *argv[]) {
	struct stat info; // file info buffer
	
	if (argc > 1) {
		while(--argc) {
			// Decrementing the arg counter allows multiple file paths to be passed
			// to the program
			printf("%s: \n", *++argv );
			do_ls(*argv);
		}
	} else {
		do_ls(".");
	}
	
}

void do_ls(char dirname[]) {
	DIR *dir_ptr;
	struct dirent *direntp;
	
	if ((dir_ptr = opendir(dirname)) == NULL) {
		fprintf(stderr, "ls2: cannot open %s\n", dirname);
	} else {
		
		while ((direntp = readdir(dir_ptr)) != NULL) {
			struct stat file_info;
			if (stat(direntp->d_name, &file_info) != -1) {
				printf("%ld %o %ld %d %d %ld %ld %s\r\n", 
											file_info.st_ino, 
											file_info.st_mode, 
											file_info.st_nlink, 
											file_info.st_uid,
											file_info.st_gid,
											file_info.st_size,
											file_info.st_mtime, 
											direntp->d_name);
			}
		}
		closedir(dir_ptr);
	}
}

// mkdir -p ./a/b/d ./a/b/e ./a/b/f ./a/c/g ./a/c/h
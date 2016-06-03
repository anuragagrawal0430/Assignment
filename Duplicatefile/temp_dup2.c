#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

char ipath[FILENAME_MAX];
int count1;
int count2;


void rec_dir(char path[FILENAME_MAX],struct stat s)
{
	DIR *d;
	struct dirent *dir;
	char tpath[FILENAME_MAX]="";
	d = opendir(path);
		if (d == NULL) {
			fprintf(stderr, "Error : Failed to open input directory - %s\n",
					strerror(errno));
			//return 1;
		}
		printf("\n=================================================\n");
		if (d) {

			while ((dir = readdir(d)) != NULL) {

				if (!strcmp(dir->d_name, "."))
					continue;
				if (!strcmp(dir->d_name, ".."))
					continue;

				printf("\n****************************\n");
				printf("\n%s\n", dir->d_name);
				strcpy(tpath, path);
				strcat(tpath, "/");
				strcat(tpath, dir->d_name);

				if (stat(tpath, &s) == 0) {
					if (s.st_mode & S_IFDIR) {
						++count1;
						printf("\ndirectory\n");
						rec_dir(tpath,s);
					} else if (s.st_mode & S_IFREG) {
						++count2;
						printf("\nfile\n");
					} else {
						printf("\n%s is something else", dir->d_name);
					}
				} else {
					printf("\nError..");
					//return 0;
				}
				printf("\n****************************\n");
				tpath[FILENAME_MAX] = "";
			}
			closedir(d);
		}
		printf("\n=================================================\n");
}


int main(void) {

	struct stat s;
	char path[FILENAME_MAX] = "";
	count1 = 0;
	count2=0;

	printf("\nEnter Path::");
	scanf("%s", ipath);

	rec_dir(ipath,s);

	printf("\n\n\nNumber of directories::%d",count1);
	printf("\n\n\nNumber of files::%d",count2);
	return (0);
}


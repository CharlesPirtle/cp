#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int sizef(char *file_name){
  struct stat fileStat;
  stat(file_name,&fileStat);
  return (fileStat.st_size);
}




int main(int argc, char* argv[]){
  if(argv[1]!=NULL){
    if(strcmp(argv[1], "--help")==0){
      printf("Usage: SOURCE DEST\n");
      printf("  or:  SOURCE... DIRECTORY\n");
      printf("  or:  DIRECTORY SOURCE...\n");
      printf("Copy SOURCE to DEST, or to DIRECTORY.\n");
      return 0;
    }
  }

  if(argc==1){
    printf("cp: missing file operand\n");
    printf("Try 'cp --help' for more information.\n");
    return 0;
  }
  if(argc==2){
    printf("cp: missing destination file operand after '%s'\n",argv[1]);
    printf("Try 'cp --help' for more information.\n");
    return 0;
  }

  if( access( argv[1], F_OK ) == -1 ) {
    printf("cp: cannot stat %s: No such file or directory\n",argv[1]);
    return 0;
  }





  char *c = (char *) calloc(100, sizeof(char));

  int a = open(argv[1],O_RDONLY);
  int b=read(a,c,sizef(argv[1]));
  int fd=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC ,0777);

  write(fd, c, sizef(argv[1]));
  printf("Ran Successfully...\n");
  close(a);
  close(fd);


  return 0;
}

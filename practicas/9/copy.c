#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  char *sourceFile = argv[1];
  char *destinationFile = argv[2];
  int sFd = open(sourceFile, O_RDONLY, 0);
  if(sFd < 0) {
    printf("Error al abrir el archivo\n");
    return 1;
  }
  int dFd = open(destinationFile, O_WRONLY|O_CREAT, 0600);
  char c;
  while(read(sFd, &c, 1)) {
    write(dFd, &c, 1);
  }
  close(sFd);
  close(dFd);
  return 0;
}
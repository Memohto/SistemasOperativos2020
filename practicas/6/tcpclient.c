#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// extern int h_errno;

int main(int argc, char **argv) {
  char *hostName = argv[1];
  char c;
  struct sockaddr_in serverAddress;
  struct hostent *serverInfo = gethostbyname(hostName);

  bzero(&serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  // serverAddress.sin_addr = serverInfo->h_addr_list[0]; // no se puede
  bcopy((char *)serverInfo->h_addr, 
    (char *)&serverAddress.sin_addr.s_addr, serverInfo->h_length);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(connect(sockfd, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
    printf("Connection error!!\n");
  }

  char *message = "GET / HTTP/1.0\r\n\r\n";
  write(sockfd, message, strlen(message));

  while(read(sockfd, &c, 1)) {
    printf("%c", c);
  }
  printf("\n");
  
  close(sockfd);
  return 0;
}
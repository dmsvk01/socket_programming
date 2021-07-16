#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT 7777
#define BACKLOG 10

int main(void) {
  int sockfd, new_fd;

  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  int sin_size;

  //PF_INET는 ipv4 protocol을 의미한다.
  if((sockfd = socket(PF_INET, SOCK_STREAM, 0)==-1)){
    perror("socket error");
    exit(1); // 프로그램이 불완전하게 종료됨을 표시 exit(0)은 성공적으로 종료됨을 의미한다.
  } 

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);

  //my_addr.sin_addr = htonl(ANY);
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 31529
#define BACKLOG 10

int main(void) {
  int sockfd, new_fd;

  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  socklen_t sin_size;
  //PF_INET는 ipv4 protocol을 의미한다.
  if( ( (sockfd = socket(PF_INET, SOCK_STREAM, 0) ) == -1 ) ){
    perror("socket error");
    exit(1); // 프로그램이 불완전하게 종료됨을 표시 exit(0)은 성공적으로 종료됨을 의미한다.
  } 

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1){
    perror("bind!");
    exit(1);
  }

  if(listen(sockfd, BACKLOG) == -1){
    perror("listen");
    exit(1);
  }
  while(1){
    sin_size = sizeof(struct sockaddr_in);
    if((new_fd = accept(sockfd, (struct sockaddr*) &their_addr, &sin_size)) == -1){
      perror("accept");
      continue;
    }
    printf("server : got connnection from %s\n", inet_ntoa(their_addr.sin_addr));
    printf("new_fd : %d\n", new_fd);
    char str[] = "hello my name is EC";
    write(new_fd, str, sizeof(str));
  }
    close(sockfd);  
    close(new_fd);
}

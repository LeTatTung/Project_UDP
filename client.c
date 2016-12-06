#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <sys/select.h>

#include "define.c"
#include "input.c"
#include "string_handling.c"
#include "display.c"

int check_mark(char* message){

  for(int i =0; i< strlen(message);i++){
    if(message[i] == '|'){
     if(message[i+1] == '1')
      return 1;
    else
      return 0;
    }
  }
  return 0;
}
int login(int sockfd){
  char mesg[BUFLEN];
  int mark,n;

  strcpy(mesg,create_message(LOGIN, input_data()));

  send(sockfd, mesg,BUFLEN, 0);
  //printf("%s\n", mesg);
  //strcpy(mesg,"");
  n=recv(sockfd, mesg, BUFLEN, 0);
  //printf("%s\n", mesg);
  mark= check_mark(mesg);
  if(mark == 1) {
    printf("\nDang nhap thanh cong !");
    return 1;
}
  else {
    printf("\nTai khoan hoac mat khau khong dung!!");
    return 0;
}
}
int sign_up(int sockfd){
   char mesg[BUFLEN];
  int mark,n;

  strcpy(mesg,create_message(SIGN_UP, input_data()));
  send(sockfd, mesg,strlen(mesg), 0);
  strcpy(mesg,"");
  n=recv(sockfd, mesg, BUFLEN, 0);
  mark= check_mark(mesg);

  if(mark == 1) {
    printf("\nDang ki thanh cong !");
    return 1;
}
  else {
    printf("\nTai khoan da ton tai!!");
    return 0;
}
}
int menu(int sockfd){

   int choice = 0;
   do{
    choice = display_unlock();
    switch (choice) {
      // Tien lap them chuc nang cu the vao nhe
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
          printf("Go to Home\n\n");
        return 1;
        default:
        break;
    }
   }while(choice !=4);
}


void main(){

  int sockfd,sentBytes, recvBytes,n=0,port;
  struct sockaddr_in serv_addr;
  char mesg[BUFLEN];
  char recv_b[BUFLEN];
  int choice, check;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER, &serv_addr.sin_addr);
  size_t size =100;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\nLoi tao socket!!");
    }
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\nXay ra loi ket noi!!\n");
       return ;
    }else
    while(1){
        choice = display_lock();
        switch (choice) {
    case 1:
    check = sign_up(sockfd);
    if(check == 1){
        menu(sockfd);
    }
      break;
    case 2:
    check = login(sockfd);
  //  printf("%d\n", sockfd);
    if(check == 1){
        menu(sockfd);
    }
      break;
    case 3:
    printf("Ket thuc chuong trinh.\n");
      break;

    }
    if(choice == 3)
      break;
    }

}

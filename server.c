#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* include fig01 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <poll.h>

//cau lenh chay server
// gcc -o server server.c `mysql_config --cflags --libs`

#include "sql.c"
// LOGIN tra ve id cua tai khoan neu login thanh cong
int login(char *message){

  char *name;
  char *pass;
  char *mesg =  malloc(sizeof(char) *100);
  char *tmp;

  //strcpy(mesg, message);
  //s = strtok(mesg,"|");
  //printf("%s\n", s);
  name = strtok(NULL,"|");
  printf("%s\n", name);
  pass = strtok(NULL, "|");
  printf("%s\n", pass);
  tmp = get_pass_account(connect_mysql(),name);
  if( tmp!= NULL){
    if(strcmp(pass, tmp) == 0){
      return get_id_account(connect_mysql(),name);
    }else return 0;
  }
  return -1;

}
// SIGNUP return id cua tai khoan moi dang ki neu thanh cong
int sign_up(char *message){

  char *name;
  char *pass;
  char *s = malloc(sizeof(char)*3);
  char *mesg =  malloc(sizeof(char) *100);
  char *tmp;
  int id =0;
  //strcpy(mesg, message);
  //s = strtok(mesg,"|");
  //printf("%s\n", s);
  name = strtok(NULL,"|");
  printf("%s\n", name);
  pass = strtok(NULL, "|");
  printf("%s\n", pass);
  tmp = get_pass_account(connect_mysql(),name);
  if(tmp == NULL){
    // khong ton tai tai khoan trung username.Luc nay moi cho phep tao tk moi
    id = atoi( get_max_id(connect_mysql())) +1;
    sprintf(s, "%d", id);
    printf("%s\n", s);
    insert_data(connect_mysql(),s, name, pass);

  }
  return id;

}
void get_list_file(int sockfd, int id){

  char ** list_file = (char**)malloc(FILE_MAX*sizeof(char*));

  for(int i =0; i< FILE_MAX;i++){
    list_file[i] = (char*)malloc(sizeof(char)*BUFLEN);
  }

  int num_file = get_list_file_account(connect_mysql(),id,list_file);
  for(int i=0; i< num_file; i++){
    send(sockfd,list_file[i],BUFLEN,0);
    printf("%s\n", list_file[i]);
  }

  send(sockfd,"ENDLIST",10,0);
}
void main(){

        int listenSock, connSock;
        struct sockaddr_in serv_addr, cliaddr;
        int clientAddrLenght;
        char buf[BUFLEN];
        char tmp[BUFLEN];
        int t,n;
        int recvBytes,sentBytes;
        fd_set readfds,allset;
        int i, maxi,sockfd,nready,connfd;
        int rv;
        struct pollfd client[OPEN_MAX];
        socklen_t     clilen;
        int array_id[OPEN_MAX]; // mang cac id cua client




        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(PORT);


        if((listenSock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
            printf("\nTao socket loi!!\n");
            return;
        }
        if(bind(listenSock, (struct sockaddr *) &serv_addr,sizeof(serv_addr))<0) {
            printf("\nBind loi!!\n");
            return;
            }
        if(listen(listenSock, 10) == -1) {
            printf("\nListen loi!!\n");
            return;
        }
        client[0].fd = listenSock;
  client[0].events = POLLRDNORM;
  for (i = 1; i < OPEN_MAX; i++){
    client[i].fd = -1;    /* -1 indicates available entry */
    array_id[i] = -1;
  }
  maxi = 0;         /* max index into client[] array */
/* end fig01 */

/* include fig02 */
  for ( ; ; ) {
    nready = poll(client, maxi+1, 3);

    if (client[0].revents & POLLRDNORM) { /* new client connection */
      clilen = sizeof(cliaddr);
      connfd = accept(listenSock, (struct sockaddr *) &cliaddr, &clilen);
      //printf("new client: %s\n", Sock_ntop((SA *) &cliaddr, clilen));

      for (i = 1; i < OPEN_MAX; i++)
        if (client[i].fd < 0) {
          client[i].fd = connfd;  /* save descriptor */
          break;
        }
      if (i == OPEN_MAX)
        printf("too many clients");

      client[i].events = POLLRDNORM;
      if (i > maxi)
        maxi = i;       /* max index in client[] array */

      if (--nready <= 0)
        continue;       /* no more readable descriptors */
    }

    for (i = 1; i <= maxi; i++) { /* check all clients for data */
      if ( (sockfd = client[i].fd) < 0)
        continue;
      if (client[i].revents & (POLLRDNORM | POLLERR)) {
        if ( (n = recv(sockfd, buf, BUFLEN,0)) < 0) {
          if (errno == ECONNRESET) {
              /*4connection reset by client */
            printf("client[%d] aborted connection\n", i);
            close(sockfd);
            client[i].fd = -1;
          } else
            printf("read error");
        } else if (n == 0) {
            /*4connection closed by client */
          printf("client[%d] closed connection\n", i);
          close(sockfd);
          client[i].fd = -1;
        } else
          {
            printf("\nXau nhan tu Client: %s\n",buf );
            char *s = strtok(buf,"|");
            printf("%s\n", s);
            if(strcmp(s,"LOGIN") == 0){
              array_id[i] = login(buf);
              sprintf(tmp,"LOGIN|%d",array_id[i]);
              send(sockfd,tmp,BUFLEN,0);
              printf("%s\n", tmp);
            }else if(strcmp(s,"SIGN_UP") == 0){
              array_id[i] = sign_up(buf);
              sprintf(tmp,"SIGN_UP|%d",array_id[i]);
              send(sockfd,tmp,BUFLEN,0);
              printf("%s\n", tmp);
            }
            else if(strcmp(s,"LIST") == 0){
              // lay ra list cac file
              get_list_file(sockfd,array_id[i]);
            }
        }

        if (--nready <= 0)
          break;        /* no more readable descriptors */
      }
    }
  }
}
  /*                      printf("\nXau nhan tu Client: %s",buf );
                        //if(strcmp(strtok(buf,"|"),"LOGIN") == 0){
            //sprintf(tmp,"LOGIN|%d",login(buf));
              //writen(sockfd,tmp,BUFLEN);
              //printf("%s\n", tmp);
           // }
                    }

                if(--rv <= 0)
                    break;
                }
            }


    }//end while
}//end mains


          // Xu ly o trong day


*/

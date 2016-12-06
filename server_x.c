#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <poll.h>
#define LEN 1024
typedef struct{
  char tk[LEN];
  char pass[LEN];
  char nich_name[LEN];
  int status; //1 on, 0 off
  int sockfd;

} User;

typedef struct{
  char nich_name[LEN];
  int sockfd;
} User_t;

typedef struct{
  char room_name[LEN];
  User_t member[3];
  int max_mem;
}Room;
int check_user(char tk[],char pass[],User user[],int max_user){
  int i;


  for(i=0;i<max_user;i++){
      if(strcmp(tk,user[i].tk)==0){
        if(strcmp(pass,user[i].pass)==0) return 1;
      }
  }
  return 0;
}
int check_mark(char mesg[]){
  int mark;
  char mesg2[LEN];

  strcpy(mesg2,mesg);
  mark = atoi(strtok(mesg2,"|"));
  return mark;
}
void creat_mesg(int mark, char partner[],char buff1[],char buff2[],char buff3[],char mesg[]){

  char buff[LEN];
  char str_mark[10];
  char str_partner[10];
  snprintf(str_mark, 9, "%d", mark);

  strcpy(buff,"");
  strcat(buff,str_mark);
  strcat(buff,"|");
  strcat(buff,partner);
  strcat(buff,"|");
  strcat(buff,buff1);
  strcat(buff,"|");
  strcat(buff,buff2);
  strcat(buff,"|");
  strcat(buff,buff3);
  strcat(buff,"|");
  strcpy(mesg,"");
  strcpy(mesg,buff);

}
int take_user(User user[]){
  int max_user;
  int i=0;
  FILE *f;
  char ch[80];
  char *pch;

  f=fopen("user_list.txt","r");
  fgets(ch,79,f);
  while(!feof(f)){
    pch = strtok(ch,"|");
    strcpy(user[i].tk,pch);
    while(1){
      pch = strtok(NULL,"|");
      strcpy(user[i].pass,pch);
      pch = strtok(NULL,"|");
      strcpy(user[i].nich_name,pch);
      pch = strtok (NULL,"|");
      pch = strtok (NULL,"|");
      if (pch == NULL) break;
    }
    user[i].status = 0;
    user[i].sockfd = -1;
    i++;
    fgets(ch,79,f);
  }
  max_user = i;
  fclose(f);
  return max_user;

}
void login(int connSock,char mesg[], User user[], int max_user){
  char tk[LEN];
  char pass[LEN];
  char mesg2[LEN];
  char *pch;
  int t,i;
  char buff_ok[LEN]="1|0|0|0|0|";
  char buff_faile[LEN]="0|0|0|0|0|";

  strcpy(mesg2,mesg);
  pch = strtok(mesg2,"|");
  pch = strtok(NULL,"|");
  pch = strtok(NULL,"|");
  strcpy(tk,"");
  strcpy(tk,pch);
  pch = strtok(NULL,"|");
  strcpy(pass,"");
  strcpy(pass,pch);
  t = check_user(tk,pass,user,max_user);
  if(t == 1){
    printf("\nUser @%s da dang nhap!!",tk);
    //thay doi trang thai cua user thanh online
    for(i=0;i<max_user;i++){
      if(strcmp(tk,user[i].tk) == 0){
        if(user[i].status == 1){
          send(connSock, buff_faile, strlen(buff_faile), 0);//dang nhap that bai
          return;
        }
        else{
          user[i].status = 1;
          user[i].sockfd = connSock;
        }

      }
    }
    send(connSock, buff_ok, strlen(buff_ok), 0);//gui lai cho client da dang nhap thanh cong
  }else{
    printf("\nDang nhap that bai!!");
    send(connSock, buff_faile, strlen(buff_faile), 0);//dang nhap that bai
  }

}
int sign_up(int connSock,char mesg[], User user[],int max_user){
  int max_u;
  char tk[LEN];
  char pass[LEN];
  char nich_name[LEN];
  char mesg2[LEN];
  char *pch;
  int t,i;
  FILE *f;
  char buff_ok[LEN]="1|0|0|0|0|";
  char buff_faile[LEN]="0|0|0|0|0|";

  strcpy(mesg2,mesg);
  pch = strtok(mesg2,"|");
  pch = strtok(NULL,"|");
  pch = strtok(NULL,"|");
  strcpy(tk,pch);
  pch = strtok(NULL,"|");
  strcpy(pass,pch);
  pch = strtok(NULL,"|");
  strcpy(nich_name,pch);
  for ( i = 0; i < max_user; i++) {
    t=0;
    if(strcmp(tk,user[i].tk)==0) {t=1;break;}

  }
  if(t == 0){
    f = fopen("user_list.txt","a");
    fprintf(f,"%s|%s|%s|\n",tk,pass,nich_name);
    fclose(f);

    /*them user vua moi tao vao danh sach*/
    strcpy(user[max_user].tk,tk);
    strcpy(user[max_user].pass,pass);
    strcpy(user[max_user].nich_name,nich_name);
    user[max_user].status=1;
    user[max_user].sockfd = connSock;
    max_u = max_user + 1;
    printf("\nUser @%s da dang ki va dang dang nhap!!",tk );
    send(connSock, buff_ok, strlen(buff_ok), 0);//gui lai cho client da dang ki thanh cong
    return max_u;
  }else{
    send(connSock, buff_faile, strlen(buff_faile), 0);//dang ki that bai
    return max_user;
  }

}

void show_user_list(int sockfd,User user[], int max_user){
  int i,x,y,t;
  char buff[LEN]="2|0|";

  for ( i = 0; i < max_user; i++){
    if(user[i].status==1){
      if(user[i].sockfd!=sockfd){
        strcat(buff,user[i].nich_name);
        strcat(buff,"|");
      }
    }
  //strcat(buff,"|");
  }
  send(sockfd,buff,strlen(buff),0);
}
void chat_request(int sockfd,char mesg[],User user[],int max_user){
  int i,t,x,y;
  char mesg2[LEN],buff[LEN],buff2[]="0";
  char *pch;
  char nich_name[LEN];

  strcpy(mesg2,mesg);
  pch= strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(nich_name,pch);
  //x: nguoi nha
  //y: nguoi gui
  for(x=0; x<max_user;x++){
    if(user[x].status == 1){
      if(strcmp(nich_name,user[x].nich_name)==0) {
        i=1;
        break;
      }
    }
    i=0;
  }

  if(i==0){
    strcpy(buff,"5|0|0|0|0|");
    send(sockfd,buff,strlen(buff),0);
    return;
  }else{
    for(y=0;y<max_user;y++){
      if(user[y].sockfd == sockfd) break;
    }
  }
  creat_mesg(3,user[y].nich_name,buff2,buff2,buff2,buff);
  send(user[x].sockfd,buff,strlen(buff),0);
}

void accept_request(int sockfd, char mesg[],User user[], int max_user){
  int i,x,y,t;
  char mesg2[LEN],buff[LEN],buff2[LEN]="0",nich_name[LEN];
  char *pch;

  strcpy(mesg2, mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(nich_name,pch);
  //x: nguoi gui mesg chap nhan
  //y: nguoi nhan
  for (x = 0; x < max_user; x++)  {
    if(user[x].sockfd==sockfd) break;
  }
  for (y = 0; y < max_user; y++){
    if(user[y].status==1){
      if(strcmp(user[y].nich_name,nich_name)==0) {
        i=1;
        break;
      }
    }
    i=0;
  }
  if(i==0){
    creat_mesg(7,user[y].nich_name,buff2,buff2,buff2,buff);
    send(sockfd,buff,strlen(buff),0);
  }else{
    creat_mesg(4,user[x].nich_name,buff2,buff2,buff2,buff);
    send(user[y].sockfd,buff,strlen(buff),0);
  }

}
void not_accept_request(int sockfd, char mesg[],User user[], int max_user){
  int i,x,y,t;
  char mesg2[LEN],buff[LEN],buff2[LEN]="0",nich_name[LEN];
  char *pch;

  strcpy(mesg2, mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(nich_name,pch);
  //x: nguoi gui
  //y: nguoi nhan
  for (x = 0; x < max_user; x++)  {
    if(user[x].sockfd==sockfd) break;
  }
  for (y = 0; y < max_user; y++){
    if(user[y].status==1){
      if(strcmp(user[y].nich_name,nich_name)==0) break;
    }
  }
  creat_mesg(5,user[x].nich_name,buff2,buff2,buff2,buff);
  send(user[y].sockfd,buff,strlen(buff),0);

}
void chatting(int sockfd, char mesg[],User user[], int max_user){
  int i,x,y,t;
  char mesg2[LEN],buff[LEN],buff2[LEN]="0",buff3[LEN],nich_name[LEN];

  char *pch;

  strcpy(mesg2, mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(nich_name,pch);
  pch=strtok(NULL,"|");
  strcpy(buff3,pch);
  //x: nguoi gui
  //y: nguoi nhan
  for (x = 0; x < max_user; x++)  {
    if(user[x].sockfd==sockfd) break;
  }
  for (y = 0; y < max_user; y++){
    if(strcmp(user[y].nich_name,nich_name)==0){
      if(user[y].status==1){
        i=1;
        break;
      }
    }
    i=0;
  }
  if(i==0){
    creat_mesg(7,nich_name,buff2,buff2,buff2,buff);
    send(sockfd,buff,strlen(buff),0);
  }else{
    creat_mesg(6,user[x].nich_name,buff3,buff2,buff2,buff);
    send(user[y].sockfd,buff,strlen(buff),0);
  }
}
void stop_chat(int sockfd,char mesg[],User user[], int max_user){
  int i,x,y,t;
  char mesg2[LEN],buff[LEN],buff2[LEN]="0",nich_name[LEN];
  char *pch;

  strcpy(mesg2, mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(nich_name,pch);
  //x: nguoi gui
  //y: nguoi nhan
  for (x = 0; x < max_user; x++)  {
    if(user[x].sockfd==sockfd) break;
  }
  for (y = 0; y < max_user; y++){
    if(user[y].status==1){
      if(strcmp(user[y].nich_name,nich_name)==0) break;
    }
  }
  strcpy(buff,"");
  creat_mesg(7,user[x].nich_name,buff2,buff2,buff2,buff);
  send(user[y].sockfd,buff,strlen(buff),0);


}

void show_room_list(int sockfd,Room room[]){
  int i,x;
  char mesg[LEN];
  char str_max_mem[4];


  strcpy(mesg,"8|");
  for(i=0;i<10;i++){
    strcat(mesg,room[i].room_name);
    strcat(mesg,"|");
    snprintf(str_max_mem, 9, "%d", room[i].max_mem);
    strcat(mesg,str_max_mem);
    strcat(mesg,"|");
    x=0;
    while(1){
      if(x==room[i].max_mem) break;
      strcat(mesg,room[i].member[x].nich_name);
      strcat(mesg,"|");
      x++;
    }
  }
  send(sockfd,mesg,strlen(mesg),0);

}

void join_room(int sockfd,char mesg[],Room room[],User user[],int max_user){
  int i,x;
  char mesg2[LEN],buff[LEN]="10|",buff2[LEN]="9|";
  char *pch;
  char room_name[LEN];
  char nich_name[LEN];



  for(i=0;i<max_user;i++){
    if(user[i].sockfd==sockfd) strcpy(nich_name,user[i].nich_name);
  }
  strcpy(mesg2,mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(room_name,pch);
  strcat(buff2,room_name);
  strcat(buff2,"|");
  strcat(buff,room_name);
  strcat(buff,"|");
  strcat(buff,room_name);
  strcat(buff,"|@");
  strcat(buff,nich_name);
  strcat(buff," DA THAM GIA ROOM|");

  for(i=0;i<10;i++){
    if(strcmp(room_name,room[i].room_name)==0){
      if(room[i].max_mem<3){
        strcpy(room[i].member[room[i].max_mem].nich_name,nich_name);
        room[i].member[room[i].max_mem].sockfd=sockfd;
        room[i].max_mem++;
        break;
      }else {
        send(sockfd,buff2,strlen(buff2),0);
        return;
      }
    }
  }
  for(x=0;x<room[i].max_mem;x++){
    send(room[i].member[x].sockfd,buff,strlen(buff),0);
  }


}

void out_room(int sockfd,char mesg[],Room room[],User user[],int max_user){
  int i,x;
  char mesg2[LEN],buff[LEN]="10|";
  char *pch;
  char room_name[LEN];
  char nich_name[LEN];



  for(i=0;i<max_user;i++){
    if(user[i].sockfd==sockfd) strcpy(nich_name,user[i].nich_name);
  }
  strcpy(mesg2,mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(room_name,pch);
  strcat(buff,room_name);
  strcat(buff,"|");
  strcat(buff,room_name);
  strcat(buff,"|@");
  strcat(buff,nich_name);
  strcat(buff," DA THOAT ROOM|");

  for(i=0;i<10;i++){
    if(strcmp(room[i].room_name,room_name)==0) break;
  }

  for(x=0;x<room[i].max_mem;x++){
    if(strcmp(nich_name,room[i].member[x].nich_name)==0) break;
  }
  if(x==room[i].max_mem) return;

  while(1){
    if(strcmp(room[i].member[x+1].nich_name,"")==0)
      break;
    strcpy(room[i].member[x].nich_name,room[i].member[x+1].nich_name);
    room[i].member[x].sockfd=room[i].member[x+1].sockfd;
    x++;
  }
  strcpy(room[i].member[x].nich_name,"");
  room[i].member[x].sockfd=-1;
  room[i].max_mem--;

  for(x=0;x<room[i].max_mem;x++){
    send(room[i].member[x].sockfd,buff,strlen(buff),0);
  }


}

void chat_room(int sockfd, char mesg[], Room room[]){
  int i,x;
  char mesg2[LEN],buff2[LEN],buff[LEN]="10|",buff3[LEN]="0";
  char *pch;
  char nich_name[LEN];
  char room_name[LEN];

  strcpy(mesg2,mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  strcpy(room_name,pch);
  pch=strtok(NULL,"|");
  strcpy(buff2,pch);

  for(i=0;i<10;i++){
    if(strcmp(room_name,room[i].room_name)==0) break;
  }
  for(x=0;x<room[i].max_mem;x++){
    if(room[i].member[x].sockfd==sockfd){
      strcpy(nich_name,room[i].member[x].nich_name);
      break;
    }
  }
  printf("%s\n",nich_name );
  creat_mesg(10,room_name,nich_name,buff2,buff3,buff);
  printf("%s\n",buff );
  for(x=0;x<room[i].max_mem;x++){
    send(room[i].member[x].sockfd,buff,strlen(buff),0);
  }

}

void log_out(int sockfd,User user[],int max_user){
  int i;
  for(i=0;i<max_user;i++){
    if(user[i].sockfd==sockfd){
      user[i].status=0;
      break;
    }
  }
}
void main(){
        int listenSock, connSock;
        struct sockaddr_in serv_addr, client_addr;
        int clientAddrLenght;
        User user[100];
        Room room[10];
        int max_user;
        char mesg[LEN];
        char mesg2[LEN];
        char buff[LEN]="11|";
        char mesg1[LEN]="1|0|tranha|aaa|0|";
        int t,n;
        int recvBytes,sentBytes;
        fd_set readfds,allset;
        int i, maxi,sockfd;
        int rv;
        struct pollfd client[30];




        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(5500);


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
        for ( i = 1; i < 30; i++){
            client[i].fd=-1;
        }
        client[0].fd = listenSock;
        client[0].events = POLLRDNORM;
        max_user= take_user(user);
        strcpy(room[0].room_name,"Vip1");
        strcpy(room[1].room_name,"Vip2");
        strcpy(room[2].room_name,"Vip3");
        strcpy(room[3].room_name,"Vip4");
        strcpy(room[4].room_name,"Vip5");
        strcpy(room[5].room_name,"Vip6");
        strcpy(room[6].room_name,"Vip7");
        strcpy(room[7].room_name,"Vip8");
        strcpy(room[8].room_name,"Vip9");
        strcpy(room[9].room_name,"Vip10");
        for ( i = 0; i < 10; i++){
          room[i].max_mem=0;
        }


    while(1){
      rv = poll(client, 30,3);

          if(client[0].revents & POLLRDNORM){
                clientAddrLenght=sizeof(client_addr);
                connSock = accept(listenSock, (struct sockaddr *) &client_addr, (socklen_t*)&clientAddrLenght);
                for(i=1;i < 30;i++){
                    if(client[i].fd < 0){
                        client[i].fd = connSock;
                        break;
                    }
                }//end for
                client[i].events = POLLRDNORM;
                if(--rv <= 0)
                    continue;
            }//end if
            for(i=1;i<30;i++){
                if((sockfd = client[i].fd) <0)
                    continue;
                if(client[i].revents & (POLLRDNORM | POLLERR)){
                    strcpy(mesg,"");
                    n=recv(sockfd, mesg, LEN, 0);
                    mesg[n]='\0';
                    if((n)==0){
                        close(sockfd);
                        client[i].fd = -1;
                        for ( i = 0; i < max_user; i++){
                          if(user[i].sockfd==sockfd){
                            user[i].status=0;
                            break;
                          }
                        }
                        for(i=0;i<10;i++){
                          strcat(buff,room[i].room_name);
                          strcat(buff,"|");
                          out_room(sockfd,buff,room,user,max_user);

                        }
                    }else{
                        printf("\nXau nhan tu Client: %s",mesg );
                        t=check_mark(mesg);
                        if(t == 0)  max_user = sign_up(sockfd,mesg,user,max_user);
                        if(t == 1)  {
                          login(sockfd,mesg,user,max_user);

                        }
                        if(t == 2)  show_user_list(sockfd,user,max_user);
                        if(t == 3)  chat_request(sockfd,mesg,user,max_user);
                        if(t == 4)  accept_request(sockfd,mesg,user,max_user);
                        if(t == 5)  not_accept_request(sockfd,mesg,user,max_user);
                        if(t == 6)  chatting(sockfd,mesg,user,max_user);
                        if(t == 7)  stop_chat(sockfd,mesg,user,max_user);
                        if(t == 8)  show_room_list(sockfd,room);
                        if(t == 9)  join_room(sockfd,mesg,room,user,max_user);
                        if(t == 10)     chat_room(sockfd,mesg,room);
                        if(t == 11) out_room(sockfd,mesg,room,user,max_user);
                        if(t == 12) log_out(sockfd,user,max_user);


                    }

                if(--rv <= 0)
                    break;
                }
            }


    }//end while
}//end mains

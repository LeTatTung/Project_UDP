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
#define LEN 1024
typedef struct{
  char nich_name[LEN];
  int type;

} User_List;
typedef struct{
  char room_name[LEN];
  User_List member[10];
  int max_mem;
} Room_List;
int check_xau(char buff[]){

  int i;

  for(i=0;i<strlen(buff);i++){
    if(buff[i] == '|') {
      printf("\nXau chua ki tu khong duoc cho phep!!");
      return 0;
    }
  }
  return 1;
}
int check_input(char buff[]){
  int i;

  if(strlen(buff)<=3 || strlen(buff)>=15) return 0;
  else return 1;

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
int login(int sockfd){
  char mesg[LEN];
  char partner[]="0";
  char tk[LEN];
  char pass[LEN];
  char nich_name[]="0";
  int mark,n;
  char str_mark;

  while(1){
    printf("\nNhap ten tai khoan: ");
    strcpy(tk,"");
    fgets(tk,LEN,stdin);
    tk[strlen(tk)-1]='\0';
    if(check_xau(tk) == 0 || check_input(tk) == 0){
      printf("\nMoi nhap lai!!");
    }else break;
  }
  while(1){
    printf("Nhap mat khau: ");
    strcpy(pass,"");
    fgets(pass,LEN,stdin);
    pass[strlen(pass)-1]='\0';
    if(check_xau(pass) == 0 || check_input(pass) == 0){
      printf("\nMoi nhap lai!!\n");
    }else break;

  }
  creat_mesg(1,partner,tk,pass,nich_name,mesg);
  send(sockfd, mesg,strlen(mesg), 0);
  strcpy(mesg,"");
  n=recv(sockfd, mesg, LEN, 0);
  mark= check_mark(mesg);
  if(mark == 1) {
    printf("\nDang nhap thanh cong");
    return 1;}
  else {
    printf("\nTai khoan hoac mat khau khong dung!!");
    return 0;}
}
int sign_up(int sockfd){
  char mesg[LEN];
  char partner[]="0";
  char tk[LEN];
  char pass[LEN];
  char nich_name[LEN];
  int mark;
  char str_mark;

  while(1){
    printf("\nNhap ten tai khoan: ");
    strcpy(tk,"");
    fgets(tk,LEN,stdin);
    tk[strlen(tk)-1]='\0';
    if(check_xau(tk) == 0 || check_input(tk) == 0){
      printf("\nMoi nhap lai!!");
    }else break;
  }
  while(1){
    printf("Nhap mat khau: ");
    strcpy(pass,"");
    fgets(pass,LEN,stdin);
    pass[strlen(pass)-1]='\0';
    if(check_xau(pass) == 0 || check_input(pass) == 0){
      printf("\nMoi nhap lai!!\n");
    }else break;
  }
  while(1){
    printf("Nhap nich name: ");
    strcpy(nich_name,"");
    fgets(nich_name,LEN,stdin);
    nich_name[strlen(nich_name)-1]='\0';
    if(check_xau(nich_name) == 0 || check_input(nich_name) == 0){
      printf("\nMoi nhap lai!!\n");
    }else break;

  }
  creat_mesg(0,partner,tk,pass,nich_name,mesg);
  send(sockfd, mesg,strlen(mesg), 0);
  strcpy(mesg,"");
  recv(sockfd, mesg, LEN, 0);
  mark= check_mark(mesg);
  if(mark == 1) {
    printf("\nDang ki thanh cong");
    return 1;}
  else {
    printf("\nTai khoan da ton tai!!");
    return 0;}
}
int check_mark(char mesg[]){
  int mark;
  char mesg2[LEN];

  strcpy(mesg2,mesg);
  mark = atoi(strtok(mesg2,"|"));
  return mark;
}
int take_user_list(char mesg[],User_List user_list[]){
  char mesg2[LEN];
  int i=0;
  char *pch;

  strcpy(mesg2,mesg);
  pch=strtok(mesg2,"|");
  pch=strtok(NULL,"|");
  while(1){
    pch=strtok(NULL,"|");
    if(pch==NULL) break;
    strcpy(user_list[i].nich_name,pch);
    i++;

  }
  return i;
}
int take_room_list(char mesg[],Room_List room_list[]){
  char mesg2[LEN];
  int i=0,max_mem=0,x;
  char *pch;

  strcpy(mesg2,mesg);
  pch=strtok(mesg2,"|");
  while(1){
    pch=strtok(NULL,"|");
    strcpy(room_list[i].room_name,pch);
    max_mem = atoi(strtok(NULL,"|"));
    room_list[i].max_mem=max_mem;
    x=0;
    while(1){
      if(x==(max_mem)) break;
      else{
        pch=strtok(NULL,"|");
        strcpy(room_list[i].member[x].nich_name,pch);
        x++;
      }
    }
    i++;
    if(i==10)break;
  }
  return i;

}
int answer_request(int sockfd,char mesg[],User_List chat_list[]){
  int i;
  char nich_name[LEN];
  char mesg2[LEN],buff[LEN],buff2[LEN];
  char *pch;

  char yes[2];

  strcpy(mesg2,mesg);

  pch= strtok(mesg2,"|");
  pch= strtok(NULL,"|");
  strcpy(nich_name,pch);
  printf("\n@%s muon chat voi ban!!",nich_name);
  printf("\nBan co dong y(y/n): ");
  //scanf("%s",yes);
  fgets(yes,3,stdin);
  if(yes[0] == 'y' || yes[0] == 'Y') {
    add_partner(nich_name,chat_list);
    strcpy(buff,"4|");
    strcat(buff,nich_name);
    strcat(buff,"|0|0|0|");
    send(sockfd,buff,strlen(buff),0);
    return 1;
  }
  else {
    strcpy(buff,"5|");
    strcat(buff,nich_name);
    strcat(buff,"|0|0|0|");
    send(sockfd,buff,strlen(buff),0);
    return 0;
  }
}
int add_partner(char nich_name[],User_List chat_list[]){
  int i=0;
  while(strcmp(chat_list[i].nich_name,"") != 0 ){
    i++;
  }
  strcpy(chat_list[i].nich_name,nich_name);
  return i+1;
}
int wait(int sockfd,User_List chat_list[]){

  printf("\nDang doi user khac...(hoac nhan 1 phim de vao MENU)");
  printf("\n");
  int rv,t,x,n;
  char mesg[LEN],nich_name[LEN],buff[LEN];
  fd_set readSet;
  struct timeval tv;

  while(1){
    tv.tv_sec = 5;
    tv.tv_usec =0;
    FD_SET(sockfd, &readSet);
    FD_SET(fileno(stdin), &readSet);
    select(sockfd +1, &readSet, NULL, NULL, &tv);

    if (FD_ISSET(fileno(stdin), &readSet)){
      fgets(buff,LEN,stdin);
      return 0;
    }else if(FD_ISSET(sockfd, &readSet)){
      strcpy(mesg,"");
      n=recv(sockfd,mesg,LEN,0);
      if(n==0) return 3;
      t=check_mark(mesg);
      if(t == 3) x = answer_request(sockfd,mesg,chat_list);
      return 1;
    }
  }
}
int del_partner(char nich_name[],User_List chat_list[]){
  int i=0;
  while(1){
    if(strcmp(nich_name,chat_list[i].nich_name)==0)
      break;
    i++;
  }
  while(1){
    if(strcmp(chat_list[i+1].nich_name,"")==0)
      break;
    strcpy(chat_list[i].nich_name,chat_list[i+1].nich_name);
    i++;
  }
  strcpy(chat_list[i].nich_name,"");
  return i;
}
void chatting(int sockfd,User_List chat_list[]){
  int i,t,a=0,x,y,rv;
  char *pch;
  char nich_name[LEN];
  char mesg[LEN],mesg2[LEN];
  char buff[LEN],buff1[LEN]="0",buff2[LEN]="0",buff3[LEN]="0";
  fd_set readSet;
  struct timeval tv;

  while(strcmp(chat_list[a].nich_name,"") != 0 ){
    a++;
  }
  while(1){
    tv.tv_sec = 0;
    tv.tv_usec =10000;
    FD_SET(sockfd, &readSet);
    FD_SET(fileno(stdin), &readSet);
    select(sockfd +1, &readSet, NULL, NULL, &tv);

    if(a>0){
      if (FD_ISSET(fileno(stdin), &readSet)) {
        if(a==1){
          while(1){
            fgets(buff,LEN,stdin);
            if(buff[0]!='\n') break;
          }
          buff[strlen(buff)-1]='\0';
          if(strlen(buff)==1 && ((buff[0]=='q') || (buff[0]=='Q'))) {
            strcpy(mesg,"");
            if(chat_list[0].type==1){
              chat_list[0].type=0;
              strcpy(mesg,"11|");
              strcat(mesg,chat_list[0].nich_name);
              strcpy(nich_name,chat_list[0].nich_name);
              strcat(mesg,"|0|0|0|");
              send(sockfd,mesg,strlen(mesg),0);

            }else{
              strcpy(mesg,"7|");
              strcat(mesg,chat_list[0].nich_name);
              strcpy(nich_name,chat_list[0].nich_name);
              strcat(mesg,"|0|0|0|");
              send(sockfd,mesg,strlen(mesg),0);
            }
            a = del_partner(nich_name,chat_list);

          }else{
            if(chat_list[0].type==1){
              creat_mesg(10,chat_list[0].nich_name,buff,buff1,buff2,mesg);
              send(sockfd,mesg,strlen(mesg),0);

            }else{
              creat_mesg(6,chat_list[0].nich_name,buff,buff1,buff2,mesg);
              send(sockfd,mesg,strlen(mesg),0);
            }
          }
        }else if(a>1){
          while(1){
            fgets(buff,LEN,stdin);
            if(buff[0]!='\n') break;
            printf("\nKhong duoc de trong!!");
          }
          buff[strlen(buff)-1]='\0';



            for ( i = 0; i < a; i++){
              if(chat_list[i].type==1){
                printf("\n%d.#%s",i+1,chat_list[i].nich_name);
              }else{
                printf("\n%d.@%s",i+1,chat_list[i].nich_name);
              }
            }
          while(1){
            printf("\nChon user de tra loi: ");
            scanf("%d",&y);
            fgets(buff3,LEN,stdin);
            if(0<y&&y<=a) break;
          }
          if(strlen(buff)==1 && ((buff[0]=='q') || (buff[0]=='Q'))) {
            strcpy(mesg,"");
            if(chat_list[y-1].type==1){
              chat_list[y-1].type=0;
              strcpy(mesg,"11|");
              strcat(mesg,chat_list[y-1].nich_name);
              strcpy(nich_name,chat_list[y-1].nich_name);
              strcat(mesg,"|0|0|0|");
              send(sockfd,mesg,strlen(mesg),0);
            }else{
              strcpy(mesg,"7|");
              strcat(mesg,chat_list[y-1].nich_name);
              strcpy(nich_name,chat_list[y-1].nich_name);
              strcat(mesg,"|0|0|0|");
              send(sockfd,mesg,strlen(mesg),0);
            }
            a=del_partner(nich_name,chat_list);

          }else{
            if(chat_list[y-1].type==1){
              creat_mesg(10,chat_list[y-1].nich_name,buff,buff1,buff2,mesg);
              send(sockfd,mesg,strlen(mesg),0);

            }else{
              creat_mesg(6,chat_list[y-1].nich_name,buff,buff1,buff2,mesg);
              send(sockfd,mesg,strlen(mesg),0);
            }
          }
        }
        FD_CLR(fileno(stdin), &readSet);
      }
      if (FD_ISSET(sockfd, &readSet)) {
        strcpy(mesg,"");
        recv(sockfd,mesg,LEN,0);
        t=check_mark(mesg);
        if(t == 6){
          strcpy(mesg2,mesg);
          pch=strtok(mesg2,"|");
          pch=strtok(NULL,"|");
          strcpy(nich_name,pch);
          printf("\n@%s: ",nich_name);
          pch=strtok(NULL,"|");
          printf("%s\n",pch);
        }
        if(t == 7)  {
          strcpy(mesg2,mesg);
          pch=strtok(mesg2,"|");
          pch=strtok(NULL,"|");
          strcpy(nich_name,pch);
          a=del_partner(nich_name,chat_list);
          printf("\n@%s da dung chat voi ban!!",nich_name);

        }
        if(t==10){
          strcpy(mesg2,mesg);
          pch=strtok(mesg2,"|");
          pch=strtok(NULL,"|");
          strcpy(nich_name,pch);
          printf("\n#%s_",nich_name);
          pch=strtok(NULL,"|");
          strcpy(nich_name,pch);
          printf("@%s :",nich_name);
          pch=strtok(NULL,"|");
          printf("%s\n",pch);


        }
        if(t==9){
          strcpy(mesg2,mesg);
          pch=strtok(mesg2,"|");
          pch=strtok(NULL,"|");
          strcpy(nich_name,pch);
          a=del_partner(nich_name,chat_list);
          printf("\nRoom #%s day nguoi!!",nich_name);
        }
        if(t == 3){
          answer_request(sockfd,mesg,chat_list);
          a=0;
          while(strcmp(chat_list[a].nich_name,"") != 0 ){
            a++;
          }

        }
        FD_CLR(sockfd, &readSet);
      }

    }else if(a == 0) {
      printf("\nChat_list rong!!");
      return;
    }



  }
}

void choose_user(int sockfd,User_List chat_list[]){
  int i,t,a,x,y;
  User_List user_list[100];
  char mesg[LEN],buff[LEN],buff2[LEN]="0",buff3[LEN];


  strcpy(buff,"2|0|0|0|0");
  send(sockfd,buff,strlen(buff),0);
  strcpy(mesg,"");
  recv(sockfd,mesg,LEN,0);
  t=check_mark(mesg);
  if(t == 2) a = take_user_list(mesg,user_list);
  if(a==0) {
    printf("\nKhong co user khac online!!");
    return;}
  for ( i = 0; i < a; i++){
    printf("\n%d.@%s",i+1,user_list[i].nich_name);
  }
  while(1){
    printf("\nChon user de chat: ");
    scanf("%d",&y);
    fgets(buff3,LEN,stdin);
    if(0<y&&y<=a) break;
  }
  strcpy(mesg,"");
  creat_mesg(3,user_list[y-1].nich_name,buff2,buff2,buff2,mesg);
  send(sockfd,mesg,strlen(mesg),0);
  strcpy(mesg,"");
  recv(sockfd,mesg,LEN,0);
  t = check_mark(mesg);
  if(t == 4){
    printf("\n@%s da dong y chat\n",user_list[y-1].nich_name);
    add_partner(user_list[y-1].nich_name,chat_list);
    fgets(buff,LEN,stdin);
    chatting(sockfd,chat_list);
    return;
  }else if(t == 5){
    printf("\nUser khong dong y chat!!\n");
    return;
  }
}

void log_out(int sockfd){

  char mesg[LEN]="12|0|0|0|0|";
  send(sockfd,mesg,strlen(mesg),0);
}

void choose_room(int sockfd,User_List chat_list[]){
  int i,t,a,x,y;
  Room_List room_list[10];
  char mesg[LEN],buff[LEN],buff2[LEN]="0",buff3[LEN];


  strcpy(buff,"8|0|0|0|0");
  send(sockfd,buff,strlen(buff),0);
  strcpy(mesg,"");
  recv(sockfd,mesg,LEN,0);
  t=check_mark(mesg);
  if(t == 8) a = take_room_list(mesg,room_list);
  for (i = 0; i < a; i++) {
    printf("\n%d.Room: %s",i+1,room_list[i].room_name);
    x=0;
    while(1){
      if(room_list[i].max_mem==0) {
        printf("\nEmpty!!");
        break;
      }
      else printf("\n@%s",room_list[i].member[x].nich_name);
      x++;
      if(x==(room_list[i].max_mem)) break;
    }
  }
  while(1){
    printf("\nChon room de vao: ");
    scanf("%d",&y);
    fgets(buff3,LEN,stdin);
    if(0<y&&y<=a) break;
  }
  strcpy(mesg,"");
  creat_mesg(9,room_list[y-1].room_name,buff2,buff2,buff2,mesg);
  send(sockfd,mesg,strlen(mesg),0);
  t=add_partner(room_list[y-1].room_name,chat_list);
  chat_list[t-1].type=1;

  chatting(sockfd,chat_list);

  /*strcpy(mesg,"");
  recv(sockfd,mesg,LEN,0);
  t = check_mark(mesg);
  if(t == 4){
    printf("\n@%s da dong y chat\n",user_list[y-1].nich_name);
    add_partner(user_list[y-1].nich_name,chat_list);
    fgets(buff,LEN,stdin);
    chatting(sockfd,chat_list);
    return;
  }else if(t == 5){
    printf("\nUser khong dong y chat!!\n");
    return;
  }*/
}

int menu(int sockfd){

  char choose[2];
  char aaa[1];
  int max_user_list;
  struct pollfd server[2];
  int rv,i,t;
  char mesg[LEN];
  User_List user_list[100];
  User_List chat_list[10];

  while(1){
    t = wait(sockfd,chat_list);
    if (t == 1){
      chatting(sockfd,chat_list);
    }else if(t ==0){
      printf("\n***MENU CHINH***\n");
      printf("\n1.Chon 1 user dang online de chat");
      printf("\n2.Chon phong de chat");
      printf("\n3.Thoat");
      printf("\n(note)Go 'q' de thoat chat thuong va chat room");
      printf("\nBan chon: ");
        fgets(choose,3,stdin);
        switch(choose[0]){
          case '1' :
            choose_user(sockfd,chat_list);
            break;
          case '2' :
            choose_room(sockfd,chat_list);
            break;
          case '3' :
            log_out(sockfd);
            return 1;
          default :
            break;


        }

    }
  }
}
void main(){
  int sockfd,sentBytes, recvBytes,n=0,port;
  struct sockaddr_in serv_addr;
  char mesg[LEN];
  char recv_b[LEN];
  char choose[2];
  //int choose;
  char aaa[1];
  int t;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5500);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    size_t size =100;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\nLoi tao socket!!");
    }
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\nConnect loi!!\n");
       return ;
    }else
    while(1){
      printf("\n*****MENU*****\n");
      printf("\n1.Dang nhap\n2.Dang ki\n3.Thoat" );
      printf("\nBan chon: ");
      //scanf("%d",&choose);
      fgets(choose,3,stdin);
      /*fgets(aaa,2,stdin);*/
      switch(choose[0]){

        case '1':
            printf("\nBan chon Dang Nhap");
            t = login(sockfd);
              if(t == 1) menu(sockfd);
              break;
        case '2':
            printf("\nBan chon Dang Ki");
            t = sign_up(sockfd);
              if(t == 1) menu(sockfd);
              break;
        case '3':
          return;
        default : break;


      }
    }



}

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>

// cac thu vien dung de ket noi voi mysql
#include <my_global.h>
#include <mysql.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
// ham dung de dong ket noi khi co loi xay ra
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
} 
//ket noi voi  MySQL database va tao 1 database co ten la udp
void create_database(){
     MYSQL *con = mysql_init(NULL);
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "root", "tung123", 
          "udp", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  // tao 1 bang Account trong database
  if (mysql_query(con, "DROP TABLE IF EXISTS Account")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE Account(Id INT, UserName TEXT, PassWord TEXT)")) {      
      finish_with_error(con);
  }
  
  
}
// ham insert data vao trong bang Account (them tai khoan)
// void insert_into(MySQL *con, int id, char[] name, char[] pass){
//     char [100] query;
//     strcat("INSERT INTO Account VALUES(",id); 
//     if (mysql_query(con, "INSERT INTO Account VALUES(1,'Audi',52642)")) {
//       finish_with_error(con);
//   }
// }
int main(void)
{
    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);
        // cho nay se tach message tu client gui den
         
        //now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
    }
 
    close(s);
    return 0;
}
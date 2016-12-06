#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split_message(char *message){

char *name;
char *pass;
char *s;
char *mesg =  malloc(sizeof(char) *100);;
strcpy(mesg, message);
s = strtok(mesg,"|");
//printf("%s\n", s);
name = strtok(NULL,"|");
printf("%s\n",name );
pass = strtok(NULL, "|");
//pass = strtok(mesg2,"|");
//printf("%s\n", pass);
}
void main(){
split_message("LOGIN|le tat tung|tung123");
}

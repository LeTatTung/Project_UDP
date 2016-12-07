#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h>
#include "define.c"

// #include "split_string.c"
// char *plush_phay(char *str){
// 	char*result = malloc(sizeof(char) *32);
// 	strcpy(result,"\'");
// 	strcat(result,str);
// 	strcat(result,"\'");

// 	return result;
// }
// char *request(char *info){
// 	char * request = malloc(sizeof(char) *100);
//     char*name = malloc(sizeof(char)*30);
//     char** tokens;
//     tokens = str_split(info,'|');
//     if(tokens){
//     	name = *(tokens);
//     	strcpy(request,SELECT_PASS);
//     	strcat(request,plush_phay(name));
//     	free(*(tokens));
//     }
//     free(tokens);



//     return request;
// }

// muc tieu cua ham nay la tao ra string co dang nhu duoi
// "SELECT PassWord FROM Account WHERE UserName = 'le tat tung'"
char * command_select_pass(char *name){
    char *command = malloc(sizeof(char) *100);
    strcpy(command, SELECT_PASS);
    strcat(command,"\'");
    strcat(command,name);
    strcat(command,"\'");

    return command;

}

char * command_select_id(char *name){
    char *command = malloc(sizeof(char) *100);
    strcpy(command, SELECT_ID);
    strcat(command,"\'");
    strcat(command,name);
    strcat(command,"\'");

    return command;

}

char * command_select_file(int id){
    char *command = malloc(sizeof(char) *100);
    char id_account[5];
    sprintf(id_account,"%d",id);
    strcpy(command, SELECT_FILE_NAME);
    strcat(command,"\'");
    strcat(command,id_account);
    strcat(command,"\'");

    return command;

}
// muc tieu cua ham nay la tao ra string co dang nhu duoi
// "INSERT INTO Account VALUES(1,'cao van minh','minh123')"
char* command_insert_account(char*id, char* name, char *pass){

    char *command = malloc(sizeof(char) *100);
    strcpy(command,INSERT_ACCOUNT);
    strcat(command,id);
    strcat(command,",\'");
    strcat(command,name);
    strcat(command, "\',\'");
    strcat(command, pass);
    strcat(command,"\')");

    return command;
}
char* create_message(char* command, char *mesg){

  char *message = malloc(sizeof(char) *100);
  strcpy(message,command);
  strcat(message,"|");
  strcat(message,mesg);

  return message;
}

// int main(){

// 	printf("%s\n",command_select_file(1) );
// 	return 0;
// }

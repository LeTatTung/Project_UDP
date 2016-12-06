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
char * command_select_pass(char *name){
    char *command = malloc(sizeof(char) *100);
    strcpy(command, SELECT_PASS);
    strcat(command,"\'");
    strcat(command,name);
    strcat(command,"\'");
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
// 	printf("%s\n", create_message(LOGIN, input_data()));
// 	return 0;
// }

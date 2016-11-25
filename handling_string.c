#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);

#include "define.c"
//"INSERT INTO Cars VALUES(1,'Audi',52642)"
char* split_after_string(char *s){
	
	char *string_after = malloc(sizeof(char)*20); 
	char *string_after1 = malloc(sizeof(char)*20);
	strcpy(string_after,strstr(s,SLASH));
	printf("%d\n", strlen(string_after));
	for(int i=1;i<strlen(string_after);i++){
		string_after1[i] = string_after[i];
	}
	return string_after1;

}
char* split_before_string(char *s){
    char *string_before = malloc(sizeof(char)*40); 

    for(int i=0;i<strlen(s);i++){
    	if(s[i] == '|'){
    		for(int j =0;j<i;j++){
    			string_before[j] = s[j];
    		}
    	}
    }
    return string_before;
}
// char* split_after_string(char *s){
//     char *string_after = malloc(sizeof(char)*20); 

//     for(int i=0;i<strlen(s);i++){
//     	if(s[i] == '|'){
//     		for(int j =i+1;j<strlen(s);j++){
//     			string_after[j] = s[j];
//     		}
//     	}
//     }
//     return string_after;
// }
int main(){
	// int id =1;
	// char name [30] = "letattung";
	// char pass [15]= "tung123";
	// char query [50];
	// char temp [3];
	// char x[20] = "Account";
	// if (mysql_query(con, "INSERT INTO Cars VALUES(2,'Mercedes',57127)")) {
 //      finish_with_error(con);
 //  }
	//if (mysql_query(con, "SELECT * FROM Account")) 


	// strcpy(query,"\"INSERT INTO Account VALUES(" );
	// sprintf(temp,"%d",id);
	// strcpy(query,strcat(query,temp));
	// strcpy(query,strcat(query,",\'"));   
	// strcpy(query,strcat(query,name));
	// strcpy(query,strcat(query,"\',\'"));  
	// strcpy(query,strcat(query, pass));
	// strcpy(query,strcat(query,"\')\""));  
	// printf("%s\n", query);

 //    strcpy(query,"\"SELECT * FROM ");
	// strcpy(query,strcat(query,x));
	// strcpy(query,strcat(query,"\""));  
	// printf("%s\n", query);
	 char *s = malloc(sizeof(char)*50);
	 s = input_data(); 
 printf("%s\n", split_before_string(s));
 printf("%s\n", s);
 printf("%s\n", split_after_string(s));
	return 0;
}
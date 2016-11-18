#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
//"INSERT INTO Cars VALUES(1,'Audi',52642)"

int main(){
	int id =1;
	char name [30] = "letattung";
	char pass [15]= "tung123";
	char query [50];
	char temp [3];
	char x[20] = "Account";
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

    strcpy(query,"\"SELECT * FROM ");
	strcpy(query,strcat(query,x));
	strcpy(query,strcat(query,"\""));  
	printf("%s\n", query);
	return 0;
}
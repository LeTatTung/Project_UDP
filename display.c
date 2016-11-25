#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.c"

int display_lock(){
	int choice; 
	
	printf("\t\tClient UDP Home Page\n\n");
	printf("\t1. Dang ki tai khoan\n");
	printf("\t2. Login\n");
	printf("\t3. Exit\n");
	do {
      printf("Ban chon: ");
      scanf("%d", &choice); DEL();
      if (choice < 1 || choice > 3) {
	printf("Ban chon sai.\n");
      }
    } while (choice < 1 || choice > 3);
	return choice;
}
int display_unlock(){
	int choice;

	printf("\t\tClient UDP\n\n");
	printf("\t1. Liet ke danh sach cac file ma server quan ly\n");
	printf("\t2. Download file\n");
	printf("\t3. Upload file\n");
	printf("\t4. Go to Home\n");
	do {
      printf("Ban chon: ");
      scanf("%d", &choice); DEL();
      if (choice < 1 || choice > 4) {
	printf("Ban chon sai.\n");
      }
    } while (choice < 1 || choice > 4);
	return choice;
}
char* input_data(){
	char username[30];
	char pass[15];
	char *return_value = malloc(sizeof(char)*50);
	// strcpy(return_value, "abc|abs");

	printf("Nhap thong tin cho tai khoan:\n");
	printf("Nhap username: ");
	scanf("%[^\n]",username);DEL();
	printf("\nNhap password: ");
	scanf("%[^\n]",pass);DEL();

	strcpy(return_value,strcat(strcat(username,SLASH),pass));
	return return_value;
	
}

// int main(){

// 	int choice1 = display_lock();
// 	switch (choice1){
// 		case 1:
// 		printf("\nThong tin cua tai khoan :%s\n",input_data());
// 		break;
// 		case 2:
// 		break;
// 		case 3:
// 		printf("Exit program !");
// 	}
// 	return 0;
// }
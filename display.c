#include <stdio.h>
#include <stdlib.h>
#define DEL() while (getchar() != '\n')

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
void display_unlock(){
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
void input_data(){
	char username[30];
	char pass[15];
	printf("Nhap thong tin cho tai khoan:\n");
	printf("Nhap username: ");
	scanf("%[^\n]",username);DEL();
	printf("\nNhap password: ");
	scanf("%[^\n]",pass);DEL();
	printf("\nThong tin cua tai khoan username: %s, pass: %s\n",username,pass );
}
int main(){
	int choice1 = display_lock();
	switch (choice1){
		case 1:
		input_data();
		break;
		case 2:
		break;
		case 3:
		printf("Exit program !");
	}
	return 0;
}
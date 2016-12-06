#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.c"

int display_lock(){
	int choice;

	printf("\t\tClient Home Page\n\n");
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

	printf("\t\tClient Menu\n\n");
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

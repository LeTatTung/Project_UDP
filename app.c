#include "display.c"

void singup(){

}
void login(){

}
int main(){

	int choice= display_lock();
	do{
switch(choice){
	case 1:
	singup();
	break;
	case 2:
	login();
	break;
	case 3:
	printf("Exit program !\n");
}
	}while(chocie !=3);
}
}
int check_string(char buff[]){

  int i;

  for(i=0;i<strlen(buff);i++){
    if(buff[i] == '|') {
      printf("\nXau chua ki tu khong duoc cho phep!!");
      return 0;
    }
  }
  return 1;
}
int check_input(char buff[]){
  int i;

  if(strlen(buff)<=1 || strlen(buff)>=30) return 0;
  else return 1;

}
char* input_data(){
	char username[30];
	char pass[30];
	char *return_value = malloc(sizeof(char)*70);
	// strcpy(return_value, "abc|abs");

	printf("Nhap thong tin cho tai khoan:\n");
	while(1){
	printf("Nhap username: ");
	scanf("%[^\n]",username);DEL();
	if(check_string(username) == 0 || check_input(username) == 0){
		printf("\nDau vao sai.Moi nhap lai!!\n");
	}else break;
}
	while(1){
	printf("\nNhap password: ");
	scanf("%[^\n]",pass);DEL();
	if(check_string(pass) == 0 || check_input(pass) == 0){
		printf("\nDau vao sai.Moi nhap lai!!\n");
	}else break;
}
	strcpy(return_value,strcat(strcat(username,SLASH),pass));
	return return_value;

}

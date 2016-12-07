#define DEL() while (getchar() != '\n')// chong luu dau enter tu xau truoc

#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data
#define OPEN_MAX 100
#define FILE_MAX 20

#define SLASH "|"
//command
#define SIGN_UP "SIGN_UP"
#define LOGIN "LOGIN"

// cac lenh truy van den database
#define SELECT_PASS "SELECT PassWord FROM Account WHERE UserName = "
#define SELECT_ID "SELECT Id FROM Account WHERE UserName = "
#define SELECT_MAX_ID "SELECT MAX(Id) FROM Account"
#define SELECT_FILE_NAME "SELECT FileName FROM ManageFile WHERE Id = "
#define INSERT_ACCOUNT "INSERT INTO Account VALUES("


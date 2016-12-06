//lenh chay
//gcc -o sql sql.c `mysql_config --cflags --libs`
// insert data
#include <my_global.h>
#include <mysql.h>
#include "string_handling.c"

// finish neu xay ra loi khi ket noi den mysql
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL* connect_mysql(){
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "letattung", "tung123",
          "testdb", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }
  return con;
}
char* get_pass_account(MYSQL*con, char*name){

  if (mysql_query(con,command_select_pass(name)))
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          if(row[i] != NULL)
            return row[i];
      }
          printf("\n");
  }

  mysql_free_result(result);
  mysql_close(con);
  return NULL;
}


// int main()
// {
//   char name[30] = "nguyen huu tien";

//   printf("%s\n", get_pass_account(connect_mysql(),name));


//   exit(0);
// }

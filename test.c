#include <my_global.h>
#include <mysql.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "letattung", "tung123",
          "testdb", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "DROP TABLE IF EXISTS ManageFile")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "CREATE TABLE ManageFile(Id INT, FileName TEXT)")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO ManageFile VALUES(1,'test.txt')")) {
      finish_with_error(con);
  }


  mysql_close(con);
  exit(0);
}

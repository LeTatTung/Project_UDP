//lenh chay
//gcc -o sql sql.c `mysql_config --cflags --libs` 
// insert data
#include <my_global.h>
#include <mysql.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}


void connect_db(){
  MYSQL *con = mysql_init(NULL);
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "root", "tung123", 
          "testdb", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
}


void create_table(MYSQL *con){
  if (mysql_query(con, "DROP TABLE IF EXISTS Account")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE Account(Id INT, UserName TEXT, PassWord TEXT)")) {      
      finish_with_error(con);
  }
}


void insert_into_data(MYSQL *con){
  if (mysql_query(con, "INSERT INTO Account VALUES(1,'le tat tung','tung123')")) {
      finish_with_error(con);
  }
  if (mysql_query(con, "INSERT INTO Account VALUES(2,'nguyen huu tien','tien123')")) {
      finish_with_error(con);
  }
  
}
void select_info(MYSQL *con, char[] query){
   if (mysql_query(con, query)) 
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
          printf("%s|", row[i] ? row[i] : "NULL");
      } 
          printf("\n"); 
  }
  
  mysql_free_result(result);
  // mysql_close(con);
  
  
}
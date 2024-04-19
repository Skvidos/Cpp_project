#include <stdio.h>
#include "sqlite3.h"

int main()
{
  sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open("test.db", &db);

  if(rc!=SQLITE_OK)
  {
    sqlite3_close(db);
  }

  char *sql = "DROP TABLE IF EXISTS people;"
  "CREATE TABLE people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER);";

  rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  if(rc!=SQLITE_OK)
  {
    printf("SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }
  sqlite3_close(db);
  printf("Table created successfully\n");
  return 0;
}
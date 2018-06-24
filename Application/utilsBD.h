#ifndef _utilsBD_h
#define _utilsBD_h

char* readLine(FILE *a);
void errorExit(PGconn *connection);
void commandErrorExit(PGconn *connection, PGresult *res);
void printColumns(PGresult *res);
void printTable(PGresult *res);
PGresult* selectCommand(PGconn* connection, char* input);
PGresult* anyCommand(PGconn* connection, char* input);
PGresult* anyCommandNoExit(PGconn* connection, char* input);
void insertToDatabase(PGconn* connection, PGresult* res, int table);
void removeFromDatabase(PGconn* connection, int table);
void updateFromDatabase(PGconn* connection, int table);
char* getDate();
char* getTime();

#endif
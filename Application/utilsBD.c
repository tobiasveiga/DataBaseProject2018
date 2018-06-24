#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>

// Read full input of user
char* readLine(FILE *a){
	char c, *string = NULL;
	int counter = 0;
	do{
		c = fgetc(a);
		string = (char*)realloc(string, sizeof(char) * (counter + 1));
		string[counter++] = c;
	}while(c != 10 && c != EOF);
	string[counter-1] = '\0';

	return string;
}

/* '[0-9]{3}\.[0-9]{3}\.[0-9]{3}\-[0-9]{2}' */
// Input as a non-formated cpf and return a formatted cpf 
char* readCPF(){
	char* a = '\0';
	a = readLine(stdin);
	char *cpf = '\0';
	char buffer[255] = "";
	int strSize ; 

	strncat(buffer, a, 3);
	strcat(buffer, ".");
	strncat(buffer, a+3, 3);
	strcat(buffer, ".");
	strncat(buffer, a+6, 3);
	strcat(buffer, "-");
	strncat(buffer, a+9, 2);

	strSize = strlen(buffer);
	cpf = (char*)malloc(strSize + 1);
	strcpy(cpf, buffer);
	return cpf;
}

/* '\([0-9]{2}\)[0-9]{8,9}' */
// Input as a non-formated phone and return a formatted phone 
char* readTelefone(){
	int strSize;
	char* a = readLine(stdin);
	char* telefone;
	char buffer[255] = "";

	strcat(buffer, "(");
	strncat(buffer, a, 2);
	strcat(buffer, ")");
	if(strlen(a) == 11)
		strncat(buffer, a+2, 9);
	else if(strlen(a) == 10)
		strncat(buffer, a+2, 8);

	strSize = strlen(buffer);
	telefone = (char*)malloc(strSize +1);
	strcpy(telefone, buffer);
	return telefone;
}

/* '[0-9]{2}\.[0-9]{3}\.[0-9]{3}\-[0-9]{4}.[0-9]{2}' */
/* ie: '12.123.123-1234.12' */
// Input as a non-formated CNPJ and returna a formated CNPJ
char* readCNPJ(){
	int strSize;
	char* a = readLine(stdin);
	char* cnpj;
	char buffer[255] = "";

	strncat(buffer, a, 2);
	strcat(buffer, ".");

	strncat(buffer, a+2, 3);
	strcat(buffer, ".");

	strncat(buffer, a+5, 3);
	strcat(buffer, "-");

	strncat(buffer, a+8, 4);
	strcat(buffer, ".");

	strncat(buffer, a+12, 2);

	strSize = strlen(buffer);
	cnpj = (char*)malloc(strSize + 1);
	strcpy(cnpj, buffer);

	return cnpj;
}

// In case of error, finishes the database connection and end program
void errorExit(PGconn *connection){
	PQfinish(connection);
	exit(1);
}

// In case of error when using a command, finishes connection , clear 'res' buffer and end program
void commandErrorExit(PGconn *connection, PGresult *res){
	fprintf(stderr, "%s\n", PQerrorMessage(connection));
	PQclear(res);
	PQfinish(connection);

	exit(1);
}

// Print the name of the colums of a table with numbers for update function
void printColumns(PGresult *res){
	int fieldSize = PQnfields(res);
	int i;
	printf("No\tCampo\n\n");
	for(i = 0; i < fieldSize; i++){
		printf("%d\t%s\n", i, PQfname(res, i));
	}
	printf("\n");
}

// Print a full table returned from a SELECT command
void printTable(PGresult *res){
	int i, j;
	int tuplesSize = PQntuples(res);
	int fieldSize = PQnfields(res);

	printf("No\t");
	// Print field names
	for(i = 0; i<fieldSize; i++){
		printf("%s\t", PQfname(res, i));
	}
	printf("\n\n");

	// Print values of fields
	for(i = 0; i < tuplesSize; i++){
		printf("%d\t", i);
		for(j = 0; j < fieldSize; j++){
			char *a = PQgetvalue(res, i, j);
			if(strcmp(a, "") != 0 ){
				printf("%s\t ", a);
			}
			else{
				printf("null\t ");
			}
		}
		printf("\n");
	}
	printf("\n");

	return;
}

// SELECT command to database with error treatment
PGresult* selectCommand(PGconn* connection, char* input){
	PGresult* res = PQexec(connection, input);
	if(PQresultStatus(res) != PGRES_TUPLES_OK){
		commandErrorExit(connection, res);
	}
	return res;
}

// Any command to database (except for SELECT [to SELECT use 'selectCommand()'])
PGresult* anyCommand(PGconn* connection, char* input){
	PGresult* res = PQexec(connection, input);
	if(PQresultStatus(res) != PGRES_COMMAND_OK){
		commandErrorExit(connection, res);
	}
	return res;
}


// Any command to database (except for SELECT [to SELECT use 'selectCommand()'])
PGresult* anyCommandNoExit(PGconn* connection, char* input){
	PGresult* res = PQexec(connection, input);
	if(PQresultStatus(res) != PGRES_COMMAND_OK){
		printf("%s\n", PQerrorMessage(connection));
		PQclear(res);
	}
	return res;
}


// Any command to insert data to database will be processed here
void insertToDatabase(PGconn* connection, PGresult* res, int table){
	char buffer[1024];
	strcpy(buffer, "INSERT INTO");
	switch(table){
		case 1:
			//strcat(buffer, " NOME"); /// NAO ESQUECER DE MUDAR !!!!!
			strcat(buffer, " PESSOA"); /// CORRETO
			break;
		case 2:
			strcat(buffer, " LOCAL");
			break;
		case 3:
			strcat(buffer, " INSUMO");
			break;
		
		case 41:
			strcat(buffer, " EMPRESA_INSUMO");
			break;
		case 42:
			strcat(buffer, " EMPRESA_BRINQUEDO");
			break;
		case 43:
			strcat(buffer, " EMPRESA_PRESENTE");
			break;
		case 44:
			strcat(buffer, " EMPRESA_FUNCIONARIO");
			break;


		case 5:
			strcat(buffer, " BRINQUEDO");
			break;
		case 6:
			strcat(buffer, " PRESENTE");
			break;
		case 7:
			strcat(buffer, " EVENTO");
			break;
	}
	strcat(buffer, " (");
	int nfields = PQnfields(res);
	int i;
	for(i = 0; i < nfields; i++){
		strcat(buffer, PQfname(res, i));
		if(i != nfields - 1){
			strcat(buffer, ", ");
		}
	}
	strcat(buffer, ") values (");
	
	char *input;
	getchar();
	for(i = 0; i<nfields; i++){
		strcat(buffer, "'");
		printf("Digite o %s:\n", PQfname(res, i));
		if(strcmp(PQfname(res, i),"cpf") == 0){
			printf("Digite apenas os numeros: ");
			input = readCPF();
		}else if(strcmp(PQfname(res, i),"cnpj") == 0){
			printf("Digite apenas os numeros: ");
			input = readCNPJ();
		}else if(strcmp(PQfname(res, i),"telefone") == 0){
			printf("Digite apenas os numeros da operadora e sem seguida o telefone(ex: 11987654321): ");
			input = readTelefone();
		}
		else{
			input = readLine(stdin);
		}

		strcat(buffer, input);
		if(i != nfields -1){
			strcat(buffer, "',");
		}
		else{
			strcat(buffer, "'");
		}
	}
	free(input);
	strcat(buffer, ");");

	int querySize = strlen(buffer);
	printf("query size: %d\n", querySize);
	char *query = (char*)malloc(querySize + 1);
	strcpy(query, buffer);
	query[querySize - 1] = '\0';
	printf("%s\n", query);
	anyCommand(connection, query);
	free(query);
	system("clear");
}

// Proccess any deletion on database
void removeFromDatabase(PGconn* connection, int table){
	PGresult* res;
	int tupleToRemove = -1;
	char buffer[255];
	char a[255];
	strcpy(buffer, "DELETE FROM");
	strcpy(a, "SELECT * FROM");
	switch(table){
		case 1:
			//strcat(buffer, " NOME"); /// NAO ESQUECER DE MUDAR !!!!!
			strcat(buffer, " PESSOA"); /// CORRETO
			strcat(a, " PESSOA");
			break;
		case 2:
			strcat(buffer, " LOCAL");
			strcat(a, " LOCAL");
			break;
		case 3:
			strcat(buffer, " INSUMO");
			strcat(a, " INSUMO");
			break;
		
		case 41:
			strcat(buffer, " EMPRESA_INSUMO");
			strcat(a, " EMPRESA_INSUMO");
			break;
		case 42:
			strcat(buffer, " EMPRESA_BRINQUEDO");
			strcat(a, " EMPRESA_BRINQUEDO");			
			break;
		case 43:
			strcat(buffer, " EMPRESA_PRESENTE");
			strcat(a, " EMPRESA_PRESENTE");			
			break;
		case 44:
			strcat(buffer, " EMPRESA_FUNCIONARIO");
			strcat(a, " EMPRESA_FUNCIONARIO");			
			break;


		case 5:
			strcat(buffer, " BRINQUEDO");
			strcat(a, " BRINQUEDO");			
			break;
		case 6:
			strcat(buffer, " PRESENTE");
			strcat(a, " PRESENTE");			
			break;
		case 7:
			strcat(buffer, " EVENTO");
			strcat(a, " EVENTO");			
			break;
	}
	strcat(buffer, " WHERE");
	strcat(a, ";");
	switch(table){
		case 1:
			strcat(buffer, " cpf"); /// CORRETO
			break;
		case 2:
			strcat(buffer, " id");
			break;
		case 3:
			strcat(buffer, " nome");
			break;
		
		case 41:
			strcat(buffer, " cnpj");
			break;
		case 42:
			strcat(buffer, " cnpj");
			break;
		case 43:
			strcat(buffer, " cnpj");
			break;
		case 44:
			strcat(buffer, " cnpj");
			break;


		case 5:
			strcat(buffer, " nome");
			break;
		case 6:
			strcat(buffer, " nome");
			break;
		case 7:
			strcat(buffer, " id");
			break;
	}
	strcat(buffer, " ='");

	res = selectCommand(connection, a);
	printTable(res);
	printf("Digite o No da tupla a ser removida: ");
	scanf("%d", &tupleToRemove);
	strcat(buffer, PQgetvalue(res, tupleToRemove, 0));
	strcat(buffer, "';");

	anyCommandNoExit(connection, buffer);
	return;
}

// Process any Update to database
void updateFromDatabase(PGconn* connection, int table){
	PGresult* res;
	int tupleToUpdate = -1;
	int columnToUpdate = -1;
	char buffer[255];
	char a[255];
	strcpy(buffer, "SELECT * FROM");
	strcpy(a, "SELECT * FROM");
	switch(table){
		case 1:
			//strcat(buffer, " NOME"); /// NAO ESQUECER DE MUDAR !!!!!
			strcat(buffer, " PESSOA"); /// CORRETO
			strcat(a, " PESSOA");
			break;
		case 2:
			strcat(buffer, " LOCAL");
			strcat(a, " LOCAL");
			break;
		case 3:
			strcat(buffer, " INSUMO");
			strcat(a, " INSUMO");
			break;
		
		case 41:
			strcat(buffer, " EMPRESA_INSUMO");
			strcat(a, " EMPRESA_INSUMO");
			break;
		case 42:
			strcat(buffer, " EMPRESA_BRINQUEDO");
			strcat(a, " EMPRESA_BRINQUEDO");			
			break;
		case 43:
			strcat(buffer, " EMPRESA_PRESENTE");
			strcat(a, " EMPRESA_PRESENTE");			
			break;
		case 44:
			strcat(buffer, " EMPRESA_FUNCIONARIO");
			strcat(a, " EMPRESA_FUNCIONARIO");			
			break;


		case 5:
			strcat(buffer, " BRINQUEDO");
			strcat(a, " BRINQUEDO");			
			break;
		case 6:
			strcat(buffer, " PRESENTE");
			strcat(a, " PRESENTE");			
			break;
		case 7:
			strcat(buffer, " EVENTO");
			strcat(a, " EVENTO");			
			break;
	}
	strcat(buffer, ";");
	res = selectCommand(connection, buffer);
	printTable(res);
	printf("Digite o No da tupla a ser alterada: ");
	scanf("%d", &tupleToUpdate);
	system("clear");

	strcat(a, " WHERE ");
	switch(table){
		case 1:
			strcat(a, " cpf"); /// CORRETO
			break;
		case 2:
			strcat(a, " id");
			break;
		case 3:
			strcat(a, " nome");
			break;
		
		case 41:
			strcat(a, " cnpj");
			break;
		case 42:
			strcat(a, " cnpj");
			break;
		case 43:
			strcat(a, " cnpj");
			break;
		case 44:
			strcat(a, " cnpj");
			break;


		case 5:
			strcat(a, " nome");
			break;
		case 6:
			strcat(a, " nome");
			break;
		case 7:
			strcat(a, " id");
			break;
	}
	strcat(a, " = '");
	strcat(a, PQgetvalue(res, tupleToUpdate, 0));
	strcat(a, "';");

	res = selectCommand(connection, a);
	printTable(res);

	printColumns(res);
	printf("Digite o No do campo que deseja alterar: ");
	scanf("%d", &columnToUpdate);
	getchar();

	printf("Digite o novo valor de %s: ", PQfname(res, columnToUpdate));
	// inserir aqui cpf, telefone, cnpj
	char* newValue;
	if(strcmp(PQfname(res, columnToUpdate),"cpf") == 0){
		printf("Digite apenas os numeros: ");
		newValue = readCPF();
	}else if(strcmp(PQfname(res, columnToUpdate),"cnpj") == 0){
		printf("Digite apenas os numeros: ");
		newValue = readCNPJ();
	}else if(strcmp(PQfname(res, columnToUpdate),"telefone") == 0){
		printf("Digite apenas os numeros da operadora e sem seguida o telefone(ex: 11987654321): ");
		newValue = readTelefone();
	}
	else{
		newValue = readLine(stdin);
	}

	strcpy(a, "UPDATE ");
	switch(table){
		case 1:
			strcat(a, " PESSOA"); /// CORRETO
			break;
		case 2:
			strcat(a, " LOCAL");
			break;
		case 3:
			strcat(a, " INSUMO");
			break;
		
		case 41:
			strcat(a, " EMPRESA_INSUMO");
			break;
		case 42:
			strcat(a, " EMPRESA_BRINQUEDO");
			break;
		case 43:
			strcat(a, " EMPRESA_PRESENTE");
			break;
		case 44:
			strcat(a, " EMPRESA_FUNCIONARIO");
			break;


		case 5:
			strcat(a, " BRINQUEDO");
			break;
		case 6:
			strcat(a, " PRESENTE");
			break;
		case 7:
			strcat(a, " EVENTO");
			break;
	}
	strcat(a, " SET ");
	strcat(a, PQfname(res, columnToUpdate));
	strcat(a, " = '");
	strcat(a, newValue);
	strcat(a, "' WHERE ");
	strcat(a, PQfname(res, 0));
	strcat(a, " = '");
	strcat(a, PQgetvalue(res, 0, 0));
	strcat(a, "';");

	anyCommand(connection, a);
	return;
}

// Return a (YYYY/MM/DD) formated date
char* getDate(){
	char buffer[255];
	char *a;
	char *b;
	int strSize;
	printf("\tDigite o ano: ");
	a = readLine(stdin);
	strcpy(buffer, a);
	strcat(buffer, "-");
	printf("\tDigite o mes(numero): ");
	a = readLine(stdin);
	strcat(buffer, a);
	strcat(buffer, "-");
	printf("\tDigite o dia: ");
	a = readLine(stdin);
	strcat(buffer, a);

	strSize = strlen(buffer);
	b = (char*)malloc(strSize + 1);
	strcpy(b, buffer);

	return b;
}

// Return a (HH:MM:SS) formatted Time
char* getTime(){
	char buffer[255];
	char *a;
	char *b;
	int strSize;
	printf("\tDigite as horas[com dois digitos(ex: 7h = 07)]: ");
	a = readLine(stdin);
	strcpy(buffer, a);
	strcat(buffer, ":");
	printf("\tDigite os minutos[com dois digitos]: ");
	a = readLine(stdin);
	strcat(buffer, a);
	strcat(buffer, ":");
	printf("\tDigite os segundos[com dois digitos]: ");
	a = readLine(stdin);
	strcat(buffer, a);

	strSize = strlen(buffer);
	b = (char*)malloc(strSize + 1);
	strcpy(b, buffer);

	return b;
}

	/*	Aux Functions:
		// Numero de linhas retornada
		printf("%d\n", PQntuples(res));

		// numero de colunas retornada
		printf("%d\n", PQnfields(res));

		// Tamanho da strng retornada em coluna:0, linha:0
		printf("%d\n", PQgetlength(res, 0, 0));

		// Printa o resultado de coluna:0, linha:0
		printf("%s\n", PQgetvalue(res, 0, 0));

		// end connection with database
	 	PQfinish(connection);
	*/

	
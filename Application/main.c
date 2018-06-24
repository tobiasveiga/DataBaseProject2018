#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>
#include "utilsBD.h"

void inicial(PGconn *connection);
void cadastrar(PGconn *connection);
void consultar(PGconn *connection);
void relatorio(PGconn *connection);
void remover(PGconn *connection);
void alterar(PGconn *connection);
int selectEmpresa();

// Menu de selecionar entre brinquedo, insumo e presente
int selectBIP(){
	system("clear");
	while(1){
		int opt = -1;
		printf("Qual?\n");
		printf("1\t Insumo\n");
		printf("2\t Presente\n");
		printf("3\t Brinquedo\n");
		printf("Digite o No da opcao: ");
		scanf("%d", &opt);
		switch(opt){
			case 1: return 1;
			case 2: return 2;
			case 3: return 3;
			default: 
				system("clear");
				printf("Opcao Invalida\n");
				break;
		}
	}
}

// Menu de selecao do tipo de empresa
int selectEmpresa(){
	system("clear");
	while(1){
		int opt = -1;
		printf("Qual tipo de Empresa ?\n");
		printf("1\t Insumo\n");
		printf("2\t Brinquedo\n");
		printf("3\t Presente\n");
		printf("4\t Funcionario\n");
		printf("Digite o No da Empresa: ");
		scanf("%d", &opt);
		switch(opt){
			case 1: return 1;
			case 2: return 2;
			case 3: return 3;
			case 4: return 4;
			default:
				system("clear"); 
				printf("Opcao Invalida\n");
				break;
		}
	}
}

// Menu de alteracao
void alterar(PGconn *connection){
	PGresult* res;
	int opt = -1;
	int nEmpresa;
	int tupleToUpdate = -1;
	int columnToUpdate = -1;
	char query[255];

	while(opt != 8){
		printf("O que deseja alterar ?\n");
		printf("1\t Pessoa\n");
		printf("2\t Local\n");
		printf("3\t Insumo\n");
		printf("4\t Empresa\n");
		printf("5\t Brinquedo\n");
		printf("6\t Presente\n");
		printf("7\t Evento\n");
		printf("======\n");
		printf("8\t Voltar\n");
		printf("Digite o numero: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				system("clear");
				updateFromDatabase(connection, 1);
				break;
			case 2:
				system("clear");
				updateFromDatabase(connection, 2);
				break;
			case 3:
				system("clear");
				updateFromDatabase(connection, 3);
				break;
			case 4:
				system("clear");
				nEmpresa = selectEmpresa();
				nEmpresa = 40 + nEmpresa;
				updateFromDatabase(connection, nEmpresa);
				break;
			case 5:
				system("clear");
				updateFromDatabase(connection, 5);
				break;
			case 6:
				system("clear");
				updateFromDatabase(connection, 6);
				break;
			case 7:
				system("clear");
				updateFromDatabase(connection, 7);
				break;
			case 8:
				system("clear");
				inicial(connection);
				break;
			default:
				system("clear");
				printf("Opcao Invalida\n");
				break;	
		}
	}
	PQclear(res);
}

// Menu de remocao
void remover(PGconn *connection){
	PGresult* res;
	int opt = -1;
	int tupleToRemove = -1;
	char query[255];
	int nEmpresa;

	while(opt != 8){
		strcpy(query, "DELETE FROM ");

		printf("O que deseja remover ?\n");
		printf("1\t Pessoa\n"); // pk = cpf(0)
		printf("2\t Local\n"); // pk = id(0)
		printf("3\t Insumo\n"); // pk = nome(0)
		printf("4\t Empresa\n"); 
		/* 
			empresa_insumo pk = cnpj(0)
			empresa_brinquedo pk = cnpj(0)
			empresa_presente pk = cnpj(0)
			empresa_funcionario pk = cnpj(0)
		*/
		printf("5\t Brinquedo\n"); // pk = nome(0)
		printf("6\t Presente\n"); // pk = nome(0)
		printf("7\t Evento\n"); // pk = id (0)
		printf("======\n");
		printf("8\t Voltar\n");
		printf("Digite o numero: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				system("clear");
				removeFromDatabase(connection, 1); // 1 = table pessoa
				break;
			case 2:
				system("clear");
				removeFromDatabase(connection, 2);
				break;
			case 3:
				system("clear");
				removeFromDatabase(connection, 3);
				break;
			case 4:
				system("clear");
				nEmpresa = selectEmpresa();
				nEmpresa = 40 + nEmpresa;
				removeFromDatabase(connection, nEmpresa);
				break;
			case 5:
				system("clear");
				removeFromDatabase(connection, 5);
				break;
			case 6:
				system("clear");
				removeFromDatabase(connection, 6);
				break;
			case 7:
				system("clear");
				removeFromDatabase(connection, 7);
				break;
			case 8:
				system("clear");
				inicial(connection);
				break;
			default:
				system("clear");
				printf("Opcao Invalida\n");
				break;	
		}
	}
	PQclear(res);
}

// Menu do relatorio
void relatorio(PGconn *connection){
	PGresult* res;
	int chooseItem = -1;
	int opt = -1;
	char *a;
	char *data1;
	char *data2;
	char query[255];
	char buffer[255];
	while(opt != 8){
		int BIP = -1;
		printf("Relatorios disponiveis:\n");
		printf("1\t Participantes e funcionarios de um evento\n"); //ok
		printf("2\t Funcionarios de uma determinada funcao\n"); // ok
		printf("3\t Locais disponiveis para determinada data e horario\n"); // ok
		printf("4\t Datas e horarios indisponiveis para um determinado local\n"); // ok
		printf("5\t Empresas fornecedoras de um determinado insumo, presente ou brinquedo\n"); // ok
		printf("6\t Frequencia de quais Universidade/Cursos contratam mais\n"); // ok
		printf("7\t Insumos/brinquedo/presente mais consumidos em eventos\n"); //OK
		printf("======\n");
		printf("8\t Voltar\n");
		printf("Digite o numero: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				system("clear");
				res = selectCommand(connection, "SELECT EVENTO FROM PARTICIPA;");
				printTable(res);
				printf("Digite o No do Evento: ");
				scanf("%d", &chooseItem);
				strcpy(buffer, "(SELECT P.CPF,	P.NOME,'PARTICIPANTE' AS CONDICAO FROM PESSOA P INNER JOIN PARTICIPA PA ON P.CPF = PA.PESSOA WHERE PA.EVENTO = ");
				strcat(buffer, PQgetvalue(res, chooseItem, 0)); // 0 = ID
				strcat(buffer, ") UNION (SELECT P.CPF, P.NOME, 'FUNCIONÁRIO' AS CONDICAO FROM PESSOA P INNER JOIN TRABALHA T ON P.CPF = T.PESSOA WHERE T.EVENTO = ");
				strcat(buffer, PQgetvalue(res, chooseItem, 0));
				strcat(buffer, ");");
				system("clear");
				printf("Participantes e funcionarios de um evento:\n");
				res = selectCommand(connection, buffer);
				printTable(res);
				break;
			case 2:
				system("clear");
				res = selectCommand(connection, "SELECT EVENTO FROM TRABALHA;");
				printTable(res);
				printf("Digite o No do Evento: ");
				scanf("%d", &chooseItem);
				system("clear");
				data1 = PQgetvalue(res, chooseItem, 0);

				res = selectCommand(connection, "SELECT CARGO FROM TRABALHA;");
				printTable(res);
				printf("Digite o No do Cargo: ");
				scanf("%d", &chooseItem);
				system("clear");
				data2 = PQgetvalue(res, chooseItem, 0);

				strcpy(query, "SELECT P.CPF, P.NOME, E.NOME AS EMPRESA FROM PESSOA P INNER JOIN TRABALHA T ON P.CPF = T.PESSOA INNER JOIN EMPRESA_FUNCIONARIO E ON T.EMPRESA = E.CNPJ WHERE T.EVENTO =");
				strcat(query, data1);
				strcat(query, "AND T.CARGO = '");
				strcat(query, data2);
				strcat(query, "';");

				res = selectCommand(connection, query);
				printf("Funcionarios de uma determinada funcao\n"); 
				printTable(res);
				break;
			case 3:
				system("clear");
				getchar();
				printf("Preencha a Data:\n");
				data1 = getDate();
				printf("%s\n", data1);
				printf("\n");
				printf("Preencha o Horario\n");
				data2 = getTime();
				printf("%s\n", data2);
				strcpy(query, "SELECT * FROM LOCAL L WHERE L.ID NOT IN (SELECT E.LOCAL FROM EVENTO E WHERE E.DATA = '");
				strcat(query, data1);
				strcat(query, "' AND E.HORA_INICIO <= '");
				strcat(query, data2);
				strcat(query, "');");

				res = selectCommand(connection, query);
				system("clear");
				printf("Locais disponiveis para determinada data e horario\n");
				printTable(res);
				break;
			case 4:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM LOCAL;");
				printTable(res);
				printf("Digite o No do Local: ");
				scanf("%d", &chooseItem);
				getchar();
				system("clear");
				a = PQgetvalue(res, chooseItem, 0); // a = id do local
				printf("Digite a data do inicio:\n");
				data1 = getDate();
				printf("\n");
				printf("Digite a data do fim (rs):\n");
				data2 = getDate();
				system("clear");
				strcpy(query, "SELECT E.DATA, E.HORA_INICIO, E.HORA_FIM FROM EVENTO E WHERE E.LOCAL = ");
				strcat(query, a);
				strcat(query, " AND E.DATA >= '");
				strcat(query, data1);
				strcat(query, "' AND E.DATA <= '");
				strcat(query, data2);
				strcat(query, "';");

				res = selectCommand(connection, query);
				printf("Datas e horarios indisponiveis para um determinado local\n");
				printTable(res);
				break;
			case 5:
				system("clear");
				BIP = selectBIP(); // 1- insumo, 2- presente, 3 - brinquedo
				system("clear");
				switch(BIP){
					case 1:
						res = selectCommand(connection, "SELECT NOME FROM INSUMO;");
						printTable(res);
						printf("Escolha o No do Insumo: ");
						scanf("%d", &chooseItem);
						system("clear");
						a = PQgetvalue(res, chooseItem, 0);
						strcpy(query, "SELECT EMPRESA FROM VENDA_INSUMO WHERE INSUMO LIKE '");
						strcat(query, a);
						strcat(query, "';");
						res = selectCommand(connection, query);
						printf("Empresas fornecedoras de um determinado insumo, presente ou brinquedo\n");
						printTable(res);

						break;
					case 2:
						res = selectCommand(connection, "SELECT NOME FROM PRESENTE;");
						printTable(res);
						printf("Escolha o No do Presente: ");
						scanf("%d", &chooseItem);
						system("clear");
						a = PQgetvalue(res, chooseItem, 0);
						strcpy(query, "SELECT EMPRESA FROM VENDA_PRESENTE WHERE PRESENTE LIKE '");
						strcat(query, a);
						strcat(query, "';");
						res = selectCommand(connection, query);
						printf("Empresas fornecedoras de um determinado insumo, presente ou brinquedo\n");
						printTable(res);
						break;
					case 3:
						res = selectCommand(connection, "SELECT NOME FROM BRINQUEDO;");
						printTable(res);
						printf("Escolha o No do Brinquedo: ");
						scanf("%d", &chooseItem);
						system("clear");
						a = PQgetvalue(res, chooseItem, 0);
						strcpy(query, "SELECT EMPRESA FROM VENDA_BRINQUEDO WHERE BRINQUEDO LIKE '");
						strcat(query, a);
						strcat(query, "';");
						res = selectCommand(connection, query);
						printf("Empresas fornecedoras de um determinado insumo, presente ou brinquedo\n");
						printTable(res);
						break;
				}
				break;
			case 6:
				system("clear");
				printf("1\t Universidade\n");
				printf("2\t Curso\n");
				scanf("%d", &chooseItem);
				system("clear");
				printf("Frequencia de quais Universidade/Cursos contratam mais\n");
				switch(chooseItem){
					case 1:
						res = selectCommand(connection, "SELECT UNIVERSIDADE,COUNT(DISTINCT(FORMATURA)) AS FREQ FROM TURMA GROUP BY	UNIVERSIDADE ORDER BY FREQ DESC;");
						printTable(res);
						break;
					case 2:
						res = selectCommand(connection, "SELECT	CURSO,COUNT(DISTINCT(FORMATURA)) AS FREQ FROM TURMA GROUP BY CURSO ORDER BY FREQ DESC;");
						printTable(res);
						break;
				}
				break;
			case 7:
				system("clear");
				BIP = selectBIP();
				system("clear");
				printf("Insumos/brinquedo/presente mais consumidos em eventos\n");
				switch(BIP){
					case 1: //insumos
						res = selectCommand(connection,
						"SELECT * FROM (SELECT V.INSUMO, COUNT(DISTINCT(V.EVENTO)) AS QTD FROM VENDA_INSUMO_EVENTO V GROUP BY V.INSUMO) G WHERE	G.QTD IN (SELECT MAX(QUERY.QTD) FROM (SELECT COUNT(DISTINCT(V.EVENTO)) AS QTD FROM VENDA_INSUMO_EVENTO V GROUP BY V.INSUMO) QUERY);");
						printTable(res);
						break;
					case 2: // presente
						res = selectCommand(connection,
						"SELECT * FROM(SELECT V.PRESENTE, COUNT(DISTINCT(V.CASAMENTO)) AS QTD FROM VENDA_PRESENTE_CASAMENTO V GROUP BY V.PRESENTE) G WHERE G.QTD IN (SELECT MAX(QUERY.QTD) FROM (SELECT COUNT(DISTINCT(V.CASAMENTO)) AS QTD FROM VENDA_PRESENTE_CASAMENTO V GROUP BY V.PRESENTE) QUERY);");
						printTable(res);
						break;
					case 3: //brinquedo
						res = selectCommand(connection,
						"SELECT * FROM (SELECT V.BRINQUEDO, COUNT(DISTINCT(V.FORMATURA)) AS QTD FROM VENDA_BRINQUEDO_FORMATURA V GROUP BY V.BRINQUEDO) G WHERE G.QTD IN (SELECT MAX(QUERY.QTD) FROM (SELECT COUNT(DISTINCT(V.FORMATURA)) AS QTD FROM VENDA_BRINQUEDO_FORMATURA V GROUP BY V.BRINQUEDO) QUERY);");
						printTable(res);
						break;
				}
				break;

			// sair	
			case 8:
				system("clear");
				inicial(connection);
				break;
			default:
				system("clear");
				printf("Opcao Invalida\n");
				break;	
		}
	}
	PQclear(res);
}

// Menu de consulta
void consultar(PGconn *connection){
	char a;
	PGresult* res;
	int opt = -1;
	int nEmpresa;
	while(opt != 8){
		printf("O que deseja consultar ?\n");
		printf("1\t Pessoa\n");
		printf("2\t Local\n");
		printf("3\t Insumo\n");
		printf("4\t Empresa\n");
		printf("5\t Brinquedo\n");
		printf("6\t Presente\n");
		printf("7\t Evento\n");
		printf("======\n");
		printf("8\t Voltar\n");
		printf("Digite o numero: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				system("clear");
				printf("Tabela Pessoa\n");
				res = selectCommand(connection, "SELECT * FROM PESSOA;"); // correto
				printTable(res);

				PQclear(res); // limpar o buffer de res
				break;
			case 2:
				system("clear");
				printf("Tabela Local\n");
				res = selectCommand(connection, "SELECT * FROM LOCAL;");
				printTable(res);

				PQclear(res); // limpar o buffer de res
				break;
			case 3:
				system("clear");
				printf("Tabela Insumo\n");
				res = selectCommand(connection, "SELECT * FROM INSUMO;");
				printTable(res);

				PQclear(res); // limpar o buffer de res
				break;
			case 4:
				nEmpresa = selectEmpresa();
				system("clear");
				if(nEmpresa == 1){
					printf("Tabela Empresa Insumo\n");
					res = selectCommand(connection, "SELECT * FROM EMPRESA_INSUMO;");
					printTable(res);
				}else if(nEmpresa == 2){
					printf("Tabela Empresa Brinquedo\n");
					res = selectCommand(connection, "SELECT * FROM EMPRESA_BRINQUEDO;");
					printTable(res);
				}else if(nEmpresa == 3){
					printf("Tabela Empresa Presente\n");
					res = selectCommand(connection, "SELECT * FROM EMPRESA_PRESENTE;");
					printTable(res);
				}else {
					printf("Tabela Empresa Funcionario\n");
					res = selectCommand(connection, "SELECT * FROM EMPRESA_FUNCIONARIO;");
					printTable(res);
				}

				PQclear(res); // limpar o buffer de res
				break;
			case 5:
				system("clear");
				printf("Tabela Brinquedo\n");
				res = selectCommand(connection, "SELECT * FROM BRINQUEDO;");
				printTable(res);

				PQclear(res); // limpar o buffer de res
				break;
			case 6:
				system("clear");
				printf("Tabela Presente\n");
				res = selectCommand(connection, "SELECT * FROM PRESENTE;");
				printTable(res);

				PQclear(res); // limpar o buffer de res
				break;
			case 7:
				system("clear");
				printf("Tabela Evento\n");
				res = selectCommand(connection, "SELECT * FROM EVENTO;");
				printTable(res);

				PQclear(res); // limpar o buffer de res
				break;
			case 8:
				system("clear");
				inicial(connection);
				break;
			default:
				system("clear");
				printf("Opcao Invalida\n");
				break;	
		}
	}
	PQclear(res);
}

// Menu de cadastro
void cadastrar(PGconn *connection){
	PGresult* res;
	int opt = -1;
	int nEmpresa;
	while(opt != 8){
		printf("O que deseja cadastrar ?\n");
		printf("1\t Pessoa\n");
		printf("2\t Local\n");
		printf("3\t Insumo\n");
		printf("4\t Empresa\n");
		printf("5\t Brinquedo\n");
		printf("6\t Presente\n");
		printf("7\t Evento\n");
		printf("======\n");
		printf("8\t Voltar\n");
		printf("Digite o numero: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM PESSOA;"); // CORRETO
				insertToDatabase(connection, res, 1);
				printf("Pessoa\n");
				break;
			case 2:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM LOCAL;");
				insertToDatabase(connection, res, 2);
				printf("Local\n");
				break;
			case 3:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM INSUMO;");
				insertToDatabase(connection, res, 3);
				printf("Insumo\n");
				break;
			case 4:
				nEmpresa = selectEmpresa();
				switch(nEmpresa){
					case 1: res = selectCommand(connection, "SELECT * FROM EMPRESA_INSUMO"); break;
					case 2: res = selectCommand(connection, "SELECT * FROM EMPRESA_BRINQUEDO"); break;
					case 3: res = selectCommand(connection, "SELECT * FROM EMPRESA_PRESENTE"); break;
					case 4: res = selectCommand(connection, "SELECT * FROM EMPRESA_FUNCIONARIO"); break;
				}
				nEmpresa = 40 + nEmpresa;
				insertToDatabase(connection, res, nEmpresa);
				system("clear");
				printf("Empresa\n");
				break;
			case 5:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM BRINQUEDO;");
				insertToDatabase(connection, res, 5);
				printf("Brinquedo\n");
				break;
			case 6:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM PRESENTE;");
				insertToDatabase(connection, res, 6);
				printf("Presente\n");
				break;
			case 7:
				system("clear");
				res = selectCommand(connection, "SELECT * FROM EVENTO;");
				insertToDatabase(connection, res, 7);
				printf("Evento\n");
				break;
			case 8:
				system("clear");
				inicial(connection);
				break;
			default:
				system("clear");
				printf("Opcao Invalida\n");
				break;	
		}
	}
	PQclear(res);
}

// Menu Inicial
void inicial(PGconn *connection){
	int opt = -1;
	while(opt != 6){
		printf("O que deseja fazer ?\n");
		printf("1\t Cadastrar\n");
		printf("2\t Consultar\n");
		printf("3\t Relatorio\n");
		printf("4\t Remover\n");
		printf("5\t Alterar\n");
		printf("6\t Sair\n");
		printf("Digite o numero: ");
		scanf("%d", &opt);
		switch(opt){
			case 1:
				system("clear");
				cadastrar(connection);
				break;
			case 2:
				system("clear");
				consultar(connection);
				break;
			case 3:
				system("clear");
				relatorio(connection);
				break;
			case 4:
				system("clear");
				remover(connection);
				break;
			case 5:
				system("clear");
				alterar(connection);
				break;
			case 6:
				system("clear");
				PQfinish(connection);
				exit(1);
				break;
			default:
				system("clear");
				printf("Opcao Invalida\n");
				break;
		}
	}
	return;
}

/* 
argv[1] = usuario
argv[2] = password
argv[3] = dbname

Para teste:
	user = postgres
	password = dev
	dbname = test
*/
int main(int argc, char const *argv[]){
	system("clear");
	if(argc < 2){
		fprintf(stderr, "Usage: out <DBuser> <DBpassword> <DBname>\n");
		exit(1);
	}
	// Connect to database
	char connectStr[255] = "";
	strcat(connectStr, "user = ");
	strcat(connectStr, argv[1]);
	strcat(connectStr, " dbname = ");
	strcat(connectStr, argv[3]);
	strcat(connectStr, " password = ");
	strcat(connectStr, argv[2]);
	PGconn *connection = PQconnectdb(connectStr);
	if(PQstatus(connection) == CONNECTION_BAD){
		fprintf(stderr, "Could not connect to database: %s\n", PQerrorMessage(connection));
		errorExit(connection);
	}

	inicial(connection);
	return 0;
}
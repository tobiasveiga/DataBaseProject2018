# DataBaseProject2018

A prototype of a database made in C, the Database script were made in PostGreSQL

## Features
* CRUD operations
* Show 'Relatorios'
⋅⋅* RELATÓRIO DE PARTICIPANTES E FUNCIONÁRIOS DO EVENTO
..* FUNCIONÁRIOS DE UMA DETERMINADA FUNÇÃO DO EVENTO
..* LOCAIS DISPONÍVEIS PARA UMA DETERMINADA DATA E HORÁRIO
..* DATAS E HORÁRIOS INDISPONÍVEIS PARA UM DETERMINADO LOCAL
..* QUANTIDADE DE EVENTOS POR CIDADE EM UM PERÍODO DE TEMPO
..* Insumos / brinquedos / presentes mais consumidos em eventos (note que consiste de um select para cada tipo)
..* Empresas fornecedoras de um determinado insumo, presente ou brinquedo
..* Frequência de quais universidades / cursos as turmas contratam mais

# How-to

To run the application first you have to run the scripts for creating the tables and inserting new tuples to it.

## How to insert scripts
First you have to copy all the .sql to /var/lib/postgresql directory (to do that, you gotta use sudo permissions):
```
sudo cp <.sql files> /var/lib/postgresql
```
Now just enter on your PostGreSQL application and log in, once you are on your postgresql account run:
```
\i inserts.sql
```

```
\i createsSQL.sql
```

## Running Application
Now that you created the tables and inserted new tuples, run:
```
make
```

and run:
```
/out <DBuser> <DBpassword> <DBname>
```
where:
* DBuser = The username of your database
* DBpassword = The password of your database
* DBname = Your database name

The application is running on Terminal, so bigger the Terminal screen, better!
Enjoy!
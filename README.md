# DataBaseProject2018

Application made in C Programming Language and the Database script were made in PostGreSQL

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
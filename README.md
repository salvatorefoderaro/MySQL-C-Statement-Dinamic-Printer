# MySQL-C-Statement-Dynamic-Printer
A C module to dinamically print the result of a MYSQL_SMT variable, with column name.

The module has been built using the official MySQL documentation (https://dev.mysql.com/doc/c-api/5.7/en/c-api-prepared-statement-type-codes.html).

This is an example for the double pointer */*/columnName.

```c
	char *toPrint[number_of_column] = {"Column 1", "Column 2", ..., "Column n"};
```

Example on how to work with C and MySQL could be found here:

1. https://blog.cotten.io/a-taste-of-mysql-in-c-87c5de84a31d
2. https://dev.mysql.com/doc/c-api/8.0/en/

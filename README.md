# MySQL-C-Statement-Dinamic-Printer
A C module to dinamically print the result of a MYSQL_SMT variable, with column name.

The module has been built using the official MySQL documentation (https://dev.mysql.com/doc/c-api/5.7/en/c-api-prepared-statement-type-codes.html).

This is an example for the double pointer */*/columnName.
'''
	char *toPrint[number_of_column] = {"Column 1", "Column 2", ..., "Column n"};
'''

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printResults(MYSQL_STMT *statement, MYSQL *connection, char **columnName){
	MYSQL *con = connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL_RES *rs_metadata;
	MYSQL_STMT *stmt = statement;
	bool is_null[4];		
	MYSQL_FIELD *fields;
	int i, num_fields, status;
	MYSQL_BIND *rs_bind;
	MYSQL_TIME *date;
	int resultIndex = 0;
	int lastresultIndex = 0;
	i = 0;

	do {
		resultIndex = i;
		printf("\n");
		num_fields = mysql_stmt_field_count(stmt);

		if (num_fields > 0) {

			rs_metadata = mysql_stmt_result_metadata(stmt);
			test_stmt_error(stmt, rs_metadata == NULL);

			fields = mysql_fetch_fields(rs_metadata);
			rs_bind = (MYSQL_BIND *)malloc(sizeof(MYSQL_BIND) * num_fields);
			if (!rs_bind) {
				printf("Cannot allocate output buffers\n");
				exit(1);
			}
			memset(rs_bind, 0, sizeof(MYSQL_BIND) * num_fields);
			
			for (i = 0; i < num_fields; ++i) {
				rs_bind[i].buffer_type = fields[i].type;
				rs_bind[i].is_null = &is_null[i];
				rs_bind[i].buffer = malloc(fields[i].length);
				rs_bind[i].buffer_length = fields[i].length;
			}

			status = mysql_stmt_bind_result(stmt, rs_bind);
			test_stmt_error(stmt, status);
			int counter = 0;
			while (1) {
				status = mysql_stmt_fetch(stmt);
				if (status == 1 || status == MYSQL_NO_DATA){
					break;
				}
				resultIndex = lastresultIndex;

				for (i = 0; i < num_fields; ++i) {

					switch (rs_bind[i].buffer_type) {
						

						case MYSQL_TYPE_TINY: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %c; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_SHORT: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %hi; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_LONG: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %d; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_LONGLONG: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %li; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_FLOAT: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %f; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_DOUBLE: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %lf; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_VAR_STRING: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %s; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_DATE:
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								date = rs_bind[i].buffer;
								printf("%s = %d/%d/%d; ", columnName[resultIndex], date->day, date->month, date->year);
							break;

						case MYSQL_TYPE_DATETIME:
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								date = rs_bind[i].buffer;
								printf("%s = %d/%d/%d - %d:%d:%d; ", columnName[resultIndex], date->day, date->month, date->year, date->hour, date->minute, date->second);
							break;

						case MYSQL_TYPE_TIME:
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								date = rs_bind[i].buffer;
								printf("%s = %d:%d:%d; ", columnName[resultIndex], date->hour, date->minute, date->second);
							break;

						case MYSQL_TYPE_TIMESTAMP:
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								date = rs_bind[i].buffer;
								printf("%s = %d/%d/%d - %d:%d:%d; ", columnName[resultIndex], date->day, date->month, date->year, date->hour, date->minute, date->second);
							break;

						case MYSQL_TYPE_STRING: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %s; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_BLOB: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = %s; ", columnName[resultIndex], (char*)rs_bind[i].buffer);
							break;

						case MYSQL_TYPE_STRING: 
							if (*rs_bind[i].is_null)
								printf("%s = NULL; ", columnName[resultIndex]);
							else
								printf("%s = NULL; ", columnName[resultIndex];
							break;

						default:
							printf("ERROR: unexpected type (%d)\n", rs_bind[resultIndex].buffer_type);
					}
					resultIndex +=1;
				}
				counter = counter + 1;
				printf("\n");
			}
			if (counter == 0){
				printf("\nNo result avaliable!\n");
			}
            
			mysql_free_result(rs_metadata);	// free metadata
			free(rs_bind);	// free output buffers
		} else {

		}

		status = mysql_stmt_next_result(stmt);
		lastresultIndex = i;
		if (status > 0)
			test_stmt_error(stmt, status);
	} while (status == 0);

	for (i = 0; i < num_fields; ++i) {
		free(rs_bind[i].buffer);
	}

	mysql_stmt_close(stmt);
	flushTerminal
	return;
}
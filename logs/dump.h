#ifndef GRAPH_DUMP_H
#define GRAPH_DUMP_H

#include "..\list.h"

void list_graph_dump (list_t *list, FILE *log_file);
void list_dump (list_t *list, const char *file_name, const char *func, const int line, const char *list_name, FILE *log);

#endif /*GRAPH_DUMP*/

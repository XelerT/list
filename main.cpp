#include <stdio.h>
#include "list.h"
#include "logs\dump.h"
#include "logs\log.h"

#define list_dump(list,html_log,graph_path) list_dump(&list, __FILE__,  __PRETTY_FUNCTION__,                    \
                                                      __LINE__, #list, html_log, #graph_path)

int main ()
{
        list_t list = {};
        int capacity = 30;
        if (list_ctor(&list, capacity))
                return NULL_DATA_PTR;

        FILE *log       = fopen("logs\\log.txt",       "w");
        FILE *log_graph = fopen("logs\\log_graph.dot", "w");
        FILE *html_log  = fopen("logs\\log.html",      "w");
        if (!log)
                return NULL_LOG_FILE;

        int error = 0;
        if (error = list_dump(list, html_log, C:\\Users\\taran\\Desktop\\X course\\List\\graph.png))
                return error;

        for (int i = 0; i < 50; i++) {
                // printf("%d\n",  list_insert(&list, i + 10, i));
                list_insert(&list, i + 10, i);
        }
        list_delete(&list, 1);
        list_insert(&list, 666, 5);
        list_delete(&list, 2);

        // for (int i = 0; i < 5; i++;)
        //         list_delete(&list, i);

        if (error = list_dump(list, html_log, C:\\Users\\taran\\Desktop\\X course\\List\\graph.png))
                return error;

        // list_graph_dump(&list, log_graph);

        list_linearize(&list);
        if (error = list_dump(list, html_log, C:\\Users\\taran\\Desktop\\X course\\List\\graph.png))
                return error;
        list_graph_dump(&list, log_graph);
        fclose(log);
        fclose(log_graph);
        //log = fopen("logs\\log.txt", "r");
        //create_html(html_log, log, "C:\\Users\\taran\\Desktop\\X course\\List\\graph.png");
        paste_img(html_log, "C:\\Users\\taran\\Desktop\\X course\\List\\graph.png");
        fclose(html_log);
        if (list_dtor(&list))
                return NULL_DATA_PTR;

        return 0;
}

#include "dump.h"

// отображеніе graphviz -> C
// struct attibute_t {
//         const char *;
// };
//
// struct atributes_t {
//         const char *color;
//         const char *shape;
// }
//
// struct node_t {
//         attribute_t *attributes;
//         node_t *next;
// };
//
// struct edge_t
// struct graph_t
//
// dump_node();

void list_dump (list_t *list, const char *file_name, const char *func, const int line, const char *list_name, FILE *log)
{
        assert(list);
        assert(log);

        fprintf(log, "Name of the file: %s\nName of the function: %s \
                        \nLine: %d\nName of the list: %s\n", file_name, func, line, list_name);
        fprintf(log, "    prev | data | next\n");
        for (int i = 0; i < list->capacity; i++) {
                fprintf(log, "%d) %5lld %5d %5lld\n", i, list->data[i].prev, list->data[i].data, list->data[i].next);
        }
}

void list_graph_dump (list_t *list, FILE *log_file)
{
        assert(list);
        assert(log_file);

        fprintf(log_file, "digraph G {                                                                    \
	                        \ngraph [dpi = 300];                                                      \
	                        \nsplines = ortho                                                         \
                                \n                                                                        \
	                        \nedge[penwidth = 5, color = \"black\"];                                  \
	                        \nnode[shape = rectangle, style = rounded, fixedsize = true,              \
	                        \nheight = 3, width = 2, fontsize = 30, penwidth = 5];                    \
                          ");

        fprintf(log_file, "\n{rank = same;\n");
        for (size_t i = 0; i < list->size; i++) {
                fprintf(log_file, "node%lld [label = \"indx %d \n prev %lld \n %d \n next  %lld\"];\n",
                        i, i, list->data[i].prev, list->data[i].data, list->data[i].next);
        }

        fprintf(log_file, "\nnode[shape = \"rectangle\", style = \"rounded, filled\",                 \
		           \nheight = 3, width = 2, fixedsize = true,                                 \
		           \nfillcolor = \"#00b899\",                                                 \
		           \nfontsize = 30,                                                           \
		           \npenwidth = 5, color = \"black\"                                          \
		           \n]\n");
        for (size_t i = list->size; i < list->capacity; i++) {
                fprintf(log_file, "node%lld [label = \"indx %d \n prev %lld \n %d \n next %lld\"];\n",
                        i, i, list->data[i].prev, list->data[i].data, list->data[i].next);
        }
        fprintf(log_file, "}\n");

        for (size_t i = 0; i < list->capacity; i++) {
                fprintf(log_file, "node%lld -> node%lld [width = 5, style = invis];\n", i, list->data[i].next);
        }
        for (size_t i = 0; i < list->capacity; i++) {           //create link between next elements
                fprintf(log_file, "node%lld -> node%lld [color = red];\n", i, list->data[i].next);
        }

        for (size_t i = 0; i < list->capacity; i++) {           //create link between previous elements
                fprintf(log_file, "node%lld -> node%lld [color = black];\n", i, list->data[i].prev);
        }

        fprintf(log_file, "\n}");
}

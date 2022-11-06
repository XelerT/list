#include "log.h"

int create_html (FILE *html_logs, FILE *log_file, const char *img)
{
        if (html_logs == nullptr) {
                fprintf(log_file, "Null html_log file pointer.\n");
                return NULL_OUTPUT_PTR;
        }
        if (log_file == nullptr) {
                fprintf(html_logs, "<h2>Null input logs file pointer.<\h2>\n");
                if (img != nullptr) {
                        fprintf(log_file, "Null img file pointer.\n");
                        fprintf(html_logs, "<img src=\"%s\" alt=\"graphics\">", img);
                } else {
                        fprintf(html_logs, "<h2>Null input graphics logs file pointer.<\h2>\n");
                        return NULL_IMG_PTR;
                }
                return NULL_INPUT_PTR;
        }

        logs_t logs = {
                .log_file_path = "logs\\log.txt",
                .log_file      = log_file,
                .buf           = nullptr,
                .n_chars       = 0,
        };
        get_log(&logs);
        fprintf(html_logs, "<pre>");
        fwrite(logs.buf, sizeof(char), logs.n_chars, html_logs);
        fprintf(html_logs, "<\pre>");
        fprintf(html_logs, "<img src=\"%s\" alt=\"graphics\" width = \"800wh\">", img);

        free(logs.buf);
        return 0;
}

void get_log (logs_t *logs)
{
        struct stat file = {};
        if (stat(logs->log_file_path, &file) < 0)
                return;
        size_t n_chars = 0;
        char *buf = (char*) calloc(file.st_size + 1, sizeof(char));
        if (!buf) {
                printf("Calloc returned NULL.\n");
                return;
        }

        assert(buf);

        n_chars = fread(buf, sizeof(char), file.st_size, logs->log_file);
        buf[n_chars] = '\0';
        logs->n_chars = n_chars;
        logs->buf = buf;
}

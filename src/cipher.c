#include "cipher.h"

#include <stdlib.h>
#include <string.h>

#define BUFF 128

#define TASK_INV 0
#define TASK_READ 1
#define TASK_WRITE 2
#define EXIT -1

//#define V

int main() {
    int done = 0;
    char* path = NULL;
    while (!done) {
        int task = readtask();
        if (task == TASK_INV) {
            printf("n/a");
#ifdef V
            printf(":main.task = %d\n", task);
#endif
            done = 1;
        } else if (task == EXIT) {
            done = 1;
        } else if (task == TASK_READ) {
            path = getpath();
            printfile(path);
            printf("\n");
        } else if (task == TASK_WRITE) {
            appfile(path);
            printf("\n");
        }
    }
}

void err() { printf("n/a"); }

int readtask() {
    int task = TASK_INV;
    int res = scanf("%d", &task);
    if (!res) {
        task = TASK_INV;
    }
    if (task != EXIT && task > TASK_WRITE) {
        task = TASK_INV;
    }
    fflush(stdin);
    return task;
}

char* getpath() {
    char* str = NULL;
    char let = ' ';
    int size = 0;
    while (scanf("%c", &let) != 0 && let != '\n' && let) {
        size++;
        str = realloc(str, (1 + size) * sizeof(char));
        str[size - 1] = let;
    }
    str[size] = '\0';
    return str;
}
#pragma region Read
char* readfile(FILE* file) {
    fseek(file, 0, SEEK_SET);
    char* out_string = NULL;
    char buffer[BUFF];
    while (fgets(buffer, (int)BUFF, file) != NULL) {
        size_t out_size = 0;
        if (out_string != NULL) {
            out_size += strlen(out_string) + 1;
        }
        out_size += strlen(buffer) + 1;
        out_string = realloc(out_string, out_size * sizeof(char));
        strcat(out_string, buffer);
        clearstring(buffer, BUFF);
    }
    return out_string;
}

void clearstring(char* str, int len) {
    for (int i = 0; i <= len; i++) {
        str[i] = ' ';
    }
    str[len + 1] = '\0';
}

void printfile(char* path) {
    FILE* file = NULL;
    char* buff = NULL;

    int nxt = (path != NULL);

    if (nxt) {
#ifdef V
        printf("printfile.path != NULL\n");
#endif
        file = fopen(path, "r");
        nxt = (file != NULL);
    }
    if (nxt) {
#ifdef V
        printf("printfile.file != NULL\n");
#endif
        buff = readfile(file);
        fclose(file);
        file = NULL;
        nxt = (buff != NULL);
    }
    if (nxt) {
#ifdef V
        printf("printfile.buff != NULL\n");
#endif
        fflush(stdout);
        printf("%s", buff);
    }
    if (!nxt) {
        err();
    }
    free(buff);
    buff = NULL;
}
#pragma endregion
#pragma region Append

void appfile(char* path) {
    FILE* file = NULL;
    char* buff = NULL;

    int nxt = (path != NULL);
    if (nxt) {
        file = fopen(path, "a");
        nxt = (file != NULL);
    }
    if (nxt) {
        buff = malloc(BUFF * sizeof(char));
        nxt = (buff != NULL);
        if (nxt) {
            fflush(stdin);
            char* valid = fgets(buff, BUFF, stdin);
            nxt = valid != NULL;
        }
        if (!nxt && buff != NULL) {
            free(buff);
            buff = NULL;
        }
    }
    if (nxt) {
        nxt = fprintf(file, buff) > 0;
        fclose(file);
    }
    if (!nxt) {
        err();
    } else {
        free(buff);
    }
    buff = NULL;
}

#pragma endregion
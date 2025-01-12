#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *bold_red = "\e[1;31m";
const char *bold_green = "\e[1;32m";
const char *reset_color = "\e[0m";

typedef struct {
    short check;
    short time;
    char description[80];
} task;

FILE* open_file(char *mode) {
    FILE *stream;
    if (!(stream = fopen(".tasks", mode))) {
        fprintf(stderr, "%serror:%s Could not open .tasks file\n", bold_red, reset_color);
        exit(EXIT_FAILURE);
    }
    return stream;
}

int count_tasks(FILE *stream) {
    int count = 0;
    char line[100];
    while (fgets(line, 100, stream))
        count++;
    return count;
}

int search_task(int len, task task_list[], char *string) {
    for (int i = 0; i < len; i++) {
        if (!(strcmp(task_list[i].description, string)))
            return i;
    }
    return -1;
}

int minutes_to_seconds(short minutes) {
    return minutes * 60;
}

void start_task(short time) {
    sleep(minutes_to_seconds(time));
    for (short i = 0; i < 60; i++) {
        printf("\a");
        usleep(100000);
        fflush(stdout);
    }
}

void restart_task(short time) {
    char restart;
    printf("This task has already been completed, do you want to start over? [y/n]: ");
    scanf("%c", &restart);
    if ((restart == 'y') || (restart == 'Y'))
        start_task(time);
    exit(EXIT_SUCCESS);
}

void update_file(int len, task task_list[]) {
    FILE *stream = open_file("w");
    for (int i = 0; i < len; i++)
        fprintf(stream, "%hi,%hi,%s\n", task_list[i].check, task_list[i].time, task_list[i].description);
    fclose(stream);
}

void print_tasks(int len, task task_list[]) {
    puts("tasks:");
    for (int i = 0; i < len; i++) {
        if (task_list[i].check)
            printf("\t%s[x]%s (%-3im) %s\n", bold_green, reset_color, task_list[i].time, task_list[i].description);
        else
            printf("\t%s[ ]%s (%-3im) %s\n", bold_red, reset_color, task_list[i].time, task_list[i].description);
    }
}
int main(int argc, char *argv[]) {
    FILE *stream = open_file("r");
    task tk_list[count_tasks(stream)];
    task tk;
    int i = 0;
    while (fscanf(stream, "%hi,%hi,%79[^\n]\n", &tk.check, &tk.time, tk.description) == 3) {
        tk_list[i].check = tk.check;
        tk_list[i].time = tk.time;
        strcpy(tk_list[i].description, tk.description);
        fflush(stdin);
        i++;
    }
    fclose(stream);
    int len = (sizeof(tk_list) / sizeof(task));
    switch (argc) {
        case 1:
            print_tasks(len, tk_list);
            break;
        case 2:
            int index = search_task(len, tk_list, argv[1]);
            if (index != -1) {
                if (tk_list[index].check)
                    restart_task(tk_list[index].time);
                start_task(tk_list[index].time);
                tk_list[index].check = 1;
                update_file(len, tk_list);
                break;
            } else {
                puts("task not found!");
                break;
            }
        default:
            fprintf(stderr, "%serror:%s the command takes only one argument.\n\texample: ./tkclock \"task description\"\n", bold_red, reset_color);
            exit(EXIT_FAILURE);
    }
    return 0;
}

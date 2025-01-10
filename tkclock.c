#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


const char RESET_COLOR[] = "\e[0m";
const char BOLD_RED[] = "\e[1;31m";
const char BOLD_GREEN[] = "\e[1;32m";

typedef struct {
    unsigned short check;
    unsigned int time;
    char description[80];
} task;

int minutes_to_seconds(int minutes) {
    return minutes * 60;
}

void start_task(int time) {
    sleep(minutes_to_seconds(time));
    for (short i = 0; i < 60; i++) {
        printf("\a"); // alert sound
        usleep(100000);
        fflush(stdout);
    }
}

FILE* open_file(char *mode) {
    FILE *tk_file;
    if (!(tk_file = fopen("./.tasks", mode))) {
        fprintf(stderr, "%serror:%s Could not open .tasks file\n", BOLD_RED, RESET_COLOR);
        exit(EXIT_FAILURE);
    }
    return tk_file;
}

void task_already_completed(int time) {
    char restart;
    printf("this task has already been completed, do you want to start again? [y/n]: ");
    scanf("%c", &restart);
    if ((restart == 'y') || (restart == 'Y'))
        start_task(time);
    else
        puts("abort task");
    exit(EXIT_SUCCESS);
}

void task_not_found() {
    puts("task not found!");
    exit(EXIT_SUCCESS);
}

int search_task(char *t) {
    FILE *tk_file = open_file("r");
    task tk;
    while (fscanf(tk_file, "%hi,%i,%79[^\n]\n", &tk.check, &tk.time, tk.description) == 3) {
        if (strstr(tk.description, t)) {
            if(tk.check)
                task_already_completed(tk.time);
            else
                start_task(tk.time);
            fclose(tk_file);
            return 0;
        }
    }
    task_not_found();
    fclose(tk_file);
}

void print_task(char *check, int time, char *description, const char *color) {
    printf("\t%s%s%s (%03im) %s\n", color, check, RESET_COLOR, time, description);
}

void print_list_tasks() {
    FILE *tk_file = open_file("r");
    task tk;
    printf("tasks list:\n");
    while(fscanf(tk_file, "%hi,%i,%79[^\n]\n", &tk.check, &tk.time, tk.description) == 3) {
        if (tk.check)
            print_task("[x]", tk.time, tk.description, BOLD_GREEN);
        else
            print_task("[ ]", tk.time, tk.description, BOLD_RED);
    }
}

int main(int argc, char *argv[]) {
    switch(argc) {
        case 1:
            print_list_tasks();
            break;
        case 2:
            search_task(argv[1]);
            break;
        default:
            fprintf(stderr, 
                    "%serror:%s the command takes only one argument.\n\texample: ./tkclock \"task description\"\n", 
                    BOLD_RED, RESET_COLOR);
            exit(EXIT_FAILURE);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    FILE *task_file;
    if (!(task_file = fopen("./.tasks", mode))) {
        fprintf(stderr, "error: Could not open .task file\n");
        exit(EXIT_FAILURE);
    }
    return task_file;
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
    FILE *t_file = open_file("r");
    task tk;
    while (fscanf(t_file, "%hi,%i,%79[^\n]\n", &tk.check, &tk.time, tk.description) == 3) {
        if (strstr(tk.description, t)) {
            if(tk.check)
                task_already_completed(tk.time);
            else
                start_task(tk.time);
            fclose(t_file);
            return 0;
        }
    }
    task_not_found();
    fclose(t_file);
}

/*void print_tasks() {
    FILE *tk_file = open_file("r");
    while(fscan
}*/

int main(int argc, char *argv[]) {
    switch(argc) {
        case 1:
            //print_tasks();
            break;
        case 2:
            search_task(argv[1]);
            break;
        default:
            fprintf(stderr, "error: the command takes only one argument.\n\texample: ./tkclock \"task description\"\n");
            exit(EXIT_FAILURE);
    }
    return 0;
}

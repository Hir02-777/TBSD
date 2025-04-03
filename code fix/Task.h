#ifndef TASK_H
#define TASK_H

#define MAX_TITLE_LEN 100
#define MAX_DESC_LEN 300

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char dueDate[11]; 
    int priority;
    char description[MAX_DESC_LEN];
    int completed;
} Task;

#endif

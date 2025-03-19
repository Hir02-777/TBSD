#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H


// structure 
typedef struct Task 
{
    int id;
    char title[100];
    char description[250];
    char deadline[20];
    struct Task *next;
} Task;

// Functions that are performed

void addTask(char *title, char *description, char *deadline);
void deleteTask(int taskId);
void editTask(int taskId, char *newDescription);
void displayTasks();

#endif

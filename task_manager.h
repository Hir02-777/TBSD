#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

// Task structure definition
typedef struct Task {
    int id;
    char title[100];
    char description[250];
    char deadline[20];
    struct Task *next; // Pointer to the next task
} Task;

// Function declarations
void addTask(char *title, char *description, char *deadline);
void deleteTask(int taskId);
void editTask(int taskId, char *newTitle, char *newDescription, char *newDeadline);
void displayTasks();

#endif // TASK_MANAGER_H

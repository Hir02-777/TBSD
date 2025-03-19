#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task_manager.h"

Task *head = NULL;  // Global head pointer for the task list

void addTask(char *title, char *description, char *deadline) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    static int taskId = 1;

    newTask->id = taskId++;
    strcpy(newTask->title, title);
    strcpy(newTask->description, description);
    strcpy(newTask->deadline, deadline);

    newTask->next = head;
    head = newTask;

    printf("Task '%s' added successfully.\n", title);
}

void displayTasks() {
    Task *current = head;
    if (!current) {
        printf("No tasks available.\n");
        return;
    }

    while (current) {
        printf("ID: %d | Title: %s | Deadline: %s\n",
               current->id, current->title, current->deadline);
        current = current->next;
    }
}

void deleteTask(int taskId) {
    Task *current = head, *prev = NULL;
    while (current) {
        if (current->id == taskId) {
            if (prev) prev->next = current->next;
            else head = current->next;
            free(current);
            printf("Task ID %d deleted successfully.\n", taskId);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Task ID %d not found.\n", taskId);
}

void editTask(int taskId, char *newTitle, char *newDescription, char *newDeadline) {
    Task *current = head;

    if (!current) {  // Handle empty list
        printf("No tasks available to edit.\n");
        return;
    }

    while (current) {
        if (current->id == taskId) {
            if (newTitle) strcpy(current->title, newTitle);
            if (newDescription) strcpy(current->description, newDescription);
            if (newDeadline) strcpy(current->deadline, newDeadline);

            printf("Task ID %d updated successfully.\n", taskId);
            return;
        }
        current = current->next;
    }

    printf("Task ID %d not found.\n", taskId);
}

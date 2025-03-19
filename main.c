#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task_manager.h"

int main() {
    int choice, id;
    char title[100], description[200], deadline[20];

    while (1) {
        printf("\nTask Management System\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Edit Task\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter Title: ");
                fgets(title, sizeof(title), stdin);
                strtok(title, "\n"); // Remove newline
                printf("Enter Description: ");
                fgets(description, sizeof(description), stdin);
                strtok(description, "\n");
                printf("Enter Deadline: ");
                fgets(deadline, sizeof(deadline), stdin);
                strtok(deadline, "\n");

                addTask(title, description, deadline);
                break;

            case 2:
                displayTasks();
                break;

            case 3:
                printf("Enter Task ID to edit: ");
                scanf("%d", &id);
                getchar();

                printf("Enter New Title: ");
                fgets(title, sizeof(title), stdin);
                strtok(title, "\n");
                printf("Enter New Description: ");
                fgets(description, sizeof(description), stdin);
                strtok(description, "\n");
                printf("Enter New Deadline: ");
                fgets(deadline, sizeof(deadline), stdin);
                strtok(deadline, "\n");

                editTask(id, title, description, deadline);
                break;

            case 4:
                printf("Enter Task ID to delete: ");
                scanf("%d", &id);
                deleteTask(id);
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

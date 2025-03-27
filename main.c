#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isdigit()
#include "Task_manager.h"

// Function to validate if the ID is numeric
int isValidID(char *id) {
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isdigit(id[i])) {
            return 0;  // Invalid ID (not numeric)
        }
    }
    return 1;  // Valid numeric ID
}

// Function to validate date format YYYY-MM-DD
int isValidDate(char *date) 
{
    int year, month, day;

    // format check: YYYY-MM-DD
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) == 3) {
        if (year >= 2024 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            return 1;  // Valid date
        }
    }
    return 0;  // Invalid date format
}
int main() {
    int choice, id;
    char idInput[10], title[100], description[200], deadline[20];

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
                // Task ID Input & Validation
                printf("Enter Task ID (Numbers only): ");
                scanf("%s", idInput);
                getchar();

                if (!isValidID(idInput)) {
                    printf("Invalid ID! Please enter numbers only.\n");
                    break;
                }

                // Task Details
                printf("Enter Title: ");
                fgets(title, sizeof(title), stdin);
                strtok(title, "\n"); // Remove newline
                printf("Enter Description: ");
                fgets(description, sizeof(description), stdin);
                strtok(description, "\n");

                // Deadline Validation
                printf("Enter Deadline (Format: YYYY-MM-DD): ");
                fgets(deadline, sizeof(deadline), stdin);
                strtok(deadline, "\n");

                if (!isValidDate(deadline)) {
                    printf("Invalid Date Format! Please use YYYY-MM-DD.\n");
                    break;
                }

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

                printf("Enter New Deadline (Format: YYYY-MM-DD): ");
                fgets(deadline, sizeof(deadline), stdin);
                strtok(deadline, "\n");

                if (!isValidDate(deadline)) {
                    printf("Invalid Date Format! Please use YYYY-MM-DD.\n");
                    break;
                }

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
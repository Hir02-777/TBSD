#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task_manager.h"
#include "notification.h"

int main() {
    int choice, id;
    char title[100], description[200], deadline[20];

    while (1) {
        printf("\nTask Management System\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Edit Task\n");
        printf("4. Delete Task\n");
        printf("5. Due Tasks\n");
        printf("6. Snooze Task Notification\n");
        printf("7. View Notification Log\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Title: ");
                fgets(title, sizeof(title), stdin);
                strtok(title, "\n");
                printf("Enter Description: ");
                fgets(description, sizeof(description), stdin);
                strtok(description, "\n");
                printf("Enter Deadline: ");
                fgets(deadline, sizeof(deadline), stdin);
                strtok(deadline, "\n");

                addTask(title, description, deadline);
                sendNotification("New task added!", title);
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
                sendNotification("Task updated!", title);
                break;

            case 4:
                printf("Enter Task ID to delete: ");
                scanf("%d", &id);
                deleteTask(id);
                sendNotification("Task deleted!", "Task Management System");
                break;

            case 5:
                checkDeadlines(taskList, taskCount);
                break;

            case 6:
                printf("Enter Task ID to snooze: ");
                scanf("%d", &id);
                getchar();

                if (id >= 0 && id < taskCount) {
                    int mins;
                    printf("Enter snooze time in minutes: ");
                    scanf("%d", &mins);
                    getchar();
                    snoozeNotification(&taskList[id], mins);
                } else {
                    printf("Invalid Task ID!\n");
                }
                break;

            case 7:
                printNotificationLog();
                break;

            case 8:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

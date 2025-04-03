#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "notification.h"
#include "task.h"


#define MAX_TITLE_LEN 100
#define MAX_DESC_LEN 300
#define INIT_CAPACITY 10


Task* taskList = NULL;
int taskCount = 0;
int taskCapacity = 0;
int taskCounter = 1;

void cleanup() {
    free(taskList);
    printf("Clean exit. Memory freed.\n");
}

void initTaskList() {
    taskList = malloc(INIT_CAPACITY * sizeof(Task));
    taskCapacity = INIT_CAPACITY;
    if (!taskList) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void ensureCapacity() {
    if (taskCount >= taskCapacity) {
        taskCapacity *= 2;
        taskList = realloc(taskList, taskCapacity * sizeof(Task));
        if (!taskList) {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
    }
}

int isValidDateFormat(const char* date) {
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') return 0;

    // Extract parts of the date
    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) return 0;

    // Basic range checks
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    return 1;
}


void trimNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

void createTask() {
    ensureCapacity();
    Task newTask;
    newTask.id = rand() % 20 + 1;

    printf("Enter task title: ");
    fgets(newTask.title, MAX_TITLE_LEN, stdin);
    trimNewline(newTask.title);

    while (1) {
        printf("Enter due date (YYYY-MM-DD): ");
        fgets(newTask.dueDate, sizeof(newTask.dueDate), stdin);
        trimNewline(newTask.dueDate);
        if (isValidDateFormat(newTask.dueDate)) break;
        printf("Invalid format. Try again.\n");
    }

    printf("Enter priority level (1-5): ");
    scanf("%d", &newTask.priority);
    getchar();

    printf("Enter task description: ");
    fgets(newTask.description, MAX_DESC_LEN, stdin);
    trimNewline(newTask.description);

    newTask.completed = 0;
    taskList[taskCount++] = newTask;
    printf("Notification: New Task created successfully!\n");

    time_t now = time(NULL);
    struct tm tm = *localtime(&now);
    char today[11];
    snprintf(today, sizeof(today), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    if (strcmp(newTask.dueDate, today) == 0) {
        sendNotification(newTask); 
    }
}

void displayTasks() {
    if (taskCount == 0) {
        printf("No tasks available to display.\n");
        return;
    }
    printf("\n--- Task List ---\n");
    for (int i = 0; i < taskCount; i++) {
        Task* t = &taskList[i];
        printf("ID: %d | Title: %s | Due: %s | Priority: %d | Status: %s\n",
            t->id, t->title, t->dueDate, t->priority, t->completed ? "Completed" : "Pending");
    }
    printf("-----------------\n");
}

void modifyTask() {
    int id;
    printf("Enter Task ID to modify: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < taskCount; i++) {
        if (taskList[i].id == id) {
            char input[MAX_TITLE_LEN];

            printf("Enter new title (blank to keep): ");
            fgets(input, MAX_TITLE_LEN, stdin);
            trimNewline(input);
            if (strlen(input) > 0) strcpy(taskList[i].title, input);

            printf("Enter new due date (YYYY-MM-DD, blank to keep): ");
            fgets(input, 20, stdin);
            trimNewline(input);
            if (strlen(input) > 0) strcpy(taskList[i].dueDate, input);

            int newPriority;
            printf("Enter new priority (1-5, -1 to keep): ");
            scanf("%d", &newPriority);
            getchar();
            if (newPriority != -1) taskList[i].priority = newPriority;

            printf("Notification: Task modified.\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void deleteTask() {
    int id;
    printf("Enter Task ID to delete: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < taskCount; i++) {
        if (taskList[i].id == id) {
            for (int j = i; j < taskCount - 1; j++) {
                taskList[j] = taskList[j + 1];
            }
            taskCount--;
            printf("Notification:Task deleted!\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void completeTask() {
    int id;
    printf("Enter Task ID to mark as complete: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < taskCount; i++) {
        if (taskList[i].id == id) {
            taskList[i].completed = 1;
            printf("Notification: Task completed !.\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void showUpcomingTasks() {
    printf("\n--- Upcoming Tasks ---\n");
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (!taskList[i].completed) {
            printf("ID: %d | %s | Due: %s\n", taskList[i].id, taskList[i].title, taskList[i].dueDate);
            found = 1;
        }
    }
    if (!found) printf("Notification: No upcoming tasks.\n");
    printf("----------------------\n");
}

void taskSearch() {
    char keyword[MAX_TITLE_LEN];
    printf("Search keyword: ");
    fgets(keyword, MAX_TITLE_LEN, stdin);
    trimNewline(keyword);
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (strstr(taskList[i].title, keyword)) {
            printf("ID: %d | Title: %s | Due: %s | Priority: %d | Status: %s\n",
                taskList[i].id, taskList[i].title, taskList[i].dueDate,
                taskList[i].priority, taskList[i].completed ? "Completed" : "Pending");
            found = 1;
        }
    }
    if (!found) printf("No matching tasks.\n");
}

void deadlineCheck() {
    time_t now = time(NULL);
    struct tm tm = *localtime(&now);

    char today[11];
    snprintf(today, sizeof(today), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    printf("\n--- Deadline Overview ---\n");
    int found = 0;

    for (int i = 0; i < taskCount; i++) {
        if (taskList[i].completed) continue;

        int comparison = strcmp(taskList[i].dueDate, today);

        printf("ID: %d | Title: %s | Due: %s | Priority: %d | Status: ",
            taskList[i].id,
            taskList[i].title,
            taskList[i].dueDate,
            taskList[i].priority
        );

        if (comparison < 0) {
            printf(" Overdue\n");
        }
        else if (comparison == 0) {
            printf("Due Today\n");
        }
        else {
            printf("Upcoming\n");
        }

        found = 1;
    }

    if (!found) {
        printf("No pending tasks with deadlines.\n");
    }

    printf("----------------------------\n");
}



void saveToFile(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Notification: Error opening file to save.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        Task t = taskList[i];
        fprintf(f, "%d;%s;%s;%d;%s;%d\n", t.id, t.title, t.dueDate, t.priority, t.description, t.completed);
    }
    fclose(f);
    printf("Notification: Tasks saved to %s\n", filename);
}

void loadFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Notification: No existing task file found.\n");
        return;
    }
    Task t;
    while (fscanf(f, "%d;%99[^;];%10[^;];%d;%299[^;];%d\n", &t.id, t.title, t.dueDate, &t.priority, t.description, &t.completed) == 6) {
        ensureCapacity();
        taskList[taskCount++] = t;
        if (t.id >= taskCounter) taskCounter = t.id + 1;
    }
    fclose(f);
    // printf("Tasks loaded from %s\n", filename); 
}

void menu(const char* filename) {
    int choice;
    do {
        printf("\n--- Student Planner ---\n");
        printf("1. Create Task\n2. View Tasks\n3. Modify Task\n4. Delete Task\n5. Complete Task\n");
        printf("6. Upcoming Tasks\n7. Search\n8. Deadline Checker\n9. Snooze Task Notification\n");
        printf("10. Dismiss Task Notification\n11. Check Notifications\n12. Save & Exit\nChoose: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: createTask(); break;
        case 2: displayTasks(); break;
        case 3: modifyTask(); break;
        case 4: deleteTask(); break;
        case 5: completeTask(); break;
        case 6: showUpcomingTasks(); break;
        case 7: taskSearch(); break;
        case 8: deadlineCheck(); break;
        case 9: {
            int id, mins;
            printf("Enter Task ID to snooze: ");
            scanf("%d", &id);
            getchar();
            printf("Enter snooze duration (minutes): ");
            scanf("%d", &mins);
            getchar();
            for (int i = 0; i < taskCount; i++) {
                if (taskList[i].id == id) {
                    snoozeNotification(taskList[i], mins);
                    printf("Notification: Task Snoozed for %d minutes.\n", mins);
                    break;
                }
            }
            break;
        }
        case 10: {
            int id;
            printf("Enter Task ID to dismiss notification: ");
            scanf("%d", &id);
            getchar();
            dismissNotification(id);
            printf("Notification dismissed for Task ID %d.\n", id);
            break;
        }
        case 11:
            printf("\n--- Notifications ---\n");
            for (int i = 0; i < taskCount; i++)
            {
              if (taskList[i].completed) continue; // skip completed tasks

             printf("Task: %s\n", taskList[i].title);

             if (strlen(taskList[i].description) > 0)
                   {
                    printf("Description: %s\n", taskList[i].description);
                   }
                else {
                    printf("Description: (No description provided)\n");
                }

                printf("-----------------------------\n");
            }

            if (taskCount == 0) 
            {
                printf("Notification: No Notification\n");
            }
            break;
        case 12:
            saveToFile(filename);
            return;
        default:
            printf("Invalid choice.\n");
        }

    } while (1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s tasks.txt\n", argv[0]);
        return 1;
    }
    srand(time(NULL));
    atexit(cleanup);
    initTaskList();
    loadFromFile(argv[1]);
    menu(argv[1]);

    return 0;
}

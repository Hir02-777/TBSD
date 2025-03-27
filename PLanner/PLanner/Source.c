#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TASKS 100
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

Task taskList[MAX_TASKS];
int taskCount = 0;
int taskCounter = 1;

int isValidDateFormat(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }

    if (date[5] > '1') return 0;
    if (date[5] == '1' && date[6] > '3') return 0;
    if (date[8] > '3') return 0;
    if (date[8] == '3' && date[9] > '2') return 0;

    return 1;
}

void trimNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void createTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full.\n");
        return;
    }

    Task newTask;
    newTask.id = taskCounter++;

    printf("Enter task title: ");
    fgets(newTask.title, MAX_TITLE_LEN, stdin);
    trimNewline(newTask.title);

    while (1) {
        printf("Enter due date (YYYY-MM-DD): ");
        fgets(newTask.dueDate, sizeof(newTask.dueDate), stdin);
        trimNewline(newTask.dueDate);
        if (!isValidDateFormat(newTask.dueDate)) {
            printf("Wrong format, please use YYYY-MM-DD with dashes.\n");
        }
        else {
            break;
        }
    }

    printf("Enter priority level (1-5): ");
    scanf("%d", &newTask.priority);
    getchar();

    printf("Enter task description: ");
    fgets(newTask.description, MAX_DESC_LEN, stdin);
    trimNewline(newTask.description);

    newTask.completed = 0;
    taskList[taskCount++] = newTask;

    printf("Task added successfully!\n");
}

void displayTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n--- Task List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("ID: %d | Title: %s | Due: %s | Priority: %d | Status: %s\n",
            taskList[i].id,
            taskList[i].title,
            taskList[i].dueDate,
            taskList[i].priority,
            taskList[i].completed ? "Completed" : "Pending");
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

            printf("Enter new title (leave blank to keep current): ");
            fgets(input, MAX_TITLE_LEN, stdin);
            trimNewline(input);
            if (strlen(input) > 0) strcpy(taskList[i].title, input);

            printf("Enter new due date (YYYY-MM-DD, blank to keep current): ");
            fgets(input, 20, stdin);
            trimNewline(input);
            if (strlen(input) > 0) strcpy(taskList[i].dueDate, input);

            int newPriority;
            printf("Enter new priority (1-5, -1 to keep current): ");
            scanf("%d", &newPriority);
            getchar();
            if (newPriority != -1) taskList[i].priority = newPriority;

            printf("Task modified successfully!\n");
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
            printf("Task deleted successfully!\n");
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
            printf("Task marked as complete!\n");
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
    if (!found) {
        printf("No upcoming tasks.\n");
    }
    printf("----------------------\n");
}

void taskSearch() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    char keyword[MAX_TITLE_LEN];
    printf("What task are you searching for: ");
    fgets(keyword, MAX_TITLE_LEN, stdin);
    trimNewline(keyword);

    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (strstr(taskList[i].title, keyword)) {
            printf("ID: %d | Title: %s | Due: %s | Priority: %d | Status: %s\n",
                taskList[i].id,
                taskList[i].title,
                taskList[i].dueDate,
                taskList[i].priority,
                taskList[i].completed ? "Completed" : "Pending");
            found = 1;
        }
    }

    if (!found) {
        printf("No matching tasks found.\n");
    }
}

void deadlineCheck() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char today[11];
    snprintf(today, sizeof(today), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    printf("\n--- Tasks Due Today (%s) ---\n", today);
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(taskList[i].dueDate, today) == 0 && !taskList[i].completed) {
            printf("ID: %d | Title: %s | Priority: %d\n", taskList[i].id, taskList[i].title, taskList[i].priority);
            found = 1;
        }
    }
    if (!found) {
        printf("No tasks due today!\n");
    }
    printf("----------------------------\n");
}

void menu() {
    while (1) {
        printf("\n--- Student Planner ---\n");
        printf("1. Create Task\n");
        printf("2. View All Tasks\n");
        printf("3. Modify Task\n");
        printf("4. Delete Task\n");
        printf("5. Mark Task as Complete\n");
        printf("6. Show Upcoming Tasks\n");
        printf("7. Search for a Task\n");
        printf("8. Deadline Checker\n");
        printf("9. Exit\n");
        printf("Choose an option: ");

        int choice;
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
        case 9: printf("Exiting program...\n"); return;
        default: printf("Invalid choice, try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "notification.h"

#define MAX_LOGS 100

static NotificationLog logs[MAX_LOGS];
static int logCount = 0;

// Enter task deadlines
int isTaskDue(Task task) {
    return 1; 
}

void sendNotification(const char* title, const char* message) {
    if (message == NULL || strlen(message) == 0) 
    {
        printf("[Notification] No message\n");
        return;
    }

    printf("[Notification] %s - %s\n", title, message);
}

void checkDeadlines(Task* taskList, int taskCount) {
    int found = 0;

    for (int x = 0; x < taskCount; x++) {
        if (isTaskDue(taskList[x])) 
        {
            printf("Task \"%s\" is due soon!\n", taskList[x].title);

            char message[200];
            snprintf(message, sizeof(message), "Task \"%s\" is due!", taskList[x].title);
            sendNotification("Due Task Alert", message);
            logNotification(taskList[x], SENT);

            found = 1;
        }
    }

    if (!found)
    {
        printf(" No tasks are due.\n");
    }
}

void snoozeNotification(Task* task, int minutes) {
    printf("[Notification] Snoozed task \"%s\" for %d minutes.\n", task->title, minutes);
    logNotification(*task, SNOOZED);
}

void dismissNotification(Task* task) {
    printf("[Notification] Dismissed task \"%s\"\n", task->title);
    logNotification(*task, DISMISSED);
}

void logNotification(Task task, NotificationStatus status) {
    if (logCount >= MAX_LOGS) return;

    logs[logCount].task = task;
    logs[logCount].status = status;

    time_t now = time(NULL);
    struct tm* local = localtime(&now);

    strftime(logs[logCount].timestamp, sizeof(logs[logCount].timestamp), "%Y-%m-%d %H:%M:%S", local);
    logCount++;
}

void printNotificationLog() {
    printf("\n--- Notification Log ---\n");

    if (logCount == 0)
    {
        printf("No notification.\n");
        return;
    }

    for (int x = 0; x < logCount; x++) {
        printf("Task: %s\nStatus: ", logs[x].task.title);
        switch (logs[x].status)
        {
        case SENT: printf("SENT"); 
            break;

        case
        SNOOZED: printf("SNOOZED"); 
            break;

        case
        DISMISSED: printf("DISMISSED");
            break;

        }
        printf("\nTime: %s\n\n", logs[x].timestamp);
    }
}

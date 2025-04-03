// notification.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "notification.h"

#define MAX_TASKS 100
#define LOG_FILE "notification_log.txt"

extern Task* taskList;
extern int taskCount;

int dismissedTasks[MAX_TASKS] = { 0 };
time_t snoozedUntil[MAX_TASKS] = { 0 }; 

void checkDeadlines() {
    time_t now = time(NULL);
    struct tm tm = *localtime(&now);
    char today[11];
    snprintf(today, sizeof(today), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    for (int x = 0; x < taskCount; x++)
    {
        if (taskList[x].completed) continue;
        if (isDismissed(taskList[x].id)) continue;
        if (isSnoozed(taskList[x].id)) continue;

        if (strcmp(taskList[x].dueDate, today) == 0)
        {
            sendNotification(taskList[x]);
        }
    }
}

void sendNotification(Task task)
{
    if (strlen(task.title) == 0) return;

    printf("\n {Notification} Task Due: %s | Due Date: %s \n", task.title, task.dueDate);

    if (strlen(task.description) > 0)
    {
        printf("Description: %s \n", task.description);
    }
    else
    {
        printf("Description: \n");
    }

    logNotification(task, "Sent");
}




void snoozeNotification(Task task, int duration)
{
    time_t future = time(NULL) + (duration * 60); // duration in seconds
    for (int x = 0; x < taskCount; x++)
    {
        if (taskList[x].id == task.id)
        {
            snoozedUntil[x] = future;
            break;
        }
    }
    logNotification(task, "Snoozed");
}

void logNotification(Task task, const char* status) 
{
    FILE* log = fopen(LOG_FILE, "a");
    if (!log) return;

    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    char timeStr[30];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);  // e.g., 2025-04-01 15:30:22

    fprintf(log, "[%s] Task ID: %d | Title: %s | Due Date: %s | Status: %s | Description: %s\n",
        timeStr,
        task.id,
        task.title,
        task.dueDate,
        status,
        strlen(task.description) > 0 ? task.description : "(No description)");

    fclose(log);
}



void dismissNotification(int taskId)
{
    for (int x = 0; x < MAX_TASKS; x++)
    {
        if (dismissedTasks[x] == 0)
        {
            dismissedTasks[x] = taskId;
            break;
        }
    }
}

int isDismissed(int taskId) {
    for (int x = 0; x < MAX_TASKS; x++)
    {
        if (dismissedTasks[x] == taskId) return 1;
    }
    return 0;
}

int isSnoozed(int taskId)
{
    time_t now = time(NULL);
    for (int x = 0; x < taskCount; x++)
    {
        if (taskList[x].id == taskId && snoozedUntil[x] > now) return 1;
    }
    return 0;
}

void viewNotificationLog() {
    FILE* f = fopen(LOG_FILE, "r");
    if (!f) {
        printf("No notification found.\n");
        return;
    }

    char line[512];
    printf("\n--- Notification Log ---\n");
    while (fgets(line, sizeof(line), f)) 
    {
        printf("%s", line);
    }
    printf("------------------------\n");

    fclose(f);
}


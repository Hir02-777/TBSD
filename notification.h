
#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "task_manager.h"
#include <time.h>

typedef enum {
    SENT,
    SNOOZED,
    DISMISSED
} NotificationStatus;

typedef struct {
    Task task;
    NotificationStatus status;
    char timestamp[64];
} NotificationLog;

void checkDeadlines(Task* taskList, int taskCount);
void sendNotification(const char* title, const char* message);
void snoozeNotification(Task* task, int minutes);
void dismissNotification(Task* task);
void logNotification(Task task, NotificationStatus status);
int isTaskDue(Task task);
void printNotificationLog(void);


#endif

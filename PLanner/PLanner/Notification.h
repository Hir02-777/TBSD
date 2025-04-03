#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "task.h"

void checkDeadlines();
void sendNotification(Task task);
void snoozeNotification(Task task, int duration);
void logNotification(Task task, const char* status);
void dismissNotification(int taskId);
int isDismissed(int taskId);
int isSnoozed(int taskId);
void viewNotificationLog();

#endif

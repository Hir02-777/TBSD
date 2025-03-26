    #include <iostream>
    #include <vector>
    #include <string>
    #include <limits>
    #include <chrono>
    #include <ctime>
    #include <iomanip>
    #include <sstream>


    using namespace std;


    struct Task {
        int id;
        string title;
        string dueDate;
        int priority;
        string description;
        bool completed;
    };

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    vector<Task> taskList;
    int taskCounter = 1; 

    bool isValidDateFormat(const string& date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;

        for (int i = 0; i < date.length(); ++i) {
            if (i == 4 || i == 7) continue;
            if (date[5] > '1' || date[6] >= '3') return false;
            if (date[8] > '3') return false;
            if (!isdigit(date[i])) return false;
        }
        return true;
    }


    void createTask() {
        Task newTask;
        newTask.id = taskCounter++;

        cout << "Enter task title: ";
        getline(cin, newTask.title);

        bool loop = true;
        while(loop == true) {
            cout << "Enter due date (YYYY-MM-DD, include dashes): ";
            getline(cin, newTask.dueDate);
                if (!isValidDateFormat(newTask.dueDate)) {
                cout << "Wrong format, please use YYYY-MM-DD with dashes";
            }
                else {
                    loop = false;
                }
                
        }

        cout << "Enter priority level (1-5): ";
        cin >> newTask.priority;
        cin.ignore();

        cout << "Enter task description: ";
        getline(cin, newTask.description);

        newTask.completed = false;
        taskList.push_back(newTask);

        cout << "Task added successfully!\n";
    }


    void displayTasks() {
        if (taskList.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "\n--- Task List ---\n";
        for (const auto& task : taskList) {
            cout << "ID: " << task.id << " | Title: " << task.title
                << " | Due: " << task.dueDate << " | Priority: " << task.priority
                << " | Status: " << (task.completed ? "Completed" : "Pending") << "\n";
        }
        cout << "-----------------\n";
    }


    void modifyTask() {
        int id;
        cout << "Enter Task ID to modify: ";
        cin >> id;
        cin.ignore();

        for (auto& task : taskList) {
            if (task.id == id) {
                cout << "Enter new title (leave blank to keep current): ";
                string newTitle;
                getline(cin, newTitle);
                if (!newTitle.empty()) task.title = newTitle;

                cout << "Enter new due date (YYYY-MM-DD, leave blank to keep current): ";
                string newDate;
                getline(cin, newDate);
                if (!newDate.empty()) task.dueDate = newDate;

                cout << "Enter new priority (1-5, enter -1 to keep current): ";
                int newPriority;
                cin >> newPriority;
                cin.ignore();
                if (newPriority != -1) task.priority = newPriority;

                cout << "Task modified successfully!\n";
                return;
            }
        }
        cout << "Task not found.\n";
    }


    void deleteTask() {
        int id;
        cout << "Enter Task ID to delete: ";
        cin >> id;

        for (auto it = taskList.begin(); it != taskList.end(); ++it) {
            if (it->id == id) {
                taskList.erase(it);
                cout << "Task deleted successfully!\n";
                return;
            }
        }
        cout << "Task not found.\n";
    }


    void completeTask() {
        int id;
        cout << "Enter Task ID to mark as complete: ";
        cin >> id;

        for (auto& task : taskList) {
            if (task.id == id) {
                task.completed = true;
                cout << "Task marked as complete!\n";
                return;
            }
        }
        cout << "Task not found.\n";
    }


    void showUpcomingTasks() {
        bool found = false;
        cout << "\n--- Upcoming Tasks ---\n";
        for (const auto& task : taskList) {
            if (!task.completed) {
                cout << "ID: " << task.id << " | " << task.title << " | Due: " << task.dueDate << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No upcoming tasks.\n";
        }
        cout << "----------------------\n";
    }

    void taskSearch() {
        if (taskList.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "What task are you searching for:\n";
 
        string choice;
        getline(cin, choice);

        bool found = false;
        for (const auto& task : taskList) {
            if (task.title.find(choice) != string::npos) {
                cout << "ID: " << task.id << " | Title: " << task.title
                    << " | Due: " << task.dueDate << " | Priority: " << task.priority
                    << " | Status: " << (task.completed ? "Completed" : "Pending") << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No matching tasks found.\n";
        }
    }

    void Deadline() {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);

        tm localTime;
    #ifdef _WIN32
        localtime_s(&localTime, &now_time);
    #else
        localtime_r(&now_time, &localTime);
    #endif

        ostringstream oss;
        oss << put_time(&localTime, "%Y-%m-%d");
        string today = oss.str();

        cout << "\n--- Tasks Due Today (" << today << ") ---\n";
        bool found = false;
        for (const auto& task : taskList) {
            if (task.dueDate == today && !task.completed) {
                cout << "ID: " << task.id << " | Title: " << task.title << " | Priority: " << task.priority << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No tasks due today!\n";
        }
        cout << "----------------------------\n";
    }


    void menu() {
        while (true) {
            cout << "\n--- Student Planner ---\n";
            cout << "1. Create Task\n";
            cout << "2. View All Tasks\n";
            cout << "3. Modify Task\n";
            cout << "4. Delete Task\n";
            cout << "5. Mark Task as Complete\n";
            cout << "6. Show Upcoming Tasks\n";
            cout << "7. Search for a task\n";
            cout << "8. Deadline Checker\n";
            cout << "9. Exit\n";
            cout << "Choose an option: ";

            int choice;
            cin >> choice;
            cin.ignore();  

            switch (choice) {
            case 1:
                createTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                modifyTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                completeTask();
                break;
            case 6:
                showUpcomingTasks();
                break;
            case 7:
                taskSearch();
                break;
            case 8:
                Deadline();
                break;
            case 9:
                cout << "Exiting program...\n";
                return;
            default:
                cout << "Invalid choice, please try again.\n";
            }
        }
    }

    // Main function
    int main() {
        menu();
        return 0;
    }

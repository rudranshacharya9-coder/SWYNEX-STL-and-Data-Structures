#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Task {
    int id{};
    string title;
    string deadline; // Use YYYY-MM-DD so dates sort chronologically as strings.
    int priority{};  // 1 = High, 2 = Medium, 3 = Low
    bool completed{false};
};

class TaskScheduler {
private:
    unordered_map<int, Task> tasks;
    vector<int> taskOrder;
    int nextId{1};

    static string priorityName(int priority) {
        switch (priority) {
            case 1: return "High";
            case 2: return "Medium";
            default: return "Low";
        }
    }

public:
    void addTask(const string& title, const string& deadline, int priority) {
        Task task{nextId, title, deadline, priority, false};
        tasks.emplace(nextId, task);
        taskOrder.push_back(nextId);
        cout << "Task added successfully. ID: " << nextId << "\n";
        ++nextId;
    }

    void displayTasks(bool sortByPriority = false) const {
        if (taskOrder.empty()) {
            cout << "No tasks found.\n";
            return;
        }

        vector<int> displayOrder = taskOrder;

        if (sortByPriority) {
            sort(displayOrder.begin(), displayOrder.end(),
                 [this](int leftId, int rightId) {
                     const Task& left = tasks.at(leftId);
                     const Task& right = tasks.at(rightId);

                     if (left.priority != right.priority)
                         return left.priority < right.priority;
                     return left.deadline < right.deadline;
                 });
        }

        cout << "\n--- TASK LIST ---\n";
        for (int id : displayOrder) {
            const Task& task = tasks.at(id);
            cout << "ID: " << task.id
                 << " | Title: " << task.title
                 << " | Deadline: " << task.deadline
                 << " | Priority: " << priorityName(task.priority)
                 << " | Status: " << (task.completed ? "Completed" : "Pending")
                 << '\n';
        }
    }

    void completeTask(int id) {
        auto it = tasks.find(id);
        if (it == tasks.end()) {
            cout << "Task ID not found.\n";
            return;
        }

        it->second.completed = true;
        cout << "Task marked as completed.\n";
    }

    void deleteTask(int id) {
        auto it = tasks.find(id);
        if (it == tasks.end()) {
            cout << "Task ID not found.\n";
            return;
        }

        tasks.erase(it);
        taskOrder.erase(
            remove(taskOrder.begin(), taskOrder.end(), id),
            taskOrder.end()
        );
        cout << "Task deleted successfully.\n";
    }

    void searchTask(const string& keyword) const {
        bool found = false;

        for (int id : taskOrder) {
            const Task& task = tasks.at(id);
            if (task.title.find(keyword) != string::npos) {
                cout << "ID: " << task.id
                     << " | Title: " << task.title
                     << " | Deadline: " << task.deadline
                     << " | Priority: " << priorityName(task.priority)
                     << " | Status: " << (task.completed ? "Completed" : "Pending")
                     << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No matching task found.\n";
    }

    void showStatistics() const {
        const int completed = static_cast<int>(count_if(
            taskOrder.begin(), taskOrder.end(),
            [this](int id) { return tasks.at(id).completed; }
        ));

        const int total = static_cast<int>(taskOrder.size());
        cout << "Total tasks: " << total << '\n'
             << "Completed: " << completed << '\n'
             << "Pending: " << total - completed << '\n';
    }
};

int main() {
    TaskScheduler scheduler;
    int choice;

    while (true) {
        cout << "\n========== C++ TASK SCHEDULER ==========\n"
             << "1. Add task\n"
             << "2. Display all tasks\n"
             << "3. Display tasks sorted by priority and deadline\n"
             << "4. Mark task as completed\n"
             << "5. Delete task\n"
             << "6. Search task by title\n"
             << "7. Show task statistics\n"
             << "0. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Thank you for using Task Scheduler!\n";
            break;
        }

        if (choice == 1) {
            string title, deadline;
            int priority;

            cout << "Enter task title: ";
            getline(cin, title);

            if (title.empty()) {
                cout << "Title cannot be empty.\n";
                continue;
            }

            cout << "Enter deadline (YYYY-MM-DD): ";
            getline(cin, deadline);

            cout << "Enter priority (1 = High, 2 = Medium, 3 = Low): ";
            if (!(cin >> priority) || priority < 1 || priority > 3) {
                cout << "Invalid priority. Please choose 1, 2, or 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            scheduler.addTask(title, deadline, priority);
        } else if (choice == 2) {
            scheduler.displayTasks();
        } else if (choice == 3) {
            scheduler.displayTasks(true);
        } else if (choice == 4 || choice == 5) {
            int id;
            cout << "Enter task ID: ";
            if (!(cin >> id)) {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 4)
                scheduler.completeTask(id);
            else
                scheduler.deleteTask(id);
        } else if (choice == 6) {
            string keyword;
            cout << "Enter title or keyword: ";
            getline(cin, keyword);
            scheduler.searchTask(keyword);
        } else if (choice == 7) {
            scheduler.showStatistics();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

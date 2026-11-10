# SWYNEX-STL-and-Data-Structures
# C++ Task Scheduler (SWYNEX Internship Task)

A menu-driven task scheduler built in C++17. It allows users to add, view, search, complete, delete, and prioritize tasks.

## Features

- Add tasks with a title, deadline, and priority.
- View all tasks.
- Sort tasks by priority and then deadline.
- Mark tasks as completed.
- Delete tasks.
- Search task titles using a keyword.
- View total, completed, and pending task counts.

## Requirements

- A C++ compiler that supports C++17 (GCC, Clang, or MSVC).

## How to compile and run

### Windows (MinGW/GCC)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o task_scheduler.exe
task_scheduler.exe
```

### Linux / macOS

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o task_scheduler
./task_scheduler
```

## STL data structures and algorithms

### Containers

- **`unordered_map<int, Task>`** stores tasks using their unique IDs as keys. It provides average O(1) lookup, insertion, and deletion by ID.
- **`vector<int>`** stores task IDs in the order they were added. It provides dynamic storage and efficient iteration. Keeping IDs separately also makes it easy to create a temporary ordering for display without changing the stored task order.

### Algorithms

- **`sort()`** orders a temporary list of task IDs by priority and then deadline. Priority 1 is High, 2 is Medium, and 3 is Low.
- **`remove()` with `erase()`** removes a deleted task's ID from the vector.
- **`count_if()`** counts completed tasks for the statistics view.

The application also uses `unordered_map::find()` for ID lookup and a simple string search for matching task titles.

## Input note

Enter deadlines in `YYYY-MM-DD` format (for example, `2026-12-15`). This format makes lexicographical sorting match chronological order, provided the date is entered in the correct format.

## Project structure

```text
swynex-task-scheduler/
├── main.cpp
├── README.md
├── CMakeLists.txt
└── .gitignore
```

## Future improvements

- Save tasks to a file so they remain available after the program closes.
- Validate calendar dates.
- Add task editing and overdue-task alerts.
- Add unit tests.

## Author

Add your name here before submitting.

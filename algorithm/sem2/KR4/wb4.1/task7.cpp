#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Task {
    string name;
    int priority;
    int order;
};

class PriorityQueue {
private:
    vector<Task> heap;
    int nextOrder = 0;

    bool higherPriority(const Task& first, const Task& second) const {
        if (first.priority != second.priority) {
            return first.priority > second.priority;
        }
        return first.order < second.order;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (higherPriority(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();

        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int best = index;

            if (left < size && higherPriority(heap[left], heap[best])) {
                best = left;
            }

            if (right < size && higherPriority(heap[right], heap[best])) {
                best = right;
            }

            if (best == index) {
                break;
            }

            swap(heap[index], heap[best]);
            index = best;
        }
    }

    int findIndexByName(const string& name) const {
        for (int i = 0; i < static_cast<int>(heap.size()); i++) {
            if (heap[i].name == name) {
                return i;
            }
        }
        return -1;
    }

public:
    bool isEmpty() const {
        return heap.empty();
    }

    void push(const string& name, int priority) {
        heap.push_back({name, priority, nextOrder});
        nextOrder++;
        heapifyUp(heap.size() - 1);
    }

    Task top() const {
        if (isEmpty()) {
            throw runtime_error("Список дел пуст");
        }

        return heap[0];
    }

    Task pop() {
        if (isEmpty()) {
            throw runtime_error("Список дел пуст");
        }

        Task result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }

        return result;
    }

    bool edit(const string& oldName, const string& newName, int newPriority) {
        int index = findIndexByName(oldName);

        if (index == -1) {
            return false;
        }

        int oldPriority = heap[index].priority;
        heap[index].name = newName;
        heap[index].priority = newPriority;

        if (newPriority > oldPriority) {
            heapifyUp(index);
        } else {
            heapifyDown(index);
        }

        return true;
    }

    void print() const {
        if (isEmpty()) {
            cout << "Список дел пуст" << endl;
            return;
        }

        for (const Task& task : heap) {
            cout << "Задание: " << task.name
                 << ", приоритет: " << task.priority << endl;
        }
    }
};

void printMenu() {
    cout << endl;
    cout << "1. Добавить задание" << endl;
    cout << "2. Выполнить задание с максимальным приоритетом" << endl;
    cout << "3. Редактировать задание" << endl;
    cout << "4. Показать список дел" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    PriorityQueue todoList;
    int command;

    do {
        printMenu();
        cin >> command;

        if (command == 1) {
            string name;
            int priority;

            cout << "Введите название задания (одно слово): ";
            cin >> name;
            cout << "Введите приоритет: ";
            cin >> priority;

            todoList.push(name, priority);
            cout << "Задание добавлено" << endl;
        } else if (command == 2) {
            if (todoList.isEmpty()) {
                cout << "Список дел пуст" << endl;
            } else {
                Task done = todoList.pop();
                cout << "Выполнено задание: " << done.name
                     << ", приоритет: " << done.priority << endl;
            }
        } else if (command == 3) {
            string oldName;
            string newName;
            int newPriority;

            cout << "Введите название задания для редактирования: ";
            cin >> oldName;
            cout << "Введите новое название (одно слово): ";
            cin >> newName;
            cout << "Введите новый приоритет: ";
            cin >> newPriority;

            if (todoList.edit(oldName, newName, newPriority)) {
                cout << "Задание отредактировано" << endl;
            } else {
                cout << "Задание не найдено" << endl;
            }
        } else if (command == 4) {
            todoList.print();
        } else if (command != 0) {
            cout << "Неверная команда" << endl;
        }
    } while (command != 0);

    return 0;
}

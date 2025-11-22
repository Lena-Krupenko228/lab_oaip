#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Структура для хранения информации о задаче
struct Task {
    string title;      // Название задачи
    int priority;      // Приоритет (число)
    string deadline;   // Срок выполнения
};

vector<Task> tasks;    // Глобальный вектор для хранения всех задач

// Функция загрузки задач из файла
void loadTasks() {
    ifstream file("tasks.txt");
    if (!file.is_open()) {
        cout << "Файл tasks.txt не найден\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        // Разделяем строку по запятым
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);

        // Проверяем, что найдены оба разделителя
        if (pos1 != string::npos && pos2 != string::npos) {
            // Создаем задачу из частей строки
            Task task;
            task.title = line.substr(0, pos1);
            task.priority = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            task.deadline = line.substr(pos2 + 1);

            tasks.push_back(task);
        }
    }
    file.close();
    cout << "Загружено задач: " << tasks.size() << endl;
}

// Функция сохранения задач в файл
void saveTasks() {
    ofstream file("tasks.txt");
    for (auto& task : tasks) {
        file << task.title << "," << task.priority << "," << task.deadline << endl;
    }
    file.close();
}

// Функция добавления новой задачи
void addTask() {
    Task task;

    cout << "Введите название задачи: ";
    getline(cin, task.title);

    // Если введена пустая строка - выходим из функции
    if (task.title.empty()) {
        cout << "Отмена добавления.\n";
        return;
    }

    cout << "Введите приоритет (число): ";
    cin >> task.priority;
    cin.ignore(); // Очищаем буфер после ввода числа

    cout << "Введите срок выполнения: ";
    getline(cin, task.deadline);

    // Добавляем задачу в вектор
    tasks.push_back(task);

    // Сохраняем изменения в файл
    saveTasks();

    // Записываем действие в лог-файл
    ofstream out("output.txt", ios::app);
    out << "ДОБАВЛЕНО: " << task.title << " | Приоритет: " << task.priority
        << " | Срок: " << task.deadline << endl;
    out.close();

    cout << "Задача успешно добавлена!\n";
}

// Функция поиска задач по названию
void searchTask() {
    string searchTitle;
    cout << "Введите название для поиска: ";
    getline(cin, searchTitle);

    // Записываем запрос в лог
    ofstream out("output.txt", ios::app);
    out << "ПОИСК: " << searchTitle << endl;

    bool found = false;

    // Ищем задачи, содержащие введенную строку в названии
    for (auto& task : tasks) {
        if (task.title.find(searchTitle) != string::npos) {
            cout << "НАЙДЕНО: " << task.title << " (приоритет: " << task.priority
                << ", срок: " << task.deadline << ")\n";
            out << "Найдено: " << task.title << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Задачи с таким названием не найдены.\n";
        out << "Ничего не найдено" << endl;
    }

    out.close();
}

// Функция сортировки задач
void sortTasks() {
    cout << "Выберите критерий сортировки:\n";
    cout << "1 - По приоритету\n";
    cout << "2 - По сроку выполнения\n";
    cout << " выбор: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        // Сортировка по приоритету (по возрастанию)
        sort(tasks.begin(), tasks.end(), [](Task a, Task b) {
            return a.priority < b.priority;
            });
        cout << "Задачи отсортированы по приоритету \n";
    }
    else if (choice == 2) {
        // Сортировка по сроку выполнения
        sort(tasks.begin(), tasks.end(), [](Task a, Task b) {
            return a.deadline < b.deadline;
            });
        cout << "Задачи отсортированы по сроку выполнения\n";
    }
    else {
        cout << "Неверный выбор\n";
        return;
    }

    // Сохраняем отсортированный список
    saveTasks();

    // Логируем действие
    ofstream out("output.txt", ios::app);
    out << "ВЫПОЛНЕНА СОРТИРОВКА" << endl;
    out.close();
}

// Функция поиска задач по приоритету
void tasksByPriority() {
    int maxPriority;
    cout << "Введите макс приоритет: ";
    cin >> maxPriority;
    cin.ignore();

    // Логируем запрос
    ofstream out("output.txt", ios::app);
    out << "ПОИСК ПО ПРИОРИТЕТУ <= " << maxPriority << endl;

    bool found = false;

    // Ищем задачи с приоритетом <= введенному значению
    for (auto& task : tasks) {
        if (task.priority <= maxPriority) {
            cout << "- " << task.title << " (приоритет: " << task.priority
                << ", срок: " << task.deadline << ")\n";
            out << "Найдено: " << task.title << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Задачи с приоритетом <= " << maxPriority << " не найдены\n";
        out << "Ничего не найдено" << endl;
    }

    out.close();
}

// Функция отображения всех задач
void showAllTasks() {
    if (tasks.empty()) {
        cout << "Список задач пуст.\n";
        return;
    }

    cout << "ВСЕ ЗАДАЧИ (" << tasks.size() << "):\n";
    cout << "----------------------------------------\n";

    for (auto& task : tasks) {
        cout << "• " << task.title << " (приоритет: " << task.priority
            << ", срок: " << task.deadline << ")\n";
    }

    // Логируем просмотр
    ofstream out("output.txt", ios::app);
    out << "ПРОСМОТР ВСЕХ ЗАДАЧ: " << tasks.size() << " задач" << endl;
    out.close();
}

int main() {
    setlocale(LC_ALL, "Russian"); 
    // Очищаем файл output.txt при запуске
    ofstream clearFile("output.txt");
    clearFile << "=== ЛОГ ПРОГРАММЫ УПРАВЛЕНИЯ ЗАДАЧАМИ ===\n";
    clearFile.close();

    cout << "=== ПРОГРАММА УПРАВЛЕНИЯ ЗАДАЧАМИ ===\n";

    // Загружаем задачи из файла
    loadTasks();

    int choice;

    // Главный цикл программы
    do {
        cout << "\n════════════════ МЕНЮ ════════════════\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Найти задачу по названию\n";
        cout << "3. Отсортировать задачи\n";
        cout << "4. Найти задачи по приоритету\n";
        cout << "5. Показать все задачи\n";
        cout << "0. Выход\n";
        cout << "═══════════════════════════════════════\n";
        cout << "Выберите действие: ";

        cin >> choice;
        cin.ignore(); // Очищаем буфер после ввода числа

        // Обрабатываем выбор пользователя
        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            searchTask();
            break;
        case 3:
            sortTasks();
            break;
        case 4:
            tasksByPriority();
            break;
        case 5:
            showAllTasks();
            break;
        case 0:
            cout << "Выход из программы\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);

    // Сохраняем задачи перед выходом
    saveTasks();

    // Логируем завершение работы
    ofstream out("output.txt", ios::app);
    out << "=== ПРОГРАММА ЗАВЕРШИЛА РАБОТУ ===\n";
    out.close();

    return 0;
}
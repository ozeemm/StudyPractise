#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

struct Student {
    string name; // Имя студента
    vector<int> labResults; // Результаты лаб.работ

    int totalResult = 0; // Итоговый результат
    int percentResult = 0; // Процент успеваемости

    bool isAutoExam = false; // Получил ли автомат
    bool isAllowedToExam = true; // Допущен ли к экзамену
};

const char fileName[] = "students.txt";

int labsNum; // Количество лаб.работ
vector<int> labsWeight; // Веса лаб.работ

int studentsNum = 0; // Количество студентов
vector<Student> students; // Массив студентов

int maxScore = 0; // Максимальное количество баллов
int maxStudentPercent = 0; // Максимальный процент успеваемости среди студентов 

int menuChoosement; // Выбор в меню

// Очистка консоли
void ClearConsole()
{
    system("cls");
}

void CountStudent(Student& student)
{
    for(int i = 0; i < labsNum; i++)
        student.totalResult += student.labResults[i] * labsWeight[i];
    student.percentResult = student.totalResult * 100 / maxScore;

    if (student.percentResult > maxStudentPercent)
        maxStudentPercent = student.percentResult;

    student.isAutoExam = (student.percentResult > 80);

    bool isBadMark = false;
    for (int mark : student.labResults) {
        if (mark <= 2) {
            isBadMark = true;
            break;
        }
    }
    if (isBadMark) {
        student.isAllowedToExam = false;
        student.isAutoExam = false;
    }
}

// Добавление данных о студенте из консоли
void AddStudent()
{
    ClearConsole();

    Student student;
    student.labResults.resize(labsNum);

    cout << "Имя студента: ";
    cin.ignore();
    getline(cin, student.name);

    for (int i = 0; i < labsNum; i++) {
        do {
            cout << "Оценка студента за " << (i + 1) << " лаб.работу: "; cin >> student.labResults[i];
            if(student.labResults[i] < 0 || student.labResults[i] > 5)
                cout << "Ошибка: оценка лабораторной работы может быть от 0 до 5" << endl;

        } while (student.labResults[i] < 0 || student.labResults[i] > 5);
    }

    CountStudent(student);

    studentsNum++;
    students.push_back(student);
}

// Считывание данных из файла
void ReadFromFile()
{
    ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile.is_open()) {
        cout << "Ошибка при чтении файла" << endl;
        return;
    }

    string inputText;

    inputFile >> inputText;
    labsNum = stoi(inputText); // Преобразование в int
    labsWeight.resize(labsNum);

    for (int i = 0; i < labsNum; i++) {
        inputFile >> inputText;
        labsWeight[i] = stoi(inputText);
        maxScore += 5 * labsWeight[i];
    }

    while (!inputFile.eof()) {
        Student student;
        inputFile.seekg(inputFile.tellg() + (std::streampos)2); // Сдвиг курсора в текстовом файле на след. строку (пропускаются символы: переход на след.строку, конец строки)
        getline(inputFile, inputText);
        student.name = inputText;
        student.labResults.resize(labsNum);
        for (int i = 0; i < labsNum; i++) {
            inputFile >> inputText;
            student.labResults[i] = stoi(inputText);
        }

        CountStudent(student);
        studentsNum++;
        students.push_back(student);
    }
  
    inputFile.close();
}

// Вывод таблицы в консоль
void PrintTable()
{
    cout.width(20); cout << "";
    for (int i = 0; i < labsNum; i++) {
        cout << setw(8) << "Лаба " << (i + 1);
    }
    cout << setw(8) << "Итог";
    cout << setw(22) << "Процент успеваемости";
    cout << setw(9) << "Автомат";
    cout << setw(9) << "Допущен";
    cout << endl;

    for (int i = 0; i < studentsNum; i++)
    {
        cout << setw(20) << students[i].name;
        for (int j = 0; j < labsNum; j++) {
            cout << setw(8) << students[i].labResults[j];
        }
        cout << setw(8) << students[i].totalResult;
        cout << setw(22) << students[i].percentResult;
        cout << setw(9) << (students[i].isAutoExam ? "+" : "-");
        cout << setw(9) << (students[i].isAllowedToExam ? "+" : "-");
        cout << endl;
    }

    // Вывод
    cout << endl;
    cout.width(20); cout << "Вес лабы";
    for (int i = 0; i < labsNum; i++) {
        cout << setw(8) << labsWeight[i];
    }
    cout << endl;

    cout << setw(20) << "Макс. возможная" << setw(8 * labsNum + 8) << maxScore << endl;
    cout << setw(20) << "сумма баллов" << endl;

    cout << setw(20) << "Самая высокая" << setw(8 * labsNum + 8 + 22) << maxStudentPercent << endl;
    cout << setw(20) << "успеваемость" << endl;
}

// Сброс данных таблицы
void ResetTable() {
    studentsNum = 0;
    students.clear();
    maxScore = 0;
    maxStudentPercent = 0;
}


int main()
{
    // Для русских символов
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    bool isFromConsole;
    cout << "Выберите способ ввода данных (0 - из файла, 1 - ручной ввод): "; cin >> isFromConsole;
    ClearConsole();

    if (isFromConsole) {
        // Ввод данных о лаб.работах
        do {
            cout << "Количество лабораторных работ: "; cin >> labsNum;

            if (labsNum <= 0)
                cout << "Ошибка: количество лабораторных работ должно быть положительным числом" << endl;
        } while (labsNum <= 0);
        labsWeight.resize(labsNum);

        cout << "Веса лабораторных работ: ";
        for (int i = 0; i < labsNum; i++) {
            do {
                cin >> labsWeight[i];
                if (labsWeight[i] <= 0)
                    cout << "Ошибка: вес лабораторной работы должнен быть положительным числом" << endl;
            } while (labsWeight[i] <= 0);
            maxScore += 5 * labsWeight[i];
        }

        // Основной цикл
        do {
            ClearConsole();
            if (studentsNum > 0)
                PrintTable();

            cout << "---------- Меню ----------" << endl;
            cout << "0 - Закрыть программу" << endl;
            cout << "1 - Добавить данные о студенте" << endl;
            cout << "2 - Сброс таблицы" << endl;
            do {
                cout << "Ввод: "; cin >> menuChoosement;
                if (menuChoosement < 0 || menuChoosement > 2)
                    cout << "Ошибка: введено некорректное значение" << endl;
            } while (menuChoosement < 0 || menuChoosement > 2);

            switch (menuChoosement)
            {
                case 1:
                    AddStudent();
                    break;

                case 2:
                    ResetTable();
                    break;
            }

        } while (menuChoosement != 0);
    }
    else {
        ReadFromFile();
        PrintTable();
    }
}
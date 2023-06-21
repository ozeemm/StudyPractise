#include <iostream>
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



int main()
{
    // Для русских символов
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    int labsNum; // Количество лаб.работ
    vector<int> labsWeight; // Веса лаб.работ
    
    int studentsNum; // Количество студентов
    vector<Student> students; // Массив студентов

    int maxScore = 0; // Максимальное количество баллов
    int maxStudentPercent = 0; // Максимальный процент успеваемости среди студентов 

    cout << "Ввод данных:" << endl;

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
            if(labsWeight[i] <= 0)
                cout << "Ошибка: вес лабораторной работы должнен быть положительным числом" << endl;
        } while (labsWeight[i] <= 0);

        maxScore += 5 * labsWeight[i];
    }
    

    // Ввод данных о студентах
    cout << "Количество студентов: "; cin >> studentsNum;
    students.resize(studentsNum);

    for (int i = 0; i < studentsNum; i++) {
        cout << "Имя студента: ";
        cin.ignore();
        getline(cin, students[i].name);
        cout << "Результаты его лабораторных работ: ";
        students[i].labResults.resize(labsNum);
        for (int j = 0; j < labsNum; j++) {
            do {
                cin >> students[i].labResults[j];
                if (students[i].labResults[j] <= 0)
                    cout << "Ошибка: оценка лабораторной работы может быть от 0 до 5" << endl;
            } while (students[i].labResults[j] < 0 || students[i].labResults[j] > 5);
        }
    }

    // Подсчёт итогового результата студента и процента успеваемости
    for (int i = 0; i < studentsNum; i++) {
        for (int j = 0; j < labsNum; j++)
            students[i].totalResult += students[i].labResults[j] * labsWeight[j];
        students[i].percentResult = students[i].totalResult * 100 / maxScore;
        if (students[i].percentResult > maxStudentPercent)
            maxStudentPercent = students[i].percentResult;
    }

    // Проверка на автомат
    for (int i = 0; i < studentsNum; i++)
        students[i].isAutoExam = (students[i].percentResult > 80);

    // Проверка на допуск
    for (int i = 0; i < studentsNum; i++) {
        bool isBadMark = false; // Есть ли плохая оценка хотя бы за одну лабу
        for (int j = 0; j < labsNum; j++) {
            if (students[i].labResults[j] <= 2) {
                isBadMark = true;
                break;
            }
        }
        if (isBadMark) {
            students[i].isAllowedToExam = false;
            students[i].isAutoExam = false;
        }
    }

    // Вывод
    cout << "Вывод данных" << endl;
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

    cout.width(20); cout << "Вес лабы";
    for (int i = 0; i < labsNum; i++) {
        cout << setw(8) << labsWeight[i];
    }
    cout << endl;

    cout <<"Макс. возм. сумма баллов: " << maxScore << endl;
    cout << "Самая высокая успеваемость: " << maxStudentPercent << endl;
}
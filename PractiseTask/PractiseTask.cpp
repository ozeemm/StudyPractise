#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

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

    cout << "Ввод данных:" << endl;

    // Ввод данных о лаб.работах
    cout << "Количество лабораторных работ: "; cin >> labsNum;
    cout << "Веса лабораторных работ: ";
    labsWeight.resize(labsNum);
    for (int i = 0; i < labsNum; i++) {
        cin >> labsWeight[i];
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
        for (int j = 0; j < labsNum; j++)
            cin >> students[i].labResults[j];
    }

    // Подсчёт итогового результата студента и процента успеваемости
    for (int i = 0; i < studentsNum; i++) {
        for (int j = 0; j < labsNum; j++)
            students[i].totalResult += students[i].labResults[j] * labsWeight[j];
        students[i].percentResult = students[i].totalResult * 100 / maxScore;
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
        cout.width(8); cout << "Лаба " << (i + 1);
    }
    cout.width(8); cout << "Итог";
    cout.width(22); cout << "Процент успеваемости";
    cout.width(9); cout << "Автомат";
    cout.width(9); cout << "Допущен";
    cout << endl;

    for (int i = 0; i < studentsNum; i++) 
    {
        cout.width(20); cout << students[i].name;
        for (int j = 0; j < labsNum; j++) {
            cout.width(8); cout << students[i].labResults[j];
        }
        cout.width(8); cout << students[i].totalResult;
        cout.width(22); cout << students[i].percentResult;
        cout.width(9); cout << (students[i].isAutoExam ? "+" : "-");
        cout.width(9); cout << (students[i].isAllowedToExam ? "+" : "-");
        cout << endl;
    }

    cout.width(20); cout << "Вес лабы";
    for (int i = 0; i < labsNum; i++) {
        cout.width(8); cout << labsWeight[i];
    }
}
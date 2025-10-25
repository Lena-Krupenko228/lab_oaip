#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    char input[1000];
    cin.getline(input, 1000);

    char words[100][100];
    int c = 0;

    char input_copy[1000];
    strcpy(input_copy, input); // Копируем для strtok

    char* token = strtok(input_copy, " ");
    while (token != NULL && c < 100) {
        strcpy(words[c], token);
        c++;
        token = strtok(NULL, " ");
    }

    // 1. Слова, оканчивающиеся на 'a'
    int c_a = 0;
    for (int i = 0; i < c; i++) {
        int len = (int)strlen(words[i]); // явное преобразование
        if (len > 0 && tolower(words[i][len - 1]) == 'a') {
            c_a++;
        }
    }
    cout << "1. Слова на 'a': " << c_a << endl;

    // 2. Длина самого короткого слова
    int mn = 1000;
    for (int i = 0; i < c; i++) {
        int len = (int)strlen(words[i]); // явное преобразование
        if (len < mn) {
            mn = len;
        }
    }
    cout << "2. Длина самого короткого слова: " << mn << endl;

    // 3. Количество 'b' во втором слове
    int c_b = 0;
    if (c >= 2) {
        for (int i = 0; words[1][i] != '\0'; i++) {
            if (tolower(words[1][i]) == 'b') {
                c_b++;
            }
        }
    }
    cout << "3. Букв 'b' во втором слове: " << c_b << endl;

    // 4. В нижний регистр
    cout << "4. В нижнем регистре: ";
    for (int i = 0; input[i] != '\0'; i++) {
        cout << (char)tolower(input[i]);
    }
    cout << endl;

    // 5. Первый и последний символ совпадают
    int c_sovp = 0;
    for (int i = 0; i < c; i++) {
        int len = (int)strlen(words[i]); // явное преобразование
        if (len > 0 && tolower(words[i][0]) == tolower(words[i][len - 1])) {
            c_sovp++;
        }
    }
    cout << "5. Первый и последний символ совпадают: " << c_sovp << endl;

    // 6. Самая короткая общая подстрока
    char shortest[100] = "";
    int shortestLen = 1000;

    for (int i = 0; i < c; i++) {
        for (int j = i + 1; j < c; j++) {
            char w1[100], w2[100];
            strcpy(w1, words[i]);
            strcpy(w2, words[j]);

            // Переводим в нижний регистр
            for (int k = 0; w1[k] != '\0'; k++) w1[k] = tolower(w1[k]);
            for (int k = 0; w2[k] != '\0'; k++) w2[k] = tolower(w2[k]);

            // Ищем общие подстроки
            for (int start = 0; w1[start] != '\0'; start++) {
                for (int end = start; w1[end] != '\0'; end++) {
                    char sub[100];
                    // Безопасное копирование
                    int subLen = end - start + 1;
                    if (subLen < 100) {
                        strncpy(sub, w1 + start, subLen);
                        sub[subLen] = '\0';

                        // ПРОВЕРЯЕМ, ЕСТЬ ЛИ ПОДСТРОКА ВО ВТОРОМ СЛОВЕ
                        if (strstr(w2, sub) != NULL) {
                            if (subLen < shortestLen) {
                                shortestLen = subLen;
                                strcpy(shortest, sub);
                            }
                        }
                    } // конец if (subLen < 100)
                } // конец for (int end...)
            }
        } // конец for (int j...)
    }

    cout << "6. Самая короткая общая подстрока: " << shortest << endl;

    return 0;
}
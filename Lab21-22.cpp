#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <Windows.h>

using namespace std;


int main() {
    //устанавливаем кириллицу в консоли
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //создаем переменную количества участников опроса
    int participants;
    cout << "Введите количество участников опроса: ";
    cin >> participants;

    //создаем переменную количества вопросов в опросе
    int number_of_questions;
    cout << "Введите количество вопросов в форме: ";
    cin >> number_of_questions;


    //открываем файл чтобы записать в него команды
    std::ofstream out;
    out.open("files.txt");
    if (out.is_open()) {
        for (int i = 0; i < number_of_questions; i++) {
            string line = "type NUL > ";
            line = line + std::to_string(i+1) + ".txt";
            out << line << std::endl;
        }
    }
    out.close();


    //предупреждение о том, что нужно пересохранить его и запустить (он создаст будущие текстоваые файлы)
    cout << "Не забудьте пересохранить файл files.txt в формате .bat!" << endl;

    for (int i = 0; i < number_of_questions; i++) {
        //создаем переменную вопроса
        string question;
        cout << "Введите вопрос: ";
        getline(cin, question);

        //создаем переменную количества вариантов ответа
        int number_of_possible_answers;
        cout << "Введите количество вариантов ответа: ";
        cin >> number_of_possible_answers;


        //создаем два массива с вариантами ответа и их процетами
        list <string> answer_options;
        list <string> percentage_ratio;
        for (int j = 0; j < number_of_possible_answers; j++) {
            //создаем переменную варианта ответа
            string answer_option;
            cout << "Введите вариант ответа: ";
            getline(cin, answer_option);

            //добавляем в список
            answer_options.push_back(answer_option);


            //создаем переменную количества выбравших этот вариант ответа
            int number_of_respondents;
            cout << "Введите количество выбравших этот вариант ответа: ";
            cin >> number_of_respondents;

            //по формуле считаем сколько это в процентах и добавляем в соответствующий список
            double p = number_of_respondents * 100.0 / participants;
            percentage_ratio.push_back(std::to_string(p));
        }

        //открываем файл номера вопроса
        string file_name = std::to_string(i + 1) + ".txt";
        std::ofstream out;
        out.open(file_name);
        if (out.is_open()) {
            //записываем первой строкой: "Вопрос № i"
            string line = "Вопрос № ";
            line = line + std::to_string(i+1) + ":";
            out << line << std::endl;

            //с помощью цикла записываем варианты ответа и их процентное соотношение ко всем участникам опроса построчно
            for (int k = 0; k < number_of_possible_answers; k++) {
                string line;
                line = answer_options.front() + "\t" + percentage_ratio.front() + "%";

                answer_options.pop_front();
                percentage_ratio.pop_front();

                out << line << std::endl;
            }
        }
        out.close();
        cout << "Информация успешно записана в файл!"<<endl;
    }
}

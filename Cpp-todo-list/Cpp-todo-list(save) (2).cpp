// Cpp-todo-list.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <conio.h>

class TodoItem {
private:
    int id;
    std::string description;
    bool completed;

public:
    TodoItem() : id(0), description(""), completed(false) {}
    ~TodoItem() = default;

    bool create(std::string new_description) {
        // generates a random integer between 1 and 100
        id = rand() % 100 + 1;
        description = new_description;
        return true;
    }

    int getId() { return id; }
    std::string getDescription() { return description; }
    bool isCompleted() { return completed; }

    void setCompleted(bool val) { completed = val; }

};

int main()
{
    char input_option;
    std::string input_description;
    int input_id;
    std::string version = "v0.2.0";
    std::list<TodoItem>todoItems;
    std::list<TodoItem>::iterator it;

    srand(time(NULL));

    todoItems.clear();

    //TodoItem test;
    //test.create("this is a test");
    //todoItems.push_back(test);

    while (1) {
        system("cls");
        std::cout << "Todo List Maker - " << version << std::endl;
        std::cout << std::endl;
        std::cout << "Just push one of the buttons displayed in the brackets below, and the function will be available." << std::endl;
        std::cout << std::endl;

        for (it = todoItems.begin(); it != todoItems.end(); it++) {

            std::string completed = it->isCompleted() ? "done" : "not done";

            std::cout << it->getId() << " | " << it->getDescription() << " | "
                << completed << std::endl;
        }

        if (todoItems.empty()) {
            std::cout << "Was gibt es heute zu tun? :)" << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << "[a]dd a new Todo" << std::endl;
        std::cout << "[c]omplete a Todo" << std::endl;
        std::cout << "[d]elete a Todo" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "choice: ";

        while (true) {
            input_option = _getch();

            if (input_option == 'a' || input_option == 'c' || input_option == 'd' || input_option == 'q') {
                std::cout << input_option << std::endl;
                break;
            }
        }

        if (input_option == 'q') {
            std::cout << "Have a great day now!" << std::endl;
            break;
        }
        else if (input_option == 'a') {
            char character;
            bool canceled = false;
            input_description = "";

            std::cout << "Missclicked? Just tap [Esc] any time or [Enter], when description line is empty." << std::endl;
            std::cout << "Add a new description: ";


            while (true) {
                character = _getch();

                if (character == '\x1b') {
                    canceled = true;
                    break;
                }
                else if (character == '\r') {
                    break;
                }
                else if (character == 8) {
                    if (!input_description.empty()) {
                        input_description.pop_back();
                        std::cout << "\b \b";
                    }
                    continue;
                }

                else if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == ' ' ||
                    character == (char)132 || // ä
                    character == (char)148 || // ö
                    character == (char)129 || // ü
                    character == (char)142 || // Ä
                    character == (char)153 || // Ö
                    character == (char)154 || // Ü
                    character == (char)225)   // ß
                {

                    input_description += character;
                    std::cout << character;
                }
            }

            std::cout << std::endl;

            if (!canceled && !input_description.empty()) {
                TodoItem newItem;
                newItem.create(input_description);
                todoItems.push_back(newItem);
            }
        }
        else if (input_option == 'c') {
            std::cout << "Missclicked? Just tap [Esc] anytime or [Enter], when description line is empty." << std::endl;
            std::cout << "Enter id to mark completed: ";

            std::string id_str = "";
            char character;
            bool canceled = false;

            while (true) {
                character = _getch();

                if (character == '\x1b') {
                    canceled = true;
                    break;
                }
                else if (character == '\r') {
                    break;
                }
                else if (character >= '0' && character <= '9') {
                    id_str += character;
                    std::cout << character;
                }
            }

            std::cout << std::endl;

            if (!canceled && !id_str.empty()) {
                input_id = std::stoi(id_str);

                bool found = false;
                for (it = todoItems.begin(); it != todoItems.end(); it++) {
                    if (input_id == it->getId()) {
                        it->setCompleted(true);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "ID not found!" << std::endl;
                    _getch();
                }
            }
        }
        else if (input_option == 'd') {
            std::cout << "Missclicked? Just tap [Esc] anytime or [Enter], when description line is empty." << std::endl;
            std::cout << "Enter id to delete: ";

            std::string id_str = "";
            char character;
            bool found = false;
            bool canceled = false;

            while (true) {
                character = _getch();

                if (character == '\x1b') {
                    canceled = true;
                    break;
                }
                else if (character == '\r') {
                    break;
                }
                else if (character >= '0' && character <= '9') {
                    id_str += character;
                    std::cout << character;
                }
            }

            std::cout << std::endl;

            if (!canceled && !id_str.empty()) {
                input_id = std::stoi(id_str);

                for (it = todoItems.begin(); it != todoItems.end(); it++) {

                    if (input_id == it->getId()) {
                        todoItems.erase(it);
                        found = true;
                        break;
                    }
                }



                if (!found) {
                    std::cout << "ID not found!" << std::endl;
                    _getch();
                }
            }
        }
    }
    return 0;
}
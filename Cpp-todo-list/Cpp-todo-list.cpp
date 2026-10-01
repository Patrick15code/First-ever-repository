// Cpp-todo-list.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <conio.h>
#include <cctype>
#include <windows.h>

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

class ListItem {
private:
    int id;
    std::string description;
    bool completed;

    std::list<TodoItem> todoItems;

public:
    ListItem() : id(0), description(""), completed(false) {}
    ~ListItem() = default;

    bool create(std::string new_description) {
        // generates a random integer between 1 and 100
        id = rand() % 100 + 1;
        description = new_description;
        completed = false;
        return true;
    }

    bool addTodo(std::string todo_description) {
        TodoItem new_todo;

        if (new_todo.create(todo_description)) {
            todoItems.push_back(new_todo);
            return true;
        }
        return false;
    }

    int getIdlist() { return id; }
    std::string getDescription() { return description; }
    bool isCompleted() { return completed; }

    void setCompleted(bool val) { completed = val; }

    std::list<TodoItem>& getTodoItems() { return todoItems; }

};






int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    char input_option;
    std::string input_description;
    int input_id;
    std::string version = "v0.2.0";
    std::list<ListItem>listItems;
    std::list<ListItem>::iterator it;
    std::list<TodoItem>todoItems;
    std::list<TodoItem>::iterator it;

    srand(time(NULL));

    listItems.clear();
    todoItems.clear();

    //TodoItem test;
    //test.create("this is a test");
    //todoItems.push_back(test);

    while (1) {
        bool list_created = false;
        system("cls");
        std::cout << "Todo List Maker - " << version << std::endl;
        std::cout << std::endl;
        
        for (it = listItems.begin(); it != listItems.end(); it++) {

            std::string completed = it->isCompleted() ? "done" : "not done";

            std::cout  << " | " << it->getIdlist() << " | " << " | " << it->getDescription() << " | "
                << completed << std::endl;

            for (auto& todo : it->getTodoItems()) {
                std::string todo_completed = todo.isCompleted() ? "done" : "not done";
                std::cout << "   -> | " << todo.getId() << " | " << todo.getDescription() << " | "
                    << todo_completed << std::endl;
            }
        }

        if (listItems.empty()) {
            std::cout << "Was gibt es heute zu tun? :)" << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << "Press [l] to create your first list!" << std::endl;
        std::cout << "Or [q] to quit the application :')" << std::endl;

        std::cout << "choice: ";


        for (auto& todoItems : it->getTodoItems()) {

            std::string completed = it->isCompleted() ? "done" : "not done";

            std::cout << "->" << " | " << it->getIdlist() << " | " << it->getDescription() << " | "
                 << completed << std::endl;
        }

        while (true) {
            input_option = _getch();

            if (input_option == 'l' || input_option == 'q')
            {
                std::cout << input_option << std::endl;
                break;
            }
        }

        if (input_option == 'q') {
            std::cout << "Have a great day now!" << std::endl;
            break;
        }
        else if (input_option == 'l') {
            char character;
            bool canceled = false;
            input_description = "";

            std::cout << "Missclicked? Just tap [Esc] any time or [Enter], when description line is empty." << std::endl << std::endl;
            std::cout << "Give your list a name: ";


            while (true) {
                character = _getch();

                if (character == '\x1b') {              // ESC gedrückt
                    canceled = true;
                    break;
                }
                if (character == '\r') {                // ENTER gedrückt
                    break;
                }
                if (character == 8) {                   // BACKSPACE gedrückt
                    if (!input_description.empty()) {
                        input_description.pop_back();
                        std::cout << "\b \b";
                    }
                    continue;
                }

                if (std::isalpha(static_cast<unsigned char>(character)) ||
                    std::isspace(static_cast<unsigned char>(character)) ||
                    std::string("äöüÄÖÜß").find(character) != std::string::npos)
                {

                    input_description += character;
                    std::cout << character;
                }
            }

            std::cout << std::endl << std::endl;

            if (!canceled && !input_description.empty()) {
                ListItem newMainList;
                newMainList.create(input_description);
                listItems.push_back(newMainList);
                list_created = true;
            }
        }

        // End of first loop where the user can deside wether or not he is creating a list.


        // Beginning of the secondary more "deeper" loop, where the user can decide to create, complete or delete todo's. Or just quit...
        if (list_created == true) {

            while (true) {

                std::cout << "Great! Now push one of the buttons as shown in the square brackets below, to choose your next step:" << std::endl;
                std::cout << std::endl;

                std::cout << "[a]dd a new Todo" << std::endl;
                std::cout << "[c]omplete a Todo" << std::endl;
                std::cout << "[d]elete a Todo" << std::endl;
                std::cout << "[q]uit" << std::endl;

                std::cout << "choice: ";

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

                    else if (std::isalpha(static_cast<unsigned char>(character)) ||
                        std::isspace(static_cast<unsigned char>(character)) ||
                        std::string("äöüÄÖÜß").find(character) != std::string::npos)
                    {

                        input_description += character;
                        std::cout << character;
                    }
                }

                std::cout << std::endl;

                if (!canceled && !input_description.empty()) {
                    if (!listItems.empty()) {
                        listItems.back().addTodo(input_description);
                    }
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

                    for (auto& currentList : listItems) {
                        for (auto& todo : currentList.getTodoItems()) {
                        if (input_id == todo.getId()) {
                            todo.setCompleted(true);
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
    }
    return 0;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.

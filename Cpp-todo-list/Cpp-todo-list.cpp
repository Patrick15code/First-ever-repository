// Hello to the viewer of this code! Thank you for coming here and trying out my stuff! 
// Please feel free to test an manipulate this code at your will. If you find something that can be improved I would love to hear from you and learn from your advise.
// This Project is inspired by the video from "Erik Yuzwa" called "Let's Build a Todo list application using C++" (https://www.youtube.com/watch?v=D17rZyd9r18),
// in which he explains and shows how to build a standard Todo-List in C++. 
// This video was the start to this project and the weeks long frenzy of improvements and expansions I subjected the code to.
// At this point, I'd like to say a big thank you to Erik Yuzwa for sharing his knowledge with the world and therefor making this project possible!
// 
// So now, feel free to test the ToDo-List and play with it.
// 
// Instructions to build the code:
// 
// I wrote this code using Visual Studio, so the only thing to do in order to make it work is to copy it into your workbench and debug it with the local Windows-Debugger.
//
//


//---------------------------------------------------------------------------------------------------------------------------------------------------
//___________________________________________________________________________________________________________________________________________________

//Start of the code


#include <iostream>                 // You know what it is...

#include <string>                   // Anables the usage of std::string, .empty, .erase, .length etc.... (which makes stuff hell a lot easier).

#include <list>                     // Anables the usage of std::list which is the very foundation of the ToDo-App.

#include <conio.h>                  // This library we need for the comfortable usage of _getch().

#include <cctype>                   // Makes it possible to manipulate strings and to use isalpha(), isdigit(), isspace() as a security-check.

#include <windows.h>                // This one we need to make use of the Windows OS. 

        

//---------------------------------------------------------------------------------------------------------------------------------------------------
//___________________________________________________________________________________________________________________________________________________


//Class-section beginning

int globalListIdCounter = 1;



class TodoItem                      // Class which contains everything for the adding, deleting and completing Todo-Items.
{

    private:                        // Safe space for the main Todo-Item "Ingredients"
        int id;
        std::string description;
        bool completed;

    public:                                                         // Public availabe section of functions usable for the manipulating of the different Todo-Item values.
        TodoItem() : id(0), description(""), completed(false) {}
        ~TodoItem() = default;

        bool create(std::string new_description, int assigned_id)   // Creates new Todo-Item with the parameter of the string, which is typed in by the user and the automatically generated assigned_id.
        {
            
            id = assigned_id;               // Generates a unique local id for every new todo-item
            description = new_description;
            completed = false;
            return true;
        }

        int getId()                         // Returns the id of a Todo. 
        {
            return id; 
        }

        std::string getDescription()        // Reads the description string and returns it.
        {
            return description;
        }

        bool isCompleted()                  // Returns the completed value (true/false)
        {
            return completed;
        }

        void setCompleted(bool value)       // From here the value for completing Todo-Items will be distributed to the variable completed and sets it to its new value.(In this case true)
        {
            completed = value;
        }

};

class ListItem                              // Class which contains everything for the adding, deleting and completing List-Items.
{

// Safe space for the main Todo-Item "Ingredients"
    private:                                
        int id;
        std::string description;
        bool completed;
        std::list<TodoItem> todoItems;
        int listSpecificTodoCounter = 1;



// Public availabe section of functions usable for the manipulating of the different Todo-Item values.
    public:                                                         
        ListItem() : id(0), description(""), completed(false) {}
        ~ListItem() = default;

        bool create(std::string new_description)                //Creats a new List-Item with the only parameter given to be the description typed in by the user.
        {
            id = globalListIdCounter++;
            description = new_description;
            completed = false;
            return true;
        }

        bool addTodo(std::string todo_description)              //Creates a new empty shell "new_Todo" and fills it with the parameter of the description typed in by the user and checks if the build was completed. 
        {
            TodoItem new_todo;

            if (new_todo.create(todo_description, listSpecificTodoCounter++))   
            {
                todoItems.push_back(new_todo);
                return true;
            }
            return false;
        }

        void checkAndResetCounter()                             //Resets the list specific counter back to "1" and informs the user about this action if there are no Todo-Items left in a list.
        {
            if (todoItems.empty())
            {
                listSpecificTodoCounter = 1;
                std::cout << "\n[Info] All todos in that list deleted. Counter has been set back to zero." << std::endl;
            }
        }

        int getIdlist()                                         
        {
            return id;
        }

        std::string getDescription()                           
        {
            return description;
        }

        bool isCompleted()                                     
        {
            return completed;
        }

        void setCompleted(bool val)                             
        {
            completed = val;
        }

        std::list<TodoItem>& getTodoItems()                    // Reference (Gateway) into the private Section of the class "ListItem" that anables us to get the original value of "todoItems" with out having to copy its value every time we want to use it. (A little bit unsafe i know...but for the sake of this simple Project and the use of memory i hope i will be forgiven by this dreary.)
        {
            return todoItems;
        }

};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Another Function-Area, for things we will do over and over again:




std::string readTextInput()                                     // This function is going to be reused for every single time, we need to read a text input from the user.
{
    std::string id_str = "";
    char character;
    bool canceled = false;
    std::string input_description = "";
    size_t cursor_pos = 0;

    while (true)
    {
        character = _getch();


        if (character == 0 || character == '\xe0')              // Here we check if the so called "special keys" (F1, F2, Arrow Keys, etc....) are hit.
        {
            char arrow_code = _getch();

            if (arrow_code == 75)                               // Left Arrow
            {
                if (cursor_pos > 0)                             // Check for the position of the cursor. If it is bigger then 0 we enable it to move left through the written strings. 
                {
                    cursor_pos--;
                    std::cout << "\b";                          
                }
            }
            else if (arrow_code == 77)                          // Right Arrow movement
            {
                if (cursor_pos < input_description.length())    
                {
                    std::cout << input_description[cursor_pos]; 
                    cursor_pos++;
                }
            }
            continue;                                         
        }

        if (character == '\x1b')                                // Esc-Key
        {
            canceled = true;
            break;
        }

        else if (character == '\r')                             // Return-(Enter) Key
        {
            break;
        }

        else if (character == 8)                                // Backspace/Erase section, with managment of the cursor position.
        {
            if (cursor_pos > 0)                                 
            {
                input_description.erase(cursor_pos - 1, 1);     //  Moving cursor-position (coordinates not the body) one step to the left, every time a string is erased.
                cursor_pos--;
                std::cout << "\b";    

                for (size_t i = cursor_pos; i < input_description.length(); ++i)           // Printing out " " for every earsed position.            
                {
                    std::cout << input_description[i];
                }

                std::cout << " "; 

                for (size_t i = input_description.length() + 1; i > cursor_pos; --i)        // Moving cursor body one step to the left every time a string is erased.
                {
                    std::cout << "\b";
                }
            }
            continue;                                              
        }

        else if (std::isalpha(static_cast<unsigned char>(character)) ||
                 std::isspace(static_cast<unsigned char>(character)) ||
                 std::isdigit(static_cast<unsigned char>(character)) ||
                 std::string("äöüÄÖÜß").find(character) != std::string::npos)        // Check if the inputs are characters (A-z), numbers, space or special characters. 
        {
            input_description.insert(cursor_pos, 1, character);                      // Printing out the input of the User to the console.
            for (size_t i = cursor_pos; i < input_description.length(); ++i)         // Iteratring the position of the already written text one step to the right for every new character written.
            {
                std::cout << input_description[i];                                   
            }
            cursor_pos++;                                                            // Iterate the coordinate of the cursor one position to the right.

            for (size_t i = input_description.length(); i > cursor_pos; --i)         // Repositioning the cursor behind the last printed string.
            {
                std::cout << "\b";
            }
        }
    }

    std::cout << std::endl << std::endl;                                              // Printing out two empty lines to make stuff more readable.
    
    return input_description;                                                         // Returning the input value the user has typed in. 
}





std::string readIdInput()                           // Function for reading an Id input from the User Keyboard.
{
    std::string id_str = "";
    char character;
    bool canceled = false;
    size_t cursor_pos = 0;


    while (true)
    {
        character = _getch();

        if (character == 0 || character == '\xe0')              // Here we check if the so called "special keys" (F1, F2, Arrow Keys, etc....) are hit.
        {
            char arrow_code = _getch();
            if (arrow_code == 75)                               // Left Arrow
            {
                if (cursor_pos > 0)                             // Check for the position of the cursor and enabling it to iterate to the left.
                {
                    cursor_pos--;
                    std::cout << "\b";
                }
            }
            else if (arrow_code == 77)                          // Right Arrow
            {
                if (cursor_pos < id_str.length())               // Check for the position of the cursor and enabling it to iterate to the right.
                {
                    std::cout << id_str[cursor_pos];
                    cursor_pos++;
                }
            }
            continue;
        }
        if (character == '\x1b')                            // ESC-Key check for canceling the action.
        {
            canceled = true;
            break;
        }
        else if (character == '\r')                         // Return(Enter-Key) check for breaking the loop.
        {
            break;
        }
        else if (character == 8)                            // Backspace/Erase-Section
        {
            if (!id_str.empty())
            {
                id_str.pop_back();
                std::cout << "\b \b";
            }
            continue;
        }
        else if (character >= '0' && character <= '9')      // Check if the typed in character is an Id. If so: print it out
        {
            id_str += character;
            std::cout << character;
        }
        (void)_getch();
        return id_str;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

//Main-Function-Section



int main()
{
    //In this Section all the local variables an iterators are listed, which we are goin to need, in order to make the main function run properly
    SetConsoleCP(CP_UTF8);                                                          
    SetConsoleOutputCP(CP_UTF8);                                                    
    char input_option;                                                                          
    std::string input_description;
    std::string id_str;
    int input_id;
    std::string version = "v3.1.0";

    std::list<ListItem>listItems;
    std::list<ListItem>::iterator itList;
    std::list<ListItem>::iterator activeListIt = listItems.end();
    bool has_active_list = false;

    std::list<TodoItem>todoItems;
    std::list<TodoItem>::iterator itTodo;

    listItems.clear();
    todoItems.clear();


    while (1)                     // Beginning of the main while loop.
    {
        bool list_created = false;
        system("cls");                          
        std::cout << "Todo List Maker - " << version << std::endl;                           
        std::cout << std::endl;

        //This loop prints out the first status Info and will be automatically update by the adding, deleting or setting 'done' of lists.
        for (itList = listItems.begin(); itList != listItems.end(); itList++)            
        {

            std::string completed = itList->isCompleted() ? "done" : "not done";

            if (has_active_list && itList == activeListIt)
            {
                std::cout << " >>>> ";
            }
            else
            {
                std::cout << "      ";
            }

            std::cout << " | ID: " << itList->getIdlist() << " |  " << itList->getDescription() << " | Status: "
                << completed << std::endl;

            for (auto& todo : itList->getTodoItems())
            {
                std::string todo_completed = todo.isCompleted() ? "done" : "not done";
                std::cout << "  -> | " << todo.getId() << " | " << todo.getDescription() << " | "
                    << todo_completed << std::endl;
            }
        }

        if (listItems.empty())      // Function for when the list is completely empty.
        {
            std::cout << "What needs to be done today? :)" << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << "Press [l] to create your first list!" << std::endl;                   // Printed out on default

        if (!listItems.empty())     // If lists are added, the following strings are added to the screen.
        {
            std::cout << "Press [s] to select a list and manage its Todos!" << std::endl;
            std::cout << "Press [c] to select a list and set it to 'done'." << std::endl;
            std::cout << "Press [d] to delete a list!" << std::endl;
        }

        std::cout << "Or [q] to quit the application :')" << std::endl;                     // Printed out on default

        std::cout << "choice: ";                                                            // Printed out on default



        // Deeper "List-Loop" for the control of the options printed out in the main while loop.
        while (true)        
        {
            input_option = _getch();    // When a Key is hit: Instantly react. No Enter needed.

            if (input_option == 'l' || input_option == 'q' || input_option == 'd' || (input_option == 's' && !listItems.empty()) || (input_option == 'c' && !listItems.empty()))
            {
                std::cout << input_option << std::endl;
                break;
            }
        }

        //Starting with this section we start defining what the computer should do when one of the "Option-Keys" is hit.
        if (input_option == 'q')        // Quitting the application.
        {
            std::cout << "Have a great day now!" << std::endl;
            break;
        }

        else if (input_option == 'l')   // Adding a list.
        {
            std::cout << "Missclicked? Just tap [Esc] any time or [Enter], when description line is empty." << std::endl << std::endl;
            std::cout << "Give your list a name: ";


            input_description = readTextInput();       // Calling the function for reading strings from the user-keyboard.

            
            
            if (!input_description.empty())            // If input description is added, we push it in to the ListItem list and set it the status to "active list".
            {
                ListItem newMainList;
                newMainList.create(input_description);
                listItems.push_back(newMainList);

                activeListIt = std::prev(listItems.end());
                list_created = true;
            }
        }

        else if (input_option == 's')       // Selecting a list by typing in the Id.
        {
            std::cout << "Enter the ID of the list you want to select (or [Esc]/[Enter] to cancel): ";
            std::string id_str = "";
            char character;
            bool canceled = false;

            id_str = readIdInput();

            std::cout << std::endl;

            if (!id_str.empty())
            {
                int search_id = std::stoi(id_str);
                bool found = false;

                for (auto it = listItems.begin(); it != listItems.end(); ++it)
                {
                    if (it->getIdlist() == search_id)
                    {
                        activeListIt = it;
                        has_active_list = true;
                        found = true;
                        break;
                    }
                }

                if (!found)     // Returning a string if the user did not type in a assigned id.
                {
                    std::cout << "List ID not found!" << std::endl;
                    (void) _getch();
                }
            }
        }

        else if (input_option == 'c')       // Selecting a list to set it 'done' by typing in the Id of that string.
        {
            std::cout << "Enter id to mark completed (or [Esc]/[Enter] to cancel): ";
            std::string id_str = "";
            char character;
            bool canceled = false;

            id_str = readIdInput();

            std::cout << std::endl;

            if (!id_str.empty())
            {
                int search_id = std::stoi(id_str);
                bool found = false;

                for (auto it = listItems.begin(); it != listItems.end(); ++it)
                {
                    if (it->getIdlist() == search_id)
                    {
                        activeListIt->setCompleted(!activeListIt->isCompleted());
                        found = true;
                        std::cout << "List " << id_str << " set 'done'. Press a button to continue.";
                        break;
                    }
                }
                if (!found)
                {
                    std::cout << "ID not found in this List!" << std::endl;
                }
                (void)_getch();
            }
        }

        else if (input_option == 'd')               // Selecting a list to delete it also by choosing it by the assigned Id.
        {
            std::cout << "Enter the ID of the list you want to delete (or [Esc]/[Enter] to cancel): ";
            std::string id_str = "";
            char character;
            bool canceled = false;

            id_str = readIdInput();

            std::cout << std::endl;

            if(!id_str.empty())
            {
                int delete_id = std::stoi(id_str);
                bool found = false;
                
                for (auto it = listItems.begin(); it != listItems.end(); ++it)
                {
                    if (it->getIdlist() == delete_id)
                    {
                        if (has_active_list && it == activeListIt)
                        {
                            has_active_list = false;
                        }

                        it = listItems.erase(it);
                        found = true;
                        std::cout << "List deleted successfully!" << std::endl;

                        if (listItems.empty())
                        {
                            globalListIdCounter = 1;
                            std::cout << "All lists cleared. ID counters reset to 1." << std::endl;
                            std::cout << "Press a button to continue." << std::endl;
                        }
                        (void) _getch();
                        break;
                    }
                    else
                    {
                        ++it;
                    }
                }
                if (!found)
                {
                std::cout << "List ID not found!" << std::endl;
                (void) _getch();
                }
            }
        } 
        //End of the explanation part.



        // Start of the deeper "ToDo-Loop"
        while (has_active_list && activeListIt != listItems.end())                      
        {

            // This section includes the default printed string for this loop, which is, as in the List-Loop above, automatically updated when the user adds, deletes or completes a todo.
            system("cls");

            std::cout << "--- CURRENT ACTIVE LIST: " << activeListIt->getDescription() << " ---" << std::endl << std::endl;

            std::cout << "Todos in the list: " << std::endl;

            auto& todos = activeListIt->getTodoItems();
            if (todos.empty())
            {
                std::cout << " (No Todos yet)" << std::endl;
            }

            else
            {
                for (auto& todo : activeListIt->getTodoItems())
                {
                    std::string todo_completed = todo.isCompleted() ? "done" : "not done";
                    std::cout << " -> | ID: " << todo.getId() << " | " << todo.getDescription() << " | " << todo_completed << std::endl;
                }
            }
            std::cout << std::endl;


            std::cout << "Great! Choose your next step:" << std::endl;
            std::cout << std::endl;
            std::cout << "[a]dd a new Todo" << std::endl;
            std::cout << "[c]omplete a Todo" << std::endl;
            std::cout << "[d]elete a Todo" << std::endl;
            std::cout << "[b]ack to main menu" << std::endl;
            std::cout << "[q]uit" << std::endl;
            std::cout << "choice: ";

            // End of the printed by default area.


            // Start of the loop containing the control of the above printed options.
            while (true)
            {
                input_option = _getch();
                if (input_option == 'a' || input_option == 'c' || input_option == 'd' || input_option == 'b' || input_option == 'q')
                {
                    std::cout << input_option << std::endl;
                    break;
                }
            }

            if (input_option == 'q')        // Quitting the application
            {
                std::cout << "Have a great day now!" << std::endl;
                return 0;
            }

            else if (input_option == 'b')       // Switching back to the list menu
            {
                has_active_list = false;
            }

            else if (input_option == 'a')       // Adding a ToDo to the list
            {
                std::cout << "Missclicked? Just tap [Esc] any time or [Enter], when description line is empty." << std::endl;
                std::cout << "Add a new description: ";

                input_description = readTextInput();
                

                if (!input_description.empty())
                {
                    activeListIt->addTodo(input_description);
                }
            }

            else if (input_option == 'c')   // Completing a todo
            {
                id_str = readIdInput();

                std::cout << std::endl;

                if (!id_str.empty())
                {
                    input_id = std::stoi(id_str);
                    bool found = false;

                    for (auto& todo : todos)
                    {
                        if (input_id == todo.getId())
                        {
                            todo.setCompleted(!todo.isCompleted());
                            found = true;
                            std::cout << "Todo " << input_id << " set 'done'. Press a button to continue.";
                            break;
                        }
                    }
                    if (!found) 
                    {
                        std::cout << "ID not found in this List!" << std::endl;
                    }
                    (void) _getch();
                }
            }
            else if (input_option == 'd')   // Seleting a Todo to delete it from the list.
            {
                std::cout << "Missclicked? Just tap [Esc] anytime or [Enter], when description line is empty." << std::endl;
                std::cout << "Enter id to delete: ";
                std::string id_str = "";
                char character;
                bool found = false;
                bool canceled = false;

                id_str = readIdInput();

                std::cout << std::endl;

                if (!canceled && !id_str.empty())
                {
                    input_id = std::stoi(id_str);
                    auto& todos = activeListIt->getTodoItems();

                    for (auto it_todo = todos.begin(); it_todo != todos.end(); )
                    {
                        if (it_todo->getId() == input_id)
                        {
                            it_todo = todos.erase(it_todo);
                            found = true;
                            std::cout << "Todo deleted successfully! Press a button to continue." << std::endl;
                            break;
                        }
                        else
                        {
                            ++it_todo;
                        }                       
                    }
                    
                    if (found)
                    {
                        activeListIt->checkAndResetCounter();
                    }
                    else
                    {
                        std::cout << "ID not found" << std::endl;
                    }
                    (void) _getch();
                }
            }
        }
    }
    return 0;
}



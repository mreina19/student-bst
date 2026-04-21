#include <iostream>
#include <stdexcept>    //exceptions
#include <limits>       //numeric_limits<streamsize>::max()
#include <string>       //string type
#include <vector>       //vector type

#include "bin_tree.h"

using namespace std;

enum class BoxStyle { Error, Warning, Success, Negative, Info };

//ANSI color codes
namespace Color {
    const string Reset = "\033[0m";     //Default color
    const string Red = "\033[31m";
    const string Green = "\033[32m";
    const string Yellow = "\033[33m";
    const string Magenta = "\033[35m";
    const string Cyan = "\033[36m";
}

//Prints a colored, prefixed message to the console using ANSI color codes.
void printMsg(const vector<string>& lines, BoxStyle style = BoxStyle::Info)
{
    string prefix, color;

    switch (style)
    {
        case BoxStyle::Error:
            prefix = "[!!] ";
            color = Color::Red;
            break;

        case BoxStyle::Warning:
            prefix = "[!] ";
            color = Color::Magenta;
            break;

        case BoxStyle::Success:
            prefix = "[+] ";
            color = Color::Green;
            break;

        case BoxStyle::Negative:
            prefix = "[-] ";
            color = Color::Yellow;
            break;

        case BoxStyle::Info:
        default:
            prefix = "[i] ";
            color = Color::Cyan;
            break;
    }

    cout << color << "\n";

    //First line gets the prefix (e.g "[i] "), remaining lines are indented with spaces to align
    for (size_t i = 0; i < lines.size(); ++i)
        cout << (i == 0 ? prefix : string(prefix.size(), ' ')) << lines[i] << "\n";

    //After printing, the console text is reset to the default color
    cout << Color::Reset << "\n";
}


void printMenu()
{
    cout << "----------------------------------------\n"
         << "1-> Insert a student\n"
         << "2-> Check minimum tree height\n"
         << "3-> Check number of students\n"
         << "4-> Check number existance\n"
         << "5-> Check student information, by order\n"
         << "6-> Delete a student\n"
         << "7-> Exit program\n\n"
         << "Option: ";
}

//Executes the selected operation
void executeOperation(short const opc, BinTree &student)
{
    switch (opc)
    {
        case 1:
        {
            size_t number;
            string name;

            while (true)
            {
                printMsg({ "Insert the student information." });
                cout << "Number: ";

                try {
                    cin >> number;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Name: ";
                    getline(cin, name);

                    Student s = { number, name };
                    student.add(s);
                    break;
                }
                catch (const ios_base::failure& e) {
                    printMsg({ "Error: Invalid input. Please enter a number." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                catch (const invalid_argument& e) {
                    printMsg({ string("Error: ") + e.what() }, BoxStyle::Error);
                }
            }

            break;
        }

        case 2:
            printMsg({ "Minimum tree height: " + to_string(student.height()) });
            break;

        case 3:
            printMsg({ "Number of students: " + to_string(student.size()) });
            break;

        case 4:
        {
            if (student.size() == 0)
            {
                printMsg({
                    "There are no elements in the tree.",
                    "First, you need to add one." },
                    BoxStyle::Warning);

                break;
            }

            size_t number;

            while (true)
            {
                printMsg({ "Insert the number to verify." });
                cout << "Number: ";

                try {
                    cin >> number;
                    break;
                }
                catch (const ios_base::failure& e) {
                    printMsg({ "Error: Invalid input. Please enter a number." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            student.contains(number) ? 
                printMsg({ "There is a student that is associated to that number." }, BoxStyle::Success) : 
                printMsg({ "There is no student that is associated to that number." }, BoxStyle::Negative);

            break;
        }

        case 5:
        {
            if (student.size() == 0) {
                printMsg({ "There are no elements in the tree." }, BoxStyle::Warning);
                break;
            }

            vector<const Student*> students = student.inOrder();
            short i = 0;

            for (const Student* s : students) {
                i++;
                printMsg({ "Student " + to_string(i) + ": " + to_string(s->number) + ", " + s->name }, BoxStyle::Success);
            }

            break;
        }

        case 6:
        {
            if (student.size() == 0)
            {
                printMsg({
                    "There are no elements in the tree.",
                    "First, you need to add one." },
                    BoxStyle::Warning);

                break;
            }

            size_t number;

            while (true)
            {
                printMsg({ "Insert the number of the student to delete." });
                cout << "Number: ";

                try {
                    cin >> number;
                    break;
                }
                catch (const ios_base::failure& e) {
                    printMsg({ "Error: Invalid input. Please enter a number." }, BoxStyle::Error);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            student.remove(number) ?
                printMsg({ "Student successfully deleted." }, BoxStyle::Success) :
                printMsg({ "There is no student associated to that number." }, BoxStyle::Negative);
                
            break;
        }

        case 7:
            cout << "Program ended.";
            break;

        default:
            printMsg({ "Select a number between 1-7." }, BoxStyle::Warning);
            break;
    }
}

int main()
{
    short opc;
    BinTree student;

    //Enable exceptions for failbit and badbit
    cin.exceptions(ios::failbit | ios::badbit);

    do
    {
        printMenu();

        try {
            cin >> opc;
        }
        catch (const ios_base::failure& e)
        {
            printMsg({ "Error: Invalid input. Please enter a number." }, BoxStyle::Error);

            //Clear the error and discard bad input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Skip to next iteration
            continue;
        }

        executeOperation(opc, student);

    } while (opc != 7);

    return 0;
}
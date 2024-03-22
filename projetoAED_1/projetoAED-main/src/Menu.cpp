#include "Menu.hpp"
#include <regex>
#include <iostream>
using std::cin, std::cout, std::stringstream, std::regex;

Menu::Menu() {
    this->menuText = "Lorem ipsum dolor sit amet.\n";
    this->allTurmas = AllTurmas("../data/classes_per_uc.csv"); // O(k)
    allTurmas.setSchedule("../data/classes.csv"); // O(l*log p)
    this->allStudents = AllStudents("../data/students_classes.csv", allTurmas); // O(m*n*log p)
    this->allRequests = AllRequests();
}


void Menu::run() {
    int prev = printMainMenu();

    while (prev != -890) { // O(n), n times an input is inserted
        string input;
        int valid;

        cin >> input;
        cout << "\n\n";

        valid = validDetect(prev,input); // O(p), where p is the size of the input string

        if (valid == 0)
            prev = chooser(false, prev);
        else if (valid == 1)
            prev = chooser(true,prev,-1,input);
        else
            prev = chooser(true,prev,stoi(input));
    }
    if (!allRequests.getProcessedRequests().empty()) allRequests.saveProcessedRequests(allStudents); // O(n*p)
    printEndMenu();
}


#ifdef _WIN32

void Menu::clearScreen() const {

}

#else

#include <unistd.h>

void Menu::clearScreen() const {
    cout << "\E[2J\E[H\E[3J";
}

#endif


int Menu::validDetect(int previous, const string& input_choice) {
    bool isInt = true;
    int res = 0;
    for (char c : input_choice) // O(n), where n is the size of the input string
        if (!isdigit(c)) {
            isInt = false;
            break;
        }
    if (isInt) {
        int choiceInt = stoi(input_choice);
        switch(previous) {
            case 0:
                if (choiceInt >= 1 and choiceInt <= 7) res = 2;
                break;
            case 2: case 5:
                if (choiceInt >= 1 and choiceInt <= 5) res = 2;
                break;
            case 1: case 105: case 21:
                if (choiceInt >= 1 and choiceInt <= 4) res = 2;
                break;
            case 111: case 112: case 12: case 211: case 212: case 221: case 222: case 223: case 224: case 6: case 501: case 502:
                if (choiceInt >= 1 and choiceInt <= 2) res = 2;
                break;
            case 22: case 23: case 231: case 232: case 233:
                if (choiceInt >= 1 and choiceInt <= 6) res = 2;
                break;
            case 4: case 500: case 1000: case 1001: case 1105: case 1111: case 1112: case 1012: case 1002: case 1021: case 1211:
            case 1212: case 1022: case 1221: case 1222: case 1223: case 1224: case 1023: case 1231: case 1232: case 1233:
            case 1004: case 1005: case 1006: case 1500: case 1501: case 1502:
            case 2000: case 2001: case 2105: case 2111: case 2112: case 2012: case 2002: case 2021: case 2211: case 2212:
            case 2022: case 2221: case 2222: case 2223: case 2224: case 2023: case 2231: case 2232: case 2233: case 2004:
            case 2005: case 2006: case 2500: case 2501: case 2502:
                if (choiceInt >= 1 and choiceInt <= 3) res = 2;
                break;
            default:
                break;
        }
    }
    else {
        stringstream inputLine(input_choice);
        string arg1, arg2, arg3, arg4;
        switch(previous) {
            case 111:
                getline(inputLine, arg1, ',');
                getline(inputLine, arg2);
                if (regex_match(arg1, regex("UP20[0-2]\\d{6}"))
                and ( regex_match(arg2, regex("L\\.[EB][ACEGIMQ][ACIO]?T?0\\d\\d")) or regex_match(arg2, regex("UP0\\d\\d")) ) )  res = 1; // O(n), where n is the size of the input string
                else res = 0;
                break;
            case 112:
                getline(inputLine, arg1, ',');
                getline(inputLine, arg2, ',');
                getline(inputLine, arg3);
                if (regex_match(arg1, regex("UP20[0-2]\\d{6}"))
                and ( regex_match(arg2, regex("L\\.[EB][ACEGIMQ][ACIO]?T?0\\d\\d")) or regex_match(arg2, regex("UP0\\d\\d")) )
                and regex_match(arg3, regex("[1-3]L[EB][ACEGIMQ][ACIO]?T?\\d\\d")) ) res = 1; // O(n)
                else res = 0;
                break;
            case 12:
                getline(inputLine, arg1, ',');
                getline(inputLine, arg2, ',');
                getline(inputLine, arg3, ',');
                getline(inputLine, arg4);
                if (regex_match(arg1, regex("UP20[0-2]\\d{6}"))
                and ( regex_match(arg2, regex("L\\.[EB][ACEGIMQ][ACIO]?T?0\\d\\d")) or regex_match(arg2, regex("UP0\\d\\d")) )
                and regex_match(arg3, regex("[1-3]L[EB][ACEGIMQ][ACIO]?T?\\d\\d"))
                and regex_match(arg4, regex("[1-3]L[EB][ACEGIMQ][ACIO]?T?\\d\\d")) ) res = 1; // O(n)
                else res = 0;
                break;

            case 211:
                getline(inputLine, arg1, ',');
                getline(inputLine, arg2);
                if ( (regex_match(arg1, regex("L\\.[EB][ACEGIMQ][ACIO]?T?0\\d\\d")) or regex_match(arg1, regex("UP0\\d\\d")))
                and regex_match(arg2, regex("[1-3]L[EB][ACEGIMQ][ACIO]?T?\\d\\d")) ) res = 1; // O(n)
                else res = 0;
                break;
            case 212:
                if (regex_match(input_choice, regex("UP20[0-2]\\d{6}"))) res = 1;
                else res = 0;
                break;
            case 221:
                getline(inputLine, arg1, ',');
                getline(inputLine, arg2);
                if ( (regex_match(arg1, regex("L\\.[EB][ACEGIMQ][ACIO]?T?0\\d\\d")) or regex_match(arg1, regex("UP0\\d\\d")) )
                and regex_match(arg2, regex("[1-3]L[EB][ACEGIMQ][ACIO]?T?\\d\\d")) ) res = 1; // O(n)
                else res = 0;
                break;
            case 222:
                if (regex_match(input_choice, regex("L\\.[EB][ACEGIMQ][ACIO]?T?"))) res = 1; // O(n)
                else res = 0;
                break;
            case 223:
                if (regex_match(input_choice, regex("Year:[1-3]"))) res = 1; // O(n)
                else res = 0;
                break;
            case 224:
                if (regex_match(input_choice, regex("CUs:[1-7]"))) res = 1; // O(n)
                else res = 0;
            default:
                break;
        }
    }
    return res;
}

int Menu::chooser(bool valid, int previous, int input_num, const string& input_codes) {
    int prev = 0;
    if (valid) {
        stringstream inputLine(input_codes);
        string arg1, arg2, arg3, arg4;
        Request request;
        switch (input_num) {
            case -1: // When the input is not a menu option (it is a string)
                switch (previous) {
                    case 111:
                        getline(inputLine, arg1, ',');
                        getline(inputLine, arg2);
                        request = Request(arg1, arg2, "", "");
                        cout << "=================================================================================\n";
                        this->allRequests.insertRequest(request);
                        prev = bottomPrinter2();
                        break;
                    case 112: // Same thing que no 111
                        getline(inputLine, arg1, ',');
                        getline(inputLine, arg2, ',');
                        getline(inputLine, arg3);
                        request = Request(arg1, arg2, arg3, "");
                        cout << "=================================================================================\n";
                        this->allRequests.insertRequest(request);
                        prev = bottomPrinter2();
                        break;
                    case 12:
                        getline(inputLine, arg1, ',');
                        getline(inputLine, arg2, ',');
                        getline(inputLine, arg3, ',');
                        getline(inputLine, arg4);
                        request = Request(arg1, arg2, arg3, arg4);
                        cout << "=================================================================================\n";
                        this->allRequests.insertRequest(request);
                        prev = bottomPrinter2();
                        break;
                    case 211:
                        getline(inputLine, arg1, ',');
                        getline(inputLine, arg2);
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.printTurmaSchedule(arg1, arg2);
                        prev = bottomPrinter();
                        break;
                    case 212:
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.printStudentSchedule(input_codes, allTurmas);
                        prev = bottomPrinter();
                        break;
                    case 221:
                        getline(inputLine, arg1, ',');
                        getline(inputLine, arg2);
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.printTurmaStudents(arg1, arg2);
                        prev = bottomPrinter();
                        break;
                    case 222:
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.printCourseStudents(input_codes);
                        prev = bottomPrinter();
                        break;
                    case 223:
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.printYearStudents(input_codes[5]);
                        prev = bottomPrinter();
                        break;
                    case 224:
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.studentsInNUcs(input_codes[4]-'0');
                        prev = bottomPrinter();
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                switch (previous) {
                    case 0: case 12:
                        prev = printMenu1();
                        break;
                    case 1: case 111: case 112:
                        prev = printMenu11Ch();
                        break;
                    case 105:
                        prev = printMenu11(input_num);
                        break;
                    case 2: case 211: case 212:
                        prev = printMenu21();
                        break;
                    case 21:
                        prev = printMenu211();
                        break;
                    case 22:
                        prev = printMenu221();
                        break;
                    case 221: case 222: case 223: case 224:
                        prev = printMenu22();
                        break;
                    case 23:
                        prev = printMenu231();
                        break;
                    case 231: // CU occupation by Occupation Ascending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        this->allTurmas.UcOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 232: // Class occupation by Occupation Ascending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        this->allTurmas.classOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 233: // Year occupation by Occupation Ascending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        this->allStudents.yearOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 4:
                        cout << "                                  PROCESSING...                                  \n"
                             << "=================================================================================\n";
                        this->allRequests.processPending(this->allStudents, this->allTurmas);
                        prev = bottomPrinter1();
                        break;
                    case 5:
                        cout << "                                  PROCESSING...                                  \n"
                             << "=================================================================================\n";
                        if (!this->allRequests.getPendingRequests().empty()) this->allRequests.undoOnePending();
                        else cout << "No requests to undo, because the pending requests queue is empty.\n";
                        prev = bottomPrinter1();
                        break;
                    case 6: case 501: case 502:
                        prev = printMainMenu();
                        break;
                    case 500:
                        prev = printMenu2();
                        break;

                    // Go back to previous menu because of invalid input
                    case 1000: case 1500: case 1501: case 1502: case 2000: case 2500: case 2501: case 2502:
                        prev = printMainMenu();
                        break;
                    case 1001: case 2001:
                        prev = printMenu1();
                        break;
                    case 1105: case 2105:
                        prev = printMenu11Ch();
                        break;
                    case 1111: case 2111:
                        prev = printMenu11(1);
                        break;
                    case 1112: case 2112:
                        prev = printMenu11(2);
                        break;
                    case 1012: case 2012:
                        prev = printMenu12();
                        break;
                    case 1002: case 2002:
                        prev = printMenu2();
                        break;
                    case 1021: case 2021:
                        prev = printMenu21();
                        break;
                    case 1211: case 2211:
                        prev = printMenu211();
                        break;
                    case 1212: case 2212:
                        prev = printMenu212();
                        break;
                    case 1022: case 2022:
                        prev = printMenu22();
                        break;
                    case 1221: case 2221:
                        prev = printMenu221();
                        break;
                    case 1222: case 2222:
                        prev = printMenu222();
                        break;
                    case 1223: case 2223:
                        prev = printMenu223();
                        break;
                    case 1224: case 2224:
                        prev = printMenu224();
                        break;
                    case 1023: case 2023:
                        prev = printMenu23();
                        break;
                    case 1231: case 2231:
                        prev = printMenu231();
                        break;
                    case 1232: case 2232:
                        prev = printMenu232();
                        break;
                    case 1233: case 2233:
                        prev = printMenu233();
                        break;
                    case 1004: case 2004:
                        prev = processRequestMenu();
                        break;
                    case 1005: case 2005:
                        prev = undoRequestMenu();
                        break;
                    case 1006: case 2006:
                        prev = printMenu6();
                        break;
                    default: // Do nothing
                        break;
                }
                break;
            case 2:
                switch (previous) {
                    case 0:
                        prev = printMenu2();
                        break;
                    case 1:
                        prev = printMenu12();
                        break;
                    case 105:
                        prev = printMenu11(input_num);
                        break;
                    case 111: case 112: case 12: case 211: case 212: case 221: case 222: case 223: case 224: case 6: case 501: case 502: 
                        // Exit the tool
                        prev = -890;
                        break;
                    case 2:
                        prev = printMenu22();
                        break;
                    case 21:
                        prev = printMenu212();
                        break;
                    case 22:
                        prev = printMenu222();
                        break;
                    case 23:
                        prev = printMenu232();
                        break;
                    case 231: //CU Occupation by Occupation Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.UcOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 232: //Class Occupation by Occupation Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.classOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 233: //Year Occupation by Occupation Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.yearOccupation(input_num);
                        prev = bottomPrinter();
                        break;

                    case 4: case 500: case 1000: case 1001: case 1105: case 1111: case 1112: case 1012: case 1002: case 1021:
                    case 1211: case 1212: case 1022: case 1221: case 1222: case 1223: case 1224: case 1023: case 1231:
                    case 1232: case 1233: case 1004: case 1005: case 1006: case 1500: case 1501: case 1502:
                    case 2000: case 2001: case 2105: case 2111: case 2112: case 2012: case 2002: case 2021:
                    case 2211: case 2212: case 2022: case 2221: case 2222: case 2223: case 2224: case 2023: case 2231:
                    case 2232: case 2233: case 2004: case 2005: case 2006: case 2500: case 2501: case 2502:
                        prev = printMainMenu();
                        break;
                    case 5:
                        cout << "                                  PROCESSING...                                  \n"
                             << "=================================================================================\n";
                        if (!this->allRequests.getPendingRequests().empty()) this->allRequests.undoAllPending();
                        else cout << "No requests to undo, because the pending requests queue is empty.\n";
                        prev = bottomPrinter1();
                        break;
                    default: // Do nothing
                        break;
                }
                break;
            case 3:
                switch (previous) {
                    case 0:
                        cout << "                                  PROCESSING...                                  \n"
                             << "=================================================================================\n";
                        this->allRequests.printPending();
                        prev = bottomPrinter1();
                        break;
                    case 1:
                        prev = printMainMenu();
                        break;
                    case 105:
                        prev = printMenu1();
                        break;
                    case 2:
                        prev = printMenu23();
                        break;
                    case 21:
                        prev = printMenu2();
                        break;
                    case 22:
                        prev = printMenu223();
                        break;
                    case 23:
                        prev = printMenu233();
                        break;
                    case 231: //CU Occupation by CU Ascending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.UcOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 232: //Class Occupation by CU Ascending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.classOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 233: //Year Occupation by CU Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.yearOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 4: case 500: case 1000: case 1001: case 1105: case 1111: case 1112: case 1012: case 1002: case 1021:
                    case 1211: case 1212: case 1022: case 1221: case 1222: case 1223: case 1224: case 1023: case 1231:
                    case 1232: case 1233: case 1004: case 1005: case 1006: case 1500: case 1501: case 1502:
                    case 2000: case 2001: case 2105: case 2111: case 2112: case 2012: case 2002: case 2021:
                    case 2211: case 2212: case 2022: case 2221: case 2222: case 2223: case 2224: case 2023: case 2231:
                    case 2232: case 2233: case 2004: case 2005: case 2006: case 2500: case 2501: case 2502:
                        // Exit the tool
                        prev = -890;
                        break;
                    case 5:
                        cout << "                                  PROCESSING...                                  \n"
                             << "=================================================================================\n";
                        if (!this->allRequests.getProcessedRequests().empty()) this->allRequests.undoOneProcessed(this->allStudents, this->allTurmas);
                        else cout << "No requests to undo, because there were no requests processed successfully.\n";
                        prev = bottomPrinter1();
                        break;
                    default: // Do nothing
                        break;
                }
                break;
            case 4:
                switch (previous) {
                    case 0:
                        prev = processRequestMenu();
                        break;
                    case 1: case 105: case 21: // Exit the tool
                        prev = -890;
                        break;
                    case 2: case 5:
                        prev = printMainMenu();
                        break;
                    case 22:
                        prev = printMenu224();
                        break;
                    case 23: // CUs with the greatest number of students
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.printTopUCs();
                        prev = bottomPrinter();
                        break;
                    case 231: // CU Occupation by CU Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.UcOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 232: // Class Occupation by CU Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allTurmas.classOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    case 233: // Year Occupation by CU Descending
                        cout << "                                   ACCESSING...                                  \n"
                             << "=================================================================================\n";
                        allStudents.yearOccupation(input_num);
                        prev = bottomPrinter();
                        break;
                    default: // Do nothing
                        break;
                }
                break;
            case 5:
                switch (previous) {
                    case 0:
                        prev = undoRequestMenu();
                        break;
                    case 2: case 5: // Exit the tool
                        prev = -890;
                        break;
                    case 22: case 23:
                        prev = printMenu2();
                        break;
                    case 231: case 232: case 233:
                        prev = printMenu23();
                        break;
                    default: // Do nothing
                        break;
                }
                break;
            case 6:
                switch (previous) {
                    case 0:
                        prev = printMenu6();
                        break;
                    case 22: case 23: case 231: case 232: case 233: // Exit the tool
                        prev = -890;
                        break;
                    default: // Do nothing
                        break;
                }
                break;
            case 7:
                if (previous == 0) prev = -890;
                break;
            default: // Do nothing
                break;
        }
        return prev;
    }
    else {
        if (previous < 2000) {
            prev = printInvalidInput();
            return previous + prev;
        }
        else {
            cout << "         You got stuck in the error menu! Start over from the main menu!         \n";
            prev = printMainMenu();
            return prev;
        }
    }
}



int Menu::printMainMenu() {
    menuText = string("=================================================================================\n")
                       + "                   Welcome to FEUP's Schedule Management Tool!                   \n"
                       + "=================================================================================\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Submit a Class/Curricular Unit change request\n"
                       + "2. Access Year/CU/Class/Student information            5. Undo Request Menu\n"
                       + "3. Check pending requests                              6. About\n"
                       + "4. Process all requests                                7. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 0;
}

int Menu::printMenu1() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Change Request Menu:\n"
                       + "<Contains all schedule changes available>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Request curricular unit change                    3. Back to Main Menu\n"
                       + "2. Request class change                              4. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 1;
}

int Menu::printMenu11Ch() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Curricular Unit Change Menu:\n"
                       + "<Allows the filling of requests for a Curricular Unit change>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Enroll in a curricular unit                       3. Back to previous menu\n"
                       + "2. Remove a curricular unit                          4. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 105;
}

int Menu::printMenu11(int opt) {
    clearScreen();
    if (opt == 1) {
        menuText = string("=================================================================================\n")
                           + "Curricular Unit Change Menu: Enrolling in a Curricular Unit\n"
                           + "<Allows the filling of requests for a Curricular Unit change>\n"
                           + "---------------------------------------------------------------------------------\n"
                           + "Insert the student's mechanographic number (preceded by 'UP') followed by a\n"
                           + "comma (,) and the code of the Curricular Unit you wish to enroll in.\n"
                           + "Ex.: UP20XXXXXXX,L.YYYYXXX\n\n"
                           + "Note 1: 'X' are digits and 'Y' are uppercase letters;\n"
                           + "Note 2: There are 9 digits in the student code, where the first 4 correspond to\n"
                           + "        the student's enrollment year (ex.: 2020);\n"
                           + "Note 3: There are 3 digits in the CU code;\n"
                           + "Note 4: There are 2-4 uppercase letters in the CU code;\n"
                           + "Note 5: The CU called UP Project doesn't follow the L.YYYYXXX format, and has\n"
                           + "        the code UPXXX instead;\n"
                           + "---------------------------------------------------------------------------------\n"
                           + "1. Back to previous menu                                             2. Exit\n"
                           + "=================================================================================\n"
                           + "Codes/Option: ";
        cout << menuText;
        return 111;
    }
    else {
            menuText = string("=================================================================================\n")
                               + "Curricular Unit Change Menu: Removing a Curricular Unit\n"
                               + "<Allows the filling of requests for a Curricular Unit change>\n"
                               + "---------------------------------------------------------------------------------\n"
                               + "Insert the student's mechanographic number (preceded by 'UP'), followed by a\n"
                               + "comma (,) and code of the Curricular Unit, followed by another comma and the code\n"
                               + "of the respective class you wish to remove from your schedule.\n"
                               + "Ex.: UP20XXXXXXX,L.YYYYXXX,XLYYYYXX\n\n"
                               + "Note 1: 'X' are digits and 'Y' are uppercase letters;\n"
                               + "Note 2: There are 9 digits in the student code, where the first 4 correspond to\n"
                               + "        the student's enrollment year (ex.: 2020);\n"
                               + "Note 3: There are 3 digits in the CU code;\n"
                               + "Note 4: There are 2-4 uppercase letters in the CU code and class code;\n"
                               + "Note 5: The CU called UP Project doesn't follow the L.YYYYXXX format, and has\n"
                               + "        the code UPXXX instead;\n"
                               + "Note 6: the first digit in the Class code refers to the degree year that class\n"
                               + "        belongs to, and the 2 digits at the end refer to the Class number;\n"
                               + "---------------------------------------------------------------------------------\n"
                               + "1. Back to previous menu                                             2. Exit\n"
                               + "=================================================================================\n"
                               + "Codes/Option: ";
        cout << menuText;
        return 112;
    }
}

int Menu::printMenu12() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Class Change Menu:\n"
                       + "<Allows the filling of requests for a class change>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the student's mechanographic number (preceded by 'UP'), followed by a\n"
                       + "comma (,) and the CU's code followed by a another comma and the old class's code,\n"
                       + "followed by another comma and the new class's code.\n"
                       + "Ex.: UP20XXXXXXX,L.YYYYXXX,XLYYYYXX,XLYYYYXX\n\n"
                       + "Note 1: 'X' are digits and 'Y' are uppercase letters;\n"
                       + "Note 2: There are 9 digits in the student code, where the first 4 correspond to\n"
                       + "        the student's enrollment year (ex.: 2020);\n"
                       + "Note 3: there are 3 digits in the CU code;\n"
                       + "Note 4: there are 2-4 uppercase letters in the CU code and class code;\n"
                       + "Note 5: the CU called UP Project doesn't follow the L.YYYYXXX format, and has\n"
                       + "        the code UPXXX instead;\n"
                       + "Note 6: the first digit in the Class code refers to the degree year that class\n"
                       + "        belongs to, and the 2 digits at the end refer to the Class number;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Codes/Option: ";
    cout << menuText;
    return 12;
}

int Menu::printMenu2() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Information Accessing Menu:\n"
                       + "<Contains information about the different Curricular Units, Classes and Students>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Schedules                                         4. Back to Main Menu\n"
                       + "2. Students' Information                             5. Exit\n"
                       + "3. Class/CU Occupation\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 2;
}

int Menu::printMenu21() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Schedules Accessing Menu:\n"
                       + "<Contains information about the schedules of every Class and Student stored>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Classes' Schedules                                3. Back to previous menu\n"
                       + "2. Students' Schedules                               4. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 21;
}

int Menu::printMenu211() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Classes' Schedule Accessing Menu:\n"
                       + "<Contains information about the schedules of every Class stored>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the CU's code, followed by a comma (',') and class's code to display its\n"
                       + "data.\n"
                       + "Ex.: L.YYYYXXX,XLYYYYXX\n\n"
                       + "Note 1: 'X' are digits and 'Y' are uppercase letters;\n"
                       + "Note 2: there are 3 digits in the CU code;\n"
                       + "Note 3: there are 2-4 uppercase letters in the CU code and class code;\n"
                       + "Note 4: The first digit in the Class code refers to the degree's year that class\n"
                       + "        belongs to, and the 2 digits at the end refer to the Class number;\n"
                       + "Note 5: The CU called UP Project doesn't follow the L.YYYYXXX format, and has\n"
                       + "        the code UPXXX instead;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Class code/Option: ";
    cout << menuText;
    return 211;
}

int Menu::printMenu212() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Students' Schedule Accessing Menu:\n"
                       + "<Contains information about the schedules of every Student stored>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the student's mechanographic number to display their schedule:\n"
                       + "Ex.: UP20XXXXXXX\n\n"
                       + "Note 1: 'X' are digits from 0 to 9, it has a total of 9 digits;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Student number/Option: ";
    cout << menuText;
    return 212;
}

int Menu::printMenu22() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Students' Information Menu:\n"
                       + "<Contains information about the all the Students stored in this tool>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Consult the students in a specific class          4. Students in N CUs\n"
                       + "2. Consult the students in a specific course         5. Back to previous menu\n"
                       + "3. Consult the students in a specific year           6. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 22;
}

int Menu::printMenu221() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Students per Class Information Menu:\n"
                       + "<Contains information about the all the Students in a specific class>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the CU's code, followed by a comma (,) and the class's code to display all\n"
                       + "of its students.\n"
                       + "Ex.: L.YYYYXXX,XLYYYYXX\n\n"
                       + "Note 1: 'X' are digits and 'Y' are uppercase letters;\n"
                       + "Note 2: there are 3 digits in the CU code;\n"
                       + "Note 3: there are 2-4 uppercase letters in the CU code and class code;\n"
                       + "Note 4: The first digit in the Class code refers to the degree's year that class\n"
                       + "        belongs to, and the 2 digits at the end refer to the Class number;\n"
                       + "Note 5: The CU called UP Project doesn't follow the L.YYYYXXX format, and has\n"
                       + "        the code UPXXX instead;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Class code/Option: ";
    cout << menuText;
    return 221;
}

int Menu::printMenu222() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Students per Course Information Menu:\n"
                       + "<Contains information about the all the Students in a specific course>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the course's code to display all of its students.\n"
                       + "Ex.: L.XXXX\n\n"
                       + "Note: there are 2-4 uppercase letters ('X') in the course code;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Course code/Option: ";
    cout << menuText;
    return 222;
}

int Menu::printMenu223() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Students per Year Information Menu:\n"
                       + "<Contains information about the all the Students in a specific year>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the word 'Year' followed by a colon (':') and the degree year to display\n"
                       + "all the students that are attending that year.\n"
                       + "Ex.: Year:X, where X is a number between 1 and 3;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Year/Option: ";
    cout << menuText;
    return 223;
}

int Menu::printMenu224() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Students in n Curricular Units Information Menu:\n"
                       + "<Contains information about the number of Students in n CUs>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the acronym 'CUs' followed by a colon (':') and the amount of CUs.\n"
                       + "Ex.: CUs:n\n\n"
                       + "Note 1: a student can be registered in a maximum of 7 Curricular Units;\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to previous menu                                             2. Exit\n"
                       + "=================================================================================\n"
                       + "Value of n/Option: ";
    cout << menuText;
    return 224;
}

int Menu::printMenu23() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Occupation Information Menu:\n"
                       + "<Contains information about the occupation of different CUs, Classes and Years>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to the option you wish to select:\n"
                       + "1. Curricular Unit Occupation             4. UCs with greatest number of students\n"
                       + "2. Class Occupation                       5. Back to previous menu\n"
                       + "3. Year Occupation                        6. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 23;
}

int Menu::printMenu231() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Curricular Unit Occupation Information Menu:\n"
                       + "<Contains information about the number of students in the different CUs>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to how you want to see the occupation sorted as:\n"
                       + "1. Occupation Ascending                              4. CU Descending\n"
                       + "2. Occupation Descending                             5. Back to previous menu\n"
                       + "3. CU Ascending                                      6. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 231;
}

int Menu::printMenu232() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Class Occupation Information Menu:\n"
                       + "<Contains information about the number of Students in the different Classes>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to how you want to see the occupation sorted as:\n"
                       + "1. Occupation Ascending                              4. CU Ascending\n"
                       + "2. Occupation Descending                             5. Back to previous menu\n"
                       + "3. CU Ascending                                      6. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 232;
}

int Menu::printMenu233() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Year Occupation Information Menu:\n"
                       + "<Contains information about the number of Students in different degree years>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "Insert the number corresponding to how you want to see the occupation sorted as:\n"
                       + "1. Occupation Ascending                              4. Year Descending\n"
                       + "2. Occupation Descending                             5. Back to previous menu\n"
                       + "3. Year Ascending                                    6. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 233;
}

int Menu::processRequestMenu() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Request Processing Menu:\n"
                       + "<Asks confirmation before the processing of the whole list of pending requests>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "After you confirm the processing of the requests, there's a possibility that you\n"
                       + "won't be able to use the Undo option in the Main Menu, to revert them.\n"
                       + "Do you wish to go through with the processing of the requests?\n"
                       + "1. Yes\n"
                       + "2. No (Back to Main Menu)                            3. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 4;
}

int Menu::undoRequestMenu() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Request Undoing Process Menu:\n"
                       + "<Provides information about the undo options available for requests>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "After you confirm the undo of the requests, they will be deleted from record and\n"
                       + "will have to be submitted again if needed.\n"
                       + "1. Undo the most recent pending request                4. Back to Main Menu\n"
                       + "2. Undo all pending requests                           5. Exit\n"
                       + "3. Undo the most recent processed request\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 5;
}

int Menu::printMenu6() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "Authors' About Page:\n"
                       + "<Provides information about the authors of this small tool>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "C++ tool developed as a group project for one of FEUP's Curricular Units during\n"
                       + "the 1st semester of the 2nd year called <Algorithms and Data Structures> as part\n"
                       + "of the Bachelor in Informatics and Computing Engineering. You can find us at:\n"
                       + "Diogo Ferreira <up202205295> - E-mail: up202205295@edu.fe.up.pt\n"
                       + "Gabriel Carvalho <up202208939> - E-mail: up202208939@edu.fe.up.pt\n"
                       + "Guilherme Silva <up202205298> - E-mail: up202205298@edu.fe.up.pt\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Back to Main Menu                                                 2. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 6;
}

int Menu::printInvalidInput() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "ERROR: INVALID INPUT\n"
                       + "<The input you have provided to the tool is invalid, press 1. to return to the\n"
                       + "previous menu and rewrite your input following the provided rules there>\n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Write a new input             2. Back to Main Menu                 3. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 1000;
}

int Menu::bottomPrinter() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "                   Information has been successfully accessed!                   \n"
                       + "---------------------------------------------------------------------------------\n"
                       + "1. Access more information       2. Back to Main Menu                 3. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 500;
}

int Menu::bottomPrinter1() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "           1. Back to Main Menu                         2. Exit                  \n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 501;
}

int Menu::bottomPrinter2() {
    clearScreen();
    menuText = string("---------------------------------------------------------------------------------\n")
                       + "1. Process the pending request (Back to Main Menu)                2. Exit\n"
                       + "=================================================================================\n"
                       + "Option: ";
    cout << menuText;
    return 502;
}

void Menu::printEndMenu() {
    clearScreen();
    menuText = string("=================================================================================\n")
                       + "                      EXITING THE TOOL AND SAVING CHANGES...                     \n"
                       + "=================================================================================\n";
    cout << menuText;
}


/*
=============================================PORTUGUESE MENU IN DEVELOPMENT=============================================
===============================POSSIBLE CONCERNS: FURTHER ENLARGEMENT OF THE SWITCH CASES===============================
*/

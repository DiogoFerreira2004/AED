#ifndef AED_MENU_HPP
#define AED_MENU_HPP

#include "Storage.hpp"
using std::string;

/// @brief Class for all the menus.
/// @details Stores all the menus that can be accessed throughout the tool's runtime, and the data structures that hold the information provided in the files.
/// @see Storage.hpp
class Menu {
private:
    /// @brief The menus' text;
    string menuText;
    /// @brief Where all the classes are stored;
    AllTurmas allTurmas;
    /// @brief Where all the students are stored;
    AllStudents allStudents;
    /// @brief Where all the requests are stored;
    AllRequests allRequests;

public:
    /*!
     * @brief Constructor of menus' interface.
     * @details Initializes the interface to run the menus. Processes all the files into the respective data structures. Initializes the menuText member variable with a placeholder text.
     * @see AllTurmas::AllTurmas()
     * @see AllTurmas::setSchedule()
     * @see AllStudents::AllStudents()
     * @note Time complexity: O(k) + O(l*log p) + O(m*n*log p). <br>
     *       - where k,l,m are number of lines in the files classes_per_uc.csv, classes.csv, students_classes.csv, respectively; <br>
     *       - n is the number of Curricular Units the student is enrolled in, and p is the number of Turma objects in this->turmas; <br>
     *       Notice: n is never higher than 7, because a student cannot be unrolled in more than 7 CUs at the same time.
     */
    Menu();

    /*!
     * @brief Runs the tool.
     * @details Starts the main menu and keeps the menus running until the 'Exit' option is selected.
     * @see validDetect()
     * @note Time complexity: O(n*(p + «complexity of chooser()» + q*r)). <br>
     *       - where n is the number of inputs inserted by the user, O(p) is the time complexity of the validDetect() function, and O(q*r) is the time complexity of the Storage::saveProcessedRequests() function.
     */
    void run();

    /*!
     * @brief Clears the screen of the terminal.
     * @details Operating System-specific function, that clears the screen of non-Windows terminals using ANSI escape sequences. <br>
     *          Doesn't clear the screen when using an IDE console! <br>
     *          Consciously avoided using system("cls") or system("clear") or any variation of system() to not expose the program to vulnerabilities.
     * @note Time complexity: O(1)
     */
    void clearScreen() const;

    /*!
     * @brief Detects if inputs are valid.
     * @details Input string is made up of an int: converted to int; evaluated if valid menu option or not. <br>
     *          Input string is made up of characters: function splits the string into arguments if needed; determines if inputted arguments are following the expected syntax with regular expressions.
     * @param previous Previous menu's integer signature (every menu has a different one).
     * @param input_choice User input: can be made up of only an int value (menu option); or string of characters (specific input).
     * @returns 0 if invalid input; 1 if valid string; 2 if valid int.
     * @note Time complexity: O(n) for both types of input: when it is turned into a digit and when it is treated as a string.
     */
    int validDetect(int previous, const string& input_choice);

    /*!
     * @brief Function that calls every other function according.
     * @details Chooses the next menu (printMenu() functions) and the functions needed to access/process the data, based on the previous menu's signature and the input provided. <br>
     *          Uses a switch-case for every possible menu option (integer inputs), as well as string inputs. Inside each case, another switch-case takes the previous menu's integer signature into consideration, to decide which menu to print next and which functions to call. <br>
     * @param valid Validity of the input, decided by validDetect() function.
     * @param previous Previous menu's integer signature (every menu has a different one).
     * @param input_num User's valid int input, defaults to -1 when the user inputs a valid string.
     * @param input_codes User's valid string input, split into arguments if needed that will be passed.
     * @returns The printed menu's integer signature. It will be evaluated in the next loop, together with the input provided, to decide which menu to print next.
     * @see validDetect()
     * @note Time complexity: Depends on the input, given the multitude of options and functions that can be called. Refer to the time complexity of the other functions in this tool.
     */
    int chooser(bool valid, int previous, int input_num = -1, const string& input_codes = "");

    /*!
     * @brief Main Menu.
     * @details This menu, as well as the following member functions, print the menus that are shown on screen when running the tool.
     * @return This menu's integer signature (0).
     * @note Time complexity: O(1).
     */
    int printMainMenu();

    /*!
     * @brief Change Request Menu
     * @details The naming of the menu-printing functions in this class follows, generally, the same pattern. <br>
     *          The number in each of the names refers not only to their return value, but also the combination of keys that needs to be pressed to access them from the Main Menu.<br>
     *          This information will be omitted from the following menu's documentation.
     * @return This menu's integer signature (1).
     * @note Time complexity: O(1).
     */
    int printMenu1();

    /*!
     * @brief Curricular Unit Change Menu.
     * @details Intermediate menu for Curricular Unit change, because there are 2 types of curricular unit change.
     * @return This menu's integer signature (105).
     * @note Time complexity: O(1).
     */
    int printMenu11Ch();

    /*!
     * @brief Curricular Unit Change Menu: Enroll & Remove operations.
     * @param opt Reflects the previous input, used to distinguish between the CU enrolling requests and the CU removing requests.
     * @return This menu's integer signature (111 or 112, depending on opt).
     * @note Time complexity: O(1).
     */
    int printMenu11(int opt);

    /*!
     * @brief Class Change Menu.
     * @return This menu's integer signature (12).
     * @note Time complexity: O(1).
     */
    int printMenu12();

    /*!
     * @brief Information Accessing Menu.
     * @return This menu's integer signature (2).
     * @note Time complexity: O(1).
     */
    int printMenu2();

    /*!
     * @brief Schedule Accessing Menu.
     * @return This menu's integer signature (21).
     * @note Time complexity: O(1).
     */
    int printMenu21();

    /*!
     * @brief Classes' Schedule Accessing Menu.
     * @return This menu's integer signature (211).
     * @note Time complexity: O(1).
     */
    int printMenu211();

    /*!
     * @brief Students' Schedule Accessing Menu.
     * @return This menu's integer signature (212).
     * @note Time complexity: O(1).
     */
    int printMenu212();

    /*!
     * @brief Students Information Menu.
     * @return This menu's integer signature (22).
     * @note Time complexity: O(1).
     */
    int printMenu22();

    /*!
     * @brief Students per Class Information Menu.
     * @return This menu's integer signature (221).
     * @note Time complexity: O(1).
     */
    int printMenu221();

    /*!
     * @brief Students per Course Information Menu.
     * @return This menu's integer signature (222).
     * @note Time complexity: O(1).
     */
    int printMenu222();

    /*!
     * @brief Students per Year Information Menu.
     * @return This menu's integer signature (223).
     * @note Time complexity: O(1).
     */
    int printMenu223();

    /*!
     * @brief Students in n Curricular Units Information Menu.
     * @return This menu's integer signature (224).
     * @note Time complexity: O(1).
     */
    int printMenu224();

    /*!
     * @brief Occupation Information Menu.
     * @return This menu's integer signature (23).
     * @note Time complexity: O(1).
     */
    int printMenu23();

    /*!
     * @brief Curricular Unit Occupation Information Menu.
     * @return This menu's integer signature (231).
     * @note Time complexity: O(1).
     */
    int printMenu231();

    /*!
     * @brief Class Occupation Information Menu.
     * @return This menu's integer signature (232).
     * @note Time complexity: O(1).
     */
    int printMenu232();

    /*!
     * @brief Year Occupation Information Menu.
     * @return This menu's integer signature (233).
     * @note Time complexity: O(1).
     */
    int printMenu233();

    /*!
     * @brief Request Processing Menu.
     * @return This menu's integer signature (4).
     * @note Time complexity: O(1).
     */
    int processRequestMenu();

    /*!
     * @brief Request Undoing Process Menu.
     * @return This menu's integer signature (5).
     * @note Time complexity: O(1).
     */
    int undoRequestMenu();

    /*!
     * @brief Authors' About Page.
     * @return This menu's integer signature (6).
     * @note Time complexity: O(1).
     */
    int printMenu6();

    /*!
     * @brief ERROR: INVALID INPUT Menu.
     * @details This function returns an integer signature that is significantly higher than the other ones. It was a choice made to facilitate the identification of the Error Menu and the ones related to it. <br>
     *          When the inputted number is not one of the displayed options, the Error Menu is printed. This menu's option to "Write a new input" raises the need to, in the next iteration of loop,
     *          save not only the previous/latest menu (this error menu), but also the menu before that, where the invalid input came from. Check the chooser() function to further understand the implementation.
     * @return This menu's integer signature (1000).
     * @see chooser()
     * @note Time complexity: O(1).
     */
    int printInvalidInput();

    /*!
     * @brief Bottom Appendage Menu nr. 0.
     * @details A small menu containing the necessary options to keep navigating between the menus. <br>
     *          It is called after the successful execution of accessing methods that print on their own.
     * @return This menu's integer signature (500).
     * @note Time complexity: O(1).
     */
    int bottomPrinter();

    /*!
     * @brief Bottom Appendage Menu nr. 1.
     * @details A small menu containing the necessary options to keep navigating between the menus.<br>
     *          It is called after the execution of certain manipulation methods that print on their own.
     * @return This menu's integer signature (501).
     * @note Time complexity: O(1).
     */
    int bottomPrinter1();

    /*!
     * @brief Bottom Appendage Menu nr. 2.
     * @details A small menu containing the necessary options to keep navigating between the menus.<br>
     *          It is called after the execution of the insertRequest method that has prints of its own.
     * @return This menu's integer signature (502).
     * @note Time complexity: O(1).
     */
    int bottomPrinter2();

    /*!
     * @brief End Menu.
     * @details A small message that is printed immediately before the exiting of the program. <br>
     *          It doesn't have a return value (integer signature) because there is no need to keep track of what the previous menu was, since the program is terminating.
     * @note Time complexity: O(1).
     */
    void printEndMenu();
};

#endif //AED_MENU_HPP

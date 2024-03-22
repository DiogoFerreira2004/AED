#ifndef AED2_MENU_HPP
#define AED2_MENU_HPP

#include "AllAirlines.hpp"
#include "AllAirports.hpp"
#include "Graph.hpp"

using namespace std;


class Menu;

/// @brief Context class (part of the State design pattern).
/// @details Stores the data structures that hold the information provided in the files.
/// @see AllAirlines.hpp
/// @see AllAirports.hpp
/// @see Graph.hpp
class Current {
private:
    /// @brief Pointer to the current menu (implementation of interface Menu) being shown on screen.
    /// @see Menu
    Menu* currentMenu;
    /// @brief Where all the airlines are stored;
    AllAirlines allAirlines;
    /// @brief Where all the airports are stored;
    AllAirports allAirports;
    /// @brief The graph data structure. It's where all the airports are stored (as Vertexes), as well as all the flights are stored (as Edges);
    Graph network;

    /*!
     * @brief Input type checker
     * @param input Can be made up of only an int value (menu option); <br>
     *              or string of characters (specific input).
     * @returns false if the input string is empty (to be evaluated as an invalid string by Menu::handleInput()); <br>
     *          false if the input string is made up of characters; <br>
     *          true if the input string is made up of an int;
     * @note Time complexity: O(n), where n is the size of the input
     */
    static bool isInt(const string& input);
public:
    /*!
     * @brief Constructor of menus' interface.
     * @details Initializes the interface to run the menus (starting from the main menu). Processes all the files into the respective data structures.
     * @see Menu
     * @see AllAirlines::AllAirlines()
     * @see AllAirports::AllAirports()
     * @see Graph::Graph()
     * @note Time complexity: O(m+n+p*q). <br>
     *       - where m,n,p are the number of lines in the files airlines.csv, airport.csv and flights.csv, respectively;
     *       - q is the total number of vertices currently in the Graph
     */
    Current();

    /*!
     * @brief Runs the tool.
     * @details Starts the main menu and keeps the menus running until the 'Exit' option is selected.
     * @see Menu::print()
     * @see Menu::handleInput()
     * @note Time complexity: O(n*(p + «complexity of handleInput() function»))
     *       - where n is the number of inputs inserted by the user and O(p) is the complexity of the isInt() function
     */
    void run();

    /*!
     * @brief Destructor of menus' interface.
     * @details Deletes the allocated memory by the currentMenu member variable at the end of the Current object's lifetime.
     * @note Time complexity: O(1)
     */
    ~Current();


    /*!
     * @brief Getter for the AllAirlines member variable.
     * @returns Const reference to the AllAirlines object.
     */
    const AllAirlines& getAllAirlines() const;

    /*!
     * @brief Getter for the AllAirports member variable.
     * @returns Const reference to the AllAirports object.
     */
    const AllAirports& getAllAirports() const;

    /*!
     * @brief Getter for the Graph member variable.
     * @returns Const reference to the Graph object.
     */
    const Graph& getNetwork() const;
};



/// @brief Interface class (abstract class) for all the menus (part of the State design pattern).
/// @details Provides an interface for all the menus to implement. Those menus can be accessed throughout the tool's runtime.
class Menu {
public:
    /*!
     * @brief Printer Interface
     * @details Pure virtual function to print the menus that are shown on screen while running the tool. <br>
     *          It needs to be implemented by the derived classes, according to what needs to be printed.
     * @note This function is marked as virtual to enable dynamic polymorphism. <br>
     *       Additionally, its signature ending with '= 0' forces the derived classes to implement it and makes this class an abstract class
     */
    virtual void print() = 0;

    /*!
     * @brief Input Handler Interface
     * @details Pure virtual function to manage the inputs. <br>
     *          Its implementations by the derived classes will check for the validity of the input. If valid, they will call all the necessary functions and then choose the next menu, according to the input provided.
     * @param menu Pointer to the Current class, to get access to the application state, mainly information in the member variables.
     * @param option User's int input, defaults to -1 when the user inputs a valid string.
     * @param input User's string input, that will be split into arguments if needed by the derived classes. Its default value ("") is used when the input isn't a string.
     */
    virtual Menu* handleInput(Current* menu, int option, string input = "") = 0;

    /*!
     * @brief Virtual destructor for the Menu class.
     * @details When an object of a derived class is deleted through a pointer to the Menu class, this virtual destructor ensures that the proper derived class destructor is called.
     * @note The destructor is marked as virtual to enable dynamic polymorphism.
     */
    virtual ~Menu() = default;
};


/// @brief Main Menu (Concrete Class)
/// @details This menu, as well as the other derived classes, print the menus that are shown on screen, handle the inputs, checking their validity, call the necessary functions and select the next menu.
/// @note This documentation will be omitted from further derived classes, as their only differences are related to user display and interaction.
/// @see AllAirlines.cpp
/// @see AllAirports.cpp
/// @see Graph.cpp
class MainMenu : public Menu {
public:

    /*!
     * @brief MainMenu's implementation of the print() function
     */
    void print() override;

    /*!
     * @brief MainMenu's implementation of the handleInput() function
     * @note Time complexity of the functions called inside handleInput() will vary depending on the derived class, and will be omitted for brevity. They can be found in their respective implementations.
     */
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu3 (Concrete Class)
class Menu3 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu4 (Concrete Class)
class Menu4 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu5 (Concrete Class)
class Menu5 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu6 (Concrete Class)
class Menu6 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu7 (Concrete Class)
class Menu7 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu8 (Concrete Class)
class Menu8 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu8 Option Chooser (Concrete Class)
class Menu8Choose : public Menu {
protected:
    /// @brief Airport's code received from input during Menu8's execution
    /// @details Stored for further use during this class's and the derived class's (Menu84) execution
    string airportCode;
public:
    /*!
     * @brief Parametrized constructor of the Menu8Choose class.
     * @details Initializes the member variable with its respective parameter.
     * @param airport_code Const reference to a string corresponding to the member variable of a Menu8Choose object
     * @note Time complexity: O(1).
     */
    Menu8Choose(const string& airport_code);

    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu84 (Concrete Class)
class Menu84 : public Menu8Choose {
private:
    /// @brief Option (one of the "reachable" ones) received from input during Menu8's execution
    /// @details Stored for further use during this class's execution
    int reachable;
public:
    /*!
     * @brief Parametrized constructor of the Menu84 class.
     * @details Initializes the member variable with its respective parameter.
     * @param airport_code Initialized using the Menu8Choose's constructor
     * @param reachable Int value corresponding to the member variable of a Menu84 object
     * @note Time complexity: O(1).
     */
    Menu84(const string& airport_code, int reachable);

    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu10 (Concrete Class)
class Menu10 : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu12 Input Receiver (Concrete Class)
class Menu12SrcDest : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu12 (Concrete Class)
class Menu12 : public Menu {
protected:
    /// @brief Flight's source received from input during Menu12SrcDest's execution
    /// @details Stored for further use during this class's and the derived class's (Menu12Filters) execution
    string source;
    /// @brief Flight's destination received from input during Menu12SrcDest's execution
    /// @details Stored for further use during this class's and the derived class's (Menu12Filters) execution
    string destination;
public:
    /*!
     * @brief Parametrized constructor of the Menu12 class.
     * @details Initializes the member variables with their respective parameters.
     * @param source,destination Const references to strings corresponding to the member variables of a Menu12 object
     * @note Time complexity: O(1).
     */
    Menu12(const string& source, const string& destination);

    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Menu12Filters (Concrete Class)
class Menu12Filters : public Menu12 {
private:
    /// @brief Filter option received from input during Menu12's execution
    /// @details Stored for further use during this class's execution
    int filter;
public:
    /*!
     * @brief Parametrized constructor of the Menu12Filters class.
     * @details Initializes the member variable with its respective parameter.
     * @param source, destination Initialized using the Menu12's constructor.
     * @param filter Int value corresponding to the member variable of a Menu12Filters object
     * @note Time complexity: O(1).
     */
    Menu12Filters(const string& source, const string& destination, int filter);

    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

/// @brief Footer Menu (Concrete Class)
class FooterMenu : public Menu {
public:
    void print() override;
    Menu* handleInput(Current* menu, int option, string input) override;
};

#endif //AED2_MENU_HPP
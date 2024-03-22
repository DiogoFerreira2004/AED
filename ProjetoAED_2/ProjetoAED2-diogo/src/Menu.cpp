#include <string>
#include <iostream>
#include <sstream>
#include "Menu.hpp"

Current::Current() {
    currentMenu = new MainMenu();
    allAirlines = AllAirlines("../dataset/airlines.csv"); // O(m)
    allAirports = AllAirports("../dataset/airports.csv"); // O(n)
    network = Graph("../dataset/flights.csv"); // O(p*complexity of findVertex()) == O(p*q)
}

bool Current::isInt(const string& input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void Current::run() {
    while (currentMenu != nullptr) {
        Menu* nextMenu;
        string input;

        currentMenu->print();

        getline(cin, input); // to read whitespaces
        cout << "\n\n";

        if (isInt(input)) nextMenu = currentMenu->handleInput(this, stoi(input));
        else nextMenu = currentMenu->handleInput(this, -1, input);

        if (nextMenu != currentMenu) delete currentMenu;
        currentMenu = nextMenu;
    }
}


Current::~Current() {
    delete currentMenu;
}

const AllAirlines& Current::getAllAirlines() const {
    return allAirlines;
}

const AllAirports& Current::getAllAirports() const {
    return allAirports;
}

const Graph& Current::getNetwork() const {
    return network;
}


void MainMenu::print() {
    string menuText = string("=================================================================================\n")
                              + "               Welcome to the Air Travel Flight Management System!               \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "Insert the number corresponding to the option you wish to select:\n"
                              + "1. Total number of airports\n"
                              + "2. Total number of available flights\n"
                              + "3. Number of flights out of a specific airport\n"
                              + "4. Number of flights per city\n"
                              + "5. Number of flights per airline\n"
                              + "6. Number of different countries you can fly directly to from a specific airport\n"
                              + "7. Number of different countries you can fly directly to from a specific city\n"
                              + "8. Number of direct and non-direct destinations from a specific airport\n"
                              + "9. Flights with the greatest number of stops in between\n"
                              + "10. Top X airports with the greatest air traffic capacity\n"
                              + "11. List of essential airports\n"
                              + "12. Best flight options\n"
                              + "13. Exit\n"
                              + "=================================================================================\n"
                              + "Option: ";
    cout << menuText;
}
Menu* MainMenu::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;

    int maxDist = 0;
    int num = 0;

    switch (option) {
        case 1:
            cout << "Total number of airports: " << menu->getAllAirports().numAirports() << "\n";
            nextMenu = new FooterMenu();
            break;
        case 2:
            cout << "Total number of available flights: " << menu->getNetwork().numTotalFlights() << "\n";
            nextMenu = new FooterMenu();
            break;
        case 3:
            nextMenu = new Menu3();
            break;
        case 4:
            nextMenu = new Menu4();
            break;
        case 5:
            nextMenu = new Menu5();
            break;
        case 6:
            nextMenu = new Menu6();
            break;
        case 7:
            nextMenu = new Menu7();
            break;
        case 8:
            nextMenu = new Menu8();
            break;
        case 9:
            for (const pair<string, string>& elem : menu->getNetwork().diameter(maxDist)) {
                cout << "From " << menu->getAllAirports().nameOfCode(elem.first) << " (" << elem.first << ") "
                     << "to " << menu->getAllAirports().nameOfCode(elem.second) << " (" << elem.second << ")"
                     << "\n";
            }
            cout << "Number of stops (maximum of this dataset): " << maxDist-1 << "\n"; //-1 porque o destino não conta como layover
            nextMenu = new FooterMenu();
            break;
        case 10:
            nextMenu = new Menu10();
            break;
        case 11:
            cout << "=================================================================================\n"
                 << "The airports essential to the network's circulation capability are: \n"
                 << "(Essential means that their removal would make areas of the network unreachable)\n"
                 << "---------------------------------------------------------------------------------\n";
            for (const string& airport : menu->getNetwork().articulationPoints()) {
                cout << menu->getAllAirports().nameOfCode(airport) << " (" << airport << ")" << "\n";
                num++;
            }
            cout << "There's a total of "<< num << " essential airports." << "\n";
            nextMenu = new FooterMenu();
            break;
        case 12:
            nextMenu = new Menu12SrcDest();
            break;
        case 13:
            nextMenu = nullptr;
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}




void Menu3::print() {
    string menuText = string("=================================================================================\n")
                              + "       Insert the 3 uppercase-letter code that corresponds to the airport.       \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Code/Option: ";
    cout << menuText;
}

Menu* Menu3::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case -1:
            if (menu->getNetwork().findVertex(input) != NULL) {
                cout << "Number of flights from airport " << menu->getAllAirports().nameOfCode(input) << " (" << input << "): "
                     << menu->getNetwork().findVertex(input)->getAdj().size() << "\n"
                     << "It has flights from " << menu->getNetwork().findVertex(input)->numDiffAirlines() << " different airlines."
                     << "\n";
                nextMenu = new FooterMenu();
            }
            else {
                cout << "Airport code not found! Check your input.\n";
                nextMenu = this;
            }
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


void Menu4::print() {
    string menuText = string("=================================================================================\n")
                              + "                          Insert the name of the city.                           \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Name/Option: ";
    cout << menuText;
}

Menu* Menu4::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case -1:
            if (!menu->getAllAirports().airportsPerCity(input).empty()) {
                cout << "Number of flights from city " << input << ": "
                     << menu->getNetwork().numFlightsPerCity(menu->getAllAirports().airportsPerCity(input)) << "\n";
                nextMenu = new FooterMenu();
            }
            else {
                cout << "City name not found! Check your input.\n";
                nextMenu = this;
            }
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


void Menu5::print() {
    string menuText = string("=================================================================================\n")
                              + "       Insert the 3 uppercase-letter code that corresponds to the airline.       \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Code/Option: ";
    cout << menuText;
}

Menu* Menu5::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case -1:
            if (!menu->getAllAirlines().nameOfCode(input).empty()) {
                cout << "Number of flights from airline " << menu->getAllAirlines().nameOfCode(input) << " (" << input
                     << "): "
                     << menu->getNetwork().numFlightsPerAirline(input) << "\n";
                nextMenu = new FooterMenu();
            }
            else {
                cout << "Airline code not found! Check your input.\n";
                nextMenu = this;
            }

            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


void Menu6::print() {
    string menuText = string("=================================================================================\n")
                              + "       Insert the 3 uppercase-letter code that corresponds to the airport.       \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Code/Option: ";
    cout << menuText;
}

Menu* Menu6::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case -1:
            if (!menu->getAllAirports().nameOfCode(input).empty()) {
                cout << "Number of countries that you can travel to, from airport " << menu->getAllAirports().nameOfCode(input) << " (" << input << "):\n"
                     << menu->getNetwork().numCountriesPerAirportDirect(input, menu->getAllAirports()) << "\n";
                nextMenu = new FooterMenu();
            }
            else {
                cout << "Airport code not found! Check your input.\n";
                nextMenu = this;
            }
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


void Menu7::print() {
    string menuText = string("=================================================================================\n")
                              + "                          Insert the name of the city.                           \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Name/Option: ";
    cout << menuText;
}

Menu* Menu7::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case -1:
            if (!menu->getAllAirports().airportsPerCity(input).empty()) {
                cout << "Number of countries that you travel can to, from " << input << ": "
                     << menu->getNetwork().numCountriesPerCityDirect(menu->getAllAirports().airportsPerCity(input),menu->getAllAirports()) << "\n";
                nextMenu = new FooterMenu();
            }
            else {
                cout << "City name not found! Check your input.\n";
                nextMenu = this;
            }
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


void Menu8::print() {
    string menuText = string("=================================================================================\n")
                              + "       Insert the 3 uppercase-letter code that corresponds to the airport.       \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Code/Option: ";
    cout << menuText;
}

Menu* Menu8::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case -1:
            if (!menu->getAllAirports().nameOfCode(input).empty()) {
                nextMenu = new Menu8Choose(input);
            }
            else {
                cout << "Airport code not found! Check your input.\n";
                nextMenu = this;
            }
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


Menu8Choose::Menu8Choose(const string& airport_code) {
    this->airportCode = airport_code;
}

void Menu8Choose::print() {
    string menuText = string("=================================================================================\n")
                              + "Number of Non-Direct Destinations From Airport " + this->airportCode + "\n"
                              + "---------------------------------------------------------------------------------\n"
                              + "Insert the number corresponding to the option you wish to select:\n"
                              + "1. Number of airports available to travel to\n"
                              + "2. Number of cities available to travel to\n"
                              + "3. Number of countries available to travel to\n"
                              + "4. Number of reachable airports with a maximum of X stops/lay-overs\n"
                              + "5. Number of reachable cities with a maximum of X stops/lay-overs\n"
                              + "6. Number of reachable countries with a maximum of X stops/lay-overs\n"
                              + "7. Back to Main Menu\n"
                              + "=================================================================================\n"
                              + "Option: ";
    cout << menuText;
}

Menu* Menu8Choose::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    switch (option) {
        case 1:
            cout << "Number of airports that you can travel to, from airport " << menu->getAllAirports().nameOfCode(airportCode) << " (" << airportCode << "):\n"
                 << menu->getNetwork().numAirportsPerAirport(airportCode) << "\n";
            nextMenu = new FooterMenu();
            break;
        case 2:
            cout << "Number of cities that you can travel to, from airport " << menu->getAllAirports().nameOfCode(airportCode) << " (" << airportCode << "):\n"
                 << menu->getNetwork().numCitiesPerAirport(airportCode, menu->getAllAirports()) << "\n";
            nextMenu = new FooterMenu();
            break;
        case 3:
            cout << "Number of countries that you can travel to, from airport " << menu->getAllAirports().nameOfCode(airportCode) << " (" << airportCode << "):\n"
                 << menu->getNetwork().numCountriesPerAirport(airportCode, menu->getAllAirports()) << "\n";
            nextMenu = new FooterMenu();
            break;
        case 4: case 5: case 6:
            nextMenu = new Menu84(airportCode, option);
            break;
        case 7:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


Menu84::Menu84(const string& airport_code, int reachable) : Menu8Choose(airport_code) {
    this->reachable = reachable;
}

void Menu84::print() {
    string menuText = string("=================================================================================\n")
                              + "           Insert the maximum number of lay-overs your flight can have.          \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               a.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Number/Option: ";
    cout << menuText;
}

Menu* Menu84::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    if (option == -1 and input == "a") nextMenu = new MainMenu();
    else if (option <= -1) {
        cout << "\nINVALID OPTION! TRY AGAIN!\n";
        nextMenu = this;
    }
    else {
        if (reachable == 4) { // airports
            cout << "Number of reachable airports from airport " << menu->getAllAirports().nameOfCode(airportCode) << " (" << airportCode
                 << ") in a maximum of " << option << " stops: \n"
                 << menu->getNetwork().numAirportsX(airportCode, option) << "\n";
        }
        else if (reachable == 5) { // cities
            cout << "Number of reachable cities from airport " << menu->getAllAirports().nameOfCode(airportCode) << " (" << airportCode
                 << ") in a maximum of " << option << " stops: \n"
                 << menu->getNetwork().numCitiesX(airportCode, option, menu->getAllAirports()) << "\n";
        }
        else { //reachable == 6, countries
            cout << "Number of reachable countries from airport " << menu->getAllAirports().nameOfCode(airportCode) << " (" << airportCode
                 << ") in a maximum of " << option << " stops: \n"
                 << menu->getNetwork().numCountriesX(airportCode, option, menu->getAllAirports()) << "\n";
        }
        nextMenu = new FooterMenu();
    }
    return nextMenu;
}


void Menu10::print() {
    string menuText = string("=================================================================================\n")
                              + "  Insert the value of X (number of airports to be ranked by number of flights).  \n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               a.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Number/Option: ";
    cout << menuText;
}

Menu* Menu10::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    if (option == -1 and input == "a") nextMenu = new MainMenu();
    else if (option <= -1 or option == 0) {
        cout << "\nINVALID OPTION! TRY AGAIN!\n";
        nextMenu = this;
    }
    else {
        menu->getNetwork().topXAirports(option);
        nextMenu = new FooterMenu();
    }
    return nextMenu;
}

void Menu12SrcDest::print() {
    string menuText = string("=================================================================================\n")
                              + "Best Flight Option(s) Input Menu\n"
                              + "---------------------------------------------------------------------------------\n"
                              + "Insert the source followed by a comma (','), and the destination of your flight.\n"
                              + "Note that both the source an destination can be:\n"
                              + "- An airport code (write the prefix 'AC.' before the code of the airport);\n"
                              + "- An airport name (write the prefix 'AN.' before the name of the airport);\n"
                              + "- A city name, where all airports departing from that city will be considered\n"
                              + "  (write the prefix 'CN.' before the name of the city);\n"
                              + "- Geographical coordinates, where the closest airport(s) will be considered;\n"
                              + "  Separate latitude and longitude with an underscore ('_'), as in the example;\n"
                              + "You can also mix and match the formats, as in the examples.\n"
                              + "Examples of the input format:\n"
                              + "- AC.CDG,AC.JFK\n"
                              + "- AN.Charles De Gaulle,AN.John F Kennedy Intl\n"
                              + "- CN.Paris,AC.JFK\n"
                              + "- 49.012779_2.550000,40.639751_-73.778925\n"
                              + "- 49.012779_2.550000,AN.John F Kennedy Intl\n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Source,Destination/Option: ";
    cout << menuText;
}

Menu* Menu12SrcDest::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;

    stringstream inputLine(input);
    string arg1, arg2;

    if (!input.empty()) {
        getline(inputLine, arg1, ',');
        getline(inputLine, arg2);

        if (inputLine.fail()) option = -2;
    }

    switch (option) {
        case -2:
            cout << "The input is incorrectly formatted! Check your input.\n";
            nextMenu = this;
            break;
        case -1:
            nextMenu = new Menu12(arg1, arg2);
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


Menu12::Menu12(const string& source, const string& destination) {
    this->source = source;
    this->destination = destination;
}


void Menu12::print() {
    string menuText = string("=================================================================================\n")
                              + "Best Flight Option(s) Filter Selector Menu\n"
                              + "---------------------------------------------------------------------------------\n"
                              + "Insert the number corresponding to the filter you wish to use for the search of\n"
                              + "the best flight option:\n"
                              + "1. Whitelist airlines ( use only the inputted airline(s) )\n"
                              + "2. Blacklist airlines ( don't use the inputted airline(s) )\n"
                              + "3. Minimize the amount of different airlines used\n"
                              + "4. No filters\n"
                              + "5. Back to Main Menu\n"
                              + "=================================================================================\n"
                              + "Option: ";
    cout << menuText;
}

Menu* Menu12::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;

    switch (option) {
        case 1: case 2:
            nextMenu = new Menu12Filters(source, destination, option);
            break;
        case 3:
            menu->getNetwork().findBestOption(source, destination, 3, "", menu->getAllAirports());
            nextMenu = new FooterMenu();
            break;
        case 4:
            menu->getNetwork().findBestOption(source, destination, 4, "", menu->getAllAirports());
            nextMenu = new FooterMenu();
            break;
        case 5:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}


Menu12Filters::Menu12Filters(const string& source, const string& destination, int filter) : Menu12(source, destination) {
    this->filter = filter;
}


void Menu12Filters::print() {
    string menuText = string("=================================================================================\n")
                              + "Best Flight Option(s) Filter Selector Menu\n"
                              + "---------------------------------------------------------------------------------\n"
                              + "Insert the code of the airline(s) that you want to " + ((filter == 1) ? "whitelist" : "blacklist") + " separated by commas (','):\n"
                              + "as in the examples:\n"
                              + "Examples:\n"
                              + "RYR\n"
                              + "RYR,MLA,AFR,BON\n"
                              + "---------------------------------------------------------------------------------\n"
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Codes/Option: ";
    cout << menuText;
}

Menu* Menu12Filters::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;

    stringstream inputLine(input);
    string airlineCode;

    switch (option) {
        case -1:
            while (getline(inputLine, airlineCode, ',')) {
                if (menu->getAllAirlines().nameOfCode(airlineCode).empty()) {
                    cout << "Airline code not found! Check your input.\n";
                    return this;
                }
            }
            menu->getNetwork().findBestOption(source, destination, filter, input, menu->getAllAirports());
            nextMenu = new FooterMenu();
            break;
        case 1:
            nextMenu = new MainMenu();
            break;
        default:
            cout << "\nINVALID OPTION! TRY AGAIN!\n";
            nextMenu = this;
            break;
    }
    return nextMenu;
}

void FooterMenu::print() {
    string menuText = string("---------------------------------------------------------------------------------\n")
                              + "                               1.Back to Main Menu                               \n"
                              + "=================================================================================\n"
                              + "Option: ";
    cout << menuText;
}
Menu* FooterMenu::handleInput(Current* menu, int option, string input) {
    Menu* nextMenu;
    if (option == 1) nextMenu = new MainMenu();
    else {
        cout << "\nINVALID OPTION! TRY AGAIN!\n";
        nextMenu = this;
    }
    return nextMenu;
}




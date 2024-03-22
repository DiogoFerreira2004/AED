#include <fstream>
#include <sstream>
#include "AllAirlines.hpp"

AllAirlines::AllAirlines() {
    unordered_set<Airline, airlineHash, airlineEquality> placeholder;
    this->airlines = placeholder;
}

AllAirlines::AllAirlines(const string &file) {
    Airline airline;

    ifstream csv(file);
    string line;
    bool first = true;

    while (getline(csv, line)) {
        if (!first) {
            string code_, name_, callsign_, country_;
            stringstream oneLine(line);

            getline(oneLine, code_, ',');
            getline(oneLine, name_, ',');
            getline(oneLine, callsign_, ',');
            getline(oneLine, country_);

            airline = Airline(code_, name_, callsign_, country_);

            addAirline(airline);
        }
        else {
            first = false;
        }
    }
}

void AllAirlines::addAirline(const Airline &a) {
    this->airlines.insert(a);
}

size_t AllAirlines::numAirlines() {
    return airlines.size();
}

string AllAirlines::nameOfCode(const string &airlineCode) const {
    Airline airline = Airline(airlineCode, "", "", "");
    auto it = airlines.find(airline);
    if (it != airlines.end()) return it->getName();
    else return "";
}

const unordered_set<Airline, airlineHash, airlineEquality> &AllAirlines::getAirlines() const {
    return airlines;
}

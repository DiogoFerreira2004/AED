#include <fstream>
#include <sstream>
#include "AllAirports.hpp"


AllAirports::AllAirports() {
    unordered_set<Airport, airportHash, airportEquality>  placeholder;
    this->airports = placeholder;
}

AllAirports::AllAirports(const string &file) {
    Airport airport;

    ifstream csv(file);
    string line;
    bool first = true;

    while (getline(csv, line)) {
        if (!first) {
            string code_, name_, city_, country_, latitude_, longitude_;
            stringstream oneLine(line);

            getline(oneLine, code_, ',');
            getline(oneLine, name_, ',');
            getline(oneLine, city_, ',');
            getline(oneLine, country_, ',');
            getline(oneLine, latitude_, ',');
            getline(oneLine, longitude_);

            airport = Airport(code_, name_, city_, country_, stof(latitude_), stof(longitude_));

            addAirport(airport);
        }
        else {
            first = false;
        }
    }
}

void AllAirports::addAirport(const Airport &a) {
    this->airports.insert(a);
}

// 3.i
size_t AllAirports::numAirports() const {
    return this->airports.size();
}

string AllAirports::nameOfCode(const string& airportCode) const {
    Airport airport = Airport(airportCode, "", "", "", 0, 0);
    auto it = airports.find(airport);
    if (it != airports.end()) return it->getName();
    return "";
}

string AllAirports::cityOfCode(const string &airportCode) const {
    Airport airport = Airport(airportCode, "", "", "", 0, 0);
    auto it = airports.find(airport);
    if (it != airports.end()) return it->getCity();
    return "";;
}

string AllAirports::countryOfCode(const string &airportCode) const {
    Airport airport = Airport(airportCode, "", "", "", 0, 0);
    auto it = airports.find(airport);
    if (it != airports.end()) return it->getCountry();
    return "";;
}

vector<string> AllAirports::airportsPerCity(const string& city) const {
    vector<string> res;

    for (const Airport& elem : airports) {
        if (elem.getCity() == city) res.push_back(elem.getCode());
    }

    return res;
}

const unordered_set<Airport, airportHash, airportEquality> &AllAirports::getAirports() const {
    return airports;
}


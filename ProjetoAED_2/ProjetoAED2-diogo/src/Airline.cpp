#include "Airline.hpp"


Airline::Airline() {
    this->code = "";
    this->name = "";
    this->callsign = "";
    this->country = "";
}

Airline::Airline(const string &code, const string &name, const string &callsign, const string &country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

const string &Airline::getCode() const {
    return code;
}

const string &Airline::getName() const {
    return name;
}

const string &Airline::getCallsign() const {
    return callsign;
}

const string &Airline::getCountry() const {
    return country;
}


void Airline::setCode(const string &code) {
    Airline::code = code;
}

void Airline::setName(const string &name) {
    Airline::name = name;
}

void Airline::setCallsign(const string &callsign) {
    Airline::callsign = callsign;
}

void Airline::setCountry(const string &country) {
    Airline::country = country;
}

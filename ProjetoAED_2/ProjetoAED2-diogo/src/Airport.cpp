#include "Airport.hpp"

Airport::Airport() {
    this->code = "";
    this->name = "";
    this->city = "";
    this->country = "";
    this->latitude = 0;
    this->longitude = 0;
}

Airport::Airport(const string &code, const string &name, const string &city, const string &country, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}


const string &Airport::getCode() const {
    return code;
}

const string &Airport::getName() const {
    return name;
}

const string &Airport::getCity() const {
    return city;
}

const string &Airport::getCountry() const {
    return country;
}

float Airport::getLatitude() const {
    return latitude;
}

float Airport::getLongitude() const {
    return longitude;
}


void Airport::setCode(const string &code) {
    Airport::code = code;
}

void Airport::setName(const string &name) {
    Airport::name = name;
}

void Airport::setCity(const string &city) {
    Airport::city = city;
}

void Airport::setCountry(const string &country) {
    Airport::country = country;
}

void Airport::setLatitude(float latitude) {
    Airport::latitude = latitude;
}

void Airport::setLongitude(float longitude) {
    Airport::longitude = longitude;
}

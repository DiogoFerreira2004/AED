#include "Student.hpp"


bool operator<(const Student &student1, const Student &student2) {
    return student1.code < student2.code;
}

Student::Student() {
    this->name = "";
    this->code = "";
    vector<pair<string,string>> uc_classes_;
    ucClasses.emplace_back("","");
    this->ucClasses = uc_classes_;
}
Student::Student(const Student &student) {
    this->name = student.getName();
    this->code = student.getCode();
    this->ucClasses = student.getUcClasses();
}
Student::Student(const string& name, const string& student_code, const vector<pair<string,string>>& uc_classes) {
    this->name = name;
    this->code = student_code;
    this->ucClasses = uc_classes;
}

const string& Student::getCode() const {
    return code;
}
const string &Student::getName() const {
    return name;
}
vector<pair<string,string>> Student::getUcClasses() const {
    return ucClasses;
}
vector<pair<string,string>>& Student::getUcClasses() {
    return ucClasses;
}


void Student::setName(const string &name_) {
    this->name = name_;
}
void Student::setCode(const string &student_code) {
    this->code = student_code;
}
void Student::setUcClasses(const vector<pair<string,string>>& uc_classes) {
    this->ucClasses = uc_classes;
}

void Student::addUcClass(const string& uc_code, const string& class_code) {
    this->ucClasses.emplace_back(uc_code,class_code);
}

void Student::changeClasses(const string& uc_code, const string& class_code) {
    for (pair<string,string>& uc_class : this->ucClasses) { // O(n), where n is the number of CUs a Student is enrolled in
        if (uc_class.first == uc_code) {
            uc_class.second = class_code;
            break;
        }
    }
}

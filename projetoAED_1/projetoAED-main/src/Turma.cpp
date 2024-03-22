#include <iostream>
#include <algorithm>
#include "Turma.hpp"
using namespace std;

bool operator<(const Turma& turma1, const Turma& turma2) {
    if (turma1.ucCode < turma2.ucCode or (turma1.ucCode == turma2.ucCode and turma1.turmaCode < turma2.turmaCode)) return true;
    return false;
}

// Constructors
Turma::Turma() {
    this->ucCode = "";
    this->turmaCode = "";

    vector<ScheduleSlot> horario;
    horario.emplace_back();
    this->schedule = horario;

    vector<Student> estudantes;
    estudantes.emplace_back();
    this->students = estudantes;
}

Turma::Turma(const Turma &turma) {
    this->ucCode = turma.getUcCode();
    this->turmaCode = turma.getTurmaCode();
    this->schedule = turma.getHorario();
    this->students = turma.getStudents();
}

Turma::Turma(string& ucCode, string& turmaCode) {
    this->ucCode = ucCode;
    this->turmaCode = turmaCode;

    vector<ScheduleSlot> horario;
    horario.emplace_back();
    this->schedule = horario;

    vector<Student> estudantes;
    estudantes.emplace_back();
    this->students = estudantes;
}

// Getters
const string &Turma::getUcCode() const {
    return this->ucCode;
}
const string &Turma::getTurmaCode() const {
    return this->turmaCode;
}
vector<ScheduleSlot> Turma::getHorario() const {
    return this->schedule;
}
vector<Student> Turma::getStudents() const {
    return this->students;
}
vector<Student> &Turma::getStudents() {
    return this->students;
}
size_t Turma::getNumStudents() const {
    return this->students.size();
}

void Turma::addScheduleSlot(const ScheduleSlot &slot) {
    if (this->schedule[0].getWeekDay().empty()) {
        this->schedule[0].setWeekDay(slot.getWeekDay());
        this->schedule[0].setBegin(slot.getBegin());
        this->schedule[0].setEnd(slot.getEnd());
        this->schedule[0].setType(slot.getType());
    }
    else this->schedule.push_back(slot);
}

void Turma::addStudent(const Student &student) {
    if (this->students[0].getCode().empty()) {
        this->students[0].setName(student.getName());
        this->students[0].setCode(student.getCode());
        this->students[0].setUcClasses(student.getUcClasses());
    }
    else this->students.push_back(student);
}

void Turma::printHorario() const {
    cout << this->ucCode << "," << this->turmaCode << ":" << endl;
    vector<ScheduleSlot> sorted_horario = this->schedule;
    sort(sorted_horario.begin(), sorted_horario.end(), sortHorario); // O(n*log n), where n is the number of items to be sorted
    for (const ScheduleSlot& slot : sorted_horario) { // O(n), where n is the number of slots in this->schedule
        if (slot.getBegin() != -1) {
            cout << "      " << slot.getWeekDay() << "," << slot.getBegin() << "," << slot.getEnd() << ","
                 << slot.getType() << endl;
        }
        else cout << "This class has no schedule.\n";
    }
}

void Turma::printStudents() const {
    cout << this->ucCode << "," << this->turmaCode << ":" << endl;
    vector<Student> sorted_students = this->students;
    sort(sorted_students.begin(), sorted_students.end(), sortStudents); // O(n*log n), where n is the number of items to be sorted
    for(const Student& student : sorted_students) { // O(n), where n is the number of Student objects in this->students
        if (!student.getCode().empty()) {
            cout << "       " << student.getCode() << "," << student.getName() << endl;
        }
        else cout << "This class has no students.\n";
    }
}

bool Turma::sortHorario(const ScheduleSlot &slot1, const ScheduleSlot &slot2) {
    int day_value1 = slot1.dayValue(), day_value2 = slot2.dayValue();
    if (day_value1 < day_value2) return true;
    else if (day_value1 == day_value2 and slot1.getBegin() < slot2.getBegin()) return true;
    else return false;
}

bool Turma::sortStudents(const Student &student1, const Student &student2) {
    if (student1.getName() < student2.getName()) return true;
    else if (student1.getName() == student2.getName() and student1.getCode() < student2.getCode()) return true;
    else return false;
}


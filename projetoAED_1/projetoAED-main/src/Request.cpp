#include "Request.hpp"


Request::Request() {
    this->studentCode = "";
    this->uc = "";
    this->oldTurma = "";
    this->newTurma = "";
}

Request::Request(const string& student_code, const string& uc, const string& old_turma, const string& new_turma) {
    this->studentCode = student_code;
    this->uc = uc;
    this->oldTurma = old_turma;
    this->newTurma = new_turma;
    
}


const string &Request::getStudentCode() const {
    return studentCode;
}
const string &Request::getUc() const {
    return uc;
}
const string &Request::getOldTurma() const {
    return oldTurma;
}
const string &Request::getNewTurma() const {
    return newTurma;
}


void Request::setStudentCode(const string &student_code) {
    Request::studentCode = student_code;
}
void Request::setUc(const string &uc_) {
    Request::uc = uc_;
}
void Request::setOldTurma(const string &old_turma) {
    Request::oldTurma = old_turma;
}
void Request::setNewTurma(const string &new_turma) {
    Request::newTurma = new_turma;
}

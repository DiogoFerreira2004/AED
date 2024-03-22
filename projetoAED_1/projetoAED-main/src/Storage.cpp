#include "Storage.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
using std::set, std::ifstream, std::ofstream, std::stringstream, std::cout;


// AllTurmas Class
AllTurmas::AllTurmas() {
    vector<Turma> placeholder;
    this->turmas = placeholder;
}

AllTurmas::AllTurmas(const string &file) {
    set<Turma> turmas_temp;
    vector<Turma> turmas_;

    ifstream csv(file);
    string line;
    bool first = true;
    while (getline(csv, line)) { //  O(n), n lines in classes_per_uc.csv
        if (!first) {
            size_t pos = line.find(',');
            string uc_code = line.substr(0,pos);
            string turma_code = line.substr(pos+1, line.size()-uc_code.size());
            Turma turma = Turma(uc_code, turma_code);
            turmas_temp.insert(turma);
        }
        else {
            first = false;
        }
    }
    for (const Turma& turma : turmas_temp) turmas_.push_back(turma); // O(n), n Turma objects = n lines in the file
    this->turmas = turmas_;
}

vector<Turma> AllTurmas::getTurmas() const {
    return this->turmas;
}

Turma& AllTurmas::getOneTurma(const string &uc_code, const string &class_code) {
    int pos = findTurma(uc_code, class_code);
    return this->turmas[pos];
}

void AllTurmas::setSchedule(const string &file) {
    ifstream csv(file);
    string line, classCode_, ucCode_, weekDay_, startHour_, duration_, type_;
    bool first = true;
    while (getline(csv, line)) { // O(n), n lines in classes.csv
        if (!first) {
            stringstream oneLine(line);
            getline(oneLine, classCode_, ',');
            getline(oneLine, ucCode_, ',');
            getline(oneLine, weekDay_, ',');
            getline(oneLine, startHour_, ',');
            getline(oneLine, duration_, ',');
            getline(oneLine, type_);
            ScheduleSlot slot = ScheduleSlot(weekDay_, type_, stof(startHour_), stof(duration_));
            this->turmas[findTurma(ucCode_,classCode_)].addScheduleSlot(slot); // O(log p), p Turma objects in this->turmas
        }
        else {
            first = false;
        }
    }
}

int AllTurmas::findTurma(const string &uc_code, const string &class_code) const { // Binary search -> O(log n)
    int low = 0, high = (int) this->turmas.size()-1;
    while (low <= high) {
        int pos = low + (high - low) / 2;
        if (uc_code < this->turmas[pos].getUcCode() or (uc_code == this->turmas[pos].getUcCode()) and class_code < this->turmas[pos].getTurmaCode()) high = pos - 1;
        else if (uc_code > this->turmas[pos].getUcCode() or (uc_code == this->turmas[pos].getUcCode()) and class_code > this->turmas[pos].getTurmaCode()) low = pos + 1;
        else return pos;
    }
    return -1;
}

void AllTurmas::printTurmasOccupation() const {
    for (const Turma& turma: this->turmas) {
        cout << turma.getUcCode() << "," << turma.getTurmaCode() << ": has " << turma.getStudents().size() << " student(s)\n";
    }
}

void AllTurmas::printUcOccupation(const vector<pair<string,int>> &uc_occupation) const {
    for (const auto& pair : uc_occupation) {
        cout << pair.first << " has " << pair.second << " student(s)\n";
    }
}

void AllTurmas::printTurmaSchedule(const string &uc_code, const string &class_code) const {
    int turma_pos = findTurma(uc_code, class_code); // O(log n)), n Turma objects in this->Turmas
    if (turma_pos != -1) {
        this->turmas[turma_pos].printHorario(); // O(p), p ScheduleSlot objects in this->schedule of a Turma object
    }
    else {
        cout << "Error! Could not find class.\n";
    }
}

void AllTurmas::printTurmaStudents(const string &uc_code, const string &class_code) const {
    int turma_pos = findTurma(uc_code, class_code); // O(log n), n Turma objects in this->turmas
    if (turma_pos != -1) {
        this->turmas[turma_pos].printStudents();
    }
    else {
        cout << "Error! Could not find class.\n";
    }
}

void AllTurmas::printTopUCs() const {
    vector<pair<string,int>> UcOccupation;
    string UC = this->turmas[0].getUcCode();
    size_t occupation = 0;

    for (const Turma& turma : this->turmas) { // O(n), n Turma objects in this->turmas
        if (UC == turma.getUcCode()) {
            occupation += turma.getStudents().size();
        }
        else {
            UcOccupation.emplace_back(UC, occupation);
            UC = turma.getUcCode();
            occupation = turma.getStudents().size();
        }
    }
    UcOccupation.emplace_back(UC, occupation);

    sort(UcOccupation.rbegin(), UcOccupation.rend(), sortByValueUC);

    for (int i = 0; i < 5; i++) {
        cout << "Top " << i + 1 << ": "<< UcOccupation[i].first << " with " << UcOccupation[i].second << " students!\n";
    }
}

void AllTurmas::classOccupation(int type) {
    vector<Turma> turmas_to_sort = this->turmas;
    switch (type) {
        case 1:  //ascending value
            sort(turmas_to_sort.begin(),turmas_to_sort.end(), sortByValue);
            printTurmasOccupation();
            break;
        case 2:  //descending value
            sort(turmas_to_sort.rbegin(),turmas_to_sort.rend(), sortByValue);
            printTurmasOccupation();
            break;
        case 3:  //ascending UC
            sort(turmas_to_sort.begin(),turmas_to_sort.end(), sortByUC);
            printTurmasOccupation();
            break;
        case 4:  //descending UC
            sort(turmas_to_sort.rbegin(),turmas_to_sort.rend(), sortByUC);
            printTurmasOccupation();
            break;
        default: // do nothing
            break;
    }
}

void AllTurmas::UcOccupation(int type) {
    vector<pair<string,int>> UcOccupation;
    string UC = this->turmas[0].getUcCode();
    size_t occupation = 0;

    for (const Turma& turma : this->turmas) { // O(n), n Turma objects in this->turmas
        if (UC == turma.getUcCode()) {
            occupation += turma.getStudents().size();
        }
        else {
            UcOccupation.emplace_back(UC, occupation);
            UC = turma.getUcCode();
            occupation = turma.getStudents().size();
        }
    }
    // Last UC
    UcOccupation.emplace_back(UC, occupation);

    switch (type) { // time complexity of printUcOccupation
        case 1: //ascending value
            sort(UcOccupation.begin(), UcOccupation.end(), sortByValueUC);
            printUcOccupation(UcOccupation);
            break;
        case 2: //descending value
            sort(UcOccupation.rbegin(), UcOccupation.rend(), sortByValueUC);
            printUcOccupation(UcOccupation);
            break;
        case 3: //ascending UC
            sort(UcOccupation.begin(), UcOccupation.end(), sortByUCUC);
            printUcOccupation(UcOccupation);
            break;
        case 4: //descending UC
            sort(UcOccupation.rbegin(), UcOccupation.rend(), sortByUCUC);
            printUcOccupation(UcOccupation);
            break;
        default: // do nothing
            break;
    }
}

bool AllTurmas::sortByValue(Turma &turma1, Turma &turma2) {
    if(turma1.getStudents().size() < turma2.getStudents().size()) return true;
    else if (turma1.getStudents().size() == turma2.getStudents().size() and turma1.getUcCode() < turma2.getUcCode()) return true;
    else if (turma1.getStudents().size() == turma2.getStudents().size() and turma1.getUcCode() == turma2.getUcCode() and turma1.getTurmaCode() < turma2.getTurmaCode()) return true;
    else return false;
}

bool AllTurmas::sortByUC(Turma &turma1, Turma &turma2) {
    if (turma1.getUcCode() < turma2.getUcCode()) return true;
    else if (turma1.getUcCode() == turma2.getUcCode() and turma1.getStudents().size() < turma2.getStudents().size()) return true;
    else if (turma1.getUcCode() == turma2.getUcCode() and turma1.getStudents().size() == turma2.getStudents().size() and turma1.getTurmaCode() < turma2.getTurmaCode()) return true;
    else return false;
}

bool AllTurmas::sortByValueUC(const pair<string,int> &pair1, const pair<string,int> &pair2) {
    if (pair1.second < pair2.second) return true;
    else if (pair1.second == pair2.second and pair1.first < pair2.first) return true;
    else return false;
}

bool AllTurmas::sortByUCUC(const pair<string,int> &pair1, const pair<string,int> &pair2) {
    return (pair1.first < pair2.first);
}

bool AllTurmas::classBalance(const Turma &new_turma, const Turma &old_turma) {
    size_t numNewTurma = new_turma.getStudents().size()+1, numOldTurma = old_turma.getStudents().size()-1;
    if (numOldTurma > numNewTurma) return true;
    else return (numNewTurma - numOldTurma) <= 4;
}


// AllStudents Class
AllStudents::AllStudents() {
    vector<Student> placeholder;
    this->students = placeholder;
}

AllStudents::AllStudents(const string &file, AllTurmas &allTurmas) {
    set<Student> students_temp;
    vector<Student> students_;
    vector<pair<string, string>> uc_classes;
    Student student;

    ifstream csv(file);
    string line, pastCode, pastName;
    bool first = true;
    while (getline(csv, line)) { // O(n), n lines in students_classes.csv
        if (!first) {
            string name_, code_, ucCode_, classCode_;
            stringstream oneLine(line);
            getline(oneLine, code_, ',');
            getline(oneLine, name_, ',');
            getline(oneLine, ucCode_, ',');
            getline(oneLine, classCode_);
            if (pastCode.empty()) {
                pastCode = code_;
                pastName = name_;
            }
            if (pastCode == code_) {
                uc_classes.emplace_back(ucCode_, classCode_);
            }
            else {
                student = Student(pastName, pastCode, uc_classes);
                students_temp.insert(student);
                for (const pair<string,string>& uc_class : uc_classes) { // O(p), p pairs of CU and class codes
                    allTurmas.getOneTurma(uc_class.first, uc_class.second).addStudent(student); // O(log q), q Turma objects in this->turmas
                }

                pastName = name_;
                pastCode = code_;

                uc_classes.clear();
                uc_classes.emplace_back(ucCode_, classCode_);
            }
        }
        else {
            first = false;
        }
    }
    // Last student
    student = Student(pastName, pastCode, uc_classes);
    students_temp.insert(student);
    for (const pair<string,string>& uc_class : uc_classes) {
        allTurmas.getOneTurma(uc_class.first, uc_class.second).addStudent(student);
    }


    for (const Student& student2 : students_temp) students_.push_back(student2); // complexidade: O(r), r Student objects in students_temp
    this->students = students_;
}

vector<Student> AllStudents::getStudents() const {
    return this->students;
}

Student& AllStudents::getOneStudent(const string &student_code) {
    int pos = findStudent(student_code);
    return this->students[pos];
}


int AllStudents::findStudent(const string &student_code) const { // Binary search -> O(log n), n Student objects in this->students
    string code_wo_up = student_code.substr(2);
    int low = 0, high = (int) this->students.size()-1;
    while (low <= high) {
        int pos = low + (high - low) / 2;
        if (code_wo_up < this->students[pos].getCode()) high = pos - 1;
        else if (code_wo_up > this->students[pos].getCode()) low = pos + 1;
        else return pos;
    }
    return -1;
}

int AllStudents::countYearStudents(const char &year) const {
    char max_year;
    int counter = 0;
    for (const Student& student : this->students) { // O(n), n Student objects in this->students
        max_year = '0';
        for(pair<string, string> uc_class : student.getUcClasses()) { // O(p), p pairs of CU and class codes
            if (uc_class.second[0] > max_year) {
                max_year = uc_class.second[0];
            }
        }
        if (max_year == year) {
            counter++;
        }
    }
    return counter;
}

void AllStudents::studentsInNUcs(const int &n) const {
    for (const Student& student : this->students) { // O(n), n Student objects in this->students
        if (student.getUcClasses().size() == n) {
            cout << student.getCode() << "," << student.getName() << "\n";
        }
    }
}

void AllStudents::yearOccupation(int type) {
    vector<pair<string,int>> yearOccupation;
    yearOccupation.emplace_back("Year 1", countYearStudents('1'));
    yearOccupation.emplace_back("Year 2", countYearStudents('2'));
    yearOccupation.emplace_back("Year 3", countYearStudents('3'));

    switch (type) {
        case 1:  //ascending value
            sort(yearOccupation.begin(), yearOccupation.end(), sortByValue);
            printYearOccupation(yearOccupation);
            break;
        case 2:  //descending value
            sort(yearOccupation.rbegin(), yearOccupation.rend(), sortByValue);
            printYearOccupation(yearOccupation);
            break;
        case 3:  //ascending year
            sort(yearOccupation.begin(), yearOccupation.end(), sortByYear);
            printYearOccupation(yearOccupation);
            break;
        case 4:  //descending year
            sort(yearOccupation.rbegin(), yearOccupation.rend(), sortByYear);
            printYearOccupation(yearOccupation);
            break;
        default: // do nothing
            break;
    }
}

void AllStudents::printStudentSchedule(const string &student_code, const AllTurmas &all_turmas) const {
    int student_pos = findStudent(student_code); // O(log n)
    if (student_pos != -1) {
        vector<pair<string, string>> uc_classes;
        Student student = this->students[student_pos];
        uc_classes = student.getUcClasses();
        cout << student.getCode() << ", " << student.getName() << ":\n";
        for (const pair<string,string>& uc_class : uc_classes) { //  O(p), n pair of CU and class codes
            all_turmas.printTurmaSchedule(uc_class.first, uc_class.second); // O(log q) + O(r)
        }
    }
    else {
        cout << "Error! Could not find student.\n";
    }
} //Complexidade final = O(log n) * O(n)

void AllStudents::printCourseStudents(const string &course) const{
    for (const Student& student : this->students) { // O(n), n Student objects in this->students
        if (student.getUcClasses()[0].first.substr(0, course.length()) == course) { // O(p), where p is the length of the resulting substr
            cout << student.getCode() << "," << student.getName() << "\n";
        }
    }
}

void AllStudents::printYearStudents(const char &year) const {
    char max_year;

    for (const Student& student : this->students) { // O(n), n Student objects in this->students
        max_year = '0';
        for(pair<string, string> uc_class : student.getUcClasses()) { // O(p), p pairs of CU and class codes
            if (uc_class.second[0] > max_year) {
                max_year = uc_class.second[0];
            }
        }
        if (max_year == year) {
            cout << student.getCode() << "," << student.getName() << "\n";
        }
    }

}

void AllStudents::printYearOccupation(const vector<pair<string,int>> &year_occupation) {
    for (const pair<string,int>& pair : year_occupation) {
        cout << pair.first << " has " << pair.second << " students\n";
    }
}


bool AllStudents::sortByValue(const pair<string,int> &pair1, const pair<string,int> &pair2) {
    if (pair1.second < pair2.second) return true;
    else if (pair1.second == pair2.second and pair1.first < pair2.first) return true;
    else return false;
}

bool AllStudents::sortByYear(const pair<string,int> &pair1, const pair<string,int> &pair2) {
    return (pair1.first < pair2.first);
}



// AllRequests Class
AllRequests::AllRequests() {
    std::queue<Request> pendPlaceholder;
    std::stack<Request> undoPlaceholder;
    this->pendingRequests = pendPlaceholder;
    this->processedRequests = undoPlaceholder;
}

const queue<Request> &AllRequests::getPendingRequests() const {
    return pendingRequests;
}
const stack<Request> &AllRequests::getProcessedRequests() const {
    return processedRequests;
}


string AllRequests::checkRequestUcE(Request &request, AllStudents &all_students, AllTurmas &all_turmas) const {
    // Request UcE (UC Enrollment)
    vector<ScheduleSlot> old_horarios;
    Student student = all_students.getOneStudent(request.getStudentCode());

    if (student.getUcClasses().size() >= 7) return "-1";

    for (const Turma& turma : all_turmas.getTurmas()) { // O(n), n Turma objects in this->turmas
        if (turma.getUcCode() == request.getUc() and turma.getNumStudents() < 30) {
            for (const pair<string, string>& uc_class : student.getUcClasses()) { // O(p), p pair of CU and class codes in student.getUcClasses()
                if (uc_class.first == request.getUc()) return "-2";

                Turma old_turma = all_turmas.getOneTurma(uc_class.first, uc_class.second); // O(log n), n Turma objects in this->turmas (complexity of findTurma())
                for (const ScheduleSlot& slot : old_turma.getHorario()) // O(q), q ScheduleSlots in a specific class
                    old_horarios.push_back(slot);
            }
            if (!ScheduleSlot::scheduleConflict(old_horarios, turma.getHorario())) // O(r*s)
                return turma.getTurmaCode();

        }
    }
    return "0";
}

int AllRequests::checkRequestCc(Request &request, AllStudents &all_students, AllTurmas &all_turmas) const {
    // Request CC (Class Change)
    Turma new_turma = all_turmas.getOneTurma(request.getUc(), request.getNewTurma()); // O(log n), n Turma objects in this->turmas (findTurma() complexity)
    Turma old_turma = all_turmas.getOneTurma(request.getUc(), request.getOldTurma()); // O(log n)
    if (new_turma.getStudents().size() >= 30) return -2;
    if (!AllTurmas::classBalance(new_turma, old_turma)) return -1;

    Student student = all_students.getOneStudent(request.getStudentCode()); // O(log p), p Student objects in this->students (findStudent() complexity)
    Turma turma;
    for (const pair<string,string>& uc_class : student.getUcClasses()) { // O(q), q pairs in student's uc_classes
        if (uc_class.first != request.getUc()) {
            turma = all_turmas.getOneTurma(uc_class.first, uc_class.second); // O(log n)
            if (ScheduleSlot::scheduleConflict(turma.getHorario(),new_turma.getHorario())) { // O(r*s)
                return 0;
            }
        }
    }
    return 1;
}

void AllRequests::insertRequest(const Request &new_request) {
    bool theyEqual = false;
    queue<Request> checkAssistant = this->pendingRequests;
    for (int i = 0; i < this->pendingRequests.size(); i++) { // O(n), n requests in the pending queue
        if (checkAssistant.front().getOldTurma().empty() and checkAssistant.front().getNewTurma().empty()) {
            // CU enroll
            if (new_request.getUc() == checkAssistant.front().getUc() and new_request.getStudentCode() == checkAssistant.front().getStudentCode()) {
                theyEqual = true;
            }
        }
        else if (!checkAssistant.front().getOldTurma().empty() and checkAssistant.front().getNewTurma().empty()) {
            // CU remove
            if (new_request.getUc() == checkAssistant.front().getUc() and new_request.getStudentCode() == checkAssistant.front().getStudentCode() and new_request.getOldTurma() == checkAssistant.front().getOldTurma()) {
                theyEqual = true;
            }
        }
        else {
            // Class change
            if (new_request.getUc() == checkAssistant.front().getUc() and new_request.getStudentCode() == checkAssistant.front().getStudentCode() and new_request.getOldTurma() == checkAssistant.front().getOldTurma() and new_request.getNewTurma() == checkAssistant.front().getNewTurma()) {
                theyEqual = true;
            }
        }
        checkAssistant.pop();        
    }

    if (theyEqual) cout << "That request has already been added to the queue of pending requests!\n";
    else {
        this->pendingRequests.push(new_request);
        cout << "Request has been added to the queue! Go back to the main menu to process it.\n";
    }
}

void AllRequests::printPending() const {
    queue<Request> copy_pending = this->pendingRequests;
    if (copy_pending.empty()) cout << "                         There are no pending requests!                          \n";
    else if (copy_pending.size() == 1) cout << "Pending requests (" << copy_pending.size() << " entry):\n";
    else cout << "Pending requests (" << copy_pending.size() << " entries):\n";
    while (!copy_pending.empty()) { // O(n), n requests in the pending queue
        if (copy_pending.front().getOldTurma().empty() and copy_pending.front().getNewTurma().empty())
            cout << " > UC enroll request from student " << copy_pending.front().getStudentCode() << " to CU '" << copy_pending.front().getUc() << "';\n";
        if (!copy_pending.front().getOldTurma().empty() and copy_pending.front().getNewTurma().empty())
            cout << " > UC removal request from student " << copy_pending.front().getStudentCode() << " of CU '" << copy_pending.front().getUc() << "';\n";
        if (!copy_pending.front().getStudentCode().empty() and !copy_pending.front().getUc().empty() and !copy_pending.front().getOldTurma().empty() and !copy_pending.front().getNewTurma().empty())
            cout << " > Class change request from student '" << copy_pending.front().getStudentCode() << "' of CU '" << copy_pending.front().getUc() << "\n   from class '" << copy_pending.front().getOldTurma() << "' to class '" << copy_pending.front().getNewTurma() << "';\n";
        copy_pending.pop();
    }
}

void AllRequests::processPending(AllStudents &all_students, AllTurmas &all_turmas) {
    int req_num = 0;
    bool CuIsThere = false;
    size_t amount_req = this->pendingRequests.size();
    string code_wo_up;
    while (!this->pendingRequests.empty()) { // O(n), n requests in the pending queue
        req_num++;
        if (this->pendingRequests.front().getOldTurma().empty() and this->pendingRequests.front().getNewTurma().empty()) {
            // UC enroll
            string checkUCE = checkRequestUcE(this->pendingRequests.front(), all_students, all_turmas);
            if (checkUCE == "-2") {
                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "is an invalid request.\n";
                cout << "Reason: " << "The student is already enrolled in the requested CU.\n";
            }

            else if (checkUCE == "-1") {
                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "is an invalid request.\n";
                cout << "Reason: " << "The student is already enrolled in the maximum amount of CUs (7).\n";
            }
            else if (checkUCE == "0") {
                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "is an invalid request.\n";
                cout << "Reason: " << "Couldn't find any class of the desired CU where the student could be enrolled in.\n";
            }
            else {
                Student& student = all_students.getOneStudent(this->pendingRequests.front().getStudentCode());
                Turma& turma = all_turmas.getOneTurma(this->pendingRequests.front().getUc(), checkUCE);

                student.addUcClass(this->pendingRequests.front().getUc(), checkUCE);
                turma.addStudent(all_students.getOneStudent(this->pendingRequests.front().getStudentCode()));

                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "has been accepted!\n";
                this->processedRequests.push(this->pendingRequests.front());
            }
        }
        else if (!this->pendingRequests.front().getOldTurma().empty() and this->pendingRequests.front().getNewTurma().empty()) {
            // UC remove
            code_wo_up = this->pendingRequests.front().getStudentCode().substr(2);
            vector<Student>& estudantes_turma = all_turmas.getOneTurma(this->pendingRequests.front().getUc(), this->pendingRequests.front().getOldTurma()).getStudents();
            vector<pair<string,string>>& turmas_estudante = all_students.getOneStudent(this->pendingRequests.front().getStudentCode()).getUcClasses();

            auto it1 = estudantes_turma.begin();
            auto it2 = turmas_estudante.begin();

            for (const Student& estudante : estudantes_turma) { // O(p), p Student objects in the old class
                if (estudante.getCode() == code_wo_up) {
                    estudantes_turma.erase(it1);
                    break;
                }
                it1++;
            }
            for (const pair<string,string>& uc_class : turmas_estudante) { // O(q), q pairs of the Student's uc_classes
                if (uc_class.first == this->pendingRequests.front().getUc()) {
                    CuIsThere = true;
                    turmas_estudante.erase(it2);
                    break;
                }
                it2++;
            }
            if (CuIsThere) cout << "Request number " << req_num << " (out of " << amount_req << ") " << "has been accepted!\n";
            else {
                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "is an invalid request.\n";
                cout << "Reason: " << "The student wasn't enrolled in the CU you want to remove him from.\n";
            }

            this->processedRequests.push(this->pendingRequests.front());
        }
        else {
            // Class change
            code_wo_up = this->pendingRequests.front().getStudentCode().substr(2);
            int checkCC = checkRequestCc(this->pendingRequests.front(), all_students, all_turmas);
            if (checkCC == 1) {
                Student& student = all_students.getOneStudent(this->pendingRequests.front().getStudentCode());
                Turma& old_turma = all_turmas.getOneTurma(this->pendingRequests.front().getUc(),this->pendingRequests.front().getOldTurma());
                Turma& new_turma = all_turmas.getOneTurma(this->pendingRequests.front().getUc(),this->pendingRequests.front().getNewTurma());

                student.changeClasses(this->pendingRequests.front().getUc(),this->pendingRequests.front().getNewTurma());
                vector<Student>& estudantes_oldT = old_turma.getStudents();
                auto it3 = estudantes_oldT.begin();

                for (const Student& estudante : estudantes_oldT) { // O(r), r students in the old class
                    if (estudante.getCode() == code_wo_up) {
                        estudantes_oldT.erase(it3);
                        break;
                    }
                    it3++;
                }
                new_turma.addStudent(student);
                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "has been accepted!\n";
                this->processedRequests.push(this->pendingRequests.front());
            }
            else {
                cout << "Request number " << req_num << " (out of " << amount_req << ") " << "is an invalid request.\n";
                if (checkCC == -2)
                    cout << "Reason: " << "The desired class has already reached the maximum occupation (30)\n";
                else if (checkCC == -1)
                    cout << "Reason: " << "The request creates an imbalance in the amount of students per class\n";
                else
                    cout << "Reason: " << "The schedule of the desired class has a conflict with the student's schedule.\n";
            }
        }
        this->pendingRequests.pop();
    }
    if (amount_req == 0) cout << "                     There are no requests to be processed!                      \n";
}

void AllRequests::undoOnePending() {
    size_t i = 0;
    // Dar pop ao pending mais recente na queue
    while (i != this->pendingRequests.size()-1) { // O(n-1), n requests in the pending queue
        this->pendingRequests.push(this->pendingRequests.front());
        this->pendingRequests.pop();
        i++;
    }
    this->pendingRequests.pop();
    cout << "                    The request has been undone successfully!                    \n";
}

void AllRequests::undoAllPending() {
    if (this->pendingRequests.size() == 1) cout << "                    The request has been undone successfully!                    \n";
    else if (this->pendingRequests.size() > 1) cout << "                   The requests have been undone successfully!                   \n";
    std::queue<Request> pendPlaceholder;
    this->pendingRequests = pendPlaceholder;
}

void AllRequests::undoOneProcessed(AllStudents &all_students, AllTurmas &all_turmas) {
    Request undo_request = this->processedRequests.top();
    string code_wo_up;

    if (undo_request.getOldTurma().empty() and undo_request.getNewTurma().empty()) {
        // CU enroll undo
        code_wo_up = undo_request.getStudentCode().substr(2);
        vector<pair<string, string>> &turmas_estudante = all_students.getOneStudent(undo_request.getStudentCode()).getUcClasses();
        vector<Student> &estudantes_turma = all_turmas.getOneTurma(turmas_estudante.back().first,
                                                                   turmas_estudante.back().second).getStudents();

        auto it1 = estudantes_turma.begin();

        for (const Student &estudante : estudantes_turma) { // O(n), n students in the old class
            if (estudante.getCode() == code_wo_up) {
                estudantes_turma.erase(it1);
                break;
            }
            it1++;
        }
        turmas_estudante.pop_back();
        cout << "Your request has been successfully undone!\n";
    }
    else if (!undo_request.getOldTurma().empty() and undo_request.getNewTurma().empty()) {
        // CU remove undo
        Turma &old_turma = all_turmas.getOneTurma(undo_request.getUc(), undo_request.getOldTurma());
        Student &student = all_students.getOneStudent(undo_request.getStudentCode());
        if (old_turma.getStudents().size() < 30) {
            student.addUcClass(undo_request.getUc(), undo_request.getOldTurma());
            old_turma.addStudent(all_students.getOneStudent(undo_request.getStudentCode()));
            cout << "Your request has been successfully undone!\n";
        }
        else {
            cout << "ERROR: It is already too late to undo this request!\n"
                 << "Undoing this request would cause conflict with the other processed requests\n";
        }
    }
    else {
        // Class change undo
        code_wo_up = undo_request.getStudentCode().substr(2);
        string old_turma_code = undo_request.getOldTurma();
        undo_request.setOldTurma(undo_request.getNewTurma());
        undo_request.setNewTurma(old_turma_code);
        int checkCC = checkRequestCc(undo_request, all_students, all_turmas);
        if (checkCC == 1) {
            Student &student = all_students.getOneStudent(undo_request.getStudentCode());
            Turma &old_turma = all_turmas.getOneTurma(undo_request.getUc(),undo_request.getOldTurma());
            Turma &new_turma = all_turmas.getOneTurma(undo_request.getUc(),undo_request.getNewTurma());

            student.changeClasses(undo_request.getUc(),undo_request.getNewTurma());
            vector<Student> &estudantes_oldT = old_turma.getStudents();
            auto it3 = estudantes_oldT.begin();

            for (const Student &estudante: estudantes_oldT) { // O(p), p students in the old class
            if (estudante.getCode() == code_wo_up) {
                estudantes_oldT.erase(it3);
                break;
            }
            it3++;
            }
            new_turma.addStudent(student);
            cout << "Your request has been successfully undone!\n";
        }
        else {
            cout << "ERROR: It is already too late to undo this request!\n"
                 << "Undoing this request would cause conflict with the other processed requests\n";
        }
    }
    this->processedRequests.pop();
}

void AllRequests::saveProcessedRequests(const AllStudents &all_students) {
    ofstream dest("../data/students_classes.csv");
    dest << "StudentCode,StudentName,UcCode,ClassCode" << "\n";
    for (const Student& student : all_students.getStudents()) { // O(n), n Student objects in this->students
        vector<pair<string, string>> uc_classes = student.getUcClasses();
        for (const pair<string,string>& uc_class : uc_classes) { // O(p), p pairs of the student's uc_classes
            dest << student.getCode() << "," << student.getName() << "," << uc_class.first << "," << uc_class.second << "\n";
        }
    }
    dest.close();
}



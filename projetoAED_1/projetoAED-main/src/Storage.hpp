#ifndef AED_STORAGE_HPP
#define AED_STORAGE_HPP

#include "Turma.hpp"
#include "Student.hpp"
#include "Request.hpp"
#include <set>
#include <queue>
#include <stack>
using std::vector, std::string, std::queue, std::stack;


/// @brief Class that stores and manipulates all the Turma (class) objects as a whole.
/// @details Uses a vector to facilitate the manipulation of the stored data.
/// @see Turma.hpp
class AllTurmas {
private:
    /// @brief Vector that stores all the classes.
    vector<Turma> turmas;

public:
    /*!
     * @brief Default constructor of the AllTurmas class.
     * @details Initializes the vector member variable with an empty vector (placeholder).
     * @note Time complexity: O(1).
     */
    AllTurmas();

    /*!
     * @brief Parametrized constructor of the AllTurmas class.
     * @details Initializes the vector with the required data, by reading it from a file.
     * @param file String containing the path to the .csv file.
     * @note Time complexity: O(n), where n is the number lines in the classes_per_uc.csv file.
     */
    AllTurmas(const string& file);

    /*!
     * @brief Getter for the vector of classes.
     * @returns Vector of Turma objects.
     */
    vector<Turma> getTurmas() const;

    /*!
     * @brief Getter for a specific element of the vector.
     * @details Calls findTurma() to access the position of vector specified by the parameters.
     * @param uc_code, class_code Unique combination of uc_code and class_code that identifies a Turma object.
     * @see findTurma()
     * @note Time complexity: complexity of findTurma(), O(log n), where n is the number of Turma objects in this->turmas.
     */
    Turma& getOneTurma(const string& uc_code, const string& class_code);


    /*!
     * @brief Sets the schedule of each Turma object inside the vector member variable.
     * @details Initializes the Turma object with the schedule information provided by the respective file.
     * @param file String containing the path to the .csv file.
     * @see Turma.hpp
     * @see findTurma()
     * @note Time complexity: O(n*log p), where n is the number of lines in classes.csv, and p is the number of Turma objects in this->turmas.
     */
    void setSchedule(const string& file);


    /*!
     * @brief Function that finds the position in the vector specified by the parameters.
     * @details Uses the binary search algorithm.
     * @param uc_code, class_code Unique combination of uc_code and class_code that identifies a Turma object.
     * @note Time complexity: O(log n), where n is the Turma objects in this->turmas.
     */
    int findTurma(const string& uc_code, const string& class_code) const;


    /*!
     * @brief Function that prints the occupation of each Turma stored in the vector.
     * @details The occupation (number of students) corresponds to the size of the vector of students inside each Turma object.
     * @note Time complexity: O(n), where n is the number of Turma objects in this->turmas.
     */
    void printTurmasOccupation() const;

    /*!
     * @brief Function that prints the occupation of each Curricular Unit (CU) stored in the tool.
     * @param uc_occupation Receives vector containing pairs of CU codes with their respective occupations from the UcOccupation function.
     * @see UcOccupation()
     * @note Time complexity: O(n), where n is the number of pairs in uc_occupation. <br>
     *       Notice: it corresponds to the number of different CUs in this->turmas (always several times lower than the number of classes in this->turmas, because each CU has several different classes).
     */
    void printUcOccupation(const vector<pair<string,int>>& uc_occupation) const;

    /*!
     * @brief Function that prints the schedule of a Turma.
     * @param uc_code, class_code Unique combination of uc_code and class_code that identifies a Turma object.
     * @see findTurma()
     * @see Turma::printHorario()
     * @note Time complexity: O(log n + p), where O(log n) is the time complexity of findTurma(), and p is the number of ScheduleSlot objects in this->schedule of a Turma object.
     */
    void printTurmaSchedule(const string& uc_code, const string& class_code) const;

    /*!
     * @brief Function that prints all the students stored in a Turma object.
     * @param uc_code, class_code Unique combination of uc_code and class_code that identifies a Turma object.
     * @see findTurma()
     * @see Turma::printStudents()
     * @note Time complexity: complexity of findTurma, O(log n), where n is the number of Turma objects in this->turmas.
     */
    void printTurmaStudents(const string& uc_code, const string& class_code) const;

    /*!
     * @brief Function that prints the Top 5 CUs with highest occupation.
     * @see Turma.hpp
     * @see UcOccupation()
     * @see sortByValueUC()
     * @note Time complexity: O(n), where n is the number of Turma objects in this->turmas.
     */
    void printTopUCs() const;


    /*!
     * @brief Function that prints the occupation of every class stored.
     * @param type User input that dictates which sort function is called and how the print is sorted.
     * @see printTurmasOccupation()
     * @see AllTurmas::sortByValue()
     * @see sortByUC()
     * @note Time complexity: complexity of printTurmasOccupation(), O(n), where n is the number of Turma objects in this->turmas.
     */
    void classOccupation(int type);

    /*!
     * @brief Function that prints the occupation of every CU stored.
     * @param type User input that dictates which sort function is called and how the print is sorted.
     * @see Turma.hpp
     * @see printTurmasOccupation()
     * @see sortByValueUC()
     * @see sortByUCUC()
     * @note Time complexity: O(n), where n is the number of Turma objects in this->turmas.
     */
    void UcOccupation(int type);


    /*!
     * @brief Comparison function for sorting a vector based on the number of students in the class.
     * @param turma1, turma2 The two Turma objects that are compared while sorting a vector.
     * @return True if: <br>
     *          - turma1 has less students than turma2; <br>
     *          - turmas have the same number of students but turma1 has a lower CU code; <br>
     *          - turmas have the same number of students and the same CU code but turma1 has a lower class code; <br>
     *         False otherwise.
     * @see Turma.hpp
     * @note Time complexity: O(1).
     */
    static bool sortByValue(Turma& turma1, Turma& turma2);

    /*!
     * @brief Comparison function for sorting a vector based on the CU code.
     * @param turma1, turma2 The two Turma objects that are compared while sorting a vector.
     * @return True if: <br>
     *          - turma1 has a lower CU code than turma2; <br>
     *          - turmas have the same CU code but turma1 has a lower number of students; <br>
     *          - turmas have the same CU code and the same number of students but turma1 has a lower class code; <br>
     *         False otherwise.
     * @see Turma.hpp
     * @note Time complexity: O(1).
     */
    static bool sortByUC(Turma& turma1, Turma& turma2);

    /*!
     * @brief Comparison function for sorting a vector based on the number of students in the CU.
     * @param pair1, pair2 The two pairs, containing the CU code and the CU occupation, that are compared while sorting the vector.
     * @return True if: <br>
     *          - the CU in pair1 has less students than the CU in pair2; <br>
     *          - the CUs have the same number of students but the CU code in pair1 is lower; <br>
     *         False otherwise.
     * @note Time complexity: O(1).
     */
    static bool sortByValueUC(const pair<string,int>& pair1, const pair<string,int>& pair2);

    /*!
     * @brief Comparison function for sorting a vector based on the CU code.
     * @param pair1, pair2 The two pairs, containing the CU code and the CU occupation, that are compared while sorting the vector.
     * @return True if the CU code in pair1 is lower than the CU code in pair2; False otherwise.
     * @note Time complexity: O(1).
     */
    static bool sortByUCUC(const pair<string,int>& pair1, const pair<string,int>& pair2);

    /*!
     * @brief Comparison function to check if class balance is maintained during a class change, based on the number of students.
     * @param new_turma, old_turma The class that the student wants to enroll in and the class the students wants to leave from, respectively.
     * @return True if the old Turma has more students than the new Turma or if the difference between the classes is less or equal to 4; False otherwise.
     * @note Time complexity: O(1).
     */
    static bool classBalance(const Turma& new_turma, const Turma& old_turma);
};


/// @brief Class that stores and manipulates all the Student objects as a whole.
/// @details Uses a vector to facilitate the manipulation of the stored data.
/// @see Student.hpp
class AllStudents {
private:
    /// @brief Vector that stores all the Student objects.
    vector<Student> students;

public:
    /*!
     * @brief Default constructor of the AllStudents class.
     * @details Initializes the vector member variable with an empty vector (placeholder).
     * @note Time complexity: O(1)
     */
    AllStudents();

    /*!
     * @brief Parametrized constructor of the AllStudents class.
     * @param file String containing the path to the .csv file.
     * @param allTurmas Used to store each Student object, created from the read data, in their respective Turma (class).
     * @details Initializes the vector with the required data about the Students, by reading it from a file.
     * @note Time complexity: O(n*p*log q), where n is the number of lines in students_classes.csv, p is the number of Curricular Units the student is enrolled in, q is the number of Turma objects in this->turmas of the all_turmas object. <br>
     *       Notice: p is never higher than 7, because a student cannot be enrolled in more than 7 CUs at the same time.
     */
    AllStudents(const string& file, AllTurmas& allTurmas);

    /*!
     * @brief Getter for the vector of students.
     * @returns Vector of Student objects.
     */
    vector<Student> getStudents() const;

    /*!
     * @brief Getter for a specific element of the vector.
     * @details Calls findStudent() to access the position of vector specified by the parameter.
     * @param student_code Identifies a Student object.
     * @see findStudent()
     * @note Time complexity: complexity of findStudent(), O(log n), where n Student objects in this->students.
     */
    Student& getOneStudent(const string& student_code);


    /*!
     * @brief Function that finds the position in the vector specified by the parameter.
     * @details Uses the binary search algorithm.
     * @param student_code Identifies a Student object.
     * @note Time complexity: O(log n), where n is the number of Student objects in this->students.
     */
    int findStudent(const string& student_code) const;

    /*!
     * @brief Function that counts the number of students in a specific year of the degree.
     * @details First finds what year the student is attending (first digit of the class_code is the degree year of that class, and finds the highest of the first digits in the classes the Student is attending). <br>
     *          Then matches that year with the parameter, to count the student if he's in that year.
     * @param year Year that students (whose numbers will be counted) are enrolled in.
     * @see Student.hpp
     * @note Time complexity: O(n*p), where n is the number of Student objects in this->students, and p is the number of Curricular Units the Student has enrolled in. <br>
     *       Notice: p is never higher than 7, because a student cannot be unrolled in more than 7 CUs at the same time.
     */
    int countYearStudents(const char& year) const;

    /*!
     * @brief Function that prints all the students that are in N CUs.
     * @param n Number of CUs that students (whose information will be printed) are enrolled in.
     * @see Student.hpp
     * @note Time complexity: O(n), where n is the number of Student objects in this->students.
     */
    void studentsInNUcs(const int& n) const;

    /*!
     * @brief Function that prints the occupation of each of the three years of the degree.
     * @param type User input that dictates which sort function is called and how the print is sorted.
     * @see countYearStudents()
     * @see printYearOccupation()
     * @see AllStudents::sortByValue()
     * @see AllStudents::sortByYear()
     * @note Time complexity: complexity of countYearStudents(), O(n*p), where n is the number of Student objects in this->students, and p is the number of Curricular Units the Student has enrolled in.
     */
    void yearOccupation(int type);


    /*!
     * @brief Function that prints the schedule of a Student.
     * @details Function checks if the student exists, if he does, it prints his schedule. <br>
     *          If he doesn't, it print an error message.
     * @param student_code Identifies a Student object.
     * @param all_turmas Used to manipulate, as needed, the classes' data, in order to store the changes.
     * @see Student.hpp
     * @see findStudent()
     * @see AllTurmas::printTurmaSchedule()
     * @note Time complexity: O(log n + p*(log q + r)), where O(log n) is the complexity of findStudent(), where p is the number of Curricular Units the Student is enrolled in, and O(log q + r) is the complexity of AllTurmas::printTurmaSchedule().
     */
    void printStudentSchedule(const string& student_code, const AllTurmas& all_turmas) const;

    /*!
     * @brief Function that prints all the students of a specific course.
     * @param course Identifies the student's course.
     * @see Student.hpp
     * @note Time complexity: O(n*p), where n is the number of Student objects in this->students and p is the length of the resulting substring.
     */
    void printCourseStudents(const string& course) const;

    /*!
     * @brief Function that prints all the students of a specific year.
     * @details Just like countYearStudents(), first finds what year the student is attending (first digit of the class_code is the degree year of that class, and finds the highest of the first digits in the classes the Student is attending). <br>
     *          Then matches the year in the parameter and prints the information about that student.
     * @param year Year that students (whose information will be printed) are enrolled in.
     * @see Student.hpp
     * @note Time complexity: O(n*p), where n is the number of Student objects in this->students, and p is the number of Curricular Units the Student has enrolled in. <br>
     *       Notice: p is never higher than 7, because a student cannot be unrolled in more than 7 CUs at the same time.
     */
    void printYearStudents(const char& year) const;

    /*!
     * @brief Function that prints all the students of a specific year.
     * @details Called by yearOccupation().
     * @param year_occupation Pair of the year number and its respective occupation.
     * @see yearOccupation()
     * @note Time complexity: O(n), where n is the number of pairs in year_occupation.
     */
    void printYearOccupation(const vector<pair<string,int>>& year_occupation);


    /*!
     * @brief Comparison function for sorting a vector based on the number of students in the class.
     * @param pair1, pair2 Pairs of the degree's years and their respective occupations.
     * @return True if: <br>
     *          - year of pair1 has less students than year of pair2; <br>
     *          - both years have the same number of students, but year of pair1 is lower; <br>
     *         False otherwise.
     * @note Time complexity: O(1)
     */
    static bool sortByValue(const pair<string,int>& pair1, const pair<string,int>& pair2);

    /*!
     * @brief Comparison function for sorting a vector based on the number of students in the class.
     * @param pair1, pair2 Pairs of the degree's years and their respective occupations.
     * @return True if: <br>
     *         - year of pair1 has less students than year of pair2; <br>
     *         - both years have the same number of students, but year of pair1 is lower; <br>
     *         False otherwise.
     * @note Time complexity: O(1).
     */
    static bool sortByYear(const pair<string,int>& pair1, const pair<string,int>& pair2);
};


/// @brief Class that stores and manipulates all the Request objects as a whole.
/// @details Uses a vector to facilitate the manipulation of the stored data.
/// @see Request.hpp
class AllRequests {
private:
    /// @brief Queue that stores all the currently pending Request objects.
    /// @details Uses the FIFO (First In, First Out) logic, making it easier to process first the requests that were made first.
    queue<Request> pendingRequests;
    /// @brief Stack that stores all the already processed Request objects.
    /// @details Uses the LIFO (Last In, First Out) logic, making it easier to undo the Request that was processed last.
    stack<Request> processedRequests;

public:
    /*!
     * @brief Default constructor of the AllRequests class.
     * @details Initializes the queue and stack member variables with the respective empty container (placeholder).
     * @note Time complexity: O(1).
     */
    AllRequests();

    /*!
     * @brief Getter for the pending Requests.
     * @returns Queue of Request objects.
     */
    const queue<Request> &getPendingRequests() const;

    /*!
     * @brief Getter for the processed Requests.
     * @returns Stack of Request objects.
     */
    const stack<Request> &getProcessedRequests() const;


    /*!
     * @brief Auxiliary function that evaluates validity of CU Enroll Requests.
     * @param request Request that is being checked.
     * @param all_students, all_turmas Used to access the necessary data.
     * @returns "-2" if the student is already enrolled in that class; <br>
     *          "-1" if the student is already enrolled in 7 CU; <br>
     *          "0" if all the classes of the desired CU are full or if there is a schedule conflict between the available classes and the classes Student is already enrolled in; <br>
     *          A string with the class's code otherwise -> valid Request;
     * @see AllTurmas::classBalance()
     * @see processPending()
     * @note Time complexity: O(n*(p*(log n + q) + r*s)). <br>
     *       - where n is the number Turma objects in all_turmas.getTurmas(), p is the number of Curricular Units the student has enrolled in,
     *       q is the number of ScheduleSlot objects in one of the student's classes, r is the number of ScheduleSlot objects among all of the student's classes,
     *       and s is the number of ScheduleSlot objects in the class the student wants to enroll in.
     */
    string checkRequestUcE(Request& request, AllStudents& all_students, AllTurmas& all_turmas) const;

    /*!
     * @brief Auxiliary function that evaluates validity of Class Change Requests.
     * @param request Request that is being checked.
     * @param all_students, all_turmas Used to access the necessary data.
     * @returns -2 if the new class has maximum occupation; <br>
     *          -1 if the balance between the old class and the new class has been; <br>
     *          0 if there is schedule conflict between the new class and the classes Student is already enrolled in; <br>
     *          1 otherwise -> valid Request;
     * @see AllTurmas::classBalance()
     * @see ScheduleSlot::scheduleConflict()
     * @see processPending()
     * @see undoOneProcessed()
     * @note Time complexity: O(log n + log p + q*(log n + r*s)). <br>
     *       - where n is the number of Turma objects in this->turmas of the all_turmas object, p is the number of Student objects in this->students of the all_students object, q is the number of Curricular Units the student has enrolled in,
     *       r is the number of ScheduleSlot objects in one of the classes the student is enrolled in, s is the number of ScheduleSlot objects in the class the student wants to enroll in.
     */
    int checkRequestCc(Request& request, AllStudents& all_students, AllTurmas& all_turmas) const;


    /*!
     * @brief Function that inserts a Request into the pending queue.
     * @details Checks if the same request has been inserted before, and if it hasn't, inserts it.
     * @param new_request Request object to be inserted.
     * @note Time complexity: O(n).
     */
    void insertRequest(const Request& new_request);

    /*!
     * @brief Function that prints all Requests in the pending queue.
     * @note Time complexity: O(n).
     */
    void printPending() const;

    /*!
     * @brief Function that processes the pending Requests and prints a message reflecting their state.
     * @details Evaluates if the requests are valid, using the checkRequestUcE() and checkRequestCc() functions, and if they are, makes the necessary changes in the data structures, through the given parameters.
     * @param all_students, all_turmas Used to manipulate, as needed, the students' and classes' data, in order to store the changes.
     * @see AllStudents::getOneStudent()
     * @see AllTurmas::getOneTurma()
     * @see checkRequestUcE()
     * @see checkRequestCc()
     * @note Time complexity: <br>
     *       >> O(n) when processing a CU enroll, where n is the number of requests in the pending queue; <br>
     *       >> O(n*(p+q)) when processing a CU remove, where p is the number of Student objects in the Student's old class, and q the number of classes the student has already enrolled in; <br>
     *       >> O(n*r) when processing a Class Change, where r is the number of Student objects in the Student's old class;
     */
    void processPending(AllStudents& all_students, AllTurmas& all_turmas);

    /*!
     * @brief Function that removes the most recent pending Request from the queue.
     * @note Time complexity: O(n-1), where n is the number of requests in the pending queue.
     */
    void undoOnePending();

    /*!
     * @brief Function that removes all the pending Request objects from the queue.
     * @note Time complexity: O(1).
     */
    void undoAllPending();

    /*!
     * @brief Function that undoes the most recent processed Request and prints a message reflecting its state.
     * @details Evaluates if undoing the request is valid, using the checkRequestCc() function, and if it is, makes the necessary changes in the data structures, through the given parameters.
     * @param all_students, all_turmas Used to manipulate, as needed, the students' and classes' data, in order to store the changes.
     * @see AllStudents::getOneStudent()
     * @see AllTurmas::getOneTurma()
     * @see checkRequestCc()
     * @note Time complexity: <br>
     *       >> O(n) when undoing a CU enroll request, where n is the number of students in the class the student wants to leave from; <br>
     *       >> O(1) when undoing a CU remove request; <br>
     *       >> O(p) when undoing a Class Change request, where p is the number of students in the class the student wants to leave from;
     */
    void undoOneProcessed(AllStudents& all_students, AllTurmas& all_turmas);

    /*!
     * @brief Function that writes the changes back into the files.
     * @details The only file that changes through all the manipulation options is students_classes.csv. <br>
     *          Through the given parameter, the function accesses the all_students vector (where all the students are stored) and prints the necessary information to the .csv file.
     * @param all_students Used to manipulate, as needed, the students' data, in order to store the changes.
     * @note Time complexity: O(n*p), where n is the number of Student objects in this->students of the all_students object and p is the number of CUs each Student is enrolled in.
     */
    void saveProcessedRequests(const AllStudents& all_students);


};

#endif //AED_STORAGE_HPP

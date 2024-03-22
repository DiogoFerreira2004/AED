#ifndef AED_TURMA_HPP
#define AED_TURMA_HPP

#include "ScheduleSlot.hpp"
#include "Student.hpp"
#include <string>
#include <vector>


/// @brief Class for classes (Turmas).
/// @details Stores the information about a single class.
/// @see ScheduleSlot.hpp
/// @see Student.hpp
class Turma {
    /*!
     * @brief Teaches the "less than" operator on how to compare two Turma objects.
     * @details A Class object is "less than" another, if their CU code is lower. <br>
     *          If they have the same CU code, a Class object is lower if their class code is lower.
     * @param turma1, turma2 The two Turma objects.
     * @return true if turma1's CU code is lower or the CU code is the same and the class code is lower. <br>
     *         false otherwise.
     * @note Time complexity: O(1)
     */
    friend bool operator<(const Turma& turma1, const Turma& turma2);

private:
    /// @brief The code of the CU the class belongs to;
    string ucCode;
    /// @brief The class code;
    string turmaCode;
    /// @brief The vector with the class's schedule;
    /// @see ScheduleSlot.hpp
    vector<ScheduleSlot> schedule;
    /// @brief The vector with the students enrolled in the class;
    /// @see Student.hpp
    vector<Student> students;

public:
    /*!
     * @brief Default constructor of the Turma class.
     * @details Initializes the string member variables with empty strings and the vector member variables with placeholders.
     * @note Time complexity: O(1).
     */
    Turma();

    /*!
     * @brief Copy constructor of the Turma class.
     * @details Initializes a Turma object by copying each member variable of another Turma object.
     * @note Time complexity: O(1).
     */
    Turma(const Turma& turma);

    /*!
     * @brief Partially parametrized constructor of the Turma class.
     * @details Initializes the string member variables with empty strings. Initializes each of the vectors with a default object inside. <br>
     *          Leaves the insertion of more objects into the vector to addScheduleSlot() and addStudent().
     * @see ScheduleSlot.hpp
     * @see Student.hpp
     * @see addScheduleSlot()
     * @see addStudent()
     * @note Time complexity: O(1).
     */
    Turma(string& uc_code, string& turma_code);


    /*!
     * @brief Getter for the CU code.
     * @returns String with the class's CU code.
     */
    const string& getUcCode() const;

    /*!
     * @brief Getter for the class code.
     * @returns String with the class's code.
     */
    const string& getTurmaCode() const;

    /*!
     * @brief Getter for the class schedule.
     * @returns Vector with the class's ScheduleSlot objects.
     */
    vector<ScheduleSlot> getHorario() const;

    /*!
     * @brief Getter for the class's students.
     * @returns Value of vector with the class's Students.
     */
    vector<Student> getStudents() const;

    /*!
     * @brief Getter for the class's students.
     * @returns Modifiable reference to the vector with the class's Students.
     */
    vector<Student>& getStudents();

    /*!
     * @brief Getter for the number of students in the class.
     * @returns Size of the vector with the class's Students.
     */
    size_t getNumStudents() const;


    /*!
     * @brief Inserts a ScheduleSlot object into the schedule member variable.
     * @details If the first element of the schedule vector has default values, it means that the vector only got initialized. The values of that element are changed to the values in the argument and it becomes a valid ScheduleSlot object. <br>
     *          Else, the ScheduleSlot in the argument is inserted into the vector.
     * @param slot ScheduleSlot object to insert into the schedule member variable.
     * @note Time complexity: O(1).
     */
    void addScheduleSlot(const ScheduleSlot& slot);

    /*!
     * @brief Inserts a Student object into the students member variable.
     * @details If the first element of the students vector has default values, it means that the vector only got initialized. The values of that element are changed to the values in the argument and it becomes a valid Student object. <br>
     *          Else, the Student in the argument is inserted into the vector.
     * @param student Student object to insert into the students member variable.
     * @note Time complexity: O(1).
     */
    void addStudent(const Student& student);


    /*!
     * @brief Function that prints the class's schedule.
     * @see sortHorario()
     * @note Time complexity: O(n*log n) + O(n), where n is the number of ScheduleSlot objects in this->schedule.
     */
    void printHorario() const;

    /*!
     * @brief Function that prints the class's students.
     * @see sortStudents()
     * @note Time complexity: O(n*log n) + O(n), where n is the number of Student objects in this->students.
     */
    void printStudents() const;


    /*!
     * @brief Comparison function for sorting a vector of ScheduleSlot objects.
     * @param slot1, slot2 the two ScheduleSlot objects that are compared while sorting a vector.
     * @return True if: <br>
     *          - slot1's weekday comes before slot2's; <br>
     *          - if they are on the same weekday, slot1 has the earlier start time; <br>
     *         False otherwise.
     * @see ScheduleSlot::dayValue()
     * @note Time complexity: O(1).
     */
    static bool sortHorario(const ScheduleSlot& slot1, const ScheduleSlot& slot2);

    /*!
     * @brief Comparison function for sorting a vector of Students.
     * @param student1, student2 the two Student objects that are compared while sorting a vector.
     * @return True if: <br>
     *          - student1's name is lexicographically lower than student2's; <br>
     *          - if they have the same name, student1 has a lower student code;<br>
     *         False otherwise.
     * @see ScheduleSlot::dayValue()
     * @note Time complexity: O(1).
     */
    static bool sortStudents(const Student& student1, const Student& student2);
};

#endif //AED_TURMA_HPP

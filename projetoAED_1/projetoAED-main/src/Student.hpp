#ifndef AED_STUDENT_HPP
#define AED_STUDENT_HPP

#include <string>
#include <vector>
using std::vector, std::pair, std::string;


/// @brief Class for students.
/// @details Stores that information about a single student.
class Student {
    /*!
     * @brief Teaches the "less than" operator on how to compare two Student objects.
     * @details A Student object is "less than" another, if the student code (numeric) is lower.
     * @param student1, student2 The two Student objects.
     * @return true if the student1's code is lower. False otherwise.
     * @note Time complexity: O(1).
     */
    friend bool operator<(const Student& student1, const Student& student2);

private:
    /// @brief The student's name;
    string name;
    /// @brief The student's code;
    string code;
    /// @brief The pairs with CU codes and classes codes represents;
    vector<pair<string,string>> ucClasses;

public:
    /*!
     * @brief Default constructor of the Student class.
     * @details Initializes the member variables with empty strings.
     * @note Time complexity: O(1).
     */
    Student();

    /*!
     * @brief Copy constructor of the Student class.
     * @details Initializes a Student object by copying each member variable of another Student object.
     * @param student The other Student object.
     * @note Time complexity: O(1).
     */
    Student(Student const &student);

    /*!
     * @brief Parametrized constructor of the Student class.
     * @details Initializes all member variables with their respective parameters.
     * @param name, student_code, uc_classes Const references to types corresponding to the member variables of a Student object.
     * @note Time complexity: O(1).
     */
    Student(const string& name, const string& student_code, const vector<pair<string,string>>& uc_classes);


    /*!
     * @brief Getter for the student code.
     * @returns String with the student code.
     */
    const string& getCode() const;

    /*!
     * @brief Getter for the student's name.
     * @returns String with the student's name.
     */
    const string& getName() const;

    /*!
     * @brief Getter for the vector of pairs.
     * @returns Value of the vector of pairs with CU codes and class codes.
     */
    vector<pair<string,string>> getUcClasses() const;

    /*!
     * @brief Getter for the vector of pairs.
     * @returns Modifiable reference to the vector of pairs with CU codes and class codes.
     */
    vector<pair<string,string>>& getUcClasses();


    /*!
     * @brief Sets the value of the name member variable.
     * @param name String containing the new student name.
     */
    void setName(const string& name);

    /*!
     * @brief Sets the value of the code member variable.
     * @param student_code String containing the new student code.
     */
    void setCode(const string& student_code);

    /*!
     * @brief Sets the value of the uc_classes member variable.
     * @param uc_classes Vector containing the pairs of CU and class codes.
     */
    void setUcClasses(const vector<pair<string,string>>& uc_classes);


    /*!
     * @brief Adds a pair of CU and class codes to the ucClasses vector.
     * @param uc_code, class_code Codes to create the new pair.
     */
    void addUcClass(const string& uc_code, const string& class_code);

    /*!
     * @brief Switches class codes in an existing pair inside the ucClasses vector.
     * @details Looks for the pair with the given uc_code parameter and switches the class code for the new class_code parameter.
     * @param uc_code, class_code CU code and the new class code.
     * @note O(n), where n is the number of CUs a Student is enrolled in. <br>
     *       Notice: p is never higher than 7, because a student cannot be unrolled in more than 7 CUs at the same time.
     */
    void changeClasses(const string& uc_code, const string& class_code);
};

#endif //AED_STUDENT_HPP

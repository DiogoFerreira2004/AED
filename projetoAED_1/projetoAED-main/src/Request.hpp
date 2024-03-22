#ifndef AED_REQUESTS_HPP
#define AED_REQUESTS_HPP

#include <string>
using std::string;


/// @brief Class for requests.
/// @details They provide the necessary information to process and store Class/Curricular Unit change requests.
class Request {
private:
    /// @brief Code of the student that made the request;
    string studentCode;
    /// @brief Code of the CU the student wants to enroll in, remove, or change classes in;
    string uc;
    /// @brief Code of the class he wants to leave from;
    string oldTurma;
    /// @brief Code of class he wants to enroll in;
    string newTurma;

public:
    /*!
     * @brief Default constructor of the Request class.
     * @details Initializes all member variables with an empty string.
     * @note Time complexity: O(1).
     */
    Request();

    /*!
     * @brief Parametrized constructor of the Request class.
     * @details Initializes all member variables with their respective parameters.
     * @param student_code, uc, old_turma, new_turma Const references to strings corresponding to the member variables of a Request object.
     * @note Time complexity: O(1).
     */
    Request(const string &student_code, const string &uc, const string &old_turma, const string &new_turma);


    /*!
     * @brief Getter for the student's code in the request.
     * @return string with the student's code.
     */
    const string &getStudentCode() const;

    /*!
     * @brief Getter for the CU in the request.
     * @return string with the CU's code.
     */
    const string &getUc() const;

    /*!
     * @brief Getter for the old class.
     * @return string with the old class's code.
     */
    const string &getOldTurma() const;

    /*!
     * @brief Getter for the new class.
     * @return string with the new class's code.
     */
    const string &getNewTurma() const;


    /*!
     * @brief Sets the value of the studentCode member variable.
     * @param student_code String containing the new student code.
     */
    void setStudentCode(const string &student_code);

    /*!
     * @brief Sets the value of the uc member variable.
     * @param uc_ String containing new the uc code.
     */
    void setUc(const string &uc_);

    /*!
     * @brief Sets value of the oldTurma member variable.
     * @param old_turma String containing the new code for the old class.
     */
    void setOldTurma(const string &old_turma);

    /*!
     * @brief Sets the value of the newTurma member variable.
     * @param new_turma String containing the new code for the new class.
     */
    void setNewTurma(const string &new_turma);

};

#endif //AED_REQUESTS_HPP

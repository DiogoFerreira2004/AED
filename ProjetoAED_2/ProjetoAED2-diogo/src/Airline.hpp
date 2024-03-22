#ifndef AED2_AIRLINES_HPP
#define AED2_AIRLINES_HPP

#include <string>

using namespace std;

/// @brief Class for airlines.
/// @details Stores the information about a single airline.
class Airline {
private:
    /// @brief The airline's 3 uppercase-letter code;
    string code;
    /// @brief The airline's full name;
    string name;
    /// @brief The airline's call sign (usually an abbreviation); Can be blank (indicated by an underscore '_')
    string callsign;
    /// @brief The airline's country of origin
    string country;

public:
    /*!
     * @brief Default constructor of the Airline class.
     * @details Initializes the member variables with empty strings.
     * @note Time complexity: O(1).
     */
    Airline();
    /*!
     * @brief Parametrized constructor of the Airline class.
     * @details Initializes all member variables with their respective parameters.
     * @param code, name, callsign, country Const references to strings corresponding to the member variables of an Airline object
     * @note Time complexity: O(1).
     */
    Airline(const string& code, const string& name, const string& callsign, const string& country);


    /*!
     * @brief Getter for the airline's code.
     * @returns String with the airline code.
     */
    const string& getCode() const;

    /*!
     * @brief Getter for the airline's name.
     * @returns String with the airline name.
     */
    const string& getName() const;

    /*!
     * @brief Getter for the airline's call sign.
     * @returns String with the airline call sign.
     */
    const string& getCallsign() const;

    /*!
     * @brief Getter for the airline's country of origin.
     * @returns String with the airline's country.
     */
    const string& getCountry() const;


    /*!
     * @brief Sets the value of the code member variable.
     * @param code String containing the new airline code.
     */
    void setCode(const string& code);

    /*!
     * @brief Sets the value of the name member variable.
     * @param name String containing the new airline name.
     */
    void setName(const string& name);

    /*!
     * @brief Sets the value of callsign name member variable.
     * @param callsign String containing the new airline callsign.
     */
    void setCallsign(const string& callsign);

    /*!
     * @brief Sets the value of the name member variable.
     * @param country String containing the new airline country.
     */
    void setCountry(const string& country);
};


#endif //AED2_AIRLINES_HPP
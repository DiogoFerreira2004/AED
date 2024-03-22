#ifndef AED2_AIRPORT_HPP
#define AED2_AIRPORT_HPP

#include <string>

using namespace std;

/// @brief Class for airports.
/// @details Stores that information about a single airport.
class Airport {
private:
    /// @brief The airport's 3 uppercase-letter code;
    string code;
    /// @brief The airport's name;
    string name;
    /// @brief The city the airport is in;
    string city;
    /// @brief The country the airport is in;
    string country;
    /// @brief The airport's latitude;
    float latitude;
    /// @brief The airport's longitude;
    float longitude;

public:
    /*!
     * @brief Default constructor of the Airport class.
     * @details Initializes the string member variables with empty strings and the float member variables with the value 0.
     * @note Time complexity: O(1).
     */
    Airport();

    /*!
     * @brief Parameterized constructor of the Airport class.
     * @details Initializes all member variables with their respective parameters.
     * @param code, name, city, country Const string references corresponding to the string member variables of an Airport object.
     * @param latitude, longitude Float values corresponding to the float member variables of an Airport object
     * @note Time complexity: O(1).
     */
    Airport(const string& code, const string& name, const string& city, const string& country, float latitude, float longitude);


    /*!
     * @brief Getter for the airport's code.
     * @returns String with the airport code.
     */
    const string& getCode() const;

    /*!
     * @brief Getter for the airport's name.
     * @returns String with the airport code.
     */
    const string& getName() const;

    /*!
     * @brief Getter for the airport's city.
     * @returns String with the name of the city where the airport is in.
     */
    const string& getCity() const;

    /*!
     * @brief Getter for the airport's country.
     * @returns String with the name of the country where the airport is in.
     */
    const string& getCountry() const;

    /*!
     * @brief Getter for the airport's latitude.
     * @returns Float with the airport's latitude.
     */
    float getLatitude() const;

    /*!
     * @brief Getter for the airport's longitude.
     * @returns Float with the airport's longitude.
     */
    float getLongitude() const;


    /*!
     * @brief Sets the value of the code member variable.
     * @param code String containing the new airport code.
     */
    void setCode(const string& code);

    /*!
     * @brief Sets the value of the name member variable.
     * @param name String containing the new airport name.
     */
    void setName(const string& name);

    /*!
     * @brief Sets the value of the city member variable.
     * @param city String containing the name of the city the new airport is in.
     */
    void setCity(const string& city);

    /*!
     * @brief Sets the value of the country member variable.
     * @param country String containing the name of the country the new airport is in.
     */
    void setCountry(const string& country);

    /*!
     * @brief Sets the value of the latitude member variable.
     * @param latitude String containing the new airport latitude.
     */
    void setLatitude(float latitude);

    /*!
     * @brief Sets the value of the longitude member variable.
     * @param longitude String containing the new airport longitude.
     */
    void setLongitude(float longitude);
};

#endif //AED2_AIRPORT_HPP
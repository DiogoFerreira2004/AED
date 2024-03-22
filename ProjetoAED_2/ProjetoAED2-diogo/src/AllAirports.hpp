#ifndef AED2_ALLAIRPORTS_HPP
#define AED2_ALLAIRPORTS_HPP


#include <unordered_set>
#include <vector>
#include "Airport.hpp"


/// @struct airportHash
/// @brief Hash function for the airports member variable of the AllAirports class.
/// @details Used to compute a hash value based on the airport code for inserting and retrieving elements from the unordered_set.
/// @note This is the implementation of a well-known hash function for strings, known as the djb2 hash function.
struct airportHash {
    /*!
     * @brief Overloading of operator() used by unordered_set for computing the hash value.
     * @param a Airport object for which the hash value is calculated.
     * @return Calculated hash value.
     */
    size_t operator()(const Airport& a) const {
        const string& code = a.getCode();
        size_t hashVal = 5381;

        for (char c : code) {
            hashVal = 33*hashVal + static_cast<size_t>(c);
        }

        return hashVal;
    }
};

/// @struct airportEquality
/// @brief Equality function for the airports member variable of the AllAirports class.
/// @details Used to check if two Airport objects are equal based on their airport codes.
struct airportEquality {
    /*!
     * @brief Overloading of operator() used by unordered_set for checking equality between two Airport objects.
     * @param a1 First Airport object for comparison.
     * @param a2 Second Airport object for comparison.
     * @return True if the airport codes of the two objects are equal, false otherwise.
     */
    bool operator()(const Airport& a1, const Airport& a2) const {
        return a1.getCode() == a2.getCode();
    }
};


/// @brief Class that stores and manipulates all the Airport objects as a whole.
/// @details Uses an unordered_set (Hash Table implementation) to facilitate the manipulation of the stored data.
/// @see Airport.hpp
class AllAirports {
private:
    /// @brief Hash table data structure that stores all the airports.
    unordered_set<Airport, airportHash, airportEquality> airports;
public:
    /*!
     * @brief Default constructor of the AllAirports class.
     * @details Initializes the airports member variable with an empty placeholder.
     * @note Time complexity: O(1).
     */
    AllAirports();

    /*!
     * @brief Parameterized constructor of the AllAirports class.
     * @details Initializes the hash table with the required data, by reading it from a file.
     * @param file String containing the path to the .csv file.
     * @note Time complexity: O(n), where n is the number lines in the airports.csv file.
     */
    AllAirports(const string& file);


    /*!
     * @brief Add an airport to the hash table.
     * @param a Airline object to be added.
     */
    void addAirport(const Airport& a);


    /*!
     * @brief Get the number of airports in the hash table.
     * @return Number of airlines in the hash table.
     */
    size_t numAirports() const;


    /*!
     * @brief Get the name of an airport based on its code.
     * @param airportCode Code of the airport.
     * @return Name of the airport if found, an empty string otherwise.
     */
    string nameOfCode(const string& airportCode) const;

    /*!
     * @brief Get the name of the city an airport is in based on its code.
     * @param airportCode Code of the airport.
     * @return Name of the city the airport is in if found, an empty string otherwise.
     */
    string cityOfCode(const string& airportCode) const;

    /*!
     * @brief Get the name of the country an airport is in based on its code.
     * @param airportCode Code of the airport.
     * @return Name of the country the airport is in if found, an empty string otherwise.
     */
    string countryOfCode(const string& airportCode) const;


    /*!
     * @brief Get a vector of airport codes belonging to a specific city.
     * @param city Name of the city.
     * @return Vector of airport codes located in the specified city.
     * @note Time complexity: O(n), where n is the number of elements in the airports member variable.
     */
    vector<string> airportsPerCity(const string& city) const;


    /*!
     * @brief Getter for the airports member variable.
     * @returns Const reference for the hash table with Airport objects.
     */
    const unordered_set<Airport, airportHash, airportEquality>& getAirports() const;
};


#endif //AED2_ALLAIRPORTS_HPP
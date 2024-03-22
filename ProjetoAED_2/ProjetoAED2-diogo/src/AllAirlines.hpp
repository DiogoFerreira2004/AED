#ifndef AED2_ALLAIRLINES_HPP
#define AED2_ALLAIRLINES_HPP


#include <unordered_set>
#include "Airline.hpp"


/// @struct airlineHash
/// @brief Hash function for the airlines member variable of the AllAirlines class.
/// @details Used to compute a hash value based on the airline code for inserting and retrieving elements from the unordered_set.
/// @note This is the implementation of a well-known hash function for strings, known as the djb2 hash function.
struct airlineHash {
    /*!
     * @brief Overloading of operator() used by unordered_set for computing the hash value.
     * @param a Airline object for which the hash value is calculated.
     * @return Calculated hash value.
     */
    size_t operator()(const Airline& a) const {
        const string& code = a.getCode();
        size_t hashVal = 5381;

        for (char c : code) {
            hashVal = 33*hashVal + static_cast<size_t>(c);
        }

        return hashVal;
    }
};

/// @struct airlineEquality
/// @brief Equality function for the airlines member variable of the AllAirlines class.
/// @details Used to check if two Airline objects are equal based on their airline codes.
struct airlineEquality {
    /*!
     * @brief Overloading of operator() used by unordered_set for checking equality between two Airline objects.
     * @param a1 First Airline object for comparison.
     * @param a2 Second Airline object for comparison.
     * @return True if the airline codes of the two objects are equal, false otherwise.
     */
    bool operator()(const Airline& a1, const Airline& a2) const {
        return a1.getCode() == a2.getCode();
    }
};


/// @brief Class that stores and manipulates all the Airline objects as a whole.
/// @details Uses an unordered_set (Hash Table implementation) to facilitate the manipulation of the stored data.
/// @see Airline.hpp
class AllAirlines {
private:
    /// @brief Hash table data structure that stores all the airlines.
    unordered_set<Airline, airlineHash, airlineEquality> airlines;
public:
    /*!
     * @brief Default constructor of the AllAirlines class.
     * @details Initializes the airlines member variable with an empty placeholder.
     * @note Time complexity: O(1).
     */
    AllAirlines();

    /*!
     * @brief Parameterized constructor of the AllAirlines class.
     * @details Initializes the hash table with the required data, by reading it from a file.
     * @param file String containing the path to the .csv file.
     * @note Time complexity: O(n), where n is the number lines in the airlines.csv file.
     */
    AllAirlines(const string& file);


    /*!
     * @brief Add an airline to the hash table.
     * @param a Airline object to be added.
     */
    void addAirline(const Airline& a);


    /*!
     * @brief Get the number of airlines in the hash table.
     * @return Number of airlines in the hash table.
     */
    size_t numAirlines();


    /*!
     * @brief Get the name of an airline based on its code.
     * @param airlineCode Code of the airline.
     * @return Name of the airline if found, an empty string otherwise.
     */
    string nameOfCode(const string& airlineCode) const;


    /*!
     * @brief Getter for the airlines member variable.
     * @returns Const reference for the hash table with Airline objects.
     */
    const unordered_set<Airline, airlineHash, airlineEquality>& getAirlines() const;
};


#endif //AED2_ALLAIRLINES_HPP
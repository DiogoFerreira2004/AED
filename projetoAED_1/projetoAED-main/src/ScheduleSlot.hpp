#ifndef AED_SCHEDULESLOT_HPP
#define AED_SCHEDULESLOT_HPP

#include <string>
#include <vector>
using std::string, std::vector;


/// @brief Class for slots.
/// @details They make up the the students'/classes' schedules.
class ScheduleSlot {
private:
    /// @brief Weekday of the class's schedule slot;
    string weekDay;
    /// @brief Type of the class (T = Theoretical Class, TP = Recitation Class (Teórico-Prática), PL = Laboratory Practice);
    string type;
    /// @brief Start time of the class (as a float, 9h30m is represented as 9,5);
    float begin;
    /// @brief End time of the class (as a float, 9h30m is represented as 9,5);
    float end;

public:
    /*!
     * @brief Default constructor of the ScheduleSlot class.
     * @details Initializes all the member variables with meaningless values in the context of this tool (empty strings for the weekDay and type, -1 for the begin and end times).
     * @note Time complexity: O(1).
     */
    ScheduleSlot();

    /*!
     * @brief Copy constructor of the ScheduleSlot class.
     * @details Initializes a ScheduleSlot object by copying each member variable of another ScheduleSlot object.
     * @param schedule_slot The other ScheduleSlot object.
     * @note Time complexity: O(1).
     */
    ScheduleSlot(const ScheduleSlot& schedule_slot);

    /*!
     * @brief Parametrized constructor of the ScheduleSlot class.
     * @details Initializes all member variables with their respective parameters. End time (end) is the result of sum between the start time and duration of the class.
     * @param week_day, begin, duration, type Const references to types corresponding to the member variables of a ScheduleSlot object.
     * @note Time complexity: O(1).
     */
    ScheduleSlot(const string& week_day, const string& type, const float& begin, const float& duration);


    /*!
     * @brief Getter for the class's weekDay.
     * @returns string with the week day.
     */
    const string& getWeekDay() const;

    /*!
     * @brief Getter for the class's type.
     * @returns string with type of class.
     */
    const string &getType() const;

    /*!
     * @brief Getter for the class's beginning.
     * @returns float with the start time of the class.
     */
    float getBegin() const;

    /*!
     * @brief Getter for the class's ending.
     * @returns float with the end time of the class.
     */
    float getEnd() const;


    /*!
     * @brief Sets the value of the weekDay member variable.
     * @param week_day String containing the class's week day.
     */
    void setWeekDay(const string& week_day);

    /*!
     * @brief Sets the value of the type member variable.
     * @param type String containing the class's type.
     */
    void setType(const string &type);

    /*!
     * @brief Sets the studentCode member variable to a different value.
     * @param begin Float containing the start time of a class.
     */
    void setBegin(float begin);

    /*!
     * @brief Sets the studentCode member variable to a different value.
     * @param end Float containing the end time of a class.
     */
    void setEnd(float end);

    /*!
     * @brief Transforms a string with a weekDay (Monday, Tuesday, ...) into an int (from 0 to 6).
     * @details Each weekday is mapped to an int in a variable inside the function definition.
     * @return Corresponding int to the weekday that called the function.
     * @note Time complexity: O(1).
     */
    int dayValue() const;

    /*!
     * @brief Check if the ScheduleSlot object that is calling this function overlaps with another existing ScheduleSlot.
     * @details If the slots have different weekDays, they doesn't overlap. <br>
     *          If the start of a slot is after the ending of the other, they don't overlap. <br>
     *          If one of the slots' class type is "theoretical class", they don't overlap. <br>
     * @param slot Const reference to the other ScheduleSlot.
     * @return true if overlaps; false if it doesn't.
     * @note Time complexity: O(1).
     */
    bool overlaps(const ScheduleSlot &slot) const;

    /*!
     * @brief Calls overlaps() function over every combination of slots between 2 vectors.
     * @details Each weekday is mapped to an int in a variable inside the function definition.
     * @param v1, v2 Two vectors containing ScheduleSlot objects, where none of the slots can overlap with each other.
     * @return true if two slots overlap; false otherwise.
     * @see overlaps()
     * @note Time complexity: O(n*p), where n is the number of ScheduleSlot objects in a specific class, and p the number of ScheduleSlot objects in another class.
     */
    static bool scheduleConflict(const vector<ScheduleSlot>& v1, const vector<ScheduleSlot>& v2);
};

#endif //AED_SCHEDULESLOT_HPP

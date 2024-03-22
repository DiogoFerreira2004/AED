#include "ScheduleSlot.hpp"
#include <map>
using std::map;

ScheduleSlot::ScheduleSlot() {
    this->weekDay = "";
    this->begin = -1;
    this->end = -1;
    this->type = "";
}
ScheduleSlot::ScheduleSlot(const ScheduleSlot &schedule_slot) {
    this->weekDay = schedule_slot.getWeekDay();
    this->begin = schedule_slot.getBegin();
    this->end = schedule_slot.getEnd();
    this->type = schedule_slot.getType();
}
ScheduleSlot::ScheduleSlot(const string &weekDay, const string &type, const float &begin, const float &duration) {
    this->weekDay = weekDay;
    this->type = type;
    this->begin = begin;
    this->end = begin+duration;
}

// Getters
const string& ScheduleSlot::getWeekDay() const {
    return weekDay;
}
float ScheduleSlot::getBegin() const {
    return begin;
}
float ScheduleSlot::getEnd() const {
    return end;
}
const string &ScheduleSlot::getType() const {
    return type;
}

// Setters
void ScheduleSlot::setWeekDay(const string &weekDay_) {
    this->weekDay = weekDay_;
}
void ScheduleSlot::setType(const string &type_) {
    this->type = type_;
}
void ScheduleSlot::setBegin(float begin_) {
    this->begin = begin_;
}
void ScheduleSlot::setEnd(float end_) {
    this->end = end_;
}


int ScheduleSlot::dayValue() const {
    map<string, int> day_value = { {"Monday", 0}, {"Tuesday", 1}, {"Wednesday", 2},
                                   {"Thursday", 3 },  {"Friday", 4}, {"Saturday", 5},
                                   {"Sunday", 6} };
    return day_value[this->weekDay];
}

bool ScheduleSlot::overlaps(const ScheduleSlot &slot) const{
    if (this->getWeekDay() != slot.getWeekDay()) return false;
    if (this->getBegin() >= slot.getEnd() or this->getEnd() <= slot.getBegin()) return false;
    if (this->getType() == "T" or slot.getType() == "T") return false;
    return true;
}

bool ScheduleSlot::scheduleConflict(const vector<ScheduleSlot> &v1, const vector<ScheduleSlot> &v2) {
    for (const ScheduleSlot& slot1 : v1) { // O(n), n ScheduleSlots in a specific class
        for (const ScheduleSlot& slot2 : v2) { // O(p), p ScheduleSlots in another class
            if (slot2.overlaps(slot1)) return true;
        }
    }
    return false;
}

#include "date.hpp"

// implementation order does not matter

Date::Date(int day, int month, int year) {
    setDay(day);
    setMonth(month);
    setYear(year);
}

int Date::Day() const noexcept { return day_; }

int Date::Month() const noexcept { return month_; }

int Date::Year() const noexcept { return year_; }

void Date::setDay(int day) {
    validateDay(day);
    day_ = day;
}

void Date::setMonth(int month) {
    validateMonth(month);
    month_ = month;
}

void Date::setYear(int year) { year_ = year; }

void Date::validateDay(int day) const {
    if (day < 1 || day > 31) {
        throw std::out_of_range("Day value must be between 1 and 31 inclusive.");
    }
}

void Date::validateMonth(int month) const {
    if (month < 1 || month > 12) {
        throw std::out_of_range("Month value must be between 1 and 12 inclusive.");
    }
}

// ... Similarly for month and year if needed
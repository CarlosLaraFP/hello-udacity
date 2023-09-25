#pragma once
//#ifndef DATE_H
//#define DATE_H

#include <stdexcept>

class Date {
public:
    Date(int day, int month, int year);
    
    int Day() const noexcept;
    int Month() const noexcept;
    int Year() const noexcept;

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

private:
    int day_;
    int month_;
    int year_;
    //
    void validateDay(int day) const;
    void validateMonth(int month) const;
};

//#endif // DATE_H
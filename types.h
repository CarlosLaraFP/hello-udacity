#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>
#include <string>

enum class TileState {
    Free, 
    Blocked,
    Closed,
    Path,
    Start,
    Finish
};

struct Coordinate {
    int x;
    int y;
};

struct Node {
    Coordinate c;
    int g;
    int h;
};

class Student {
public:
    Student(std::string name, int grade, float gpa) {
        setName(name);
        setGrade(grade);
        setGpa(gpa);
    }
    
    void setName(std::string value) {
        name_ = value;
    }
    
    void setGrade(int value) {
        if (value < 0 || value > 12) throw std::invalid_argument("Grade must be between 0 and 12");
        grade_ = value;
    }
    
    void setGpa(float value) {
        if (value < 0.0 || value > 4.0) throw std::invalid_argument("GPA must be between 0.0 and 4.0");
        gpa_ = value;
    }
    
    std::string Name() const noexcept { return name_; }
    int Grade() const noexcept { return grade_; }
    float GPA() const noexcept { return gpa_; }

private:
    std::string name_;
    int grade_;
    float gpa_;
};

#endif // TYPES_H
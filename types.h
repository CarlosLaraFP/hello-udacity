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

class Vehicle {
public:
    Vehicle(int wheels, const std::string& color, bool flies) : wheels_{wheels}, color_{color}, flies_{flies} {}
    
    virtual void Print() const
    {
        std::cout << "This " << color_ << " vehicle has " << wheels_ << " wheels!" << std::endl;
    }
    
private:
    int wheels_;
    std::string color_;

protected:
    bool flies_;
};

class Car : public Vehicle {
public:
    bool sunroof {false};
};

class Bicycle : public Vehicle {
public:
    bool kickstand {true};
};

class Scooter : private Vehicle {
public:
    Scooter(int w, const std::string& c, bool f) : Vehicle(w, c, f) {};
    
    void Print() const override
    {
        Vehicle::Print();
        
        if (flies_) std::cout << "And it flies!" << std::endl;
        else std::cout << "But it does not fly yet." << std::endl;
    }
};

class Square {
public:
    Square(int side) : side_{side} {};
private:
    int side_;
    friend class Rectangle;
};

class Rectangle {
public:
    Rectangle(const Square& square) : width_{square.side_}, height_{square.side_} {}
    
    int Area() const noexcept {
        return width_ * height_;
    }
private:
    int width_;
    int height_;
};

#endif // TYPES_H
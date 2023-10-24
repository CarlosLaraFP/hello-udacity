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

class Point {
public:
    Point(float x, float y) : x_{x}, y_{y} {}
    
    Point operator+(const Point& point) { 
        auto new_x = x_ + point.X();
        auto new_y = y_ + point.Y();
        return Point(new_x, new_y);
    }
    
    float X() const noexcept { return x_; }
    float Y() const noexcept { return y_; }
    
private:
    float x_;
    float y_;
};

class MyMovableClass
{
private:
    int _size;
    int* _data;

public:
    MyMovableClass(size_t size) // 0 : constructor
    {
        _size = size;
        _data = new int[_size];
        std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
    }

    ~MyMovableClass() // 1 : destructor
    {
        std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
        delete[] _data;
    }
    
    MyMovableClass(MyMovableClass&& source) // 2 : move constructor
    {
        std::cout << "MOVING (constructor) instance " << &source << " to instance " << this << std::endl;
        _data = source._data; // makes a copy of the pointer to the existing memory address
        _size = source._size; // regular copy
        source._data = nullptr; // ensures there is only 1 pointer in this new instance
        source._size = 0; // ?
        // source destructor is called at the end of this scope
        // any references to source in the caller scope are now invalid
    }
    
    MyMovableClass(const MyMovableClass& source) // 3 : copy constructor
    {
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data;
        std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }
    
    MyMovableClass& operator=(const MyMovableClass& source) // 4 : copy assignment operator
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
        if (this == &source)
            return *this;
        delete[] _data;
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data;
        return *this;
    }
};

#endif // TYPES_H
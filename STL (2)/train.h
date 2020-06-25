#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<set>

class Train
{
private:
    std::string destination;
    std::string number;
    bool express;
    size_t hours;
    size_t minutes;
public:
    Train() = default;
    ~Train() = default;
    
    std::string getDestination() const { return destination; }
    std::string getNumber() const { return number; }
    bool getExpress() const { return express; }
    size_t getHours() const { return hours; }
    size_t getMinutes() const { return minutes; }
    const bool operator<(const Train&) const;
    Train& operator=(std::string str)
    {
        destination = str;
        return *this;
    }
    
    friend std::istream& operator>>(std::istream&, Train&);
    friend std::ostream& operator<<(std::ostream&, const Train&);
};

std::istream& operator>>(std::istream& fin, Train& train)
{
    fin >> train.destination;
    fin >> train.number;
    fin >> train.express;
    fin >> train.hours;
    fin >> train.minutes;
    return fin;
}

std::ostream& operator<<(std::ostream& out, const Train& train)
{
    std::cout << std::left
    << std::setw(11) << train.getDestination()
    << std::setw(7) << train.getNumber();
    
    if (train.getExpress())
    {
        out << std::left << std::setw(7) << "yes";
        
    }
    else
    {
        out << std::left << std::setw(7) << "no";
    }
    
    out << std::right << std::setw(2) << train.getHours() << ":" << std::setw(2) << train.getMinutes() << "\n";
    return out;
}

bool const Train::operator<(const Train& train) const
{
    if (getHours() < train.getHours())
    {
        return true;
    }
    else if(getHours() == train.getHours())
    {
        return getMinutes() < train.getMinutes() ? true : false;
    }
    else
    {
        return false;
    }
}

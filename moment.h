#ifndef MOMENT_H
#define MOMENT_H

#include <iostream>
#include <chrono>

using namespace std;

class Moment
{
protected:
    size_t _hours;
    size_t _min;
    size_t _sec;
    size_t _milliseconds;
    size_t _microseconds;

public:
    Moment();
    Moment(size_t hours, size_t min, size_t sec, size_t milli, size_t micro);
    Moment(const Moment& t);

    size_t get_hours() const;
    size_t get_min() const;
    size_t get_sec() const;
    size_t get_milliseconds() const;
    size_t get_microseconds() const;

    double to_hours();
    double to_min();
    double to_sec();
    double to_milliseconds();
    double to_microseconds();

    bool operator== (Moment &t);
    bool operator!= (Moment& t);
    bool operator> (Moment& t);
    bool operator< (Moment& t);
    bool operator>= (Moment& t);
    bool operator<= (Moment& t);
    Moment operator+ (const Moment& t);
    Moment operator- (const Moment& t);
    Moment& operator= (const Moment& t);

    //add or substract a certain time to the moment
    void increment(size_t hours, size_t min, size_t sec, size_t milli, size_t micro);
    void decrement(size_t hours, size_t min, size_t sec, size_t milli, size_t micro);
    string  toString() const;
};

#endif // MOMENT_H

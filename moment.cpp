#include "moment.h"

Moment::Moment()
    : _hours(0)
    , _min(0)
    , _sec(0)
    , _milliseconds(0)
    , _microseconds(0)
{}

Moment::Moment(size_t hours, size_t min, size_t sec, size_t milli, size_t micro)
{
    size_t temp = 0;
    _microseconds = micro % 1000;
    temp = micro / 1000;
    _milliseconds = temp + (milli % 1000);
    temp = milli / 1000;
    _sec = temp + (sec % 60);
    temp = sec / 60;
    _min = temp + (min % 60);
    temp = min / 60;
    _hours = temp + hours;
}

Moment::Moment(const Moment &t)
{
    this->_hours = t.get_hours();
    this->_min = t.get_min();
    this->_sec = t.get_sec();
    this->_milliseconds = t.get_milliseconds();
    this->_microseconds = t.get_microseconds();
}

//===============ACCESSEURS ===================

size_t Moment::get_hours() const
{ return _hours; }

size_t Moment::get_min() const
{ return _min; }

size_t Moment::get_sec() const
{ return _sec; }

size_t Moment::get_milliseconds() const
{ return _milliseconds; }

size_t Moment::get_microseconds() const
{ return _microseconds; }

//=====================CONVERTIONS==================

double Moment::to_hours()
// les millisecondes et les microsecondes sont négligeables
{
    double value = this->_hours;
    value += (double)(this->_min / 60);
    value += (double)(this->_sec / 3600);
    return value;
}

double Moment::to_min()
// les microsecondes sont négligeables
{
    double value = _min;
    value += (double)(this->_hours * 60);
    value += (double)(this->_sec / 60);
    value += (double)(this->_milliseconds / 60000);
    return value;
}

double Moment::to_sec()
{
    double value = this->_sec;
    value += (double)(this->_hours * 3600);
    value += (double)(this->_min * 60);
    value += (double)(this->_milliseconds / 1000);
    value += (double)(this->_microseconds / 1000000);
    return value;
}

double Moment::to_milliseconds()
{
    double value = this->_milliseconds;
    value += (double)(this->_hours * 3600000);
    value += (double)(this->_min * 60000);
    value += (double)(this->_sec * 1000);
    value += (double)(this->_microseconds / 1000);
    return value;
}

double Moment::to_microseconds()
{
    double value = this->_microseconds;
    value += (double)(this->_hours * 3600000000);
    value += (double)(this->_min * 60000000);
    value += (double)(this->_sec * 1000000);
    value += (double)(this->_milliseconds * 1000);
    return value;
}

//===================OPERATEURS======================

bool Moment::operator ==(Moment& t)
{
    return(this->to_microseconds() == t.to_microseconds() ? true : false);
}

bool Moment::operator !=(Moment& t)
{
    return(this->to_microseconds() != t.to_microseconds() ? true : false);
}

bool Moment::operator >(Moment& t)
{
    return(this->to_microseconds() > t.to_microseconds() ? true : false);
}

bool Moment::operator <(Moment& t)
{
    return(this->to_microseconds() < t.to_microseconds() ? true : false);
}

bool Moment::operator >=(Moment& t)
{
    return(this->to_microseconds() >= t.to_microseconds() ? true : false);
}

bool Moment::operator <=(Moment& t)
{
    return(this->to_microseconds() <= t.to_microseconds() ? true : false);
}

Moment Moment::operator +(const Moment& t)
{
    Moment temp(this->get_hours() + t.get_hours()
                , this->get_min() + t.get_min()
                , this->get_sec() + t.get_sec()
                , this->get_milliseconds() + t.get_milliseconds()
                , this->get_microseconds() + t.get_microseconds());
    return temp;
}

Moment Moment::operator -(const Moment& t)
{
    Moment temp(this->get_hours() - t.get_hours()
                , this->get_min() - t.get_min()
                , this->get_sec() - t.get_sec()
                , this->get_milliseconds() - t.get_milliseconds()
                , this->get_microseconds() - t.get_microseconds());
    return temp;
}

Moment& Moment::operator =(const Moment& t)
{
    this->_hours = t.get_hours();
    this->_min = t.get_min();
    this->_sec = t.get_sec();
    this->_milliseconds = t.get_milliseconds();
    this->_microseconds = t.get_microseconds();
    return *this;
}

//=================AUTRES METHODES==================

void Moment::increment(size_t hours, size_t min, size_t sec, size_t milli, size_t micro)
{
    *this = Moment(this->get_hours() + hours
                   ,this->get_min() + min
                   ,this->get_sec() + sec
                   ,this->get_milliseconds() + milli
                   ,this->get_microseconds() + micro);
}

void Moment::decrement(size_t hours, size_t min, size_t sec, size_t milli, size_t micro)
{
    *this = Moment(this->get_hours() - hours
                   ,this->get_min() - min
                   ,this->get_sec() - sec
                   ,this->get_milliseconds() - milli
                   ,this->get_microseconds() - micro);
}

string Moment::toString() const
{
    string str = to_string(this->get_hours())
            +":"
            + to_string(this->get_min())
            +":"
            + to_string(this->get_sec())
            +":"
            + to_string(this->get_milliseconds())
            +":"
            + to_string(this->get_microseconds());
    return str;
}

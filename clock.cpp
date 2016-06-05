#include "clock.h"

//=====================CONSTRUCTEUR===========================

Clock::Clock()
    :_timelapse {0}
    , _limit {0}
    ,_running {false}
    , _has_ticked {false}
{ }


Moment Clock::get_time_since_begin() const
{
    size_t temp = chrono::duration_cast<chrono::microseconds>
            (_check - _begin).count();
    size_t hours = temp / 3600000000;
    temp %= 3600000000;
    size_t min = temp / 60000000;
    temp %= 60000000;
    size_t sec = temp / 1000000;
    temp %= 1000000;
    size_t milliseconds = temp / 1000;
    temp %= 1000;
    size_t microseconds = temp;
    Moment m(hours, min, sec, milliseconds, microseconds);
    return m;
}

Moment Clock::get_time_since_tick() const
{
    size_t temp = _timelapse;
    size_t hours = temp / 3600000000;
    temp %= 3600000000;
    size_t min = temp / 60000000;
    temp %= 60000000;
    size_t sec = temp / 1000000;
    temp %= 1000000;
    size_t milliseconds = temp / 1000;
    temp %= 1000;
    size_t microseconds = temp;
    Moment m(hours, min, sec, milliseconds, microseconds);
    return m;
}

vector<Moment> Clock::get_ticks() const
{
    vector<Moment> moments;
    for(auto i : _ticks)
    {
        moments.push_back(
                    Moment(0, 0, 0, 0,chrono::duration_cast<chrono::microseconds>
                                 (i - _begin).count()));
    }
    return moments;
}

//==================ACCESSEURS=======================

bool Clock::is_running() const
{
    return _running;
}

bool Clock::has_ticked() const
{
    return _has_ticked;
}

//====================================================

//===================AUTRES METHODES==================

void Clock::start()
{
    _begin = chrono::system_clock::now();
    _start = chrono::system_clock::now();
    _running = true;
}

void Clock::stop()
{
    _running = false;
}

void Clock::reset()
{
    _start = _check;
    _timelapse = 0;
    _has_ticked = false;
}

void Clock::set_alarm(Moment m)
{
    _limit = m.to_microseconds();
}

void Clock::update()
{
    if(is_running())
    {
        _check = chrono::system_clock::now();
        _timelapse = chrono::duration_cast<chrono::microseconds>
                (_check - _start).count();
    }
}

void Clock::check_time()
{
    if(is_running())
    {
        _check = chrono::system_clock::now();
        _timelapse = chrono::duration_cast<chrono::microseconds>
                (_check - _start).count();
    }

    if(_timelapse >= _limit)
    {
        _has_ticked = true;
        _ticks.push_back(chrono::time_point<chrono::system_clock>(chrono::system_clock::now()));
    }
}

Moment Clock::get_time_between(chrono::time_point<chrono::_V2::system_clock> earlier
                               , chrono::time_point<chrono::_V2::system_clock> later)
{
    return Moment(0,0,0,0
                  ,chrono::duration_cast<chrono::microseconds>
                  (later - earlier).count());
}

Moment Clock::get_time_between(Moment &earlier, Moment &later)
{
    return later - earlier;
}

Moment Clock::get_time_since(chrono::time_point<chrono::_V2::system_clock> time_point)
{
    return Moment(0,0,0,0
                  ,chrono::duration_cast<chrono::microseconds>
                  (chrono::system_clock::now() - time_point).count());
}

//======================================================

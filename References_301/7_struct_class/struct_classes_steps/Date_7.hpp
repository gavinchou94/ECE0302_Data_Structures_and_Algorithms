// This is Date_7.hpp
// Changes from Date_6.hpp
// 1. set private attribute to be enum type MONTH, instead of int type
// 2. change all return types of month from int to MONTH

#ifndef _DATE_H
#define _DATE_H

enum MONTH {JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

class Date{
    private:
        int year;
        MONTH month;
        int day;
    public:
        Date(int y, MONTH m, int d);
        int get_year() const;
        MONTH get_month() const;
        int get_day() const;
        bool set_year(int);
        bool set_month(MONTH);
        bool set_day(int);
        static const int min_year;
        bool operator==(const Date&); // operator usually just takes arg as const reference
};

bool operator<(const Date&, const Date&); //non-member operator, or non-member function

#endif
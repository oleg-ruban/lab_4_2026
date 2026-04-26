#pragma once
#include <string>

struct Student {
    std::string name;
    double avgGrade;
    bool wantsToLearn;
    int cheatedWorks;

    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator==(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;
};
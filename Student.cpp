#include "Student.h"

bool Student::operator<(const Student& other) const { return name < other.name; }
bool Student::operator>(const Student& other) const { return name > other.name; }
bool Student::operator==(const Student& other) const { return name == other.name; }
bool Student::operator<=(const Student& other) const { return name <= other.name; }
bool Student::operator>=(const Student& other) const { return name >= other.name; }
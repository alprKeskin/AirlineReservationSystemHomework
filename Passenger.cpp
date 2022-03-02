#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    // TODO
    // if my last name is less than it
    if (lastname < rhs.lastname) {
        return true;
    }
    // if my last name is greater than it
    else if (lastname > rhs.lastname) {
        return false;
    }
    // if my last name is equal to it
    else {
        // if my first name is less than it
        if (firstname < rhs.firstname) {
            return true;
        }
        // if my first name is greater than it
        else if (firstname > rhs.firstname) {
            return false;
        }
        // if my first name is equal to it
        else {
            return false;
        }
    }
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}

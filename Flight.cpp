#include "Flight.h"

Flight::Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    this->flightCode = flightCode;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->departureCity = departureCity;
    this->arrivalCity = arrivalCity;
    this->economyCapacity = economyCapacity;
    this->businessCapacity = businessCapacity;
    this->completed = false;
}

const std::string &Flight::getFlightCode() const {
    return flightCode;
}

const std::string &Flight::getDepartureTime() const {
    return departureTime;
}

const std::string &Flight::getArrivalTime() const {
    return arrivalTime;
}

const std::string &Flight::getDepartureCity() const {
    return departureCity;
}

const std::string &Flight::getArrivalCity() const {
    return arrivalCity;
}

int Flight::getEconomyCapacity() const {
    return economyCapacity;
}

int Flight::getBusinessCapacity() const {
    return businessCapacity;
}

bool Flight::isCompleted() const {
    return completed;
}

void Flight::setCompleted(bool completed) {
    this->completed = completed;
}

bool Flight::addTicket(const Ticket &ticket) {
    // TODO
    int economyClassPackness = 0;
    int businessClassPackness = 0;

    // count the packnesses of economy and business classes
    for (int i = 0; i < tickets.size(); i++) {
        if ((tickets[i]).getTicketType() == economy) {
            economyClassPackness++;
        }
        else if ((tickets[i]).getTicketType() == business) {
            businessClassPackness++;
        }
    }

    // if the ticket is an economy class ticket and there is available space in economy class
    if (ticket.getTicketType() == economy && economyClassPackness < getEconomyCapacity()) {
        // add the ticket to the flight's tickets vector
        tickets.push_back(ticket);
        return true;
    }
    // if the ticket is an business class ticket and there is available space in business class
    else if (ticket.getTicketType() == business && businessClassPackness < getBusinessCapacity()) {
        // add the ticket to the flight's tickets vector
        tickets.push_back(ticket);
        return true;
    }
    // if there is no available seat in corresponding class
    else {
        return false;
    }

}

bool Flight::operator<(const Flight &rhs) const {
    // TODO
    // if my flightcode is less than the rhs's flightcode
    if (getFlightCode() < rhs.getFlightCode()) {
        return true;
    }
    // if my flightcode is greater than the rhs's flightcode
    else if (getFlightCode() > rhs.getFlightCode()) {
        return false;
    }
    // if my flightcode is equal to the rhs's flightcode
    else {
        return false;
    }
}

bool Flight::operator>(const Flight &rhs) const {
    return rhs < *this;
}

bool Flight::operator==(const Flight &rhs) const {
    return flightCode == rhs.flightCode;
}

bool Flight::operator!=(const Flight &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << "Flight(flightCode: " << flight.flightCode;
    os << ", departureTime: " << flight.departureTime;
    os << ", arrivalTime: " << flight.arrivalTime;
    os << ", departureCity: " << flight.departureCity;
    os << ", arrivalCity: " << flight.arrivalCity;
    os << ", economyCapacity: " << flight.economyCapacity;
    os << ", businessCapacity: " << flight.businessCapacity;
    os << ", completed: " << (flight.completed ? "yes" : "no");
    os << ", tickets: [";
    for (int i = 0 ; i < flight.tickets.size() ; ++i) {
        os << flight.tickets[i];
        if (i != (flight.tickets.size() - 1)) os << ", ";
    }
    os << "])";
    return os;
}

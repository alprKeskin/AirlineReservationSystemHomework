#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    // TODO
    // create a new passenger
    Passenger newPassenger(firstname, lastname);
    // insert a new node with newPassenger as data into the passengers tree
    passengers.insert(newPassenger);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    // TODO
    // create a new passenger
    Passenger newPassenger(firstname, lastname);
    // search this passenger in the passengers tree
    BSTNode<Passenger>* searchedPassenger = passengers.search(newPassenger);
    // if searchedPassenger is NULL
    if (searchedPassenger == NULL) {
        // then, this passenger is not contained by the passengers tree
        return NULL;
    }
    // if searchedPassenger is not NULL
    else {
        // then, this passenger is contained by the passengers tree
        // return a pointer to the corresnponding passenger
        return &(searchedPassenger->data);
    }
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    // TODO
    // create a new flight
    Flight newFlight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    // insert a new node with newFlight as data into the flights tree
    flights.insert(newFlight);
}

std::vector<Flight *> AirlineReservationSystem::searchFlightHelper(const std::string &departureCity, const std::string &arrivalCity, BSTNode<Flight> *node) {
    // HELPER
    // base case
    if (node == NULL) {
        // return an empty vector
        std::vector<Flight *> emptyFlight(0);
        return emptyFlight;
    }
    // recursive case
    std::vector<Flight *> availableFlights;
    std::vector<Flight *> availableFlightsLeft;
    std::vector<Flight *> availableFlightsRight;
    // if this is a suitable flight
    if (departureCity == (node->data).getDepartureCity() && arrivalCity == (node->data).getArrivalCity()) {
        // add a pointer, pointing this flight, into the availableFlights vector
        availableFlights.push_back(&(node->data));
    }
    // search for other suitable flights in the left subtree
    availableFlightsLeft = searchFlightHelper(departureCity, arrivalCity, node->left);
    // search for other suitable flights in the right subtree
    availableFlightsRight = searchFlightHelper(departureCity, arrivalCity, node->right);
    // add available flights in the left subtree to availableFlights
    for (int i = 0; i < availableFlightsLeft.size(); i++) {
        availableFlights.push_back(availableFlightsLeft[i]);
    }
    // add available flights in the right subtree to availableFlights
    for (int i = 0; i < availableFlightsRight.size(); i++) {
        availableFlights.push_back(availableFlightsRight[i]);
    }
    // return available flights
    return availableFlights;
}
std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    // TODO
    // call helper function
    return searchFlightHelper(departureCity, arrivalCity, flights.getRoot());
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    // TODO
    // create a passenger with the given first name and last name to find in passengers tree
    Passenger samplePassenger(firstname, lastname);
    // find the passenger from the passengers tree
    BSTNode<Passenger> *ticketOwnerNode = passengers.search(samplePassenger);
    // if ticketOwner is null
    if (ticketOwnerNode == NULL) {
        // then, such a passanger does not exist in the airline reservation system
        return;
    }
    // such a passenger exists in the airline reservation system
    // create a sample flight with the given flightCode to find in flights tree
    Flight sampleFlight(flightCode, "12.00", "13.00", "Ankara", "Samsun", 100, 200);
    // find the flight having the given flight code from the passengers tree
    BSTNode<Flight> *ticketFlightNode = flights.search(sampleFlight);
    // if tickerFlight is null
    if (ticketFlightNode == NULL) {
        // then, a flight with the given flight code does not exist in the airline reservation system
        return;
    }
    // such a flight exists in the airline reservation system

    // create a ticket with the given data
    Ticket issuedTicket(&(ticketOwnerNode->data), &(ticketFlightNode->data), ticketType);
    // add this ticket to the corresponding flight
    (ticketFlightNode->data).addTicket(issuedTicket);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    // TODO
    // create a passenger with the given first name and last name to find in passengers tree
    Passenger samplePassenger(firstname, lastname);
    // find the passenger from the passengers tree
    BSTNode<Passenger> *ticketOwnerNode = passengers.search(samplePassenger);
    // if ticketOwner is null
    if (ticketOwnerNode == NULL) {
        // then, such a passanger does not exist in the airline reservation system
        return;
    }
    // such a passenger exists in the airline reservation system
    // create a sample flight with the given flightCode to find in flights tree
    Flight sampleFlight(flightCode, "12.00", "13.00", "Ankara", "Samsun", 100, 200);
    // find the flight having the given flight code from the passengers tree
    BSTNode<Flight> *ticketFlightNode = flights.search(sampleFlight);
    // if tickerFlight is null
    if (ticketFlightNode == NULL) {
        // then, a flight with the given flight code does not exist in the airline reservation system
        return;
    }
    // such a flight exists in the airline reservation system

    // create a ticket with the given data
    Ticket requestedTicket(&(ticketOwnerNode->data), &(ticketFlightNode->data), ticketType);
    // add this new ticket to the free ticket requests queue
    freeTicketRequests.enqueue(requestedTicket);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    // TODO
    // create a sample flight with the given flightCode to find in flights tree
    Flight sampleFlight(flightCode, "12.00", "13.00", "Ankara", "Samsun", 100, 200);
    // find the flight having the given flight code from the passengers tree
    BSTNode<Flight> *ticketFlightNode = flights.search(sampleFlight);
    // if tickerFlight is null
    if (ticketFlightNode == NULL) {
        // then, a flight with the given flight code does not exist in the airline reservation system
        return;
    }
    // such a flight exists in the airline reservation system

    // check whether the flight has already been carried out
    if ((ticketFlightNode->data).isCompleted()) {
        // then, do nothing
        return;
    }

    // traverse the whole queue
    for (int i = 0; i < freeTicketRequests.size(); i++) {
        // if this flight does not belong to this ticket
        if ( (freeTicketRequests.peek()).getFlight()->getFlightCode() != flightCode ) {
            // first dequeue and then enqueue
            freeTicketRequests.enqueue(freeTicketRequests.dequeue());
        }
        // if this flight belongs to this ticket
        else {
            // try to add this ticket
            // if the ticket could be added
            if ( (ticketFlightNode->data).addTicket(freeTicketRequests.peek()) ) {
                // dequeue that ticket from freeTicketRequests queue
                freeTicketRequests.dequeue();
            }
            // if the ticket is not suitable to added into flight
            else {
                // first dequeue and then enqueue
                freeTicketRequests.enqueue(freeTicketRequests.dequeue());
            }
        }
        
    }

    // mark the flight as completed
    (ticketFlightNode->data).setCompleted(true);
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}

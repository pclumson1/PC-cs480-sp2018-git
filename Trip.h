/*
 * Trip.h
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#ifndef TRIP_H_
#define TRIP_H_

#include <vector>

#include "TripLeg.h"

/**
 * The Trip class identifies properties of a trip (route)
 */
class Trip {
public:
	// Default constructor
	Trip();

	// Copy constructor
	Trip(const Trip &trip);

	// Destructor
	~Trip();

	// Accessor to return list of pointers to trip legs
 	//  (caller must delete memory for trip legs referenced by list of pointers)
	std::vector<TripLeg *> getLegs() const;

	// Accessor to return the number of trip legs
	int getNumberLegs() const;

	// Accessor to return the trip leg for the index provided
	TripLeg getLeg(int index) const;

	// Accessor to return the total distance traveled (miles)
	double getTotalDistance() const;

	// Accessor to return the distance traveled in the city (miles)
	double getCityDistance() const;

	// Accessor to return the distance traveled on the highway (miles)
	double getHighwayDistance() const;

	// Overloaded assignment operator =
	Trip &operator =(const Trip &trip);

private:
	// Instance variables
	std::vector<TripLeg *> tripLegs;
};

#endif /* TRIP_H_ */

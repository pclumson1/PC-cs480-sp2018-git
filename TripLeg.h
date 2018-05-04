/*
 * TripLeg.h
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#ifndef TRIP_LEG_H_
#define TRIP_LEG_H_

/**
 * The TripLeg class identifies properties of a trip leg
 */
class TripLeg {
public:
	// Enumerated type (city or highway) for trip leg
	enum Type { CITY, HIGHWAY };

	// Default constructor
	TripLeg();

	// Constructor allowing caller to specify a trip leg's distance (miles)
	//  and type (city or highway)
	TripLeg(double distance, Type type);

	// Accessor to return trip leg's distance (miles)
	double getDistance() const;

	// Accessor to return trip leg's type (city or highway)
	Type getType() const;

	// Accessor to return true/false whether trip leg's type is city
	bool isCity() const;

	// Accessor to return true/false whether trip leg's type is highway
	bool isHighway() const;

private:
	// Instance variables
	double distance;
	Type type;
};

#endif /* TRIP_LEG_H_ */

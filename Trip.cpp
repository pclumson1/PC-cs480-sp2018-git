/**
 * Trip route details
 *
 * @author Joe Shobe
 *
 */

#include "Trip.h"

/**
 * Default constructor
 */
Trip::Trip()
{
	// Initialize list of trip legs (trip route)
	tripLegs.push_back(new TripLeg(3.3,   TripLeg::CITY));
	tripLegs.push_back(new TripLeg(23.2,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(0.05,  TripLeg::CITY));
	tripLegs.push_back(new TripLeg(0.2,   TripLeg::CITY));
	tripLegs.push_back(new TripLeg(56.2,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(50.3,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(6.8,   TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(53.5,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(21.3,  TripLeg::CITY));
	tripLegs.push_back(new TripLeg(229.0, TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(2.8,   TripLeg::CITY));
	tripLegs.push_back(new TripLeg(74.7,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(47.3,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(69.3,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(0.2,   TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(24.3,  TripLeg::CITY));
	tripLegs.push_back(new TripLeg(21.2,  TripLeg::CITY));
	tripLegs.push_back(new TripLeg(79.2,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(208.0, TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(181.3, TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(86.6,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(106.7, TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(8.0,   TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(45.6,  TripLeg::CITY));
	tripLegs.push_back(new TripLeg(0.1,   TripLeg::CITY));
	tripLegs.push_back(new TripLeg(0.5,   TripLeg::CITY));
	tripLegs.push_back(new TripLeg(22.7,  TripLeg::HIGHWAY));
	tripLegs.push_back(new TripLeg(0.6,   TripLeg::CITY));
	tripLegs.push_back(new TripLeg(1.7,   TripLeg::CITY));
}

/**
 * Copy constructor
 */
Trip::Trip(const Trip &trip)
{
	// Create copy of source trip legs (allocates new memory)
	for (int i = 0; i < (int) trip.tripLegs.size(); i++) {
		tripLegs.push_back(new TripLeg(*trip.tripLegs[i]));
	}
}

/**
 * Destructor
 */
Trip::~Trip()
{
	// Delete existing memory for trip legs
	for (int i = 0; i < (int) tripLegs.size(); i++)
		delete tripLegs[i];

	// Clear vector of trip legs
	tripLegs.clear();
}

/**
 * Accessor to return list of pointers to trip legs
 *  (caller must delete memory for trip legs referenced by list of pointers)
 */
std::vector<TripLeg *> Trip::getLegs() const
{
	std::vector<TripLeg *> tempTripLegs;
	for (int i = 0; i < (int) tripLegs.size(); i++)
		tempTripLegs.push_back(new TripLeg(*tripLegs[i]));
	return tempTripLegs;
}

/**
 * Accessor to return the number of trip legs
 */
int Trip::getNumberLegs() const
{
	return (int) tripLegs.size();
}

/**
 * Accessor to return the trip leg for the index provided
 */
TripLeg Trip::getLeg(int index) const
{
	if (index < 0 || index >= (int) tripLegs.size())
		return TripLeg();
	return *tripLegs[index];
}

/**
 * Return the total distance traveled (miles)
 */
double Trip::getTotalDistance() const
{
	double totalDistance = 0.0;
	for (int i = 0; i < (int) tripLegs.size(); i++)
		totalDistance += tripLegs[i]->getDistance();
	return totalDistance;
}

/**
 * Return the distance traveled in the city (miles)
 */
double Trip::getCityDistance() const
{
	double cityDistance = 0.0;
	for (int i = 0; i < (int) tripLegs.size(); i++)
		if (tripLegs[i]->isCity())
			cityDistance += tripLegs[i]->getDistance();
	return cityDistance;
}

/**
 * Return the distance traveled on the highway (miles)
 */
double Trip::getHighwayDistance() const
{
	double highwayDistance = 0.0;
	for (int i = 0; i < (int) tripLegs.size(); i++)
		if (tripLegs[i]->isHighway())
			highwayDistance += tripLegs[i]->getDistance();
	return highwayDistance;
}

/**
 * Overloaded assignment operator =
 */
Trip &Trip::operator =(const Trip &trip)
{
	// Ignore if assignment to self (t = t)
	if (this == &trip)
		return *this;

	// Delete existing memory for trip legs
	for (int i = 0; i < (int) tripLegs.size(); i++)
		delete tripLegs[i];

	// Clear vector of trip legs
	tripLegs.clear();

	// Create copy of source trip legs (allocates new memory)
	for (int i = 0; i < (int) trip.tripLegs.size(); i++) {
		tripLegs.push_back(new TripLeg(*trip.tripLegs[i]));
	}

	return *this;
}


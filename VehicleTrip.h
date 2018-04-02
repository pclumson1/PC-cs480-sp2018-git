/*
 * VehicleTrip.h
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#ifndef VEHICLE_TRIP_H_
#define VEHICLE_TRIP_H_

#include <iostream>
#include <vector>

#include "Trip.h"
#include "TripParameters.h"
#include "Vehicle.h"

/**
 * The VehicleTrip class identifies properties of a trip taken by a vehicle
 **/
class VehicleTrip {
public:
	// Default constructor
	VehicleTrip();

	// Constructor allowing caller to specify a vehicle's trip information
	VehicleTrip(const Vehicle *vehicle, const Trip &trip, const TripParameters &tripParameters);

	// Copy constructor
	VehicleTrip(const VehicleTrip &vehicleTrip);

	// Destructor
	~VehicleTrip();

	// Accessor to return the vehicle
	Vehicle getVehicle() const;

	// Accessor to return the distance traveled in the city (miles)
	double getDistanceTraveledCity() const;

	// Accessor to return the distance traveled on the highway (miles)
	double getDistanceTraveledHighway() const;

	// Accessor to return the number of gallons of fuel added
	double getFuelAdded() const;

	// Accessor to return the number of gallons of fuel used
	double getFuelUsed() const;

	// Accessor to return the number of gallons of fuel remaining
	double getFuelRemaining() const;

	// Accessor to return the number of fuel stops
	int getFuelStops() const;

	// Accessor to return the travel time in minutes
	double getTime() const;

	// Accessor to return the number of days portion of the travel time when expressed as d.hh:mm
	int getTimeNumDays() const;

	// Accessor to return the number of hours portion of the travel time when expressed as d.hh:mm
	int getTimeNumHours() const;

	// Accessor to return the number minutes portion of the travel time when expressed as d.hh:mm
	int getTimeNumMinutes() const;

	// Accessor to return the cost based on fuel added
	double getFuelAddedCost() const;

	// Accessor to return the cost based on fuel used
	double getFuelUsedCost() const;

	// Return true/false whether vehicle trip time is less
	bool isTimeLessThan(const VehicleTrip &vehicleTrip) const;

	// Return true/false whether vehicle trip time is more
	bool isTimeMoreThan(const VehicleTrip &vehicleTrip) const;

	// Return true/false whether vehicle trip costs less based on fuel added
	bool isFuelAddedCostLessThan(const VehicleTrip &vehicleTrip) const;

	// Return true/false whether vehicle trip costs more based on fuel added
	bool isFuelAddedCostMoreThan(const VehicleTrip &vehicleTrip) const;

	// Return true/false whether vehicle trip costs less based on fuel used
	bool isFuelUsedCostLessThan(const VehicleTrip &vehicleTrip) const;

	// Return true/false whether vehicle trip costs more based on fuel used
	bool isFuelUsedCostMoreThan(const VehicleTrip &vehicleTrip) const;

	// Returns true/false whether vehicle trip is valid (initialized)
	bool isValid() const;

	// Overloaded assignment operator =
	VehicleTrip &operator =(const VehicleTrip &vehicleTrip);

	// Overloaded insertion operator <<
	friend std::ostream &operator <<(std::ostream &os, const VehicleTrip &vehicleTrip);

private:
	// Instance variables
	Vehicle *vehicle;
	TripParameters tripParameters;
	double distanceTraveledCity;
	double distanceTraveledHighway;
	double fuelAdded;
	double fuelUsed;
	double fuelRemaining;
	int fuelStops;
	bool reachedDestination;
	bool initialized;
};

#endif /* VEHICLE_TRIP_H_ */

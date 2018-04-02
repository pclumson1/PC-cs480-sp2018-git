/*
 * TripParameters.h
 *
 *  Created on: Jan 31, 2017
 *      Author: Joe
 */

#ifndef TRIP_PARAMETERS_H_
#define TRIP_PARAMETERS_H_

#include <fstream>
#include <stdexcept>
#include <string>

/**
 * The TripParameters class identifies parameters used for computing a trip route
 */
class TripParameters {
public:
	// Default constructor
	TripParameters();

	// Constructor to fetch input parameters from INI file provided
	TripParameters(const char filename[]) throw (std::ifstream::failure, std::invalid_argument, std::out_of_range);

	// Accessor to return the average speed in the city (MPH)
	double getMphCity() const;

	// Accessor to return the average speed on the highway (MPH)
	double getMphHighway() const;

	// Accessor to return the average fuel price per gallon
	double getFuelPrice() const;

	// Accessor to return the distance between gas stations (miles)
	double getDistanceBetweenGasStations() const;

	// Accessor to return the time between taking naps (hours)
	double getTimeBetweenNaps() const;

	// Accessor to return the time required to refuel (minutes)
	int getRefuelTime() const;

	// Accessor to return the time required to use the restroom (minutes)
	int getRestroomTime() const;

	// Accessor to return the time required to take a nap (minutes)
	int getNapTime() const;

private:
	// Instance variables
	double mphCity;
	double mphHighway;
	double fuelPrice;
	double distanceBetweenGasStations;
	double timeBetweenNaps;
	int refuelTime;
	int restroomTime;
	int napTime;

	// Parse name=value and store value if name is supported
	void parseValue(std::string nameValuePair) throw (std::invalid_argument, std::out_of_range);
};

#endif /* TRIP_PARAMETERS_H_ */

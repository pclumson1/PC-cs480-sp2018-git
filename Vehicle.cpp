/*
 * Vehicle.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>

#include "Vehicle.h"

/**
 * String constants
 */
static const char VEHICLE_STATS[] =
	"%s %s\n  Engine size: %.1fL %d cyl, Tank size: %.1f, MPG city: %d, MPG highway: %d";

/**
 * Default constructor
 */
Vehicle::Vehicle()
{
	initialized = false;
	// make[0] = '\0'; // Not necessary for type string
	// model[0] = '\0'; // Not necessary for type string
	engineSize = 0.0;
	engineCylinders = 0;
	tankSize = 0.0;
	mpgCity = 0;
	mpgHighway = 0;
}

/**
 * Constructor allowing caller to specify a vehicle's make, model,
 *  engine size (in liters), number of cylinders, tank size (in gallons),
 *  and MPG rating (both city and highway)
 */
Vehicle::Vehicle(
	const std::string &make,
	const std::string &model,
	double engineSize,
	int engineCylinders,
	double tankSize,
	int mpgCity,
	int mpgHighway
)
{
	this->initialized = false;

	// Init other vehicle's attributes
	this->make = make;
	this->model = model;
	this->engineSize = engineSize;
	this->engineCylinders = engineCylinders;
	this->tankSize = tankSize;
	this->mpgCity = mpgCity;
	this->mpgHighway = mpgHighway;

	// Vehicle now initialized
	this->initialized = true;
}

/**
 * Accessor to return vehicle's make
 */
std::string Vehicle::getMake() const
{
	return make;
}

/**
 * Accessor to return vehicle's model
 */
std::string Vehicle::getModel() const
{
	return model;
}

/**
 * Accessor to return vehicle's engine size (in liters)
 */
double Vehicle::getEngineSize() const
{
	return engineSize;
}

/**
 * Accessor to return vehicle's number of cylinders
 */
int Vehicle::getEngineCylinders() const
{
	return engineCylinders;
}

/**
 * Accessor to return vehicle's tank size (in gallons)
 */
double Vehicle::getTankSize() const
{
	return tankSize;
}

/**
 * Accessor to return vehicle's MPG rating in the city
 */
int Vehicle::getMpgCity() const
{
	return mpgCity;
}

/**
 * Accessor to return vehicle's MPG rating on the highway
 */
int Vehicle::getMpgHighway() const
{
	return mpgHighway;
}

/**
 * Returns true/false whether vehicle is valid (initialized)
 */
bool Vehicle::isValid() const
{
	return initialized;
}

/**
 * Returns a string representing vehicle's attributes
 */
std::string Vehicle::toString() const
{
	char str[200];

	// Format string
	sprintf(str, VEHICLE_STATS, make.c_str(), model.c_str(), engineSize, engineCylinders, tankSize, mpgCity, mpgHighway);

	return std::string(str);
}

/**
 * Overloaded insertion operator <<
 */
std::ostream &operator <<(std::ostream &os, const Vehicle &vehicle)
{
	// Output formatted string
	os << vehicle.toString();

	return os;
}

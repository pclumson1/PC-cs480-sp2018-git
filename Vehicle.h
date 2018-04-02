/*
 * Vehicle.h
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <ostream>
#include <string>

/**
 * The Vehicle class identifies properties of a vehicle
 */
class Vehicle {
public:
	// Default constructor
	Vehicle();

	// Constructor allowing caller to specify a vehicle's make, model,
	//  engine size (in liters), number of cylinders, tank size (in gallons),
	//  and MPG rating (both city and highway)
	Vehicle(const std::string &make, const std::string &model, double engineSize, int engineCylinders, double tankSize, int mpgCity, int mpgHighway);

	// Accessor to return vehicle's make
	std::string getMake() const;

	// Accessor to return vehicle's model
	std::string getModel() const;

	// Accessor to return vehicle's engine size (in liters)
	double getEngineSize() const;

	// Accessor to return vehicle's number of cylinders
	int getEngineCylinders() const;

	// Accessor to return vehicle's tank size (in gallons)
	double getTankSize() const;

	// Accessor to return vehicle's MPG rating in the city
	int getMpgCity() const;

	// Accessor to return vehicle's MPG rating on the highway
	int getMpgHighway() const;

	// Returns true/false whether vehicle is valid (initialized)
	bool isValid() const;

	// Returns a string representing vehicle's attributes
	std::string toString() const;

	// Overloaded insertion operator <<
	friend std::ostream &operator <<(std::ostream &os, const Vehicle &vehicle);

private:
	// Instance variables
	bool initialized;
	std::string make;
	std::string model;
	double engineSize;
	int engineCylinders;
	double tankSize;
	int mpgCity;
	int mpgHighway;
};

#endif /* VEHICLE_H_ */

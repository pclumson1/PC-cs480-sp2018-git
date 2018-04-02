/*
 * VehicleTrip.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#include <cmath>
#include <cstdio>
#include <cstring>

#include "VehicleTrip.h"

/**
 * Constants
 */
static const int HOURS_PER_DAY = 24;
static const int MINUTES_PER_HOUR = 60;
static const double NO_MORE_GAS_STATIONS = 10000000.0;

/**
 * String constants
 */
static const char TRIP_STATS[] =
	"TripTime=%.2f (%d.%02d:%02d)  TripCostBasedOnFuelAdded=%.2f  TripCostBasedOnFuelUsed=%.2f\n  FuelAdded=%.4f  FuelUsed=%.4f  FuelRemaining=%.4f  FuelStops=%d";

/**
 * Default constructor
 */
VehicleTrip::VehicleTrip()
{
	// Initialize variables
	vehicle = NULL;
	//tripParameters = TripParameters(); // Not necessary for type TripParameters
	distanceTraveledCity = 0;
	distanceTraveledHighway = 0;
	fuelAdded = 0.0;
	fuelUsed = 0.0;
	fuelRemaining = 0.0;
	fuelStops = 0;
	reachedDestination = false;
	initialized = false;
}

/**
 * Constructor allowing caller to specify a vehicle's trip information
 */
VehicleTrip::VehicleTrip(const Vehicle *vehicle, const Trip &trip, const TripParameters &tripParameters)
{
	initialized = false;

	// Can't continue if source vehicle is invalid, so just return
	if (!vehicle || !vehicle->isValid())
		return;

	// Initialize vehicle
	this->vehicle = new Vehicle(*vehicle);

	// Initialize trip parameters
	this->tripParameters = tripParameters;

	// Initialize trip variables
	distanceTraveledCity = 0.0;
	distanceTraveledHighway = 0.0;

	// Initialize fuel variables
	fuelAdded = 0.0;
	fuelUsed = 0.0;
	fuelRemaining = 0.0;
	fuelStops = 0;
	reachedDestination = false;

	// Initialize other trip route-related variables
	bool ranOutOfFuel = false;
	bool isNextLegCity = false;
	double distanceRemainingForNextLeg = 0.0;

	int leg = 0;
	fuelRemaining = this->vehicle->getTankSize();

	// Do until we reach our destination (or run out of gas)
	while (!reachedDestination && !ranOutOfFuel) {
		double distanceFromThisGasStationCity = 0.0;
		double distanceFromThisGasStationHighway = 0.0;
		double distanceToNextGasStation = this->tripParameters.getDistanceBetweenGasStations();

		// Do until we reach the next gas station
		while (distanceToNextGasStation > 0.0) {
			// If we don't know the distance (city or highway) for next leg of trip,
			//  determine it now
			if (distanceRemainingForNextLeg == 0.0) {
				if (leg < trip.getNumberLegs()) {
					TripLeg tripLeg = trip.getLeg(leg);
					distanceRemainingForNextLeg = tripLeg.getDistance();
					isNextLegCity = tripLeg.isCity();
					leg++;
				}
			}

			// Determine if any more gas stations
			if (leg >= trip.getNumberLegs())
				distanceToNextGasStation = NO_MORE_GAS_STATIONS;

			// Increase distance traveled from this gas station (city and highway) while
			//  decreasing distance traveled to next gas station until station is reached
			if (distanceRemainingForNextLeg > 0.0) {
				if (distanceToNextGasStation <= distanceRemainingForNextLeg) {
					if (isNextLegCity)
						distanceFromThisGasStationCity += distanceToNextGasStation;
					else
						distanceFromThisGasStationHighway += distanceToNextGasStation;
					distanceRemainingForNextLeg -= distanceToNextGasStation;
					distanceToNextGasStation = 0.0;
				} else {
					if (isNextLegCity)
						distanceFromThisGasStationCity += distanceRemainingForNextLeg;
					else
						distanceFromThisGasStationHighway += distanceRemainingForNextLeg;
					distanceToNextGasStation -= distanceRemainingForNextLeg;
					distanceRemainingForNextLeg = 0.0;
				}
			} else {
				// We must have reached our destination
				reachedDestination = true;
				break;
			}
		}

		// Now that we've determined the distance (both city and highway) to
		//  travel from this gas station to the next, compute fuel required to
		//  get to next station
		double fuelRequiredFromThisGasStation = (distanceFromThisGasStationCity / this->vehicle->getMpgCity()) +
												(distanceFromThisGasStationHighway / this->vehicle->getMpgHighway());

		// Compute how much fuel would be used to reach next gas station and
		//  if we don't have enough to reach station, refuel now before continuing
		if (fuelRemaining < fuelRequiredFromThisGasStation) {
			double fuelRequired = this->vehicle->getTankSize() - fuelRemaining;
			fuelAdded += fuelRequired;
			fuelRemaining = this->vehicle->getTankSize();
			fuelStops++;
		}

		// Keep track of fuel used
		fuelUsed += fuelRequiredFromThisGasStation;

		// Reduce fuel in the tank by amount needed to reach next station
		fuelRemaining -= fuelRequiredFromThisGasStation;
		if (fuelRemaining < 0.0)
			ranOutOfFuel = true;

		// Keep track of distance traveled (both city and highway)
		distanceTraveledCity += distanceFromThisGasStationCity;
		distanceTraveledHighway += distanceFromThisGasStationHighway;
	}

	initialized = true;
}

/**
 * Copy constructor
 */
VehicleTrip::VehicleTrip(const VehicleTrip &vehicleTrip)
{
	// Can't continue if vehicle is invalid, so just return
	if (!vehicleTrip.isValid())
		return;

	// Initialize vehicle (allocates new memory)
	vehicle = new Vehicle(*vehicleTrip.vehicle);

	// Initialize trip parameters
	tripParameters = vehicleTrip.tripParameters;

// Initialize member variables
	distanceTraveledCity = vehicleTrip.distanceTraveledCity;
	distanceTraveledHighway = vehicleTrip.distanceTraveledHighway;
	fuelAdded = vehicleTrip.fuelAdded;
	fuelUsed = vehicleTrip.fuelUsed;
	fuelRemaining = vehicleTrip.fuelRemaining;
	fuelStops = vehicleTrip.fuelStops;
	reachedDestination = vehicleTrip.reachedDestination;
	initialized = vehicleTrip.initialized;
}

/**
 * Destructor
 */
VehicleTrip::~VehicleTrip()
{
	// Delete existing memory for vehicle
	if (vehicle)
		delete vehicle;
}

/**
 * Accessor to return the distance traveled in the city (miles)
 */
double VehicleTrip::getDistanceTraveledCity() const
{
	return distanceTraveledCity;
}

/**
 * Accessor to return the vehicle
 */
Vehicle VehicleTrip::getVehicle() const
{
	if (!vehicle)
		return Vehicle();

	return *vehicle;
}

/**
 * Accessor to return the distance traveled on the highway (miles)
 */
double VehicleTrip::getDistanceTraveledHighway() const
{
	return distanceTraveledHighway;
}

/**
 * Accessor to return the number of gallons of fuel added
 */
double VehicleTrip::getFuelAdded() const
{
	return fuelAdded;
}

/**
 * Accessor to return the number of gallons of fuel used
 */
double VehicleTrip::getFuelUsed() const
{
	return fuelUsed;
}

/**
 * Accessor to return the number of gallons of fuel remaining
 */
double VehicleTrip::getFuelRemaining() const
{
	return fuelRemaining;
}

/**
 * Accessor to return the number of fuel stops
 */
int VehicleTrip::getFuelStops() const
{
	return fuelStops;
}

/**
 * Accessor to return the travel time in minutes
 */
double VehicleTrip::getTime() const
{
	// Can't continue if vehicle is invalid, so just return 0.0
	if (!vehicle || !vehicle->isValid() || tripParameters.getMphCity() == 0 || tripParameters.getMphHighway() == 0)
		return 0.0;

	// Determine time to drive
	double timeTraveled = ((distanceTraveledCity / tripParameters.getMphCity()) * MINUTES_PER_HOUR) + ((distanceTraveledHighway / tripParameters.getMphHighway()) * MINUTES_PER_HOUR);

	// Determine how many stops are required to use the restroom
	//  (must use restroom at every other fuel stop, starting with the second stop)
	int restroomStops = fuelStops / 2;

	// Determine how many stops are required to take naps
	int napStops = (int) (timeTraveled / (tripParameters.getTimeBetweenNaps() * MINUTES_PER_HOUR));
	if ((timeTraveled / (tripParameters.getTimeBetweenNaps() * MINUTES_PER_HOUR)) - napStops == 0.0)
		napStops--;

	// Determine time to refuel, use restroom, and take naps
	int timeRefuel = fuelStops * tripParameters.getRefuelTime();
	int timeRestroom = restroomStops * tripParameters.getRestroomTime();
	int timeNap = napStops * tripParameters.getNapTime();

	// Return travel time (minutes)
	return round(timeTraveled + timeRefuel + timeRestroom + timeNap);
}

/**
 * Accessor to return the number of days portion of the travel time when expressed as d.hh:mm
 */
int VehicleTrip::getTimeNumDays() const
{
	return (int) (getTime() / HOURS_PER_DAY / MINUTES_PER_HOUR);
}

/**
 * Accessor to return the number of hours portion of the travel time when expressed as d.hh:mm
 */
int VehicleTrip::getTimeNumHours() const
{
	return (int) ((getTime() - (getTimeNumDays() * HOURS_PER_DAY * MINUTES_PER_HOUR)) / MINUTES_PER_HOUR);
}

/**
 * Accessor to return the number minutes portion of the travel time when expressed as d.hh:mm
 */
int VehicleTrip::getTimeNumMinutes() const
{
	return (int) ((int) (getTime() - (getTimeNumDays() * HOURS_PER_DAY * MINUTES_PER_HOUR)) % MINUTES_PER_HOUR);
}

/**
 * Accessor to return the cost based on fuel added
 */
double VehicleTrip::getFuelAddedCost() const
{
	// Can't continue if vehicle is invalid, so just return 0.0
	if (!vehicle || !vehicle->isValid())
		return 0.0;

	return fuelAdded * tripParameters.getFuelPrice();
}

/**
 * Accessor to return the cost based on fuel used
 */
double VehicleTrip::getFuelUsedCost() const
{
	// Can't continue if vehicle is invalid, so just return 0.0
	if (!vehicle || !vehicle->isValid())
		return 0.0;

	return fuelUsed * tripParameters.getFuelPrice();
}

/**
 * Return true/false whether vehicle trip time is less
 */
bool VehicleTrip::isTimeLessThan(const VehicleTrip &vehicleTrip) const
{
	return (!vehicleTrip.isValid() || (vehicleTrip.reachedDestination && (!isValid() || getTime() < vehicleTrip.getTime())));
}

/**
 * Return true/false whether vehicle trip time is more
 */
bool VehicleTrip::isTimeMoreThan(const VehicleTrip &vehicleTrip) const
{
	return (!vehicleTrip.isValid() || (vehicleTrip.reachedDestination && (!isValid() || getTime() > vehicleTrip.getTime())));
}

/**
 * Return true/false whether vehicle trip costs less based on fuel added
 */
bool VehicleTrip::isFuelAddedCostLessThan(const VehicleTrip &vehicleTrip) const
{
	return (!vehicleTrip.isValid() || (vehicleTrip.reachedDestination && (!isValid() || getFuelAddedCost() < vehicleTrip.getFuelAddedCost())));
}

/**
 * Return true/false whether vehicle trip costs more based on fuel added
 */
bool VehicleTrip::isFuelAddedCostMoreThan(const VehicleTrip &vehicleTrip) const
{
	return (!vehicleTrip.isValid() || (vehicleTrip.reachedDestination && (!isValid() || getFuelAddedCost() > vehicleTrip.getFuelAddedCost())));
}

/**
 * Return true/false whether vehicle trip costs less based on fuel used
 */
bool VehicleTrip::isFuelUsedCostLessThan(const VehicleTrip &vehicleTrip) const
{
	return (!vehicleTrip.isValid() || (vehicleTrip.reachedDestination && (!isValid() || getFuelUsedCost() < vehicleTrip.getFuelUsedCost())));
}

/**
 * Return true/false whether vehicle trip costs more based on fuel used
 */
bool VehicleTrip::isFuelUsedCostMoreThan(const VehicleTrip &vehicleTrip) const
{
	return (!vehicleTrip.isValid() || (vehicleTrip.reachedDestination && (!isValid() || getFuelUsedCost() > vehicleTrip.getFuelUsedCost())));
}

/**
 * Returns true/false whether vehicle is valid (initialized)
 */
bool VehicleTrip::isValid() const
{
	return initialized;
}

/**
 * Overloaded assignment operator =
 */
VehicleTrip &VehicleTrip::operator =(const VehicleTrip &vehicleTrip)
{
	// Ignore if assignment to self (vt = vt)
	if (this == &vehicleTrip)
		return *this;

	// Delete existing memory for vehicle
	if (vehicle) {
		delete vehicle;
		vehicle = NULL;
	}

	// Initialize vehicle (allocates new memory)
	if (vehicleTrip.vehicle)
		vehicle = new Vehicle(*vehicleTrip.vehicle);

	// Initialize trip parameters
	tripParameters = vehicleTrip.tripParameters;

	// Initialize member variables
	distanceTraveledCity = vehicleTrip.distanceTraveledCity;
	distanceTraveledHighway = vehicleTrip.distanceTraveledHighway;
	fuelAdded = vehicleTrip.fuelAdded;
	fuelUsed = vehicleTrip.fuelUsed;
	fuelRemaining = vehicleTrip.fuelRemaining;
	fuelStops = vehicleTrip.fuelStops;
	reachedDestination = vehicleTrip.reachedDestination;
	initialized = vehicleTrip.initialized;

	return *this;
}

/**
 * Overloaded insertion operator <<
 */
std::ostream &operator <<(std::ostream &os, const VehicleTrip &vehicleTrip)
{
	char str[400];

	// Can't continue if RHS VehicleTrip is invalid, so just return
	if (!vehicleTrip.isValid())
		return os;

	// Format string
	sprintf(str, TRIP_STATS, vehicleTrip.getTime(),
		vehicleTrip.getTimeNumDays(), vehicleTrip.getTimeNumHours(), vehicleTrip.getTimeNumMinutes(),
		vehicleTrip.getFuelAddedCost(), vehicleTrip.getFuelUsedCost(),
		vehicleTrip.fuelAdded, vehicleTrip.fuelUsed, vehicleTrip.fuelRemaining, vehicleTrip.fuelStops);

	// Output formatted string
	os << *vehicleTrip.vehicle << std::endl << "  " << str;

	return os;
}

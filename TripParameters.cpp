/*
 * TripParameters.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: Joe
 */

#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

#include "StringEnh.h"
#include "TripParameters.h"

/**
 * Constants
 */
static const double AVERAGE_MILES_PER_HOUR_CITY = 25.0;
static const double AVERAGE_MILES_PER_HOUR_HIGHWAY = 70.0;
static const double AVERAGE_PRICE_PER_GALLON = 2.19;
static const double DISTANCE_BETWEEN_GAS_STATIONS = 80.0;
static const double TIME_BETWEEN_NAPS = 8.0;
static const int AMOUNT_OF_TIME_TO_REFUEL = 20;
static const int AMOUNT_OF_TIME_TO_USE_RESTROOM = 10;
static const int AMOUNT_OF_TIME_TO_TAKE_NAP = 15;

static std::string NAME_VALUE_DELIMITER = "=";

/**
 * Parse name=value and store value if name is supported
 */
void TripParameters::parseValue(std::string lineString) throw (std::invalid_argument, std::out_of_range)
{
	// Transform vehicle record from a string to a tokenized string (vector of strings)
	std::vector<std::string> nameValuePair = StringEnh::tokenize(lineString, NAME_VALUE_DELIMITER);

	// Validate name=value includes 2 sub-components, cannot continue if not
	if (nameValuePair.size() != 2)
		throw std::invalid_argument("Improper syntax for name=value pair (" + lineString + ")");

	std::string name = StringEnh::trim(nameValuePair[0]);
	std::string value = StringEnh::trim(nameValuePair[1]);

	if (name.empty() || value.empty())
		throw std::out_of_range("Improper syntax for name=value pair (" + lineString + ")");

	if (name == "MphCity") {
		try {
			mphCity = std::stod(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "MphHighway") {
		try {
			mphHighway = std::stod(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "FuelPrice") {
		try {
			fuelPrice = std::stod(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "DistanceBetweenGasStations") {
		try {
			distanceBetweenGasStations = std::stod(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "TimeBetweenNaps") {
		try {
			timeBetweenNaps = std::stod(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "RefuelTime") {
		try {
			refuelTime = std::stoi(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "RestroomTime") {
		try {
			restroomTime = std::stoi(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	} else if (name == "NapTime") {
		try {
			napTime = std::stoi(value);
		} catch (const std::invalid_argument &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("'" + name + "' has invalid value (" + lineString + ")");
		}
	}
}

/**
 * Default constructor
 */
TripParameters::TripParameters()
{
	// Initialize trip parameters
	mphCity = AVERAGE_MILES_PER_HOUR_CITY;
	mphHighway = AVERAGE_MILES_PER_HOUR_HIGHWAY;
	fuelPrice = AVERAGE_PRICE_PER_GALLON;
	distanceBetweenGasStations = DISTANCE_BETWEEN_GAS_STATIONS;
	timeBetweenNaps = TIME_BETWEEN_NAPS;
	refuelTime = AMOUNT_OF_TIME_TO_REFUEL;
	restroomTime = AMOUNT_OF_TIME_TO_USE_RESTROOM;
	napTime = AMOUNT_OF_TIME_TO_TAKE_NAP;
}

/**
 * Constructor to fetch input parameters from INI file provided
 */
TripParameters::TripParameters(const char filename[]) throw (std::ifstream::failure, std::invalid_argument, std::out_of_range) : TripParameters()
{
	std::ifstream ifs;

	// Enable throwing of fail and bad exceptions
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Open file containing vehicles
	ifs.open(filename);

	// Enable throwing of bad exceptions (when eofbit is set, failbit may also be set)
	ifs.exceptions(std::ifstream::badbit);

	// Repeat while lines still exist
	while (ifs.peek() != EOF) {
		// Read a line from the file
		std::string lineString;
		getline(ifs, lineString);

		// Determine if line is a comment, blank line, or a trip parameter
		lineString = StringEnh::trim(lineString);
		if (!lineString.empty() && lineString[0] != '#') {
			// Get trip parameter value
			parseValue(lineString);
		}
	}

	// Close file
	ifs.close();

	// Check for name=value correctness
	if (mphCity <= 0.0 || mphHighway <= 0.0 ||
			fuelPrice <= 0.0 || distanceBetweenGasStations <= 0.0 || timeBetweenNaps <= 0.0 ||
			refuelTime < 0 || restroomTime < 0 || napTime < 0)
		throw std::out_of_range("One or more trip parameters has an invalid value (less than or equal to zero)");
}

/**
 * Accessor to return the average speed in the city (MPH)
 */
double TripParameters::getMphCity() const
{
	return mphCity;
}

/**
 * Accessor to return the average speed on the highway (MPH)
 */
double TripParameters::getMphHighway() const
{
	return mphHighway;
}

/**
 * Accessor to return the average fuel price per gallon
 */
double TripParameters::getFuelPrice() const
{
	return fuelPrice;
}

/**
 * Accessor to return the distance between gas stations (miles)
 */
double TripParameters::getDistanceBetweenGasStations() const
{
	return distanceBetweenGasStations;
}

/**
 * Accessor to return the time between taking naps (hours)
 */
double TripParameters::getTimeBetweenNaps() const
{
	return timeBetweenNaps;
}

/**
 * Accessor to return the time required to refuel (minutes)
 */
int TripParameters::getRefuelTime() const
{
	return refuelTime;
}

/**
 * Accessor to return the time required to use the restroom (minutes)
 */
int TripParameters::getRestroomTime() const
{
	return restroomTime;
}

/**
 * Accessor to return the time required to take a nap (minutes)
 */
int TripParameters::getNapTime() const
{
	return napTime;
}

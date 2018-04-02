/*
 * TripLeg.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#include "TripLeg.h"

/**
 * Default constructor
 */
TripLeg::TripLeg() : distance(0.0), type(CITY)
{
}

/**
 * Constructor allowing caller to specify a trip leg's distance (miles)
 *  and type (city or highway)
 */
TripLeg::TripLeg(double distance, Type type) : distance(distance), type(type)
{
}

/**
 * Accessor to return trip leg's distance (miles)
 */
double TripLeg::getDistance() const
{
	return distance;
}

/**
 * Accessor to return trip leg's type (city or highway)
 */
TripLeg::Type TripLeg::getType() const
{
	return type;
}

/**
 * Accessor to return true/false whether trip leg's type is city
 */
bool TripLeg::isCity() const
{
	return (type == CITY);
}

/**
 * Accessor to return true/false whether trip leg's type is highway
 */
bool TripLeg::isHighway() const
{
	return (type == HIGHWAY);
}

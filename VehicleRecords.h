/*
 * VehicleRecords.h
 *
 *  Created on: Jan 31, 2017
 *      Author: Joe
 */

#ifndef VEHICLE_RECORDS_H_
#define VEHICLE_RECORDS_H_

#include <fstream>
#include <stdexcept>
#include <vector>

#include "Vehicle.h"
#include "VehicleTrip.h"

/**
 * The VehicleRecords class identifies the list of vehicles
 */
class VehicleRecords {
public:
	// Get list of vehicles
	static std::vector<Vehicle *> getVehicles(const char filename[]) throw (std::ifstream::failure, std::invalid_argument, std::out_of_range);

	// Format vehicle trip header as a string for storing in a file
	static std::string formatHeaderForFile();

	// Format vehicle trip data record as a string for storing in a file
	static std::string formatRecordForFile(const VehicleTrip &vehicleTrip);

private:
	// Default constructor (use private to prevent creation)
	VehicleRecords();
};

#endif /* VEHICLE_RECORDS_H_ */

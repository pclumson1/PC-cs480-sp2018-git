/*
 *
 *  Created on: Jan 21, 2017
 *      Author: Joe
 */

#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Trip.h"
#include "TripParameters.h"
#include "Vehicle.h"
#include "VehicleRecords.h"
#include "VehicleTrip.h"

using namespace std;

static const int debug = 0;

/**
 * Constants
 */
static const char FILENAME_INPUT[] = "WichitaToMonticello-Input.ini";
static const char FILENAME_RESULTS[] = "WichitaToMonticello-Results.txt";
static const char FILENAME_VEHICLES[] = "WichitaToMonticello-Vehicles.txt";

/**
 * Output trip distance objective
 */
static void outputTripDistance(ostream &fout, const Trip &trip)
{
	char str[100];

	sprintf(str, "Total trip distance: %.2f (city: %.2f, highway: %.2f)",
		trip.getTotalDistance(), trip.getCityDistance(), trip.getHighwayDistance());

	fout << endl << str << endl;
}


/**
 * Output vehicle satisfying trip objective
 */
static void outputVehicleTripObjective(ostream &fout, const char objective[], const VehicleTrip &vehicleTrip)
{
	fout << endl << objective << ":" << endl << vehicleTrip << endl;
}

/**
 * Output vehicle arriving first
 */
static void outputVehicleArrivingFirst(ostream &fout, const VehicleTrip &vehicleTrip)
{
	outputVehicleTripObjective(fout, "Vehicle arriving first", vehicleTrip);
}

/**
 * Output vehicle arriving last
 */
static void outputVehicleArrivingLast(ostream &fout, const VehicleTrip &vehicleTrip)
{
	outputVehicleTripObjective(fout, "Vehicle arriving last", vehicleTrip);
}

/**
 * Output vehicle costing least (based on fuel added)
 */
static void outputVehicleCostingLeastFuelAdded(ostream &fout, const VehicleTrip &vehicleTrip)
{
	outputVehicleTripObjective(fout, "Vehicle costing least (based on fuel added)", vehicleTrip);
}

/**
 * Output vehicle costing most (based on fuel added)
 */
static void outputVehicleCostingMostFuelAdded(ostream &fout, const VehicleTrip &vehicleTrip)
{
	outputVehicleTripObjective(fout, "Vehicle costing most (based on fuel added)", vehicleTrip);
}

/**
 * Output vehicle costing least (based on fuel used)
 */
static void outputVehicleCostingLeastFuelUsed(ostream &fout, const VehicleTrip &vehicleTrip)
{
	outputVehicleTripObjective(fout, "Vehicle costing least (based on fuel used)", vehicleTrip);
}

/**
 * Output vehicle costing most (based on fuel used)
 */
static void outputVehicleCostingMostFuelUsed(ostream &fout, const VehicleTrip &vehicleTrip)
{
	outputVehicleTripObjective(fout, "Vehicle costing most (based on fuel used)", vehicleTrip);
}

/**
 * Store trip results for a vehicle
 */
static void storeVehicle(ofstream &file, const VehicleTrip &vehicleTrip) {
	static bool needHeader = true;

	if (needHeader) {
		needHeader = false;
		file << VehicleRecords::formatHeaderForFile() << endl;
	}
	file << VehicleRecords::formatRecordForFile(vehicleTrip) << endl;
}

/**
 * Store trip results for a vehicle satisfying trip objective
 */
static void storeVehicleTripObjective(ofstream &file, const string &objective, const VehicleTrip &vehicleTrip) {
	static bool needLineSeparator = true;

	if (needLineSeparator) {
		needLineSeparator = false;
		file << endl;
	}
	file << (VehicleRecords::formatRecordForFile(vehicleTrip) + " # " + objective) << endl;
}

/**
 * Store trip results for vehicle arriving first
 */
static void storeVehicleArrivingFirst(ofstream &file, const VehicleTrip &vehicleTrip) {
	storeVehicleTripObjective(file, "Vehicle arriving first", vehicleTrip);
}

/**
 * Store trip results for vehicle arriving last
 */
static void storeVehicleArrivingLast(ofstream &file, const VehicleTrip &vehicleTrip) {
	storeVehicleTripObjective(file, "Vehicle arriving last", vehicleTrip);
}

/**
 * Store trip results for vehicle costing least (based on fuel added)
 */
static void storeVehicleCostingLeastFuelAdded(ofstream &file, const VehicleTrip &vehicleTrip) {
	storeVehicleTripObjective(file, "Vehicle costing least (fuel added)", vehicleTrip);
}

/**
 * Store trip results for vehicle costing most (based on fuel added)
 */
static void storeVehicleCostingMostFuelAdded(ofstream &file, const VehicleTrip &vehicleTrip) {
	storeVehicleTripObjective(file, "Vehicle costing most (fuel added)", vehicleTrip);
}

/**
 * Store trip results for vehicle costing least (based on fuel used)
 */
static void storeVehicleCostingLeastFuelUsed(ofstream &file, const VehicleTrip &vehicleTrip) {
	storeVehicleTripObjective(file, "Vehicle costing least (fuel used)", vehicleTrip);
}

/**
 * Store trip results for vehicle costing most (based on fuel used)
 */
static void storeVehicleCostingMostFuelUsed(ofstream &file, const VehicleTrip &vehicleTrip) {
	storeVehicleTripObjective(file, "Vehicle costing most (fuel used)", vehicleTrip);
}

/**
 * Entry point of the program.
 */
int main()
{
	// Get trip parameters
	TripParameters tripParameters;
	try {
		tripParameters = TripParameters(FILENAME_INPUT);
	} catch (const ifstream::failure &e) {
		cout << "Unable to open trip parameters file" << e.what() << endl;
		cout << "Program ending!" << endl;
		exit(1);
	} catch (const invalid_argument &e) {
		cout << e.what() << endl;
		cout << "Program ending!" << endl;
		exit(1);
	} catch (const out_of_range &e) {
		cout << e.what() << endl;
		cout << "Program ending!" << endl;
		exit(1);
	}

	// Output debug information for each trip parameter
	if (debug) {
		cout << "Average speed in the city (MPH): " << tripParameters.getMphCity() << endl;
		cout << "Average speed on the highway (MPH): " << tripParameters.getMphHighway() << endl;
		cout << "Average fuel price per gallon: " << tripParameters.getFuelPrice( )<< endl;
		cout << "Distance between gas stations (miles): " << tripParameters.getDistanceBetweenGasStations( )<< endl;
		cout << "Time between taking naps (hours): " << tripParameters.getTimeBetweenNaps() << endl;
		cout << "Time required to refuel (minutes): " << tripParameters.getRefuelTime() << endl;
		cout << "Time required to use the restroom (minutes): " << tripParameters.getRestroomTime() << endl;
		cout << "Time required to take a nap (minutes): " << tripParameters.getNapTime() << endl;
	}

	// Get trip route
	Trip trip;

	// Get list of vehicles
	vector<Vehicle *> vehicles;
	try {
		vehicles = VehicleRecords::getVehicles(FILENAME_VEHICLES);
	} catch (const ifstream::failure &e) {
		cout << "Unable to open vehicle records file" << e.what() << endl;
		cout << "Program ending!" << endl;
		exit(1);
	} catch (const invalid_argument &e) {
		cout << e.what() << endl;
		cout << "Program ending!" << endl;
		exit(1);
	} catch (const out_of_range &e) {
		cout << e.what() << endl;
		cout << "Program ending!" << endl;
		exit(1);
	}

	// Open file for storing results (truncates file)
	ofstream file;
	file.open(FILENAME_RESULTS);
	if (file.fail()) {
		cout << "Unable to open vehicle results file" << endl;
		cout << "Program ending!" << endl;
		exit(1);
	}

	// Initialize minimum/maximum vehicle trip objective variables
	VehicleTrip minVehicleTripTime;
	VehicleTrip maxVehicleTripTime;
	VehicleTrip minVehicleTripCostFuelAdded;
	VehicleTrip maxVehicleTripCostFuelAdded;
	VehicleTrip minVehicleTripCostFuelUsed;
	VehicleTrip maxVehicleTripCostFuelUsed;

	// Iterate over list of vehicles to determine which vehicles fulfill objectives
	for (int i = 0; i < (int) vehicles.size(); i++) {
		VehicleTrip vehicleTrip(vehicles[i], trip, tripParameters);

		// Determine if this vehicle satisfies one (or more) of the objectives
		if (minVehicleTripTime.isTimeMoreThan(vehicleTrip))
			minVehicleTripTime = vehicleTrip;
		if (maxVehicleTripTime.isTimeLessThan(vehicleTrip))
			maxVehicleTripTime = vehicleTrip;
		if (minVehicleTripCostFuelAdded.isFuelAddedCostMoreThan(vehicleTrip))
			minVehicleTripCostFuelAdded = vehicleTrip;
		if (maxVehicleTripCostFuelAdded.isFuelAddedCostLessThan(vehicleTrip))
			maxVehicleTripCostFuelAdded = vehicleTrip;
		if (minVehicleTripCostFuelUsed.isFuelUsedCostMoreThan(vehicleTrip))
			minVehicleTripCostFuelUsed = vehicleTrip;
		if (maxVehicleTripCostFuelUsed.isFuelUsedCostLessThan(vehicleTrip))
			maxVehicleTripCostFuelUsed = vehicleTrip;

		// Output debug information for each vehicle trip
		if (debug)
			cout << endl << vehicleTrip << endl;

		// Store vehicle trip results in file
		storeVehicle(file, vehicleTrip);
	}

	// Output results
	outputTripDistance(cout, trip);
	outputVehicleArrivingFirst(cout, minVehicleTripTime);
	outputVehicleArrivingLast(cout, maxVehicleTripTime);
	outputVehicleCostingLeastFuelAdded(cout, minVehicleTripCostFuelAdded);
	outputVehicleCostingMostFuelAdded(cout, maxVehicleTripCostFuelAdded);
	outputVehicleCostingLeastFuelUsed(cout, minVehicleTripCostFuelUsed);
	outputVehicleCostingMostFuelUsed(cout, maxVehicleTripCostFuelUsed);

	// Store results in file
	storeVehicleArrivingFirst(file, minVehicleTripTime);
	storeVehicleArrivingLast(file, maxVehicleTripTime);
	storeVehicleCostingLeastFuelAdded(file, minVehicleTripCostFuelAdded);
	storeVehicleCostingMostFuelAdded(file, maxVehicleTripCostFuelAdded);
	storeVehicleCostingLeastFuelUsed(file, minVehicleTripCostFuelUsed);
	storeVehicleCostingMostFuelUsed(file, maxVehicleTripCostFuelUsed);

	// Close file for storing results
	file.close();
}

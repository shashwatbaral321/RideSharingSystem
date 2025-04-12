#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Base Ride class
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0;  // Polymorphic method
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID
             << ", Pickup: " << pickupLocation
             << ", Dropoff: " << dropoffLocation
             << ", Distance: " << distance << " miles\n";
    }

    virtual ~Ride() {}
};

// StandardRide subclass
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 2.0;  // $2 per mile
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Standard Ride, Fare: $" << fare() << "\n";
    }
};

// PremiumRide subclass
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.5;  // $3.5 per mile
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Premium Ride, Fare: $" << fare() << "\n";
    }
};

// Driver class with encapsulation
class Driver {
private:
    int driverID;
    string name;
    float rating;
    vector<shared_ptr<Ride>> assignedRides;  // private ride list

public:
    Driver(int id, string n, float r) : driverID(id), name(n), rating(r) {}

    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "\nDriver ID: " << driverID << ", Name: " << name << ", Rating: " << rating << "\n";
        cout << "Assigned Rides:\n";
        for (const auto& ride : assignedRides) {
            ride->rideDetails();
        }
    }
};

// Rider class
class Rider {
private:
    int riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(int id, string n) : riderID(id), name(n) {}

    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "\nRider ID: " << riderID << ", Name: " << name << "\n";
        cout << "Ride History:\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
        }
    }
};

// Main simulation
int main() {
    // Create rides
    shared_ptr<Ride> ride1 = make_shared<StandardRide>(101, "Downtown", "Airport", 10);
    shared_ptr<Ride> ride2 = make_shared<PremiumRide>(102, "Hotel", "Convention Center", 5);

    // Create driver and assign rides
    Driver driver(1, "Alex Johnson", 4.8);
    driver.addRide(ride1);
    driver.addRide(ride2);

    // Create rider and request rides
    Rider rider(1001, "Emily Davis");
    rider.requestRide(ride1);
    rider.requestRide(ride2);

    // Output
    rider.viewRides();
    driver.getDriverInfo();

    return 0;
}

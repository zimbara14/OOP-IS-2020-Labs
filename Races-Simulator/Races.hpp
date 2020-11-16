//
//  Created by Sara Nikolić on 07.11.2020.
//  Copyright © 2020 Sara Nikolić. All rights reserved.
//

#ifndef Races_hpp
#define Races_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>


// - - - - TRANSPORTS - - - -
class Transport{
protected:
    double speed;
    std::string name;
    std::string typeTransport;
public:
    virtual ~Transport() = 0;
    double getSpeed() const;
    std::string getName() const;
    std::string getTypeTransport() const;

    virtual Transport* createTransport(std::string type) = 0;
    virtual double Calculator(double dist) = 0;
};

// - - - - EARTH TRANSPORTS - - - -
class EarthTransport : public Transport{
protected:
    int restInterval;
public:
    Transport* createTransport(std::string type) override;
    
    double Calculator(double dist) override;
    virtual double calcRestDuration(double distance) = 0;
    ~EarthTransport() = default;
};

class TwoHumpCamel : public EarthTransport{
public:
    TwoHumpCamel();
    
    double calcRestDuration(double distance) override;
};

class FastCamel : public EarthTransport{
public:
    FastCamel();
    
    double calcRestDuration(double distance) override;
};

class Centaur : public EarthTransport{
public:
    Centaur();
    
    double calcRestDuration(double distance) override;
};

class MagicBoots : public EarthTransport{
public:
    MagicBoots();
    
    double calcRestDuration(double distance) override;
};


// - - - - AIR TRANSPORTS - - - -
class AirTransport : public Transport{
public:
    Transport* createTransport(std::string type) override;
    
    ~AirTransport() = default;
    double Calculator(double dist) override;
    virtual double calcDistanceReducer(double distance) = 0;
};

class MagicCarpet : public AirTransport{
public:
    MagicCarpet();

    double calcDistanceReducer(double distance) override;
};

class Cane : public AirTransport{
public:
    Cane();
    
    double calcDistanceReducer(double distance);
};

class Broom : public AirTransport{
public:
    Broom();
    
    double calcDistanceReducer(double distance) override;
};

// - - - - BOTH TRANSPORTS - - - -
class BothTransport : public Transport {
public:
    Transport* createTransport(std::string type) override;
    
};

// - - - - RACE - - - -
class Race{
protected:
    double distance;
    std::string name;
    std::vector<Transport*> transportsRacing;
public:
    Race(std::string raceName, double raceDistance);
    ~Race();
    
    std::string getRaceName() const;
    double getRaceDistance() const;
    
    void addTransport(Transport* transport);
    int removeTransport(std::string transportName);
    
    std::string runThisRace();
    
    void printAll();
};

// - - - - GAME ENGINE - - - -
class GameEngine{
    Race* curr_race = nullptr;
public:
    std::string getCurr_RaceName();
    int getCurr_RaceDistance();
    
    void createRace(Race* race);
    void setRace(Race* race);
    
    void putVehicle(Transport* transportName);
    void removeVehicle(std::string transportName);
    
    std::string runRace();
    void stopRace();
    
    void printContestants();
};

#endif

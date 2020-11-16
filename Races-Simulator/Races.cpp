//
//  Races.cpp
//  races
//
//  Created by Sara Nikolić on 07.11.2020.
//  Copyright © 2020 Sara Nikolić. All rights reserved.
//

#include "Races.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <algorithm>


// - - - - TRANSPORTS - - - -
Transport::~Transport(){
    speed = 0;
    name = "";
    typeTransport = "";
}

std::string Transport::getName() const{
    return name;
}

double Transport::getSpeed() const{
    return speed;
}

std::string Transport::getTypeTransport() const{
    return typeTransport;
}

// - - - - EARTH TRANSPORTS - - - -
double EarthTransport::Calculator(double dist){
    double Time = dist / this->speed;
    if(Time < restInterval) return Time;
    else return (Time - this->calcRestDuration(dist));
}

TwoHumpCamel::TwoHumpCamel(){
    typeTransport = "Earth";
    name = "two-humped camel";
    speed = 10;
    restInterval = 30;
}

double TwoHumpCamel::calcRestDuration(double distance){
    int counter = distance / (speed * restInterval);
    if(counter == 1) return 5;
    else if(counter > 1) return (8 * (counter - 1) + 5);
    else throw std::runtime_error("Error! Something went wrong within the function TwoHumpCamel::calcRestDuration().");
}

FastCamel::FastCamel(){
    typeTransport = "Earth";
    name = "fast camel";
    speed = 40;
    restInterval = 10;
}

double FastCamel::calcRestDuration(double distance) {
    int counter = distance / (speed * restInterval);
    if(counter == 1) return 5;
    else if(counter == 2) return 5;
    else if(counter > 2) return (5 + 6.5 + (counter - 2) * 8);
    else throw std::runtime_error("Error! Something went wrong within the function FastCamel::calcRestDuration().");
}

Centaur::Centaur(){
    typeTransport = "Earth";
    name = "centaur";
    speed = 15;
    restInterval = 8;
}

double Centaur::calcRestDuration(double distance) {
    int counter = distance / (speed * restInterval);
    if(counter*2 != 0) return counter * 2;
    else throw std::runtime_error("Error! Something went wrong within the function Centaur::calcRestDuration().");
}

MagicBoots::MagicBoots(){
    typeTransport = "Earth";
    name = "magic boots";
    speed = 6;
    restInterval = 60;
}

double MagicBoots::calcRestDuration(double distance) {
    int counter = distance / (speed * restInterval);
    if(counter == 1) return 10;
    else if(counter > 1) return (10 + (counter - 1) * 5);
    else throw std::runtime_error("Error! Something went wrong within the function MagicBoots::calcRestDuration().");
}

Transport* EarthTransport::createTransport(std::string type){
    if(type == "two-humped camel") return new TwoHumpCamel();
        else if(type == "fast camel") return new FastCamel();
        else if(type == "magic boots") return new MagicBoots();
        else if(type == "centaur") return new Centaur();
        else throw std::runtime_error("Error! Transport with invalid name within the function EarthTransport::createTransport().");
}

// - - - - AIR TRANSPORTS - - - -
double AirTransport::Calculator(double dist){
    return ((dist * (1 - this->calcDistanceReducer(dist))) / speed);
}

MagicCarpet::MagicCarpet(){
    typeTransport = "Air";
    name = "magic carpet";
    speed = 10;
}

double MagicCarpet::calcDistanceReducer(double distance){
    if(distance < 1000) return 0;
    else if(distance < 5000) return 0.03;
    else if(distance < 10000) return 0.1;
    else if(distance >= 10000) return 0.05;
    else throw std::runtime_error("Error! Something went wrong within the function MagicCarpet::calcDistanceReducer().");
}

Cane::Cane(){
    typeTransport = "Air";
    name = "cane";
    speed = 8;
}

double Cane::calcDistanceReducer(double distance){
    return 0.06;
}

Broom::Broom(){
    typeTransport = "Air";
    name = "broom";
    speed = 10;
}

double Broom::calcDistanceReducer(double distance) {
    double _distanceReducer = 0;
    int _distance = distance;
    if(_distance >= 1000){
        while(_distance >= 1000){
            _distanceReducer += 0.01;
            _distance -= 1000;
        }
    } else _distanceReducer = 0;
    return _distanceReducer;
}

Transport* AirTransport::createTransport(std::string type){
    if(type == "magic carpet") return new MagicCarpet();
    else if(type == "broom") return new Broom();
    else if(type == "cane") return new Cane();
    else throw std::runtime_error("Error! Transport with invalid name within the function AirTransport::createTransport().");
}

// - - - - BOTH TRANSPORTS - - - -
Transport* BothTransport::createTransport(std::string type){
    if(type == "two-humped camel") return new TwoHumpCamel();
        else if(type == "fast camel") return new FastCamel();
        else if(type == "magic boots") return new MagicBoots();
        else if(type == "centaur") return new Centaur();
        else if(type == "magic carpet") return new MagicCarpet();
        else if(type == "broom") return new Broom();
        else if(type == "cane") return new Cane();
        else throw std::runtime_error("Error! Transport with invalid name within the function BothTransport::createTransport().");
}

// - - - - RACE - - - -
Race::Race(std::string Name, double dist){
    if(!(Name == "Both" || Name == "Air" || Name == "Earth")) throw std::runtime_error("Error! Invalid race type within the function Race::Race().");
    this->name = Name;
    this->distance = dist;
}

Race::~Race(){
    for(Transport* transport : transportsRacing) delete transport;
}

double Race::getRaceDistance() const{
    return this->distance;
}

std::string Race::getRaceName() const{
    return name;
}

void Race::addTransport(Transport* transport){
    if(this->getRaceName() == transport->getTypeTransport() || this->getRaceName() == "Both"){
        std::vector<Transport*>::iterator it;
        it = find (transportsRacing.begin(), transportsRacing.end(), transport);
        if (it != transportsRacing.end()) throw std::runtime_error("Error! Transport already exists within the function Race::addTransport().");
        transportsRacing.push_back(transport);
    } else throw std::runtime_error("Error! Invalid type of transport within the function Race::addTransport().");
}

int Race::removeTransport(std::string transportName){
    for(Transport* element : transportsRacing){
        if (element->getName() == transportName) {
            transportsRacing.erase(std::remove(transportsRacing.begin(), transportsRacing.end(), element));
            delete element;
            return 0;
        }
    }
    return -1;
}

void Race::printAll(){
    for(auto it = transportsRacing.begin(); it != transportsRacing.end(); ++it) std::cout << "Contestant is: " << (*it)->getName() << "\n";
}

std::string Race::runThisRace(){
    std::map<double, std::string> winners;
    for(auto it = transportsRacing.begin(); it != transportsRacing.end(); ++it){
        double Time = (*it)->Calculator(this->getRaceDistance());
        if(Time != 0) {winners[Time] = (*it)->getName();}
    }
    if(winners.begin()->first != 0) return winners.begin()->second;
    else return "Error";
}

// - - - - GAME ENGINE - - - -
std::string GameEngine::getCurr_RaceName(){
    return curr_race->getRaceName();
}

int GameEngine::getCurr_RaceDistance(){
    return curr_race->getRaceDistance();
}

void GameEngine::createRace(Race* race){
    if(!curr_race) this->curr_race = race;
    else throw std::runtime_error("Error! A race already exists within function GameEngine::createRace().");
}

void GameEngine::setRace(Race* race){
    if(!curr_race) this->curr_race = race;
    else{
        delete this->curr_race;
        this->curr_race = race;
    }
}

void GameEngine::putVehicle(Transport* transportName){
    if(!curr_race) throw std::runtime_error("Error! Invalid insertion of a transport within the function GameEngine::putVehicle().\n");
    this->curr_race->addTransport(transportName);
}

void GameEngine::removeVehicle(std::string transportName){
    if(this->curr_race->removeTransport(transportName) == -1) throw std::runtime_error("Error! Could not delete transport within the function GameEngine::removeTransport().");
}

void GameEngine::printContestants(){
    this->curr_race->printAll();
}

std::string GameEngine::runRace(){
    std::string result = this->curr_race->runThisRace();
    if(result != "Error") return result;
    else throw std::runtime_error("Error! Something went wrong within the function GameEngine::runRace().");
}

void GameEngine::stopRace(){
    if(curr_race) curr_race = nullptr;
    else throw std::runtime_error("Error! Unable to stop the race because it does not exist within the function GameEngine::stopRace().");
}

/*
 * Flight.h
 *
 *  Created on: 15/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <string>

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "Position.h"
#include "Common.h"
#include <list>

typedef struct {
	Position pos;
	float speed;
} Route;

class Flight {
public:
	Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed);
	Flight();
	virtual ~Flight();

	void update(float delta_t);
	void draw();


	std::list<Route> *getRoute() { return &route;};
	bool routed() { return !route.empty();};
	void setFocused(bool state) { focused = state;};
	bool getFocused() { return focused;};
	Position getPosition() { return pos;};
	float getInclination() { return inclination;};
	float getBearing() { return bearing;};
	float getDesbear() { return desbear;};
	void setDesbear();
	float getSpeed() { return speed;};
	float getPoints() {return points;};
	float getInstorm() {return instorm;}
	void setInstorm(bool state){ instorm = state;};
	std::string getId(){return id;};
	void setbegcurve();
	void getEndcurve();
	void getCenterrot();


private:
	std::string id;
	Position pos, last_pos;
	float bearing, inclination;
	float desbear;
	float speed;
	std::list<Route> route;
	bool focused;
	bool instorm;
	bool incurve;
	int testing;
	int closestd;
	Position centerrotation;
	float points;
	float radiorot;
	int signw;
	bool firstbear;
};

#endif /* FLIGHT_H_ */

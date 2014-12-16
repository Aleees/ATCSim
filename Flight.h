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

//typedef struct {
	//Position pointT;

//}TurnPoints;

typedef struct {

	Position pini;
	Position pfin;

}DosPuntos;

typedef enum  {NORMAL, GIRANDO}Tipostate;

class Flight {
public:
	Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed);
	virtual ~Flight();

	void update(float delta_t);
	void draw();


	std::list<Route> *getRoute() { return &route;};
	//std::list<TurnPoints> *getTurnPoints() { return &turnpoints;};
	bool routed() { return !route.empty();};
	void setFocused(bool state) { focused = state;};
	bool getFocused() { return focused;};
	Position getPosition() { return pos;};
	float getInclination() { return inclination;};
	float getBearing() { return bearing;};
	float getSpeed() { return speed;};
	float SetSpeed(float _speed) {speed= _speed;}
	float getPoints() {return points;};
	std::string getId(){return id;};
	float aceleration(float delta_t);
	void test();
	void doit( float delta_t);
	DosPuntos puntogiro(Position P2, Position P3, float radio);
	float AngularSpeed();
	bool Getsecuestrado(){return secuestrado;};
	Tipostate Setstate(Tipostate _state){state= _state;};
	bool SetCollisionPosible(bool _Col){CollisionPosible=  _Col;};

	float SetGoalBear( float GolB){goalBearing= GolB;};
int HL; //Nivel de 0 -> Ruta Aterrizaje, 1->1000, 2-> 1500 , , , ,   100 -> Sin Ruta 



private:
	std::string id;
	Position pos, last_pos;
	float bearing, inclination;
	float speed;
	std::list<Route> route;

	bool focused;

	float points;
	bool secuestrado;
	Tipostate state;
	int i;
	int j;

	float Dist;

	std::list<Position> turnpointso;
	std::list<Position> turnpointsf;
	std::list<Position> listvector;

	bool CollisionPosible;
float goalBearing;

//float goalBearing;




};

#endif /* FLIGHT_H_ */

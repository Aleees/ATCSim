/*
 * Storm.h
 *
 *  Created on: 12/11/2014
 *      Author: Jonathan
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

#ifndef ___STORM___
#define ___STORM___

#include "Position.h"
#include "Common.h"
#include <list>
#include "Flight.h"

class Storm {
public:
	Storm(int _id, Position _pos, float _bearing);
	virtual ~Storm();

	void update(float delta_t);
	void draw();

	Position getPosition() { return pos;};
	float getBearing() { return bearing;};
	float getSpeed() { return speed;};
	int getId(){return id;};

private:
	int id;
	Position pos, last_pos;
	float bearing,inclination;
	float speed;
	float radio;
	float minh, maxh;
};

#endif /*  ___STORM___ */

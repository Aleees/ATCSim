/*
 * Storm.cpp
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

#include "Storm.h"

#include "GUI.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "Common.h"

#include <iostream>
#include <string>
#include <math.h>

Storm::~Storm() {
	// TODO Auto-generated destructor stub
}

Storm::Storm(int _id, Position _pos, float _bearing)
{
	Route endroute;
	
	id = _id;
	pos = _pos;
	bearing = _bearing-pi/2;
	speed = 2000 + randomDouble()*100; //VIentos entre 20 y 100 m/s
	radio = randomDouble()*1900.0 + 100.0; //Radio de la tormenta entre 100 y 2000m
	minh = 100 + randomDouble()*1900; //Altura minima a la que se ven afectados los aviones
	maxh = minh + randomDouble()*(2000-minh);
	std::cerr	<<"Tormenta creada. Pos("<<pos.get_x()<<","<<pos.get_y()<<")"<<std::endl
			<<"bearing: "<<bearing*180/pi<<std::endl;

}

void
Storm::update(float delta_t)
{
	float trans;

	last_pos = pos;

	trans = speed * delta_t;


	pos.set_x(pos.get_x() + trans * sin(bearing) * cos(inclination));
	pos.set_y(pos.get_y() + trans * cos(bearing) * cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

//	if(pos.distance(last_pos) > pos.distance(endpos))
//		~Storm();
		

}

void
Storm::draw()
{

	

	glPushMatrix();

	//Draw Aeroplane
	glTranslatef(pos.get_x(), pos.get_y(), pos.get_z());
	GLUquadric *quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	//GLUquadratic colorcilinder[2,2,2,1]
	gluQuadricTexture(quadratic, GL_TRUE);
	//gluSphere( quadratic, COLLISION_DISTANCE/2.0f, 32, 32);
	gluCylinder(quadratic, radio,radio,500,32,1);
	glPopMatrix();

}

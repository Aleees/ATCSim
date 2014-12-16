/*
 * Flight.cpp
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

#include "Flight.h"

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

Flight::~Flight() {
	// TODO Auto-generated destructor stub
}
Flight::Flight(){

}
Flight::Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed)
{
	id = _id;
	pos = _pos;
	bearing = _bearing;
	inclination = _inclination;
	speed = _speed;
	route.clear();
	firstbear = true;
	points = INIT_FLIGHT_POINTS;
	focused = false;
	instorm = false;
	testing = 1;
	incurve = false;
	closestd = 0;
}
//Position Flight::getBegcurve()
//{
//	Position CPpos, beg;
//	float x,y,z;
//	float distcurve = 100;
//
//	CPpos = route.front().pos;
//	x = CPpos.get_x() - distcurve*sin(bearing)*cos(inclination);
//	y = CPpos.get_y() - distcurve*cos(bearing)*cos(inclination);
//	z = CPpos.get_z() - distcurve*sin(inclination);
//
//
//	beg.set_pos(x,y,z);
//
//
//}



//void
//Flight::setbegcurve()
//{
//	Position CPpos;
//	float distcurve = 500;
//	float x,y,z;
//	Route r;
//	CPpos = route.front().pos;
//
//		x = CPpos.get_x() - distcurve* cos(bearing) * cos(inclination);
//		y = CPpos.get_y() - distcurve* sin(bearing) * cos(inclination);
//		z = CPpos.get_z() - distcurve*sin(inclination);
//	Position pos(x,y,z);
//	r.pos = pos;
//	r.speed = route.front().speed;
//	route.push_front(r);
//	getEndcurve();
//	testing++;
//
//}

//void
//Flight::getEndcurve()
//{
//	Position beg,inter;
//	Route begr, interr,endr,nextr;
//	float x,y,z;
//	float distcurve = 500;
//	float futbearing,futincl;
//
//
//	begr = route.front();
//	route.pop_front();
//	interr = route.front();
//	route.pop_front();
//	nextr = route.front();
//
//	interr.pos.angles(nextr.pos,futbearing,futincl);
//
//	x = interr.pos.get_x() - distcurve*cos(futbearing)*cos(futincl);
//	y = interr.pos.get_y() - distcurve*sin(futbearing)*cos(futincl);
//	z = interr.pos.get_z() - distcurve*sin(futincl);
//
//	Position end(x,y,z);
//	endr.pos = end;
//	endr.speed = interr.speed;
//
//	route.push_front(endr);
//	route.push_front(interr);
//	route.push_front(begr);
//	getCenterrot();
//}

//Position Flight::getCenterrot()
//{
//	Route beg,inter,end,next;
//	float futbear, futincl;
//
//	beg = route.front();
//	route.pop_front();
//	inter = route.front();
//	route.pop_front();
//	end = route.front();
//	route.pop_front();
//	next = route.front();
//
//	route.push_front(end);
//	route.push_front(inter);
//	route.push_front(beg);
//
//	end.pos.angles(next.pos,futbear,futincl);
//
//
//}
//void
//Flight::getCenterrot()
//{
//	Route beg,inter,end,next,test;
//	Position posbeg, posend,CPpos;
//	float m1, m2;
//	float inc1, inc2;
//	float bearing2;
//	float normalm1, normalm2;
//	float rx, ry,rz;
//	float xb,yb,zb;
//	float xe,ye,ze;
//	float alfa1,alfa2,basura;
//
//
//
//	beg = route.front();
//	route.pop_front();
//	inter = route.front();
//	route.pop_front();
//	end = route.front();
//	route.pop_front();
//	next = route.front();
//
//	route.push_front(end);
//	//route.push_front(inter);
//	route.push_front(beg);
//
//
//	posbeg = beg.pos;
//	posend = end.pos;
//	CPpos = inter.pos;
//
//	CPpos.angles(posend,bearing2,inc2);
//
//	m1 = tan(bearing);
//	if(bearing2 != 0)
//		m2 = tan(bearing2);
//	else
//		m2 = tan(0.0000001);
//
//	normalm1 = -1/m1;
//	normalm2 = -1/m2;
//
//	xb = posbeg.get_x();
//	yb = posbeg.get_y();
//	zb = posbeg.get_z();
//
//	xe = posend.get_x();
//	ye = posend.get_y();
//	ze = posend.get_z();
//
//	rx = (yb-ye-normalm1*xb+normalm2*xe)/(normalm2-normalm1);
//	ry = yb+normalm1*(rx-xb);
//	rz = zb;
//
//	Position centerradio(rx,ry,rz);
//	centerrotation = centerradio;
//	//test.pos = centerradio;
//	//test.speed = inter.speed;
//	//route.push_back(test);
//	//std::cerr<<"x="<<CPpos.get_y()<<"y="<<posend.get_y()<<std::endl;
//	radiorot = posbeg.distance(centerradio);
//
//	std::cerr<<"En getCenterrot:"<<rx<<" "<<ry<<" "<<rz<<std::endl;
//	std::cerr<<"En posget:"<<posbeg.get_x()<<" "<<posbeg.get_y()<<" "<<posbeg.get_z()<<std::endl;
//	std::cerr<<"radiorot:"<<radiorot<<std::endl;
//
//	beg.pos.angles(end.pos,alfa1,basura);
//	end.pos.angles(next.pos,alfa2,basura);
//	signw = 1 - 2*(alfa1>alfa2 && alfa1<(pi+alfa2));
//	std::cerr<<"signw"<<" "<<signw<<std::endl;
//
//}

void
Flight::update(float delta_t)
{
	float trans;
	Position CPpos;
	float alfa1,alfa2;
	float basura;
	Route aux;
	Route next;
	bool status;
	//int signw;

	aux = route.front();
	route.pop_front();
	next = route.front();
	route.push_front(aux);

	if(routed()&&firstbear)
	{
		CPpos = route.front().pos;
		pos.angles(CPpos, bearing, inclination);
		bearing = normalizePi(bearing + M_PI);
		//speed = route.front().speed;
		firstbear = false;
	}

	if(routed())
	{
		CPpos = route.front().pos;
		pos.angles(CPpos, desbear, inclination);
		desbear = normalizePi(desbear + M_PI);
		//std::cerr<<(bearing<desbear) && (bearing > normalizePi(desbear-M_PI))<<std::endl;
		status = (bearing<desbear) && (bearing > normalizePi(desbear-M_PI));
//		if(focused)
//		{
//			std::cerr<<status<<std::endl;
//			std::cerr<<"Bear"<<bearing<<" "<<toDegrees(bearing)<<std::endl;
//			std::cerr<<"Desbear"<<desbear<<" "<<toDegrees(desbear)<<std::endl;
//			std::cerr<<"nor Desbear"<<normalizePi(desbear-M_PI)<<" "<<toDegrees(normalizePi(desbear-M_PI))<<std::endl;
//			std::cerr<<saturate((desbear-bearing),-1,1)*delta_t<<std::endl;
//			std::cerr<<"------------"<<std::endl;
//
//
//		}
		if(abs(desbear-bearing)<0.01)
			bearing = desbear;
		else{
			if((bearing<desbear) && (bearing > normalizePi(desbear-M_PI)))
			{
				bearing = normalizePi(bearing +saturate((desbear-bearing),-1,1)*delta_t);
			} else
			{
				bearing = normalizePi(bearing -saturate(abs((abs(desbear)-abs(bearing))),-1,1)*delta_t);
			}
		}


		//desbear = normalizePi(desbear + M_PI);
		//bearing = normalizePi(bearing +saturate((desbear-bearing),-1,1)*delta_t);
		//bearing = normalizePi(bearing +closestdir(desbear,bearing)*delta_t);



//		std::cerr<<"desbear"<<" "<<toDegrees(desbear)<<std::endl;
//		std::cerr<<"bearing"<<" "<<toDegrees(bearing)<<std::endl;
//		std::cerr<<toDegrees(0.2)<<" "<<toDegrees(normalizePi(0.2+M_PI))<<std::endl;
//		std::cerr<<closestd<<std::endl;
//		std::cerr<<saturate((desbear-bearing),-1,1)<<std::endl;
		//std::cerr<<"Resta"<<" "<<bearing - 0.00001*(bearing-desbear)<<std::endl;
//		std::cerr<<"------------------"<<std::endl;
		//bearing = normalizePi(bearing + M_PI);

		//std::cerr<<saturate(speed-route.front().speed,-30,30)*delta_t<<std::endl;
		speed = speed+ saturate(route.front().speed-speed,-30,30)*delta_t;


	}
	else
		inclination = 0.0;

	last_pos = pos;

	trans = speed * delta_t;

	if(!incurve)
	{
		pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
		pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
		pos.set_z(pos.get_z() + ( trans * sin(inclination)));
	}

	//if(pos.distance(last_pos) > pos.distance(CPpos))
	if(100 > pos.distance(CPpos) && route.size() > 2)
	{
		route.pop_front();
		pos.angles(CPpos, desbear, inclination);
		closestd = closestdir(desbear,bearing);

		//incurve = !incurve;
		//std::cerr<<"incurve"<<" "<<incurve<<std::endl;
	} else if(pos.distance(last_pos) > pos.distance(CPpos))
	{
		route.pop_front();
	}

	points = points - delta_t - instorm*delta_t*3;
//	if(testing<1)
//		setbegcurve();

}

void
Flight::draw()
{



	glPushMatrix();

	//Draw Aeroplane
	glTranslatef(pos.get_x(), pos.get_y(), pos.get_z());
	glRotatef(toDegrees(bearing), 0.0f, 0.0f, 1.0f);
	glRotatef(toDegrees(-inclination), 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glColor3f(1.0f,0.0f,0.0f);

		glVertex3f( 30.0f, 0.0f, 0.0f);
		glVertex3f( -30.0f, 32.0f, 0.0f);
		glVertex3f( -30.0f, -32.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.0f,0.0f,1.0f);

		glVertex3f( -10.0f, 0.0f, 0.0f);
		glVertex3f( -30.0f, 0.0f, 0.0f);
		glVertex3f( -30.0f, 0.0f, 21.0f);
	glEnd();


	//Draw Collision sphere

	if(focused)
		glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
	else if(instorm)
		glColor4f(0.0f,1.0f,1.0f, 0.2f);
	else
		glColor4f(1.0f,1.0f,1.0f, 0.2f);


	GLUquadric *quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	gluSphere( quadratic, COLLISION_DISTANCE/2.0f, 32, 32);
	glPopMatrix();

	if(focused)
	{
		std::list<Route>::iterator it;

		TextDisplay *textDisplay = TextDisplay::getInstance();
		char pos_str[255];

		textDisplay->displayText((char*)id.c_str(), 15, 75, GUI::win_width, GUI::win_height, LIGHTBLUE, GLUT_BITMAP_HELVETICA_18);
		snprintf(pos_str, 255, "Points: %5.5lf ", points);
		textDisplay->displayText(pos_str, 15, 95, GUI::win_width, GUI::win_height, YELLOW, GLUT_BITMAP_HELVETICA_12);

		snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", pos.get_x(), pos.get_y(), pos.get_z());
		textDisplay->displayText(pos_str, 15, 115, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Bearing: %lf deg", toDegrees(bearing));
		textDisplay->displayText(pos_str, 15, 135, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Inclination: %lf deg", toDegrees(inclination));
		textDisplay->displayText(pos_str, 15, 155, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Speed: %lf m/sec", speed);
		textDisplay->displayText(pos_str, 15, 175, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		//TEXTO POR MI!!!!!!!!!!!!!! BORRAR LUEGO!
		snprintf(pos_str, 255, "Incurve: %d", incurve);
		textDisplay->displayText(pos_str, 15, 195, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Instorm: %d", instorm);
		textDisplay->displayText(pos_str, 15, 215, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);


		if(!route.empty())
		{

			glColor4f(0.0f,0.0f,1.0f, 1.0f);
			glBegin(GL_LINES);

			glVertex3f(pos.get_x(), pos.get_y(), pos.get_z());
			for(it = route.begin(); it!=route.end(); ++it)
			{
				glVertex3f((*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
				glVertex3f((*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
			}
			glEnd();

			for(it = route.begin(); it!=route.end(); ++it)
			{
				glPushMatrix();
				glTranslatef((*it).pos.get_x(), (*it).pos.get_y(),(*it).pos.get_z());
				GLUquadric *quadratic = gluNewQuadric();
				gluQuadricNormals(quadratic, GLU_SMOOTH);
				gluQuadricTexture(quadratic, GL_TRUE);
				gluSphere( quadratic, 50.0f, 32, 32);
				glPopMatrix();
			}


			textDisplay->displayText((char *)"Route", 15, 230, GUI::win_width, GUI::win_height, BLUE, GLUT_BITMAP_HELVETICA_12);

			int c = 0;
			for(it = route.begin(); it!=route.end(); ++it)
			{
				snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", (*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
				textDisplay->displayText(pos_str, 25, 250+(20*c), GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
				c++;
			}
			//MIOOOOOOOOOOOOOOOOO!!!!
			snprintf(pos_str, 255, "Position of center: (%lf, %lf, %lf) m", centerrotation.get_x(), centerrotation.get_y(), centerrotation.get_z());
			textDisplay->displayText(pos_str, 25, 250+(20*(c+1)), GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);

			glPushMatrix();
				glTranslatef(centerrotation.get_x(), centerrotation.get_y(),centerrotation.get_z());
				GLUquadric *quadratic = gluNewQuadric();
				gluQuadricNormals(quadratic, GLU_SMOOTH);
				gluQuadricTexture(quadratic, GL_TRUE);
				gluSphere( quadratic, 50.0f, 32, 32);
			glPopMatrix();

		}

	}




}

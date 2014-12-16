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
#include "AirController.h"

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

Flight::Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed)
{
	id = _id;
	pos = _pos;
	bearing = _bearing;
	inclination = _inclination;
	speed = _speed;
	route.clear();

	points = INIT_FLIGHT_POINTS;
	focused = false;
	secuestrado=randomDouble()>0.99;
	state = NORMAL;
	i=0;

	CollisionPosible=0;
	 j=0;
	HL=100;

}


float Flight::aceleration(float t)
{
	float V1=route.front().speed;

	float a;
	float Vo=speed;
	

	a=(V1-Vo)/t;

	if (a>MAX_ACELERATION)
	{
		a=MAX_ACELERATION;
		return a;
	}
	if (a<MIN_ACELERATION)
	{
		a=MIN_ACELERATION;
		return a;
	}
	return a;

}

float Flight::AngularSpeed()
{

Position CPpos;


		CPpos = route.front().pos;
		pos.angles(CPpos, goalBearing, inclination);
/*
if (CollisionPosible==1)
{
	goalBearing=-bearing;
std::cerr<<"holaaaaaaaaaaa***************************"<<std::endl;
}
else 
*/
	goalBearing=normalizePi(goalBearing+M_PI);

	float angularspeed;

angularspeed=normalizePi(goalBearing-bearing);


//std::cerr<<"bearing: "<<bearing<<" goalbearing: "<<goalBearing<<"AngularSpeed:  "<<angularspeed<<" MAX_AngularSpeed: "<<MAX_ANGULARSPEED<<" MIN_AngularSpeed:  "<<MIN_ANGULARSPEED<<std::endl;

	if (angularspeed>MAX_ANGULARSPEED)
	{
		angularspeed=MAX_ANGULARSPEED;
		return angularspeed;
	}
	if (angularspeed<MIN_ANGULARSPEED)
	{
		angularspeed=MIN_ANGULARSPEED;
		return angularspeed;
	}


	return angularspeed;



}


void
Flight::test()
{


	std::list<Flight*>::iterator it;

	float radio;
	radio=route.front().speed/ANGULARSPEED;//mejor route.front().speed que speed xk cuando vaya a girar va a tener esa velocidad
	Position P1, P2, P3, Po,Pfin;
	DosPuntos Point;

	//P1=pos;
	P2=route.begin()->pos;
	std::list<Route>::iterator it1=route.begin();
	it1++;
	P3=(*it1).pos;

	Point=puntogiro(P2, P3,radio);

		Route NRoute;
	Position posNR (pos.get_x()-route.front().pos.get_x(),
				      pos.get_y()-route.front().pos.get_y(), 
				      pos.get_z()-route.front().pos.get_z() );
	NRoute.speed =speed;
	NRoute.pos=posNR;


	switch (state)
	{

	case NORMAL:

		if((pos.distance(route.front().pos))<Dist )
			{
				state= GIRANDO;
	//			route.pop_front();
			}
		else if (CollisionPosible==1)
			{	
				state= GIRANDO;
				//route.pop_front();
				//route.push_front(NRoute);
				std::cerr<<"estoy girandooooooooooooooooooooooooooooooooooo"<<std::endl;
				
			}

			else
			{

				state= NORMAL;

			}
		break;

	case GIRANDO:


		if (fabs(AngularSpeed())<0.1)

		{
			state=NORMAL;

		}


		break;

	default:
		state= NORMAL;


	}
}


void Flight::doit( float delta_t)
{
	float radio=speed/ANGULARSPEED;
	std::list<Flight*>::iterator it;
Position CPpos;



	switch (state)
	{

	case NORMAL:

		CPpos = route.front().pos;
		pos.angles(CPpos, bearing, inclination);

		bearing=normalizePi(bearing+M_PI);


		//std::cerr<<" bearing normal: "<<bearing<<"goalbearing: "<<goalBearing<<std::endl;
		i=0;

		break;

	case GIRANDO:

	bearing=normalizePi(bearing+AngularSpeed()*delta_t);
	//std::cerr<<"estoy girando"<<std::endl;


		if(i==0)
	 	{	

		route.pop_front();// borra el primer punto de la lista
		//route.push_front(NRoute);
		i++;
		}

		break;

	}
}

void
Flight::update(float delta_t)
{
	Position pos3(-750.0, 0.0, 25.0);
	Position finalapp(0.0, 0.0, 25.0);
	Position finalapp1(500.0, 0.0, 100.0);
	int estado;
	float trans;
	Position CPpos;
	float AngularSpeed;

	if(routed())

	{

		if (route.front().pos.get_x()== finalapp.get_x() &&
			route.front().pos.get_y()== finalapp.get_y() &&
			route.front().pos.get_z()== finalapp.get_z() )
		{

				CPpos = route.front().pos;
				pos.angles(CPpos, bearing, inclination);
				bearing = normalizePi(bearing+M_PI);

				//std::cerr<<"estoy fueraaaaaaaaaaaa"<<std::endl;

			}
		else
		{

					test();
					doit(delta_t);

		}

//std::cerr<<"distancia para girar"<<(pos.distance(route.front().pos))<<"valor absoluto: "<<"distancia"<<Dist<<std::endl;

//std::cerr<<"  goaaal beariiing: "<<goalBearing<<std::endl;


	if (j==0)
	{
		speed = route.front().speed;
	j++;
	}

	else
	{
		//speed = route.front().speed;
	     speed += aceleration(delta_t)*delta_t;
	}

	
	

	}else
		inclination = 0.0;

	last_pos = pos;

	trans = speed * delta_t;





	pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
	pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

	if(pos.distance(last_pos) > pos.distance(CPpos))
		route.pop_front();

	if (secuestrado)
		points = points - 4*delta_t;
	else
		points = points - delta_t;




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

	if(!secuestrado)
		glColor3f(1.0f,0.0f,0.0f);
	else
		glColor3f(0.0f,1.0f,0.0f);

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

		}

	}


}
DosPuntos Flight::puntogiro(Position P2, Position P3,float radio)
{
    float P1x,P1y,P1z;  //PUNTOS
    float P2x,P2y,P2z;
    float P3x,P3y,P3z;

    float PC1x,PC1y,PC1z;  //PUNTOS
    float PC2x,PC2y,PC2z;

    float V21x,V21y,V21z;   //VECTORES
    float V23x,V23y,V23z;

    float MV21, MV23;       //MODULOS
    float Ang;
    float Radio = radio;

    Position P1=pos;
    DosPuntos PuntoOut;

    P1x = P1.get_x();
    P1y = P1.get_y();
    P1z = P1.get_z();

    P2x = P2.get_x();
    P2y = P2.get_y();
    P2z = P2.get_z();

    P3x = P3.get_x();
    P3y = P3.get_y();
    P3z = P3.get_z();




    V21x = P1x - P2x;
    V21y = P1y - P2y;
    V21z = P1z - P2z;

    V23x = P3x - P2x;
    V23y = P3y - P2y;
    V23z = P3z - P2z;

    MV21 = sqrt( V21x*V21x + V21y*V21y + V21z*V21z );
    MV23 = sqrt( V23x*V23x + V23y*V23y + V23z*V23z );




    Ang =acos( ((V21x*V23x)+(V21y*V23y)+(V21z*V23z))/(MV21*MV23));   //*(180/3.14159265359);

    //float Dist ;
    Dist = Radio / tan(Ang/2);

    float Land21 = Dist / MV21;
    float Land23 = Dist / MV23;



    PC1x = P2x + Land21 * V21x;
    PC1y = P2y + Land21 * V21y;
    PC1z = P2z + Land21 * V21z;

    PC2x = P2x + Land23 * V23x;
    PC2y = P2y + Land23 * V23y;
    PC2z = P2z + Land23 * V23z;

    PuntoOut.pini.set_x(PC1x);
    PuntoOut.pini.set_y(PC1y);
    PuntoOut.pini.set_z(PC1z);

    PuntoOut.pfin.set_x(PC2x);
    PuntoOut.pfin.set_y(PC2y);
    PuntoOut.pfin.set_z(PC2z);

	//std::cout<<"los puntos son:"<<PuntoOut.pini.get_x()<<","<<PuntoOut.pini.get_y()<<","<<PuntoOut.pini.get_z()<<std::endl;
/*
	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);
	glTranslatef(PuntoOut.pini.get_x(),PuntoOut.pini.get_y(),PuntoOut.pini.get_z());
				GLUquadric *quadratic = gluNewQuadric();
				gluQuadricNormals(quadratic, GLU_SMOOTH);
				gluQuadricTexture(quadratic, GL_TRUE);
				gluSphere( quadratic, 50.0f, 32, 32);
				glPopMatrix();




				glPushMatrix();
				glColor3f(1.0f,0.0f,0.0f);
				glTranslatef(PuntoOut.pfin.get_x(),PuntoOut.pfin.get_y(),PuntoOut.pfin.get_z());
							//GLUquadric *quadratic = gluNewQuadric();
							gluQuadricNormals(quadratic, GLU_SMOOTH);
							gluQuadricTexture(quadratic, GL_TRUE);
							gluSphere( quadratic, 50.0f, 32, 32);
							glPopMatrix();
*/
    turnpointso.push_back(PuntoOut.pini);
    turnpointsf.push_back(PuntoOut.pfin);
 	//anglegiro.push_back(Ang);

Position puntoauxo= turnpointso.front();
Position puntoauxf= turnpointsf.front();

/*
				glPushMatrix();
				glColor3f(0.0f,1.0f,0.0f);
				glTranslatef(puntoauxo.get_x(),puntoauxo.get_y(),puntoauxo.get_z());
							GLUquadric *quadratic = gluNewQuadric();
							gluQuadricNormals(quadratic, GLU_SMOOTH);
							gluQuadricTexture(quadratic, GL_TRUE);
							gluSphere( quadratic, 50.0f, 32, 32);
							glPopMatrix();


				glPushMatrix();
				glColor3f(0.0f,1.0f,0.0f);
				glTranslatef(puntoauxf.get_x(),puntoauxf.get_y(),puntoauxf.get_z());
							//GLUquadric *quadratic = gluNewQuadric();
							gluQuadricNormals(quadratic, GLU_SMOOTH);
							gluQuadricTexture(quadratic, GL_TRUE);
							gluSphere( quadratic, 50.0f, 32, 32);
							glPopMatrix();

*/
float Pvy, Pvx, Pvz;
	Pvx=(V21y*V23z)-(V23y*V21z);
	Pvy=(V21x*V23z)-(V23x*V21z);
	Pvz=(V21x*V23y)-(V23x*V21y);

Position vectorxyz;

	vectorxyz.set_x(Pvx);
	vectorxyz.set_y(Pvy);
	vectorxyz.set_z(Pvz);

	listvector.push_back(vectorxyz);



    return PuntoOut;

/*	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;


	for(it = flights.begin(); it!=flights.end(); ++it)
	{


			if((*it)->getTurnPoints()->empty())
			{

				(*it)->getTurnPoints()->push_back(PuntoOut.pini);
				(*it)->getTurnPoints()->push_front(PuntoOut.pfin);



				}
			}
*/



}

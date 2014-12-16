/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
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

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include <list>
#include <sys/time.h>

AirController::AirController() {
	// TODO Auto-generated constructor stub
	Position pos1(3000.0, 000.0, 600.0);
	Route r1;
	Entryroute rutaen;
	int i;
	for(i=0;i<NUM_RUTAS_ENTRADA;i++)
	{
		pos1.set_x(pos1.get_x()+i*DIST_RUTAS_ENTRADA);
		r1.pos = pos1;
		r1.speed = 100.0;
		rutaen.route = r1;
		//iniRutaentrada(rutaen);
		if(i==1)
		{
			std::cerr<<"R1pos"<<r1.pos.get_x()<<std::endl;
		}
		rutasentrada[i] = rutaen;

	}
	iniRutaentrada();
	lastupdate = 0;


}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

// bool AirController::checkAvailability(float pista, float tiempo)
// {
//	int i,j;
//	for(i=pista;i>0;i--)
//	{
//		for(j=tiempo;j>0;i--)
//		{
//			if(tablahorarios[i][j]==true)		
//		
//		}
//	
//	
//	}
// 
// 
// }
void
AirController::iniRutaentrada()
{

	Position pos1(3000.0, 000.0, 600.0);
	Route r1;
	int j;
	int rutanum;
	Entryroute rutaen;
	int i;
	for(i=0;i<NUM_RUTAS_ENTRADA;i++)
	{
		pos1.set_x(pos1.get_x()+i*DIST_RUTAS_ENTRADA);
		r1.pos = pos1;
		r1.speed = 100.0;
		rutaen.route = r1;
		//iniRutaentrada(rutaen);
		if(i==1)
		{
			std::cerr<<"R1pos"<<r1.pos.get_x()<<std::endl;
		}
		rutasentrada[i] = rutaen;
		for(j=0;j<FRANJAS_EN_RUTA;j++)
		{
			rutasentrada[i].timetable[j] = false;


		}

	}
	//iniRutaentrada();
	lastupdate = 0;
//	for(i=0;i< NUM_RUTAS_ENTRADA;i++)
//	{
//		for(j=0;j<FRANJAS_EN_RUTA;j++)
//		{
//			rutasentrada[i].timetable[j] = false;
//
//
//		}
//	}

}
float
AirController::timetoarrive(Entryroute ruta, Flight vuelo)
{
	float distancia = vuelo.getPosition().distance(ruta.route.pos);
	return distancia / vuelo.getSpeed();
}

int
AirController::timetofranja(float tiempo,int secenfranja)
{
	int i=0;
	while((i+1)*secenfranja<tiempo)
		i++;
	std::cerr<<tiempo<<" "<<i<<std::endl;
	return i;

}
//void
//AirController::generateEntryRoute()
//{
//	float x = 600+rutasentrada.size()*100;
//	Position pos1(3000.0, 000.0, x);
//	Route r1;
//	Entryroute ruta;
//	r1.pos = pos1;
//	r1.speed = 100.0;
//	ruta.route = r1;
//	iniRutaentrada(ruta);
//	rutasentrada.push_front(ruta);
//
//}

bool
AirController::disponibilidad(Entryroute ruta, Flight vuelo)
{
	float tiempo = timetoarrive(ruta,vuelo);
	int franja = timetofranja(tiempo,SEC_FRANJA );
	return ruta.timetable[franja];
}

int
AirController::franjadisponible(int inifranja)
{
	int i;
	//int inifranja = timetofranja(timetoarrive(rutasentrada[0],vuelo),5);
	bool asigned=false;
	i = inifranja;
	while(!asigned)
	{
		if(!rutasentrada[0].timetable[i])
			asigned = true;
		else
			i++;
	}
	return i;
}


Route
AirController::asignroute(Flight vuelo)
{
	int i;
	int inifranja = timetofranja(timetoarrive(rutasentrada[0],vuelo),SEC_FRANJA );
	int franjaen0 = franjadisponible(inifranja);
	bool status;
	std::cerr<<vuelo.getId()<<std::endl;
	std::cerr<<inifranja<<std::endl;
	std::cerr<<franjaen0<<std::endl;
	std::cerr<<timetoarrive(rutasentrada[0],vuelo)<<std::endl;
	for(i=0;i<NUM_RUTAS_ENTRADA;i++)
	{
		if((franjaen0-i)<0)
			break;
		rutasentrada[i].timetable[franjaen0-i] = true;
	}

	if(franjaen0==inifranja)
	{
//		for(i=0;i<NUM_RUTAS_ENTRADA;i++)
//		{
//			if((franjaen0-i)<0)
//				break;
//			rutasentrada[i].timetable[franjaen0-i] = true;
//		}
		std::cerr<<"ruta"<<0<<std::endl;
		return rutasentrada[0].route;
	} else
	{

		//status = (franjaen0-inifranja)<(NUM_RUTAS_ENTRADA-1);
		//std::cerr<<status<<std::endl;
			if(((franjaen0-inifranja)<(NUM_RUTAS_ENTRADA-1)))
			{
//				std::cerr<<franjaen0-inifranja<<std::endl;
//				std::cerr<<rutasentrada[2].route.pos.get_x()<<std::endl;
//				std::cerr<<rutasentrada[2].route.pos.get_y()<<std::endl;
//				std::cerr<<rutasentrada[2].route.pos.get_z()<<std::endl;
				std::cerr<<"ruta"<<franjaen0-inifranja<<std::endl;
				return rutasentrada[franjaen0-inifranja].route;
			}
			else {
				std::cerr<<"ruta"<<franjaen0%(NUM_RUTAS_ENTRADA-1)<<std::endl;
				return rutasentrada[franjaen0%(NUM_RUTAS_ENTRADA-1)].route;
			}

	}


//	if(franjaen0<10)
//	{
//		for(i=0;i<franjaen0;i++)
//		{
//			rutasentrada[franjaen0-i].timetable[i] = true;
//
//		}
//		return rutasentrada[0].route;
//	} else {
//		for(i=0;i<10;i++)
//		{
//			rutasentrada[i].timetable[franjaen0-(10-i)-2]=true;
//		}
//	}
//	return rutasentrada[franjaen0].route;
}

void
AirController::updaterutas()
{
	int i,j;
	for(i=0;i<NUM_RUTAS_ENTRADA;i++)
	{
		for(j=0;j<FRANJAS_EN_RUTA-1;j++)
		{
			rutasentrada[i].timetable[j] = rutasentrada[i].timetable[j+1];
		}
		rutasentrada[i].timetable[FRANJAS_EN_RUTA-1] = false;
	}


}

void AirController::boo()
{

};

void
AirController::paintTable()
{
	int i,j;
	for(i=0;i<NUM_RUTAS_ENTRADA;i++)
	{
		std::cerr<<"ruta"<<i<<std::endl;
		for(j=0;j<10;j++)
		{
			std::cerr<<" "<<rutasentrada[i].timetable[j]<<" ";
		}
		std::cerr<<std::endl;
	}

}
void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;
	long ta;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	//Flight vuelo;

	ta = tv.tv_sec*1000000 + tv.tv_usec;
	//tb = last_ts.tv_sec*1000000 + last_ts.tv_usec;

//	delta_t = ((float)(ta-tb)) /1000000.0;
//	last_ts = tv;
	float bearing,inclination;

	
	
	Position pos0(5000.0, 2000.0, 1200.0);
	Position pos1(3000.0, 000.0, 600.0);
	Position pos2(0.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	Route r0, r1, r2, r3;
	r0.pos = pos0;
	r0.speed = 200;


	r1.pos = pos1;
	r1.speed = 100.0;



	//Linea final. NO TOCAR. Común a todos.
	r2.pos = pos2;
	r2.speed = 15.0;
	r3.pos = pos3;
	r3.speed = 0.0;



	for(it = flights.begin(); it!=flights.end(); ++it)
	{
		if((*it)->getRoute()->empty())
		{
			if(it != flights.begin()){
				paintTable();
				r1 = asignroute(*(*it));
				paintTable();
				//std::cerr<<r1.pos.get_x()<<std::endl;
				--it;
				it++;

			}
//			if(it != flights.begin()){
//					r1.pos.set_x(r1.pos.get_x()+(*(--it))->getRoute()->begin()->pos.get_x());
//					it++;
//
//				}

			(*it)->getRoute()->push_back(r3);
			(*it)->getRoute()->push_front(r2);
			(*it)->getRoute()->push_front(r1);

			(*it)->getPosition().angles(pos2,bearing,inclination);
			bearing = normalizePi(bearing+M_PI);
			//std::cerr<<bearing<<std::endl;
			if(bearing<0.9&&bearing>0)
			{
				r0 = r1;
				r0.pos.set_y(-300);
				(*it)->getRoute()->push_front(r0);
			}
			if(bearing>-0.9 && bearing<0)
			{
				r0 = r1;
				r0.pos.set_y(300);
				(*it)->getRoute()->push_front(r0);
			}


			//(*it)->getRoute()->push_front(r0);

		}
//		 if((*it)->getRoute()->empty())
//		        {
//		            if(it != flights.begin()){
//		                r1.pos.set_x(r1.pos.get_x()+(*(--it))->getRoute()->begin()->pos.get_x());
//		                it++;
//
//		            }
//		            (*it)->getRoute()->push_front(r1);
//		            (*it)->getRoute()->push_back(r2);
//		            (*it)->getRoute()->push_back(r3);
//		        }
	}

	if(ta-lastupdate >SEC_FRANJA*1000000)
	{
		updaterutas();
		lastupdate = ta;
	}
	boo();



}

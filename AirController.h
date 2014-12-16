/*
 * AirController.h
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

#ifndef AIRCONTROLLER_H_
#define AIRCONTROLLER_H_

#include "Singleton.h"
#include "Position.h"
#include "Flight.h"

class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();

	bool GetTurnCollision(){return TurnCollision;};
	

private:

	
   Position HLP[4][10];
   Route r[4][10];
    Position AltF;
    Position AltF1;
    Route RAltF1;
    Route RAltF;
    int NVE; // NUMERO DE VUELOS EN ESPERA
    int Ini; // Inicia Vuelos
    int CambioAlt;    

    int g;



	float t1;
	float t2;
	//int cont;
	float distanciax;
	float distanciay;
	float distanciaz;
	Route raux;
	bool TurnCollision;
	int f1;


};

#endif /* AIRCONTROLLER_H_ */

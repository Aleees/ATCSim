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
#include <list>
#include "Flight.h"


//int numrutasentrada = 10;
typedef struct{
	Route route;
	bool timetable[SEC_FRANJA];
} Entryroute;

class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();
private:
	//float tablahorarios[10][30];
	//int numrutasentrada = 10;
	Entryroute rutasentrada[NUM_RUTAS_ENTRADA];
	void iniRutaentrada();
	float timetoarrive(Entryroute ruta, Flight vuelo);
	bool disponibilidad(Entryroute ruta, Flight vuelo);
	int timetofranja(float tiempo,int secenfranja);
	void paintTable();
	int franjadisponible(int inifranja);
	Route asignroute(Flight vuelo);
	void generateEntryRoute();
	double lastupdate;
	void updaterutas();
	void boo();
};

#endif /* AIRCONTROLLER_H_ */

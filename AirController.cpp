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
#include <math.h>
#include <time.h>
#include <time.h>



    //Primer Segundo Indide Numero de Puntos, Indice Nivel
 

AirController::AirController() {
    // TODO Auto-generated constructor stub


   int Indi[8]={0, 1, 2, 3, 0, 1, 2, 3};     

    

//std::list<Route> LRoute;
    

    NVE=0; // NUMERO DE VUELOS EN ESPERA
    Ini=0; // Inicia Vuelos
    CambioAlt=0;    

    g=0;

    f1=0;

    //NIVEL ->0 TRAYECTORIA DE ATERIZAJE
    HLP[0][0]=Position(-750.0, 0.0,  25.0);    
    HLP[1][0]=Position(   0.0, 0.0,  25.0);
    HLP[2][0]=Position( 50.0, 0.0, 100.0);
    HLP[3][0]=Position(5000.0, 0.0, 500.0);

    r[0][0].pos=HLP[0][0];         r[0][0].speed =  15.0;
    r[1][0].pos=HLP[1][0];         r[1][0].speed =  20.0;
    r[2][0].pos=HLP[2][0];         r[2][0].speed =  80.0;
    r[3][0].pos=HLP[3][0];         r[3][0].speed = 380.0;

    int k ;
    float Altura = 1000.0 ;
    for ( k=1 ; k<10 ; k++)
    {
    

        HLP[0][k]=Position( 3000.0,   -10000.0,   Altura);
        HLP[1][k]=Position( 3000.0,   -2000.0,   Altura);
        HLP[2][k]=Position( 13000.0,  -2000.0,   Altura);
        HLP[3][k]=Position( 13000.0,  -10000.0,   Altura);

        Altura += 500.0;
    }

    for ( k=1 ; k<10; k++)
    {
        r[0][k].pos=HLP[0][k];         r[0][k].speed = 380.0;
        r[1][k].pos=HLP[1][k];         r[1][k].speed = 380.0;
        r[2][k].pos=HLP[2][k];         r[2][k].speed = 380.0;
        r[3][k].pos=HLP[3][k];         r[3][k].speed = 380.0;
    }

}

AirController::~AirController() {
    // TODO Auto-generated destructor stub
}


void TimepoColision()
{

}


void
AirController::doWork()
{

int NHLA=0;
//    std::list<Flight*>::iterator i,j;


    std::list<Flight*> flights = Airport::getInstance()->getFlights();
    std::list<Flight*>::iterator it, it1, it2, it3, it4;

    // ESTABLECE LAS 8 RUTAS PARA LOS VUELOS INICIALES  
    if(g<10)
    {
        for(it = flights.begin(); it!=flights.end(); it++) 
        {

            if ((*it)->Getsecuestrado()==1 && (*it)->getRoute()->empty())
                {
                (*it)->getRoute()->push_front(r[0][0]);
                (*it)->getRoute()->push_front(r[1][0]);
                (*it)->getRoute()->push_front(r[2][0]);
                (*it)->getRoute()->push_front(r[3][0]);
                //g++;
                }
            else if((*it)->getRoute()->empty() )       
            {
                (*it)->HL=g;
                (*it)->getRoute()->push_front(r[0][g]);
                (*it)->getRoute()->push_front(r[1][g]);
                (*it)->getRoute()->push_front(r[2][g]);
                (*it)->getRoute()->push_front(r[3][g]);
                //g++;
            }


/*
			std::cerr	<<"Numero Vuelos:"<< flights.size()
					<<" Vuelo:"       << (*it)->getId() 
                    <<" Nivel:"       << (*it)->HL 
					<<" Numero P.R.:" << (*it)->getRoute()->size()
					<<" speed:" << (*it)->getRoute()->begin()->speed  
					<<" altura:" << (*it)->getRoute()->begin()->pos.get_z()  
              		<<  std::endl;	
*/



        }    
    }

	// NHL -> NUMERO DE VUELOS EN EL NIVEL 0, RUTA ATERRIZAJE
    int NHL=0;
    for (it1 = flights.begin(); it1!=flights.end(); it1++) 
    {
        if ((*it1)->HL==0)
            NHL++;
    } 

    // CONTROL SOBRE LAS RUTAS PARA QUE SE HAGAN EN CIRCULOS Y SABER SI HA ATERRIZADO
    for (it2 = flights.begin(); it2!=flights.end(); it2++) 
    {

		if ((*it2)->getId()=="IB0004") 
		{
/*
			std::cerr  <<"Vuelo:"       << (*it2)->getId() 
	                   	<<" Nivel:"      << (*it2)->HL    
					<<" altura:" << (*it2)->getRoute()->begin()->pos.get_z() 

      		<<  std::endl;	

*/

		}
		
        if ((*it2)->HL > 0  && (*it2)->HL < 100 && (*it2)->getRoute()->size() ==1)
        {
/*
            (*it2)->getRoute()->push_front(r[0][(*it2)->HL]);
            (*it2)->getRoute()->push_front(r[1][(*it2)->HL]);
            (*it2)->getRoute()->push_front(r[2][(*it2)->HL]);
            (*it2)->getRoute()->push_front(r[3][(*it2)->HL]);
	*/		
			
            (*it2)->getRoute()->push_back(r[3][(*it2)->HL]);
            (*it2)->getRoute()->push_back(r[2][(*it2)->HL]);
            (*it2)->getRoute()->push_back(r[1][(*it2)->HL]);
            (*it2)->getRoute()->push_back(r[0][(*it2)->HL]);


        }
        // SEPUEDE HACER UN CAMBIO DE ALTURA  SI A LA RUTA 0 LE QUEDAN DOS PUNTOS Y SOLO HAY UN AVION
        if ((*it2)->HL==0 && (*it2)->getRoute()->size()  <=  2 && NHL < 2)
	    {
            CambioAlt=1;
        }
/*
			std::cerr	<<"Numero Vuelos:"<< flights.size()
					<<" Vuelo:"       << (*it)->getId() 
                    <<" Nivel:"       << (*it)->HL 
					<<" Numero P.R.:" << (*it)->getRoute()->size()
					<<" speed:" << (*it)->getRoute()->begin()->speed  
					<<" altura:" << (*it)->getRoute()->begin()->pos.get_z()  
              		<<  std::endl;	
*/
    }    
///*

// CAMBIO DE ALTURA
    int PrimerUno = 0;
    if ( CambioAlt==1)
    {


        for(it3 = flights.begin(); it3!=flights.end(); it3++) 
        {


            if( (*it3)->HL == 1  && (*it3)->HL < 100 && PrimerUno == 0 )
            {                
                (*it3)->getRoute()->clear();
                (*it3)->getRoute()->push_front(r[0] [0]);
                (*it3)->getRoute()->push_front(r[1] [0]);
                (*it3)->getRoute()->push_front(r[2] [0]);
                (*it3)->getRoute()->push_front(r[3] [0]);
                (*it3)->HL=0;
                PrimerUno = 1;
            }




            if( (*it3)->HL >= 1  && (*it3)->HL < 100 )
            {
                int N = (*it3)->getRoute()->size() ;  //NUMERO DE ELEMENTOS
					switch ( N )
					{
						case 4:
							(*it3)->getRoute()->clear();
							(*it3)->getRoute()->push_front(r[ 0 ][((*it3)->HL)-1]);    

							(*it3)->getRoute()->push_front(r[ 1 ][((*it3)->HL)-1]); //BAJA NIVEL
							(*it3)->getRoute()->push_front(r[ 2 ][((*it3)->HL)-1]);
							(*it3)->getRoute()->push_front(r[ 3 ][((*it3)->HL)]);//TRAMO NISMO NIVEL

							(*it3)->HL = ((*it3)->HL)-1;
							break;

						case 3:
						 	(*it3)->getRoute()->clear();
							(*it3)->getRoute()->push_front(r[ 0 ][((*it3)->HL)-1]);    //TRAMO NISMO NIVEL

							(*it3)->getRoute()->push_front(r[ 1 ][((*it3)->HL)-1]); //BAJA NIVEL
							(*it3)->getRoute()->push_front(r[ 2 ][((*it3)->HL)]);

							(*it3)->HL = ((*it3)->HL)-1;
							break;

						case 2:
						 	(*it3)->getRoute()->clear();
							(*it3)->getRoute()->push_front(r[ 0 ][((*it3)->HL)-1]);    //TRAMO NISMO NIVEL

							(*it3)->getRoute()->push_front(r[ 1 ][((*it3)->HL)]); //BAJA NIVEL

							(*it3)->HL = ((*it3)->HL)-1;
							break;

						case 1:
						 	(*it3)->getRoute()->clear();
							(*it3)->getRoute()->push_front(r[ 0 ][((*it3)->HL)]);    //TRAMO NISMO NIVEL
							(*it3)->HL = ((*it3)->HL)-1;
							break;

					}




            }


        }

       // if (g>2)
		//	g = g-1;

	CambioAlt=0;

    }


int max=500;

	for(it4 = flights.begin(); it4!=flights.end(); it4++) 
	{


		if ((*it4)->getRoute()->begin()->pos.get_z()>max && (*it4)->HL <100)
		{
			max=(*it4)->getRoute()->begin()->pos.get_z();
		}



/*
			std::cerr  <<"Vuelo:"       << (*it)->getId() 
	                   	<<" Nivel:"      << (*it)->HL    
					<<" altura:" << (*it)->getRoute()->begin()->pos.get_z() 
					<<" max" << max 
					<<" g " << g 
      		<<  std::endl;	
*/
	}

		//std::cerr<<"-----------------------------------------------"<<std::endl;

		g=int(max/500);

















}


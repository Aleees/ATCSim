// Aqui se incluyen todos los cambios que se van haciendo
//No forma parte del programa y en ningun momento debe ser compilado

//EN Common.h
Introduccion de var globales para tormenta

saturate
closest

//Storm.h Storm.cpp

//Airport
Añadido funciones:
	generate_storm
	removestorm
	instorm

Añadido de variables
	cronostorm ->contiene el tiempo de ultima tormenta

//flight
Añadido parametros:
	instrorm;

	Se cambia tambien la forma de restar puntos para tener en cuenta si esta en tormenta


//-----------------//
	Cambios para las leyes del movimiento. Conseguir que el avion acelere, desacelere y rote.

	Flight
		Añadidos funciones que toman en cuenta los giros
			centerrotation


//---------A REVERTIR------------//
	Solo hay un avion.
	Variable testing en flight.h
	No estas modificando la inclinación


//PORQUE SSSSSSSSS!

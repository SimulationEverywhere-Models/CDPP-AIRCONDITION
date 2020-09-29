/*******************************************************************
*
*  DESCRIPCION: Propagacion de temperatura (simulación del termómetro)
*
*******************************************************************/

//#include <string.h>
#include "proptemp.h"
#include "message.h"
#include "parsimu.h"
#include "strutil.h"       // str2Value( ... )

/*******************************************************************
* CLASS ProptempState
*********************************************************************/

/*******************************************************************
* Function Name: operator =
*********************************************************************/
ProptempState& ProptempState::operator=(ProptempState& thisState) {

	(AtomicState &)*this  = (AtomicState &) thisState;
	return *this;
}

/*******************************************************************
* Function Name: copyState
*********************************************************************/
void ProptempState::copyState(ProptempState *rhs) {
	*this = *((ProptempState *) rhs);
}

/*******************************************************************
* Function Name: getSize
*********************************************************************/
int  ProptempState::getSize() const {
	return sizeof( ProptempState );
}


/*******************************************************************
* CLASS proptemp
*********************************************************************/

/*******************************************************************
* Nombre de la Funci¢n: Proptemp::Proptemp()
* Descripción: Constructor
********************************************************************/
Proptemp::Proptemp( const string &name ) : Atomic( name ), exterior( addInputPort( "exterior" ) )
	, frio( addInputPort( "frio" ) ), calor( addInputPort( "calor" ) ), habitacion( addOutputPort( "habitacion" ) )
	, frioActivado( 0 ), calorActivado( 0 ), tempExterior( 25 ) , tempHabitacion( 25 ), tempActual(25), tiempoInicial( 0 )
    , tiempoEvento( 0 ), modificador( 20 ), aumenta( 0 )
{
	string tE( ParallelMainSimulator::Instance().getParameter( description(), "tempExterior" ) ) ;
    if( tE != "" )
	    tempExterior = str2Value( tE );
	string tH( ParallelMainSimulator::Instance().getParameter( description(), "tempHabitacion" ) ) ;
    if( tH != "" )
	    tempHabitacion = str2Value( tH );
    tempActual = tempHabitacion;
	string mo( ParallelMainSimulator::Instance().getParameter( description(), "modificador" ) ) ;
    if( mo != "" )
	    modificador = str2Value( mo );
}

/*******************************************************************
* Nombre de la Función: Proptemp::initFunction()
* Descripción: Función de Inicialización
********************************************************************/

Model &Proptemp::initFunction()
{
    float mod = 0.0;
    if (frioActivado)
        mod = (-1.0) * modificador;
    if (calorActivado)
        mod = modificador;
    if ((tempExterior + mod - tempHabitacion)==0)
        passivate();
    else
    {
        tiempoInicial = 0;
        tiempoEvento = 3600000.0/(fabs(tempExterior + mod - tempHabitacion)); //para pasarlo a segundos
        if ((tempExterior + mod - tempHabitacion)>0)
                aumenta = 1;
        else
                aumenta = 0;
        holdIn( AtomicState::active, VTime(0.0,0.0,0.0,tiempoEvento) );
    }

	return *this ;
}


/*******************************************************************
* Nombre de la Función: Proptemp::externalFunction()
* Descripción: Maneja los eventos externos (activación y desactivación)
********************************************************************/

Model &Proptemp::externalFunction( const ExternalMessage &msg )
{
#ifdef DEVS_DELAY_EXTERNAL
	string a;
	for (int i = 1; i < 100000; i++ ) {
		if ( a.length() > 100 )
			a = "";
		else
			a += i;
	}
#endif
    float mod = 0.0;
    if (frioActivado)
        mod = (-1.0) * modificador;
    if (calorActivado)
        mod = modificador;
    float tempExtAnterior = tempExterior + mod;
	if( msg.port() == frio )                // Si entra una orden de activación de frio
	{
		frioActivado = msg.value();
	}
	if( msg.port() == calor )               // Si entra una orden de activación de calor
	{
		calorActivado = msg.value();
	}
	if( msg.port() == exterior )            // Si entra un cambio en la temperatura exterior
	{
	    tempExterior = msg.value();
    }

    mod = 0.0;
    if (frioActivado)
        mod = (-1.0) * modificador;
    if (calorActivado)
        mod = modificador;
    if ((tempExterior + mod - tempActual)==0)
        passivate();
    else
    {
        float sentido;
        if (aumenta)
            sentido = 1.0;
        else
            sentido = -1.0;
        float varTemp;
        if ((tempExtAnterior - tempActual)!=0.0)
            varTemp = ((msg.time().asMsecs())-tiempoInicial)/(tiempoEvento)*sentido*(tempHabitacion+sentido-tempActual);
        else
            varTemp = 0.0;
        tempActual = tempActual + varTemp*sentido;
        tiempoEvento = 3600000.0*(1.0-(tempActual-tempHabitacion)*sentido)/(fabs(tempExterior + mod - (tempActual-varTemp*sentido))); //para pasarlo a segundos*2
        tiempoInicial = msg.time().asMsecs();
        if ((tempExterior + mod - (tempActual))>0)
            aumenta = 1;
        else
            aumenta = 0;
        holdIn( AtomicState::active, VTime(0.0,0.0,0.0,tiempoEvento) );
 
    }

	return *this;
}

/*******************************************************************
* Nombre de la Función: Proptemp::internalFunction()
* Descripción: Pone el modelo en estado pasivo
********************************************************************/
Model &Proptemp::internalFunction( const InternalMessage &msg )
{
#ifdef DEVS_DELAY_INTERNAL
	string a;
	for (int i = 1; i < 100000; i++ ) {
		if ( a.length() > 100 )
			a = "";
		else
			a += i;
	}
#endif
    float mod = 0.0;
    if (frioActivado)
        mod = (-1.0) * modificador;
    if (calorActivado)
        mod = modificador;
    if ((tempExterior + mod - tempHabitacion)==0)
        passivate();
    else
    {
        tiempoInicial = msg.time().asMsecs();
        tiempoEvento = 3600000.0/(fabs(tempExterior + mod - tempHabitacion)); //para pasarlo a segundos
        if ((tempExterior + mod - tempHabitacion)>0)
                aumenta = 1;
        else
                aumenta = 0;
        holdIn( AtomicState::active, VTime(0.0,0.0,0.0,tiempoEvento) );
    }

	return *this ;
}


/*******************************************************************
* Nombre de la Función: Proptemp::outputFunction()
* Descripción: Envía consumo
********************************************************************/
Model &Proptemp::outputFunction( const CollectMessage &msg )
{
    if (aumenta)
        tempHabitacion = tempHabitacion + 1.0;
    else
        tempHabitacion = tempHabitacion - 1.0;
    tempActual = tempHabitacion;
    sendOutput( msg.time(), habitacion, tempHabitacion ) ;

	return *this ;
}

/*******************************************************************
*
*  DESCRIPCION: Unidad de control
*
*******************************************************************/

//#include <string.h>
#include "ucontrol.h"
#include "message.h"
#include "parsimu.h"
#include "strutil.h"       // str2Value( ... )

/*******************************************************************
* CLASS UcontrolState
*********************************************************************/

/*******************************************************************
* Function Name: operator =
*********************************************************************/
UcontrolState& UcontrolState::operator=(UcontrolState& thisState) {

	(AtomicState &)*this  = (AtomicState &) thisState;
	return *this;
}

/*******************************************************************
* Function Name: copyState
*********************************************************************/
void UcontrolState::copyState(UcontrolState *rhs) {
	*this = *((UcontrolState *) rhs);
}

/*******************************************************************
* Function Name: getSize
*********************************************************************/
int  UcontrolState::getSize() const {
	return sizeof( UcontrolState );
}


/*******************************************************************
* CLASS ucontrol
*********************************************************************/

/*******************************************************************
* Nombre de la Funci¢n: Ucontrol::Ucontrol()
* Descripción: Constructor
********************************************************************/
Ucontrol::Ucontrol( const string &name ) : Atomic( name ), deseada( addInputPort( "deseada" ) )
	, real( addInputPort( "real" ) ), frio( addOutputPort( "frio" ) ), calor( addOutputPort( "calor" ) )
	, frioActivado( 0 ), calorActivado( 0 ), tempDeseada( 25 ) , tempReal( 25 ), tolerancia( 2 )
{
	string tD( ParallelMainSimulator::Instance().getParameter( description(), "tempDeseada" ) ) ;
        if( tD != "" )
	    tempDeseada = str2Value( tD );
	string tR( ParallelMainSimulator::Instance().getParameter( description(), "tempReal" ) ) ;
        if( tR != "" )
	    tempReal = str2Value( tR );
	string to( ParallelMainSimulator::Instance().getParameter( description(), "tolerancia" ) ) ;
        if( to != "" )
	    tolerancia = str2Value( to );
}

/*******************************************************************
* Nombre de la Función: Ucontrol::initFunction()
* Descripción: Función de Inicialización
********************************************************************/

Model &Ucontrol::initFunction()
{
    holdIn( AtomicState::active, VTime::Zero );
	return *this ;
}


/*******************************************************************
* Nombre de la Función: Ucontrol::externalFunction()
* Descripción: Maneja los eventos externos (activación y desactivación)
********************************************************************/

Model &Ucontrol::externalFunction( const ExternalMessage &msg )
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

	if( msg.port() == deseada )
	{
	     tempDeseada = msg.value();
        }
        if( msg.port() == real )
	{
	     tempReal = msg.value();
        }

        holdIn( AtomicState::active, VTime::Zero );

	return *this;
}

/*******************************************************************
* Nombre de la Función: Ucontrol::internalFunction()
* Descripción: Pone el modelo en estado pasivo
********************************************************************/
Model &Ucontrol::internalFunction( const InternalMessage & )
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
	passivate();
	return *this ;
}


/*******************************************************************
* Nombre de la Función: Ucontrol::outputFunction()
* Descripción: Envía consumo
********************************************************************/
Model &Ucontrol::outputFunction( const CollectMessage &msg )
{
        if ((tempReal - tempDeseada)> tolerancia && !frioActivado)
        {
            if (calorActivado)
            {
                sendOutput( msg.time(), calor, 0.0 ) ;
                calorActivado = 0;
            }
            sendOutput( msg.time(), frio, 1.0 ) ;
            frioActivado = 1;
        }
        else
        {
            if ((tempDeseada - tempReal)> tolerancia && !calorActivado)
            {
                if (frioActivado)
                {
                    sendOutput( msg.time(), frio, 0.0 ) ;
                    frioActivado = 0;
                }
                sendOutput( msg.time(), calor, 1.0 ) ;
                calorActivado = 1;
            }
            else
            {
                if (calorActivado && (tempReal >= tempDeseada))
                {
                    sendOutput( msg.time(), calor, 0.0 ) ;
                    calorActivado = 0;
                }
                if (frioActivado && (tempReal <= tempDeseada))
                {
                    sendOutput( msg.time(), frio, 0.0 ) ;
                    frioActivado = 0;
                }
            }
        }

	return *this ;
}

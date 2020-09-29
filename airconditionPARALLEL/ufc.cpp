/*******************************************************************
*
*  DESCRIPCION: Unidad frío o calor (para calcular consumo)
*
*******************************************************************/

//#include <string.h>
#include "ufc.h"
#include "message.h"
#include "parsimu.h"
#include "strutil.h"       // str2Value( ... )

/*******************************************************************
* CLASS UfcState
*********************************************************************/

/*******************************************************************
* Function Name: operator =
*********************************************************************/
UfcState& UfcState::operator=(UfcState& thisState) {

	(AtomicState &)*this  = (AtomicState &) thisState;
	return *this;	
}

/*******************************************************************
* Function Name: copyState
*********************************************************************/
void UfcState::copyState(UfcState *rhs) {
	*this = *((UfcState *) rhs);	
}

/*******************************************************************
* Function Name: getSize
*********************************************************************/
int  UfcState::getSize() const {
	return sizeof( UfcState );
}


/*******************************************************************
* CLASS Ufc
*********************************************************************/

/*******************************************************************
* Nombre de la Funci¢n: Ufc::Ufc()
* Descripción: Constructor
********************************************************************/
Ufc::Ufc( const string &name ) : Atomic( name ), activar( addInputPort( "activar" ) )
	, salida( addOutputPort( "salida" ) )
	, consumoPorHora( 1000 ) , tiempoActivacion( 0 )
{
	string consumo( ParallelMainSimulator::Instance().getParameter( description(), "consumo" ) ) ;

	if( consumo != "" )
		consumoPorHora = str2Value( consumo );
}

/*******************************************************************
* Nombre de la Función: Ufc::initFunction()
* Descripción: Función de Inicialización
********************************************************************/

Model &Ufc::initFunction()
{
    passivate();
	return *this ;
}


/*******************************************************************
* Nombre de la Función: Ufc::externalFunction()
* Descripción: Maneja los eventos externos (activación y desactivación)
********************************************************************/

Model &Ufc::externalFunction( const ExternalMessage &msg )
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

	if( msg.port() == activar )                           // Si entra una orden de activación
	{
		if( msg.value() == 1 )                            // Si hay que activar
			tiempoActivacion = (msg.time()).asMsecs();
                        passivate();
		if( msg.value() == 0)                             // Si hay que desactivar se manda el consumo
		    holdIn( AtomicState::active, VTime::Zero );
	}
	return *this;
}

/*******************************************************************
* Nombre de la Función: Ufc::internalFunction()
* Descripción: Pone el modelo en estado pasivo 
********************************************************************/
Model &Ufc::internalFunction( const InternalMessage & )
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
* Nombre de la Función: Ufc::outputFunction()
* Descripción: Envía consumo
********************************************************************/
Model &Ufc::outputFunction( const CollectMessage &msg )
{
    float o = ((msg.time()).asMsecs() - tiempoActivacion)*consumoPorHora/(3600 * 1000);
	sendOutput( msg.time(), salida, o ) ;
	return *this ;
}

/*******************************************************************
*
*  DESCRIPCION: Propagacion de temperatura (simulaci�n del term�metro)
*
*******************************************************************/

//#include <string.h>
#include "gentemp.h"
#include "message.h"
#include "parsimu.h"
#include "strutil.h"       // str2Value( ... )
extern "C"  
{
#include "randlib.h"
}

/*******************************************************************
* CLASS GentempState
*********************************************************************/

/*******************************************************************
* Function Name: operator =
*********************************************************************/
GentempState& GentempState::operator=(GentempState& thisState) {

	(AtomicState &)*this  = (AtomicState &) thisState;
	return *this;
}

/*******************************************************************
* Function Name: copyState
*********************************************************************/
void GentempState::copyState(GentempState *rhs) {
	*this = *((GentempState *) rhs);
}

/*******************************************************************
* Function Name: getSize
*********************************************************************/
int  GentempState::getSize() const {
	return sizeof( GentempState );
}


/*******************************************************************
* CLASS ucontrol
*********************************************************************/

/*******************************************************************
* Nombre de la Funci�n: Gentemp::Gentemp()
* Descripci�n: Constructor
********************************************************************/
Gentemp::Gentemp( const string &name ) : Atomic( name ), salida( addOutputPort( "salida" ) )
	, temperatura( 25 ), intervalo(30)
{
	string t( ParallelMainSimulator::Instance().getParameter( description(), "temperatura" ) ) ;
        if( t != "" )
	    temperatura = str2Value( t );
	string i( ParallelMainSimulator::Instance().getParameter( description(), "intervalo" ) ) ;
        if( i != "" )
	    intervalo = str2Value( i );
}

/*******************************************************************
* Nombre de la Funci�n: Gentemp::initFunction()
* Descripci�n: Funci�n de Inicializaci�n
********************************************************************/

Model &Gentemp::initFunction()
{
    holdIn( AtomicState::active, VTime(intervalo) );
	return *this ;
}


/*******************************************************************
* Nombre de la Funci�n: Gentemp::externalFunction()
* Descripci�n: Maneja los eventos externos (activaci�n y desactivaci�n)
********************************************************************/

Model &Gentemp::externalFunction( const ExternalMessage &msg )
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
	return *this;
}

/*******************************************************************
* Nombre de la Funci�n: Gentemp::internalFunction()
* Descripci�n: Pone el modelo en estado pasivo
********************************************************************/
Model &Gentemp::internalFunction( const InternalMessage &msg )
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
    holdIn( AtomicState::active, VTime(0.0,0.0,intervalo,0.0) );
	return *this ;
}


/*******************************************************************
* Nombre de la Funci�n: Gentemp::outputFunction()
* Descripci�n: Env�a consumo
********************************************************************/
Model &Gentemp::outputFunction( const CollectMessage &msg )
{
    float coef1 = 0.1*(50.0-temperatura)/30.0;
    float coef2 = 0.1*(temperatura+10.0)/30.0;
    float num = genunf(0.0,1.0);
    if (num < coef1)
        {
        temperatura = temperatura + 1;
        sendOutput( msg.time(), salida, temperatura ) ;
        }
    if ( num > (1-coef2))
        {
        temperatura = temperatura - 1;
        sendOutput( msg.time(), salida, temperatura ) ;
        }

	return *this ;
}

/*******************************************************************
*
*  DESCRIPCION: Propagacion de temperatura (simulación del termómetro)
*
*******************************************************************/
#ifndef __PROPTEMP_H
#define __PROPTEMP_H

#include "atomic.h"     	// class Atomic
#include "atomicstate.h"	//

class ProptempState : public AtomicState {

public:

	ProptempState() {};
	virtual ~ProptempState(){};

	ProptempState& operator=(ProptempState& thisState); //Assignment
	void copyState(ProptempState *);
	int  getSize() const;

};

class Proptemp : public Atomic
{
public:
	Proptemp( const string &name = "Proptemp" );
	virtual string className() const {  return "Proptemp" ;}
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const CollectMessage & );

	ModelState* allocateState() {
		return new ProptempState;
	}

private:

    const Port &exterior;
    const Port &frio;
    const Port &calor;
	Port &habitacion;
    int frioActivado;
    int calorActivado;
	float tempExterior;
	float tempHabitacion;
    float tempActual;
    float tiempoInicial;
    float tiempoEvento;
    float modificador;
    int aumenta;

};	// class Proptemp

#endif   //__PROPTEMP_H

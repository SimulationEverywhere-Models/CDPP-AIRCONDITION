/*******************************************************************
*
*  DESCRIPCION: Unidad de control
*
*******************************************************************/
#ifndef __UCONTROL_H
#define __UCONTROL_H

#include "atomic.h"     	// class Atomic
#include "atomicstate.h"	//

class UcontrolState : public AtomicState {

public:

	UcontrolState() {};
	virtual ~UcontrolState(){};

	UcontrolState& operator=(UcontrolState& thisState); //Assignment
	void copyState(UcontrolState *);
	int  getSize() const;

};

class Ucontrol : public Atomic
{
public:
	Ucontrol( const string &name = "Ucontrol" );
	virtual string className() const {  return "Ucontrol" ;}
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const CollectMessage & );

	ModelState* allocateState() {
		return new UcontrolState;
	}

private:

    const Port &deseada;
    const Port &real;
	Port &frio;
       	Port &calor;
        int frioActivado;
        int calorActivado;
	float tempDeseada;
	float tempReal;
        float tolerancia;

};	// class Ucontrol

#endif   //__UCONTROL_H

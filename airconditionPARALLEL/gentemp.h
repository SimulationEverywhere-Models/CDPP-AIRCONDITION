/*******************************************************************
*
*  DESCRIPCION: Propagacion de temperatura (simulación del termómetro)
*
*******************************************************************/
#ifndef __GENTEMP_H
#define __GENTEMP_H

#include "atomic.h"     	// class Atomic
#include "atomicstate.h"	//

class GentempState : public AtomicState {

public:

	GentempState() {};
	virtual ~GentempState(){};

	GentempState& operator=(GentempState& thisState); //Assignment
	void copyState(GentempState *);
	int  getSize() const;

};

class Gentemp : public Atomic
{
public:
	Gentemp( const string &name = "Gentemp" );
	virtual string className() const {  return "Gentemp" ;}
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const CollectMessage & );

	ModelState* allocateState() {
		return new GentempState;
	}

private:

 	Port &salida;
	float temperatura;
	float intervalo;

};	// class Gentemp

#endif   //__GENTEMP_H

/*******************************************************************
*
*  DESCRIPCION: Unidad frío o calor (para calcular consumo)
*
*******************************************************************/
#ifndef __UFC_H
#define __UFC_H

#include "atomic.h"     	// class Atomic
#include "atomicstate.h"	//

class UfcState : public AtomicState {

public:

	UfcState() {};
	virtual ~UfcState(){};

	UfcState& operator=(UfcState& thisState); //Assignment
	void copyState(UfcState *);
	int  getSize() const;

};

class Ufc : public Atomic
{
public:
	Ufc( const string &name = "Ufc" );
	virtual string className() const {  return "Ufc" ;}
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const CollectMessage & );

	ModelState* allocateState() {
		return new UfcState;
	}

private:

    const Port &activar;
	Port &salida;
	float consumoPorHora;
	float tiempoActivacion; //en milisegundos
 	
};	// class Ufc

#endif   //__UFC_H

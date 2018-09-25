#ifndef EULER_H
#define EULER_H

#include "MegoldasiModszer.h"

namespace mercure
{
	class Euler : public MegoldasiModszer		//MegoldasiModszer osztalybol szarmaztatva
	{
	private:
		double* k1;		//seged valtozo - "olyan mint Runge-Kutta k1"

	public:
	//csak letezo kezdetiertek feladattal inicializalhato:
		Euler(DifEgyenletek& _DifE);
		~Euler();

		virtual void Lepes(double dt);
	};
}
#endif

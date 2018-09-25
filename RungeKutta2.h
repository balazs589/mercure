#ifndef RUNGEKUTTA2_H
#define RUNGEKUTTA2_H

#include "MegoldasiModszer.h"

namespace mercure
{
	class RungeKutta2 : public MegoldasiModszer		//MegoldasiModszer osztalybol szarmaztatva
	{
	private:
		double* k1;		//seged valtozo - Runge-Kutta k1
		double* k2;		//seged valtozo - Runge-Kutta k2

	public:
	//csak letezo kezdetiertek feladattal inicializalhato:
		RungeKutta2(DifEgyenletek& _DifE);
		~RungeKutta2();

		virtual void Lepes(double dt);
	};
}
#endif

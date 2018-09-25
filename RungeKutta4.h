#ifndef RUNGEKUTTA4_H
#define RUNGEKUTTA4_H

#include "MegoldasiModszer.h"

namespace mercure
{
	class RungeKutta4 : public MegoldasiModszer		//MegoldasiModszer osztalybol szarmaztatva
	{
	private:
		double* k1;			//seged valtozo - Runge-Kutta k1
		double* k2;			//seged valtozo - Runge-Kutta k2
		double* k3;			//seged valtozo - Runge-Kutta k3
		double* k4;			//seged valtozo - Runge-Kutta k4

	public:
		//csak letezo kezdetiertek feladattal inicializalhato:
		RungeKutta4(DifEgyenletek& _DifE);
		~RungeKutta4();

		virtual void Lepes(double dt);
	};
}
#endif

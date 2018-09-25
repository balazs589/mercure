#include "Euler.h"
#include "DifEgyenletek.h"

namespace mercure
{
	Euler::Euler(DifEgyenletek& _DifE)
	: MegoldasiModszer(_DifE)
	{
		k1 = new double[N];
	}

	Euler::~Euler()
	{
		delete[] k1;		//dinamikusan lefoglalt memoria felszabaditasa
	}


/*****************************************************************************/
// a Euler::Lepes(double dt) fuggveny teljesen analog
// RungeKutta4::Lepes(double dt) fuggvennyel,
// a valtozok es ciklusok az Euler modszer
// matematikai kepleteinek megfeleloen vannak modositva
/*****************************************************************************/

	void Euler::Lepes(double dt)
	{
		for(int iii = 0; iii < N; iii++)
		{
			X[iii] = DifE.X[iii];
		}

		for(int iii = 1; iii<N; iii++)
		{
			k1[iii] = (DifE.*(DifE.fp[iii]))(X);
		}

		DifE.X[0] += dt;
		for(int iii = 1; iii<N; iii++)
		{
			DifE.X[iii] += k1[iii] * dt;
		}

		return;
	}
}

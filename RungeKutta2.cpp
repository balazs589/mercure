#include "RungeKutta2.h"
#include "DifEgyenletek.h"

namespace mercure
{
	RungeKutta2::RungeKutta2(DifEgyenletek& _DifE)
	: MegoldasiModszer(_DifE)
	{
		k1 = new double[N];
		k2 = new double[N];
	}

	RungeKutta2::~RungeKutta2()
	{
		delete[] k1;		//
		delete[] k2;		//dinamikusan lefoglalt memoria felszabaditasa
	}

/*****************************************************************************/
// a RungeKutta2::Lepes(double dt) fuggveny teljesen analog
// RungeKutta4::Lepes(double dt) fuggvennyel,
// a valtozok es ciklusok a "Runge-Kutta2 Midpoint method"
// matematikai kepleteinek megfeleloen vannak modositva
/*****************************************************************************/

	void RungeKutta2::Lepes(double dt)
	{
		for(int iii = 0; iii < N; iii++)
		{
			X[iii] = DifE.X[iii];
		}

		for(int iii = 1; iii<N; iii++)
		{
			k1[iii] = (DifE.*(DifE.fp[iii]))(X);
		}

		X[0] += dt / 2.0;
		for(int iii = 1; iii<N; iii++)
		{
			X[iii] = DifE.X[iii] + k1[iii] * dt / 2;
		}

		for(int iii = 1; iii<N; iii++)
		{
			k2[iii] = (DifE.*(DifE.fp[iii]))(X);
		}

		DifE.X[0] += dt;
		for(int iii = 1; iii<N; iii++)
		{
			DifE.X[iii] += k2[iii] * dt;
		}

		return;
	}
}

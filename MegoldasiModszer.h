#ifndef MEGOLDASIMODSZER_H
#define MEGOLDASIMODSZER_H

#include "DifEgyenletek.h"

/*****************************************************************************/
//teszoleges szamu, Runge-Kutta modszernek megfeleloen
//dX/dt = F(t, X) alakban felirt
/*		X(t) = [x1(t), x2(t), ..., xn(t)]
		F(X) = [f1(X), f2(X), ..., fn(X)]
		dX(t)/dt = [dx1(t)/dt, dx2(t)/dt, ..., dxn(t)/dt]		*/
//egy fuggetlen valtozos elsorendu differencialegyenletbol allo
//differencialegyenlet rendszer megoldasara
/*****************************************************************************/

namespace mercure
{
	class MegoldasiModszer
	{
	protected:
		int N;					// N = egyenletek szama + 1
		DifEgyenletek& DifE;	// meoldando kezdeti ertek feladat
		double* X;				// seged valtozo adatok tarolasara

		//csak letezo kezdetiertek feladattal inicializalhato:
		MegoldasiModszer(DifEgyenletek& _DifE)
		: N(_DifE.N), DifE(_DifE)
		{
			X = new double[N];
		}
		
		~MegoldasiModszer()
		{
			delete[] X;		//dinamikusan lefoglalt memoria felszabaditasa
		}
		
	public:
		//szarmaztatott osztalyokban kidolgozando,
		//a megoldas kovetkezo lepeset szolgaltato fuggveny:
		virtual void Lepes(double dt) = 0;
		
	};	
}
#endif

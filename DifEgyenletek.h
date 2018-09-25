#ifndef DIFEGYENLETEK_H
#define DIFEGYENLETEK_H

#include "Bolygo.h"

/*****************************************************************************/
//Runge-Kutta modszernek megfeleloen dX/dt = F(t, X) alakban felirt
/*		X(t) = [x1(t), x2(t), ..., xn(t)]
		F(X) = [f1(X), f2(X), ..., fn(X)]
		dX(t)/dt = [dx1(t)/dt, dx2(t)/dt, ..., dxn(t)/dt]		*/
//egy fuggetlen valtozos elsorendu differencialegyenletek tarolasara

//(a feladatnak megfelelo 4db differencialegenlettel megavolsitva)
/*****************************************************************************/

namespace mercure
{
	class DifEgyenletek
	{
	private:
		double* X;				//kezdeti es eppen aktualis ertekeket tartalmazo tombre fog mutatni
		const int N;			//valtozok szama - hazifeladatban: 5 (t, x, y, vy, vy)

		//differencialegyenletek parameterei:
		const double M;			//Nap tomege
		const double G;			//gravitacios allando

		//hogy kesobb rgyszeruen csak indexekkel tudjunk az egyenletekre hivatkozni:
		typedef double (DifEgyenletek::*tagfuggvenypointer)(double* X);
		tagfuggvenypointer* fp;

		//differencialegyenletek:
		double dx1dt(double* X);
		double dx2dt(double* X);
		double dx3dt(double* X);
		double dx4dt(double* X);

	public:
		DifEgyenletek(double* _X, int _N);		//alapvetoen kezdeti ertekeket tartalmazo
												//tomb megadasaval es (esetleges ellenorzes keppen)
												//a differencial egyenletek szamaval tudjuk letrehozni
												//a kezdeti ertek feladatot

		DifEgyenletek(Bolygo& _Bolygo, int _N);	//masik parameterlistaju konstruktor
		~DifEgyenletek();


		friend class Euler;
		friend class RungeKutta2;
		friend class RungeKutta4;
		friend class MegoldasiModszer;
	};
}
#endif

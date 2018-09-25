#include "RungeKutta4.h"
#include "DifEgyenletek.h"

namespace mercure
{
	RungeKutta4::RungeKutta4(DifEgyenletek& _DifE)
	: MegoldasiModszer(_DifE)
	{
		k1 = new double[N];
		k2 = new double[N];
		k3 = new double[N];
		k4 = new double[N];
	}

	RungeKutta4::~RungeKutta4()
	{
		delete[] k1;		//
		delete[] k2;		//
		delete[] k3;		//
		delete[] k4;		//dinamikusan lefoglalt memoria felszabaditasa
	}

/*****************************************************************************/
//Runge-Kutta4 modszer lepeseit megvalosito fuggveny:
/* felhasznalt irodalom:
http://www.physics.buffalo.edu/phy410-505-2009/topic3/lec-3-2.pdf
http://www.nsc.liu.se/~boein/f77to90/rk.html
*/
//lepesrol lepesre az inicializalaskor megadott DifE nevu kezdetiertek feladat
//adattagjainak aktualis erteket hasznaljuk es modositjuk,
//a DifE adattagjakent letezo, DifE tagfuggvenyeire mutato pointerek tombjenek hasznalataval
//es parameterkent megkapott dt lepeskozzel

//(mivel DifE X pointer tipusu valtozoja Bolygo.X -szel lett egyenlove teve,
// ezert valojaban kozvetve  a Bolygo osztaly peldanyanak
// a (t, x, y, vy, vy) valtozoknak megfelelo Bolygo.X tombjet modositjuk)

/*****************************************************************************/

	void RungeKutta4::Lepes(double dt)
	{
		for(int iii = 0; iii < N; iii++)
		{
			X[iii] = DifE.X[iii];	//segedvaltozoba mentjuk a valtozok pillanatnyi erteket
		}

		for(int iii = 1; iii<N; iii++)					//Runge - Kutta k1
		{
			k1[iii] = (DifE.*(DifE.fp[iii]))(X);		//azaz k1 = F(t,X(t))
		}

		X[0] += dt / 2.0;								//t -> t + dt/2
		for(int iii = 1; iii<N; iii++)
		{
			X[iii] = DifE.X[iii] + k1[iii] * dt / 2;	//X -> X + k1*dt/2
		}

		for(int iii = 1; iii<N; iii++)					//Runge - Kutta k2
		{
			k2[iii] = (DifE.*(DifE.fp[iii]))(X);		//azaz k2 = F(t+dt/2, X(t)+k1*dt/2 )
		}

		// t -> t + dt/2    :     X[0] nem valtozik
		for(int iii = 1; iii<N; iii++)
		{
			X[iii] = DifE.X[iii] + k2[iii] * dt / 2;	//X -> X + k2*dt/2
		}

		for(int iii = 1; iii<N; iii++)					//Runge - Kutta k3
		{
			k3[iii] = (DifE.*(DifE.fp[iii]))(X);		//azaz k3 = F(t+dt/2, X(t)+k2*dt/2 )
		}

		X[0] += dt / 2.0;								//t -> t + dt
		for(int iii = 1; iii<N; iii++)
		{
			X[iii] = DifE.X[iii] + k3[iii] * dt;		//X -> X + k3*dt
		}

		for(int iii = 1; iii<N; iii++)					//Runge - Kutta k4
		{
			k4[iii] = (DifE.*(DifE.fp[iii]))(X);		//azaz k4 = F(t+dt, X(t)+k3*dt )
		}

		DifE.X[0] += dt;					//a megoldast idoerteket leptetjuk a kovekezo idopontba
		for(int iii = 1; iii<N; iii++)
		{
			//es rogzitjuk a valtozok kovetkezo idoponthoz tartozo uj ertekeit
			DifE.X[iii] += (k1[iii]+2 * k2[iii] +2 * k3[iii] + k4[iii]) * dt / 6.0;
		}

		return;
	}
}

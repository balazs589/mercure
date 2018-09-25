#include "DifEgyenletek.h"
#include "Bolygo.h"
#include <assert.h>
#include <math.h>

//a header fajlban deklaralt fuggvenyek (differencialegyenletek) kidolgozasa

namespace mercure
{
	DifEgyenletek::DifEgyenletek(double* _X, int _N)		//peldanyositas tombbel
	: X(_X), N(_N), M(1.9891e30), G(6.67428e-11)
	{
		fp = new tagfuggvenypointer[N];		//N = egyenletek szama + 1

		//sorban a megfelelo tagfuggvenyekre mutatunk:
		//fp[0] -kihagyva az egyertelmubb jeloles kedveert
		fp[1] = &DifEgyenletek::dx1dt;
		fp[2] = &DifEgyenletek::dx2dt;
		fp[3] = &DifEgyenletek::dx3dt;
		fp[4] = &DifEgyenletek::dx4dt;
	}

	DifEgyenletek::DifEgyenletek(Bolygo& _Bolygo, int _N)	//peldanyositas Bolygo-val
	: X(_Bolygo.X), N(_N), M(1.9891e30), G(6.67428e-11)
	{
		fp = new tagfuggvenypointer[N];		//N = egyenletek szama + 1

		//sorban a megfelelo tagfuggvenyekre mutatunk:
		//fp[0] -kihagyva az egyertelmubb jeloles kedveert
		fp[1] = &DifEgyenletek::dx1dt;
		fp[2] = &DifEgyenletek::dx2dt;
		fp[3] = &DifEgyenletek::dx3dt;
		fp[4] = &DifEgyenletek::dx4dt;
	}

	DifEgyenletek::~DifEgyenletek()
	{
		delete[] fp;
	}

	inline double DifEgyenletek::dx1dt(double* X)
	{
		return X[3];		//   dx/dt = vx
	}

	double DifEgyenletek::dx2dt(double* X)
	{
		return X[4];		//   dy/dt = vy
	}

	double DifEgyenletek::dx3dt(double* X)
	{
		// dvx/dt = (-M*G*x)/ ( (x^2 + y^2)^(3/2) )

		return ( (-1.0) * M * G * X[1]) / pow((X[1] * X[1] + X[2] * X[2] ),1.5);
	}

	double DifEgyenletek::dx4dt(double* X)
	{
		// dvy/dt = (-M*G*y)/ ( (x^2 + y^2)^(3/2) )

		return ( (-1.0) * M * G * X[2]) / pow((X[1] * X[1] + X[2] * X[2] ),1.5);
	}
}

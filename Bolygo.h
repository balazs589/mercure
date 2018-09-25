#ifndef BOLYGO_H
#define BOLYGO_H

#include <iostream>

namespace mercure
{
	class Bolygo
	{
	private:
		double X[5];			//t, x, y, vx, vy
		
	public:
		Bolygo(double _t, double _x, double _y, double _vx, double _vy)
		{
			X[0] = _t;
			X[1] = _x;
			X[2] = _y;
			X[3] = _vx;
			X[4] = _vy;
		}

		//ha szukseg lenne a Bolygo adatainak lekerdezesere:
		double GetT()  const { return X[0]; }
		double GetX()  const { return X[1]; }
		double GetY()  const { return X[2]; }
		double GetVx() const { return X[3]; }
		double GetVy() const { return X[4]; }

		//operator overloading Bolygo obejktum kiiratasara:
		friend std::ostream& operator<<(std::ostream& out, const Bolygo& _Bolygo);
		
		friend class DifEgyenletek;
	};
}
#endif

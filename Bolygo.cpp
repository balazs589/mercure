#include "Bolygo.h"

using namespace std;

namespace mercure
{
	//operator overloading Bolygo objektum kiiratasara:
	//t, x, y
	ostream& operator<<(ostream& out, const Bolygo& _Bolygo)
	{
		out << _Bolygo.X[0] << ", " << _Bolygo.X[1] << ", " << _Bolygo.X[2] << endl;
		return out;
	}
}

#ifndef BEOLVAS_H
#define BEOLVAS_H

#include <fstream>

namespace mercure
{
	enum ModszerValaszto {EULER, RK2, RK4};

	double** Beolvas(std::ifstream& infile, ModszerValaszto& _Modszer, int& _FeladatokSzama);
}
#endif

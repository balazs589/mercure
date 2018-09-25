#ifndef VEGREHAJT_H
#define VEGREHAJT_H

#include <fstream>

namespace mercure
{
void VegrehajtRK4(double input[6], std::ofstream& outfile);
void VegrehajtRK2(double input[6], std::ofstream& outfile);
void VegrehajtEuler(double input[6], std::ofstream& outfile);
}
#endif

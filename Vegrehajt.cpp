#include "Vegrehajt.h"
#include "Bolygo.h"
#include "RungeKutta4.h"
#include "RungeKutta2.h"
#include "Euler.h"

using namespace std;

namespace mercure
{

/*****************************************************************************/
//a vegrehajto fuggvenyek a parameterkent megkapott 6 elemu tombok elemeit
//tmax, dt, x0, y0, vx0, vy0 sorrendben ertelmezve a parametrekent megkapott
//kimeneti szoveges fajl egy soraba irjak, majd t=0 es ezekkel az x0, y0, vx0, vy0
//ertekekkel letrehoznak egy Bolygo tipusu objektumot,
//ezt a Bolygo tipusu objektumot kezdeti ertekkent ertelmezve letrehoznak
//egy DifEgyenletek objektumot,
//es az igy letrejott kezdeti ertek feladatot egy-egy megfelelo,
//MegoldasiModszer-bol szarmaztatott objektumot letrehozasaval es tagfuggvenyenek
//"dt" idokozokkel valo hivasaval lepesenkent megoldja
/*****************************************************************************/

//Euler modszer
void VegrehajtEuler(double input[6], ofstream& outfile)
{
	outfile <<							//kimeneti fajl 1 soraba valo iras
	". tmax=" << input[0] << ", "
	<< "dt=" << input[1] << ", "
	<< "x0=" << input[2] << ", "
	<< "y0=" << input[3] << ", "
	<< "vx0="<< input[4] << ", "
	<< "vy0="<< input[5] << endl;

	int CiklusSzam = input[0] / input[1];						// (tmax / dt)
	Bolygo Merkur(0, input[2], input[3], input[4], input[5]);	// Bolygo(t0, x0, y0, vx0, vy0)
	DifEgyenletek DifE(Merkur, 5);
	Euler EulerPeldany(DifE);
	for(int iii = 0; iii < CiklusSzam; iii++)
	{
		EulerPeldany.Lepes(input[1]);
		outfile << Merkur;					//minden lepes utan fajlba irjuk az uj ertekekt
	}

	return;
}

//RungeKutta2 modszer
void VegrehajtRK2(double input[6], ofstream& outfile)
{
	outfile <<							//kimeneti fajl 1 soraba valo iras
	". tmax=" << input[0] << ", "
	<< "dt=" << input[1] << ", "
	<< "x0=" << input[2] << ", "
	<< "y0=" << input[3] << ", "
	<< "vx0="<< input[4] << ", "
	<< "vy0="<< input[5] << endl;

	int CiklusSzam = input[0] / input[1];						// (tmax / dt)
	Bolygo Merkur(0, input[2], input[3], input[4], input[5]);	// Bolygo(t0, x0, y0, vx0, vy0)
	DifEgyenletek DifE(Merkur, 5);
	RungeKutta2 RungeKutta2Peldany(DifE);
	for(int iii = 0; iii < CiklusSzam; iii++)
	{
		RungeKutta2Peldany.Lepes(input[1]);
		outfile << Merkur;					//minden lepes utan fajlba irjuk az uj ertekekt
	}	
	
	return;
}

//RungeKutta4 modszer
void VegrehajtRK4(double input[6], ofstream& outfile)
{
	outfile <<							//kimeneti fajl 1 soraba valo iras
	". tmax=" << input[0] << ", "
	<< "dt=" << input[1] << ", "
	<< "x0=" << input[2] << ", "
	<< "y0=" << input[3] << ", "
	<< "vx0="<< input[4] << ", "
	<< "vy0="<< input[5] << endl;

	int CiklusSzam = input[0] / input[1];						// (tmax / dt)
	Bolygo Merkur(0, input[2], input[3], input[4], input[5]);	// Bolygo(t0, x0, y0, vx0, vy0)
	DifEgyenletek DifE(Merkur, 5);
	RungeKutta4 RungeKutta4Peldany(DifE);
	for(int iii = 0; iii < CiklusSzam; iii++)
	{
		RungeKutta4Peldany.Lepes(input[1]);
		outfile << Merkur;					//minden lepes utan fajlba irjuk az uj ertekekt
	}

	return;
}


}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>

#include "Vegrehajt.h"
#include "Beolvas.h"

using namespace mercure;
using namespace std;

/*****************************************************************************/
//a main gondoskodik a program altal megkapott parancssori parameterek
//ertelmezeserol es feldolgozasarol
//megnyitja olvasasra a megadott input fajlt
//a Beolvas fuggveny meghivasaval feldolgozza az input fajl sorait
//megnyitja irasra a megadott fajlnevu szoveges fajlt
//az igy kapott adatokat tovabbitva a megfelelo modszert vegrehajtjo fugvenynek,
//elvegezteti az eredmeny meghatarozasat es output fajlba valo irasat
/*****************************************************************************/
int main(int argc, char *argv[])
{
	//a program legalabb 1 legfeljebb 3 parancssori parametert var
	if( (argc != 2) && (argc != 3) && (argc != 4) )
	{
		cout << "a program inditasi parametereinek helyes formaja:" << endl;
		cout << "mercure [-m<e|2|4>] <parameterek fajlja> [<eredmeny fajl>]" << endl;
		cout << "pl.: mercure -me input.txt output.txt" << endl;
		cout << "a [] kozott szerpelo parameterek opcionalisak" << endl;
		return 1;
	}

	string strModszer;							//
	string strInputFajl;						//
	string strOutputFajl;						//a parancssori parameterek tarolasara

	bool bModszerParancsSorbol = false;			//ha legalabb 2 parameterrrel hivtuk meg
												//a programot es ezek kozul az elso
												// modszer valaszto parameterkent ertelmezheto
												// "-me" "-m2" "-m4" akkor erteke igaz lesz

	switch(argc)
	{
		case 4:									//teljes prameterlistaval torteno inditas eseten
			strModszer = argv[1];				//a megadott sorrend szerint ertelmezzuk
			strInputFajl = argv[2];				//a parametereket
			strOutputFajl = argv[3];			//
			bModszerParancsSorbol = true;		//es a moszdervalasztast innen fogjuk vegezni
			break;

		case 2:										//minimalis parameterlistaval torteno inditas eseten
			strModszer = "-m4";						//
			strInputFajl = argv[1];					//a megadott egyetlen parameter az input fajlt jelenti
			strOutputFajl = "output_BGGUER.txt";	//a tobbi az alapertelmezett ertekeket kapja
			break;

		case 3:			//ha 2 parameterrel inditjuk a programot
						//attol fuggoen, hogy az elsot tudjuk-e modszervalasztaskent ertelmezni
			if( (strcmp(argv[1], "-me") == 0) || (strcmp(argv[1], "-m2") == 0) || (strcmp(argv[1], "-m4") == 0)  )
			{
				strModszer = argv[1];					//ha igen akkor az lesz a hasznalt modszer
				strInputFajl = argv[2];					//a masodik az inputfajl
				strOutputFajl = "output_BGGUER.txt";	//
				bModszerParancsSorbol = true;			//
			}
			else							//ha nem
			{
				strModszer = "-m4";			//
				strInputFajl = argv[1];		//akkor az elsot input
				strOutputFajl = argv[2];	//a masodikat output fajlkent ertelmezzuk
			}
			break;
	}

	ifstream infile(strInputFajl.c_str());		//megprobaljuk elerni az inputfajlt

	if(!infile)		//ha nem sikerul, akkor megszakitjuk a program futasat
	{
		cerr << strInputFajl << endl;
		cerr << "a megadott inputfajlt nem sikerult megnyitni" << endl;
		return 1;
	}

	double** KezdetiErtekek;			//ezen keresztul foguk elerni az input fajlbol szarmazo ertekeket
	int FeladatokSzama = 0;				//megoldando kezdeti ertek feladatok
	ModszerValaszto Modszer = RK4;		//enum valtozo a modszerek szamara {EULER, RK2, RK4}
										//alapertelmezett ertek: Runge-Kutta4


	//meghivjuk az input fajl feldolgozasat vegzo fuggvenyt
	//ami visszateresi ertekkent double tombokre mutato pointert ad
	//amin keresztul elerjuk a kezdeti ertekeket
	//a megoldando feladatok szamat es esetlegesen a fajlban rogzitett modszert
	//referenciakon keresztuli modositassal szolgaltatja
	KezdetiErtekek = Beolvas(infile, Modszer, FeladatokSzama);

	if(bModszerParancsSorbol)		//ha parancssor ban adtunk meg modszervalasztast
									//akkor az lesz a meghatarozott
	{
		if(strModszer == "-me") Modszer = EULER;
		if(strModszer == "-m2") Modszer = RK2;
		if(strModszer == "-m4") Modszer = RK4;
	}
	//egyebkent nem valtoztatunk azon ami az inputfajlbol szarmazik

	ofstream outfile(strOutputFajl.c_str());		//megnyitjuk irasra a megfelelo szoveges fajlt

	if(!outfile)
	{
		cerr << "nem sikerult a fajl megnyitasa irasra: (" << strOutputFajl <<")" << endl;
		return 1;
	}

	outfile << "Programozas 2 II. feladat 2012" << endl;		//feladatban elvasrt ertek

	cout << "Szamitas folyamatban." << endl;

	switch(Modszer)		//Modszer erteke vagy parancssori parameterbol
						//vagy az input fajlbol szarmazik, vagy alapertelmezett
						//erteke altal meghatarozottan hivjuk meg a megfelelo vegrehajto fuggvenyt
						//a feladatok szamaval megegyezo szamszor
						//(egy-egy hivassal egy-egy feladatot tudunk megoldani)
	{
		case EULER :
			for(int iii = 0; iii < FeladatokSzama; iii++)
			{
				outfile 	<< iii+1;
				VegrehajtEuler( KezdetiErtekek[iii], outfile);
			}
			break;

		case RK2 :
			for(int iii = 0; iii < FeladatokSzama; iii++)
			{
				outfile 	<< iii+1;
				VegrehajtRK2( KezdetiErtekek[iii], outfile);
			}
			break;

		case RK4 :
			for(int iii = 0; iii < FeladatokSzama; iii++)
			{
				outfile 	<< iii+1;
				VegrehajtRK4( KezdetiErtekek[iii], outfile);
			}
			break;
	}
							//a szamitasok befejezese utan
	outfile.close();		//zarjuk a kimeneti szoveges fajlt

	cout << "Szamitas befejezve." << endl;

	return 0;
}

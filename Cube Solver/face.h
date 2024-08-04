#pragma once
#ifndef _CUBIE
#include "library.h"

//
// Each face has 9 cubies w/ color
//
class Face
{
private:
	Color cubieOne;
	Color cubieTwo;
	Color cubieThree;
	Color cubieFour;
	Color cubieFive;
	Color cubieSix;
	Color cubieSeven;
	Color cubieEight;
	Color cubieNine;
public:
	Face(Color = White);
	Face(Color, Color, Color, Color, Color, Color, Color, Color, Color);

	const Color getCubieOne() const;
	const Color getCubieTwo() const;
	const Color getCubieThree() const;
	const Color getCubieFour() const;
	const Color getCubieFive() const;
	const Color getCubieSix() const;
	const Color getCubieSeven() const;
	const Color getCubieEight() const;
	const Color getCubieNine() const;

	void setCubieOne(const Color);
	void setCubieTwo(const Color);
	void setCubieThree(const Color);
	void setCubieFour(const Color);
	void setCubieFive(const Color);
	void setCubieSix(const Color);
	void setCubieSeven(const Color);
	void setCubieEight(const Color);
	void setCubieNine(const Color);
};
#endif // !_CUBIE

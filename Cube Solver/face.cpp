#include "face.h"

Face::Face(Color color)
{
	cubieOne = color;
	cubieTwo = color;
	cubieThree = color;
	cubieFour = color;
	cubieFive = color;
	cubieSix = color;
	cubieSeven = color;
	cubieEight = color;
	cubieNine = color;
}
Face::Face(Color colorOne, Color colorTwo, Color colorThree, Color colorFour, Color colorFive, Color colorSix, Color colorSeven, Color colorEight, Color colorNine)
{
	cubieOne = colorOne;
	cubieTwo = colorTwo;
	cubieThree = colorThree;
	cubieFour = colorFour;
	cubieFive = colorFive;
	cubieSix = colorSix;
	cubieSeven = colorSeven;
	cubieEight = colorEight;
	cubieNine = colorNine;
}

const Color Face::getCubieOne() const
{
	return cubieOne;
}
const Color Face::getCubieTwo() const
{
	return cubieTwo;
}
const Color Face::getCubieThree() const
{
	return cubieThree;
}
const Color Face::getCubieFour() const
{
	return cubieFour;
}
const Color Face::getCubieFive() const
{
	return cubieFive;
}
const Color Face::getCubieSix() const
{
	return cubieSix;
}
const Color Face::getCubieSeven() const
{
	return cubieSeven;
}
const Color Face::getCubieEight() const
{
	return cubieEight;
}
const Color Face::getCubieNine() const
{
	return cubieNine;
}

void Face::setCubieOne(const Color color)
{
	cubieOne = color;
}
void Face::setCubieTwo(const Color color)
{
	cubieTwo = color;
}
void Face::setCubieThree(const Color color)
{
	cubieThree = color;
}
void Face::setCubieFour(const Color color)
{
	cubieFour = color;
}
void Face::setCubieFive(const Color color)
{
	cubieFive = color;
}
void Face::setCubieSix(const Color color)
{
	cubieSix = color;
}
void Face::setCubieSeven(const Color color)
{
	cubieSeven = color;
}
void Face::setCubieEight(const Color color)
{
	cubieEight = color;
}
void Face::setCubieNine(const Color color)
{
	cubieNine = color;
}
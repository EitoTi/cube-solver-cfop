#include "rubik.h"

/*
	Color of 6 faces:
	up      -	yellow
	front   -	blue
	left	-	orange
	right	-	red
	back	-	green
	down	-	white
*/

Rubik::Rubik() : Face(), upFace(Yellow), frontFace(Blue), leftFace(Orange), rightFace(Red), backFace(Green), downFace(White) {}


// Move cubies of a face (clockwise)
// a face has 9 cubies
void Rubik::clockWise(Face& face)
{
	Color tmp01 = face.getCubieOne();
	Color tmp02 = face.getCubieTwo();
	face.setCubieOne(face.getCubieSeven());
	face.setCubieTwo(face.getCubieFour());
	face.setCubieSeven(face.getCubieNine());
	face.setCubieFour(face.getCubieEight());
	face.setCubieNine(face.getCubieThree());
	face.setCubieEight(face.getCubieSix());
	face.setCubieThree(tmp01);
	face.setCubieSix(tmp02);
}

// Move cubies of a face (counter clockwise)
// a face has 9 cubies
void Rubik::counterClockWise(Face& face)
{
	Color tmp01 = face.getCubieOne();
	Color tmp02 = face.getCubieTwo();
	face.setCubieOne(face.getCubieThree());
	face.setCubieTwo(face.getCubieSix());
	face.setCubieThree(face.getCubieNine());
	face.setCubieSix(face.getCubieEight());
	face.setCubieNine(face.getCubieSeven());
	face.setCubieEight(face.getCubieFour());
	face.setCubieSeven(tmp01);
	face.setCubieFour(tmp02);
}

/*
	Get faces of the cube
*/

Face& Rubik::getUpFace()
{
	return upFace;
}
Face& Rubik::getDownFace()
{
	return downFace;
}
Face& Rubik::getLeftFace()
{
	return leftFace;
}
Face& Rubik::getRightFace()
{
	return rightFace;
}
Face& Rubik::getFrontFace()
{
	return frontFace;
}
Face& Rubik::getBackFace()
{
	return backFace;
}

/* 
	Move Notations
*/

void Rubik::U()
{
	clockWise(upFace);

	Color tmp01 = frontFace.getCubieOne();
	Color tmp02 = frontFace.getCubieTwo();
	Color tmp03 = frontFace.getCubieThree();

	frontFace.setCubieOne(rightFace.getCubieOne());
	frontFace.setCubieTwo(rightFace.getCubieTwo());
	frontFace.setCubieThree(rightFace.getCubieThree());

	rightFace.setCubieOne(backFace.getCubieNine());
	rightFace.setCubieTwo(backFace.getCubieEight());
	rightFace.setCubieThree(backFace.getCubieSeven());

	backFace.setCubieNine(leftFace.getCubieOne());
	backFace.setCubieEight(leftFace.getCubieTwo());
	backFace.setCubieSeven(leftFace.getCubieThree());

	leftFace.setCubieOne(tmp01);
	leftFace.setCubieTwo(tmp02);
	leftFace.setCubieThree(tmp03);
}
void Rubik::U_p()
{
	counterClockWise(upFace);

	Color tmp01 = frontFace.getCubieOne();
	Color tmp02 = frontFace.getCubieTwo();
	Color tmp03 = frontFace.getCubieThree();

	frontFace.setCubieOne(leftFace.getCubieOne());
	frontFace.setCubieTwo(leftFace.getCubieTwo());
	frontFace.setCubieThree(leftFace.getCubieThree());

	leftFace.setCubieOne(backFace.getCubieNine());
	leftFace.setCubieTwo(backFace.getCubieEight());
	leftFace.setCubieThree(backFace.getCubieSeven());

	backFace.setCubieNine(rightFace.getCubieOne());
	backFace.setCubieEight(rightFace.getCubieTwo());
	backFace.setCubieSeven(rightFace.getCubieThree());

	rightFace.setCubieOne(tmp01);
	rightFace.setCubieTwo(tmp02);
	rightFace.setCubieThree(tmp03);
}

void Rubik::D()
{
	clockWise(downFace);
	Color tmp01 = frontFace.getCubieSeven();
	Color tmp02 = frontFace.getCubieEight();
	Color tmp03 = frontFace.getCubieNine();

	frontFace.setCubieSeven(leftFace.getCubieSeven());
	frontFace.setCubieEight(leftFace.getCubieEight());
	frontFace.setCubieNine(leftFace.getCubieNine());

	leftFace.setCubieSeven(backFace.getCubieThree());
	leftFace.setCubieEight(backFace.getCubieTwo());
	leftFace.setCubieNine(backFace.getCubieOne());

	backFace.setCubieThree(rightFace.getCubieSeven());
	backFace.setCubieTwo(rightFace.getCubieEight());
	backFace.setCubieOne(rightFace.getCubieNine());

	rightFace.setCubieSeven(tmp01);
	rightFace.setCubieEight(tmp02);
	rightFace.setCubieNine(tmp03);
}
void Rubik::D_p()
{
	counterClockWise(downFace);

	Color tmp01 = frontFace.getCubieSeven();
	Color tmp02 = frontFace.getCubieEight();
	Color tmp03 = frontFace.getCubieNine();

	frontFace.setCubieSeven(rightFace.getCubieSeven());
	frontFace.setCubieEight(rightFace.getCubieEight());
	frontFace.setCubieNine(rightFace.getCubieNine());

	rightFace.setCubieSeven(backFace.getCubieThree());
	rightFace.setCubieEight(backFace.getCubieTwo());
	rightFace.setCubieNine(backFace.getCubieOne());

	backFace.setCubieThree(leftFace.getCubieSeven());
	backFace.setCubieTwo(leftFace.getCubieEight());
	backFace.setCubieOne(leftFace.getCubieNine());

	leftFace.setCubieSeven(tmp01);
	leftFace.setCubieEight(tmp02);
	leftFace.setCubieNine(tmp03);
}

void Rubik::R()
{
	clockWise(rightFace);

	Color tmp01 = frontFace.getCubieThree();
	Color tmp02 = frontFace.getCubieSix();
	Color tmp03 = frontFace.getCubieNine();

	frontFace.setCubieThree(downFace.getCubieThree());
	frontFace.setCubieSix(downFace.getCubieSix());
	frontFace.setCubieNine(downFace.getCubieNine());

	downFace.setCubieThree(backFace.getCubieThree());
	downFace.setCubieSix(backFace.getCubieSix());
	downFace.setCubieNine(backFace.getCubieNine());

	backFace.setCubieThree(upFace.getCubieThree());
	backFace.setCubieSix(upFace.getCubieSix());
	backFace.setCubieNine(upFace.getCubieNine());

	upFace.setCubieThree(tmp01);
	upFace.setCubieSix(tmp02);
	upFace.setCubieNine(tmp03);
}
void Rubik::R_p()
{
	counterClockWise(rightFace);

	Color tmp01 = upFace.getCubieNine();
	Color tmp02 = upFace.getCubieSix();
	Color tmp03 = upFace.getCubieThree();

	upFace.setCubieNine(backFace.getCubieNine());
	upFace.setCubieSix(backFace.getCubieSix());
	upFace.setCubieThree(backFace.getCubieThree());

	backFace.setCubieNine(downFace.getCubieNine());
	backFace.setCubieSix(downFace.getCubieSix());
	backFace.setCubieThree(downFace.getCubieThree());

	downFace.setCubieNine(frontFace.getCubieNine());
	downFace.setCubieSix(frontFace.getCubieSix());
	downFace.setCubieThree(frontFace.getCubieThree());

	frontFace.setCubieNine(tmp01);
	frontFace.setCubieSix(tmp02);
	frontFace.setCubieThree(tmp03);
}

void Rubik::L()
{
	clockWise(leftFace);

	Color tmp01 = frontFace.getCubieOne();
	Color tmp02 = frontFace.getCubieFour();
	Color tmp03 = frontFace.getCubieSeven();

	frontFace.setCubieOne(upFace.getCubieOne());
	frontFace.setCubieFour(upFace.getCubieFour());
	frontFace.setCubieSeven(upFace.getCubieSeven());

	upFace.setCubieOne(backFace.getCubieOne());
	upFace.setCubieFour(backFace.getCubieFour());
	upFace.setCubieSeven(backFace.getCubieSeven());

	backFace.setCubieOne(downFace.getCubieOne());
	backFace.setCubieFour(downFace.getCubieFour());
	backFace.setCubieSeven(downFace.getCubieSeven());

	downFace.setCubieOne(tmp01);
	downFace.setCubieFour(tmp02);
	downFace.setCubieSeven(tmp03);
}
void Rubik::L_p()
{
	counterClockWise(leftFace);

	Color tmp01 = frontFace.getCubieOne();
	Color tmp02 = frontFace.getCubieFour();
	Color tmp03 = frontFace.getCubieSeven();

	frontFace.setCubieOne(downFace.getCubieOne());
	frontFace.setCubieFour(downFace.getCubieFour());
	frontFace.setCubieSeven(downFace.getCubieSeven());

	downFace.setCubieOne(backFace.getCubieOne());
	downFace.setCubieFour(backFace.getCubieFour());
	downFace.setCubieSeven(backFace.getCubieSeven());

	backFace.setCubieOne(upFace.getCubieOne());
	backFace.setCubieFour(upFace.getCubieFour());
	backFace.setCubieSeven(upFace.getCubieSeven());

	upFace.setCubieOne(tmp01);
	upFace.setCubieFour(tmp02);
	upFace.setCubieSeven(tmp03);
}

void Rubik::B()
{
	clockWise(backFace);

	Color tmp01 = upFace.getCubieOne();
	Color tmp02 = upFace.getCubieTwo();
	Color tmp03 = upFace.getCubieThree();

	upFace.setCubieOne(rightFace.getCubieThree());
	upFace.setCubieTwo(rightFace.getCubieSix());
	upFace.setCubieThree(rightFace.getCubieNine());

	rightFace.setCubieThree(downFace.getCubieNine());
	rightFace.setCubieSix(downFace.getCubieEight());
	rightFace.setCubieNine(downFace.getCubieSeven());

	downFace.setCubieNine(leftFace.getCubieSeven());
	downFace.setCubieEight(leftFace.getCubieFour());
	downFace.setCubieSeven(leftFace.getCubieOne());

	leftFace.setCubieSeven(tmp01);
	leftFace.setCubieFour(tmp02);
	leftFace.setCubieOne(tmp03);
}
void Rubik::B_p()
{
	counterClockWise(backFace);

	Color tmp01 = upFace.getCubieOne();
	Color tmp02 = upFace.getCubieTwo();
	Color tmp03 = upFace.getCubieThree();

	upFace.setCubieOne(leftFace.getCubieSeven());
	upFace.setCubieTwo(leftFace.getCubieFour());
	upFace.setCubieThree(leftFace.getCubieOne());

	leftFace.setCubieSeven(downFace.getCubieNine());
	leftFace.setCubieFour(downFace.getCubieEight());
	leftFace.setCubieOne(downFace.getCubieSeven());

	downFace.setCubieNine(rightFace.getCubieThree());
	downFace.setCubieEight(rightFace.getCubieSix());
	downFace.setCubieSeven(rightFace.getCubieNine());

	rightFace.setCubieThree(tmp01);
	rightFace.setCubieSix(tmp02);
	rightFace.setCubieNine(tmp03);
}

void Rubik::F()
{
	clockWise(frontFace);

	Color tmp01 = upFace.getCubieSeven();
	Color tmp02 = upFace.getCubieEight();
	Color tmp03 = upFace.getCubieNine();

	upFace.setCubieSeven(leftFace.getCubieNine());
	upFace.setCubieEight(leftFace.getCubieSix());
	upFace.setCubieNine(leftFace.getCubieThree());

	leftFace.setCubieNine(downFace.getCubieThree());
	leftFace.setCubieSix(downFace.getCubieTwo());
	leftFace.setCubieThree(downFace.getCubieOne());

	downFace.setCubieThree(rightFace.getCubieOne());
	downFace.setCubieTwo(rightFace.getCubieFour());
	downFace.setCubieOne(rightFace.getCubieSeven());

	rightFace.setCubieOne(tmp01);
	rightFace.setCubieFour(tmp02);
	rightFace.setCubieSeven(tmp03);
}
void Rubik::F_p()
{
	counterClockWise(frontFace);

	Color tmp01 = upFace.getCubieSeven();
	Color tmp02 = upFace.getCubieEight();
	Color tmp03 = upFace.getCubieNine();

	upFace.setCubieSeven(rightFace.getCubieOne());
	upFace.setCubieEight(rightFace.getCubieFour());
	upFace.setCubieNine(rightFace.getCubieSeven());

	rightFace.setCubieOne(downFace.getCubieThree());
	rightFace.setCubieFour(downFace.getCubieTwo());
	rightFace.setCubieSeven(downFace.getCubieOne());

	downFace.setCubieThree(leftFace.getCubieNine());
	downFace.setCubieTwo(leftFace.getCubieSix());
	downFace.setCubieOne(leftFace.getCubieThree());

	leftFace.setCubieNine(tmp01);
	leftFace.setCubieSix(tmp02);
	leftFace.setCubieThree(tmp03);
}

void Rubik::M()
{
	Color tmp01 = upFace.getCubieTwo();
	Color tmp02 = upFace.getCubieFive();
	Color tmp03 = upFace.getCubieEight();

	upFace.setCubieTwo(backFace.getCubieTwo());
	upFace.setCubieFive(backFace.getCubieFive());
	upFace.setCubieEight(backFace.getCubieEight());

	backFace.setCubieTwo(downFace.getCubieTwo());
	backFace.setCubieFive(downFace.getCubieFive());
	backFace.setCubieEight(downFace.getCubieEight());

	downFace.setCubieTwo(frontFace.getCubieTwo());
	downFace.setCubieFive(frontFace.getCubieFive());
	downFace.setCubieEight(frontFace.getCubieEight());

	frontFace.setCubieTwo(tmp01);
	frontFace.setCubieFive(tmp02);
	frontFace.setCubieEight(tmp03);
}
void Rubik::M_p()
{
	Color tmp01 = upFace.getCubieTwo();
	Color tmp02 = upFace.getCubieFive();
	Color tmp03 = upFace.getCubieEight();

	upFace.setCubieTwo(frontFace.getCubieTwo());
	upFace.setCubieFive(frontFace.getCubieFive());
	upFace.setCubieEight(frontFace.getCubieEight());

	frontFace.setCubieTwo(downFace.getCubieTwo());
	frontFace.setCubieFive(downFace.getCubieFive());
	frontFace.setCubieEight(downFace.getCubieEight());

	downFace.setCubieTwo(backFace.getCubieTwo());
	downFace.setCubieFive(backFace.getCubieFive());
	downFace.setCubieEight(backFace.getCubieEight());

	backFace.setCubieTwo(tmp01);
	backFace.setCubieFive(tmp02);
	backFace.setCubieEight(tmp03);
}

void Rubik::E()
{
	Color tmp01 = frontFace.getCubieFour();
	Color tmp02 = frontFace.getCubieFive();
	Color tmp03 = frontFace.getCubieSix();

	frontFace.setCubieFour(leftFace.getCubieFour());
	frontFace.setCubieFive(leftFace.getCubieFive());
	frontFace.setCubieSix(leftFace.getCubieSix());

	leftFace.setCubieFour(backFace.getCubieSix());
	leftFace.setCubieFive(backFace.getCubieFive());
	leftFace.setCubieSix(backFace.getCubieFour());

	backFace.setCubieSix(rightFace.getCubieFour());
	backFace.setCubieFive(rightFace.getCubieFive());
	backFace.setCubieFour(rightFace.getCubieSix());

	rightFace.setCubieFour(tmp01);
	rightFace.setCubieFive(tmp02);
	rightFace.setCubieSix(tmp03);
}
void Rubik::E_p()
{
	Color tmp01 = frontFace.getCubieFour();
	Color tmp02 = frontFace.getCubieFive();
	Color tmp03 = frontFace.getCubieSix();

	frontFace.setCubieFour(rightFace.getCubieFour());
	frontFace.setCubieFive(rightFace.getCubieFive());
	frontFace.setCubieSix(rightFace.getCubieSix());

	rightFace.setCubieFour(backFace.getCubieSix());
	rightFace.setCubieFive(backFace.getCubieFive());
	rightFace.setCubieSix(backFace.getCubieFour());

	backFace.setCubieSix(leftFace.getCubieFour());
	backFace.setCubieFive(leftFace.getCubieFive());
	backFace.setCubieFour(leftFace.getCubieSix());

	leftFace.setCubieFour(tmp01);
	leftFace.setCubieFive(tmp02);
	leftFace.setCubieSix(tmp03);
}

void Rubik::S()
{
	Color tmp01 = upFace.getCubieFour();
	Color tmp02 = upFace.getCubieFive();
	Color tmp03 = upFace.getCubieSix();

	upFace.setCubieFour(leftFace.getCubieEight());
	upFace.setCubieFive(leftFace.getCubieFive());
	upFace.setCubieSix(leftFace.getCubieTwo());

	leftFace.setCubieEight(downFace.getCubieSix());
	leftFace.setCubieFive(downFace.getCubieFive());
	leftFace.setCubieTwo(downFace.getCubieFour());

	downFace.setCubieSix(rightFace.getCubieTwo());
	downFace.setCubieFive(rightFace.getCubieFive());
	downFace.setCubieFour(rightFace.getCubieEight());

	rightFace.setCubieTwo(tmp01);
	rightFace.setCubieFive(tmp02);
	rightFace.setCubieEight(tmp03);
}
void Rubik::S_p()
{
	Color tmp01 = upFace.getCubieFour();
	Color tmp02 = upFace.getCubieFive();
	Color tmp03 = upFace.getCubieSix();

	upFace.setCubieFour(rightFace.getCubieTwo());
	upFace.setCubieFive(rightFace.getCubieFive());
	upFace.setCubieSix(rightFace.getCubieEight());

	rightFace.setCubieTwo(downFace.getCubieSix());
	rightFace.setCubieFive(downFace.getCubieFive());
	rightFace.setCubieEight(downFace.getCubieFour());

	downFace.setCubieSix(leftFace.getCubieEight());
	downFace.setCubieFive(leftFace.getCubieFive());
	downFace.setCubieFour(leftFace.getCubieTwo());

	leftFace.setCubieEight(tmp01);
	leftFace.setCubieFive(tmp02);
	leftFace.setCubieTwo(tmp03);
}

void Rubik::u()
{
	U();
	E_p();
}
void Rubik::u_p()
{
	U_p();
	E();
}

void Rubik::d()
{
	D();
	E();
}
void Rubik::d_p()
{
	D_p();
	E_p();
}

void Rubik::r()
{
	R();
	M_p();
}
void Rubik::r_p()
{
	R_p();
	M();
}

void Rubik::l()
{
	L();
	M();
}
void Rubik::l_p()
{
	L_p();
	M_p();
}

void Rubik::f()
{
	F();
	S();
}
void Rubik::f_p()
{
	F_p();
	S_p();
}

void Rubik::b()
{
	B();
	S_p();
}
void Rubik::b_p()
{
	B_p();
	S();
}

void Rubik::x()
{
	r();
	L_p();
}
void Rubik::x_p()
{
	r_p();
	L();
}

void Rubik::y()
{
	U();
	d_p();
}
void Rubik::y_p()
{
	U_p();
	d();
}

void Rubik::z()
{
	B_p();
	f();
}
void Rubik::z_p()
{
	B();
	f_p();
}

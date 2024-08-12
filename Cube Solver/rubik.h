#pragma once
#ifndef _RUBIK_CUBE
#include "face.h"

class Rubik : public Face
{
private:
	/////// Faces of cube ///////
	Face upFace;
	Face downFace;
	Face leftFace;
	Face rightFace;
	Face frontFace;
	Face backFace;
	///////////////////////////
protected:
	void clockWise(Face&);
	void counterClockWise(Face&);
public:
	Rubik(); // init the cube

	Face& getUpFace();
	Face& getDownFace();
	Face& getLeftFace();
	Face& getRightFace();
	Face& getFrontFace();
	Face& getBackFace();

	// Move Notations
	void U();
	void U_p(); // U'

	void D();
	void D_p(); // D'

	void R();
	void R_p(); // R'

	void L();
	void L_p(); // L'

	void B();
	void B_p(); // L'

	void F();
	void F_p(); // F'

	void M();
	void M_p(); // M'

	void E();
	void E_p(); // E'

	void S();
	void S_p(); // S'

	void u();
	void u_p(); // u'

	void d();
	void d_p(); // d'

	void r();
	void r_p(); // r'

	void l();
	void l_p(); // l'

	void f();
	void f_p(); // f'

	void b();
	void b_p(); // b'

	void x();
	void x_p(); // x'

	void y();
	void y_p(); // y'

	void z();
	void z_p(); // z'
};
#endif // !_RUBIK_CUBE

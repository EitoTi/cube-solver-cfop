#include "cfop.h"

int main()
{
	CFOP solver;

	/*string data = "U R F R' R2";
	solver.process(data);*/
	solver.solveCross();
	std::string cross = solver.getCrossData();
	std::cout << "cross: " << cross << std::endl;
	
	solver.solveF2l();
	std::string f2l = solver.getF2lData();
	std::cout << "f2l: " << f2l << std::endl;

	solver.solveOLL();
	std::string oll = solver.getOllData();
	std::cout << "oll: " << oll << std::endl;

	solver.solvePll();
	std::string pll = solver.getPllData();
	std::cout << "pll: " << pll << std::endl;

	std::string solution = cross + " " + f2l + " " + oll + " " + pll;
	solver.visualSolver(solution);

	return 0;
}
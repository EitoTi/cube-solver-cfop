#pragma once
#ifndef _CFOP
#include "color_detection.h"

class CFOP : public ColorDetection
{
private:
	/*
		Cross
	*/
	std::string crossData;
	std::vector<int> crossArray;
	bool crossFinish;

	// Depth of recursive call stack used in DFS to find cross solution
	int crossStep;

	// Maximum depth before backtracking
	int crossDepth;

	// Map variable to translate moves to string (moves from 1 to 18 --> basic moves)
	std::map<int, std::string> mpCrossMove;



	/*
		F2L
	*/
	std::string f2lData;
	int f2lIndex;
	std::vector<std::string> f2lArray;
public:
	CFOP();


	////////////////// Cross Handle //////////////////////

	// Turn for DFS Search for cross solving
	void turn(const int&);

	std::string getCrossData() const;
	bool isCrossFinish();
	void solveCross();
	void searchCrossSolution();
	std::string getCrossString(const std::vector<int>&);

	//////////////////////////////////////////////////////


	/////////////////// F2L Handle ///////////////////////
	void solveF2l();
	std::string getF2lData() const;

	// Perform 41 f2l algo
	bool f2lAlgo();

	// Check whether a pair of f2l is finished
	bool isF2lPairFinish();
	
	/*
		Cases of edge position
	*/

	// Up face edge position
	bool upTwoFrontRight();
	bool upTwoRightFront();

	bool upFourFrontRight();
	bool upFourRightFront();

	bool upSixFrontRight();
	bool upSixRightFront();

	bool upEightFrontRight();
	bool upEightRightFront();

	// Front face edge position
	bool frontFourFrontRight();
	bool frontFourRightFront();

	bool frontSixFrontRight();
	bool frontSixRightFront();

	// Back face edge position
	bool backFourFrontRight();
	bool backFourRightFront();

	bool backSixFrontRight();
	bool backSixRightFront();
}; 
#endif // !_CFOP
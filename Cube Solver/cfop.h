#pragma once
#ifndef _CFOP
#include "color_detection.h"

class CFOP : public ColorDetection
{
private:
	// Map variable to translate moves to string (moves from 1 to 18 --> basic moves)
	std::map<int, std::string> mpMove;

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

	/*
		F2L
	*/
	std::string f2lData;
	int f2lIndex;
	std::vector<std::string> f2lArray;

	/*
		OLL
	*/
	std::string ollString;
	std::string ollData;

	/*
		PLL
	*/
	std::string pllData;
	std::string pllString;
public:
	CFOP();

	// Use for DFS Search in cross solving
	// Perform moves in 'rubik'
	void turn(const int&);

	////////////////// Cross Handle //////////////////////


	std::string getCrossData() const;
	bool isCrossFinish();
	void solveCross();
	void searchCrossSolution();
	std::string getCrossString(const std::vector<int>&);

	//////////////////////////////////////////////////////


	/////////////////// F2L Handle ///////////////////////
	void solveF2l();
	std::string getF2lData();

	// Apply each pair of f2l solution to Rubik's Cube
	void applyF2lPairSolution(const std::string&);

	// Perform 41 f2l algo
	bool f2lAlgo();

	// Check whether a pair of f2l is finished
	bool isF2lPairFinish();

	// Handle cases when 41 f2l algo are not feasible
	void handleSpecialF2l();

	// functions to check whether corners and edges are well-oriented or not
	// is used in handleF2l()
	const bool isCornerCorrect(const Color&, const Color&, const Color&);
	const bool isEdgeCorrect(const Color&, const Color&);

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

	//////////////////////////////////////////////////



	//////////////////// OLL /////////////////////////

	void solveOLL();

	std::string getOllData() const;

	// Check for cubie to support OLL finding
	bool checkYellowCubie(const Color&, const Color&, const Color&, const Color&, const Color&, const Color&, const Color&, const Color&);
	
	// Find an Oll -> true
	bool handleOLL();

	// Check whether up face is finished
	bool isUpFaceFinish();

	// Apply OLL solution into rubik
	void applyOllSolution(const std::string&);

	//////////////////////////////////////////////////


	////////////////////// PLL ///////////////////////

	void solvePll();

	std::string getPllData() const;

	bool isLastLayerFinish();

	void applyPllSolution(const std::string&);

	bool handlePll();

	/////////////////////////////////////////////////
}; 
#endif // !_CFOP
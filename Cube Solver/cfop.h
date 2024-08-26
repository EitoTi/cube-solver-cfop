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
public:
	CFOP();

	// Turn for DFS Search
	void turn(const int&);

	////////////////// Cross Handle //////////////////////
	std::string getCrossData() const;
	bool isCrossFinish();
	void solveCross();
	void searchCrossSolution();
	std::string getCrossString(const std::vector<int>&);
};
#endif // !_CFOP

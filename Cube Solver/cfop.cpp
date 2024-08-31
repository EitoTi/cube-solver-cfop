#include "cfop.h"

CFOP::CFOP() : ColorDetection()
{
	this->run();

    mpMove = {
        {1, "R"},
        {2, "L"},
        {3, "U"},
        {4, "D"},
        {5, "F"},
        {6, "B"},
        {7, "R'"},
        {8, "L'"},
        {9, "U'"},
        {10, "D'"},
        {11, "F'"},
        {12, "B'"},
        {13, "R2"},
        {14, "L2"},
        {15, "U2"},
        {16, "D2"},
        {17, "F2"},
        {18, "B2"},
        {19, "r"},
        {20, "l"},
        {21, "u"},
        {22, "d"},
        {23, "f"},
        {24, "b"},
        {25, "r'"},
        {26, "l'"},
        {27, "u'"},
        {28, "d'"},
        {29, "f'"},
        {30, "b'"},
        {31, "M"},
        {32, "E"},
        {33, "S"},
        {34, "x"},
        {35, "y"},
        {36, "z"},
        {37, "M'"},
        {38, "E'"},
        {39, "S'"},
        {40, "x'"},
        {41, "y'"},
        {42, "z'"}
    };

    // Cross
    crossData = "";
    crossArray = std::vector<int>(8);
    crossDepth = crossStep = 0;
    crossFinish = false;

    // F2l
    f2lIndex = 0;
    f2lData = "";
    f2lArray = std::vector<std::string>(4, "");
    canUpdateF2l = false;
}

void CFOP::turn(const int& turn)
{
    switch (turn) {
        case 1:
            this->getCube().R();
            break;
        case 2:
            this->getCube().L();
            break;
        case 3:
            this->getCube().U();
            break;
        case 4:
            this->getCube().D();
            break;
        case 5:
            this->getCube().F();
            break;
        case 6:
            this->getCube().B();
            break;
        case 7:
            this->getCube().R_p();
            break;
        case 8:
            this->getCube().L_p();
            break;
        case 9:
            this->getCube().U_p();
            break;
        case 10:
            this->getCube().D_p();
            break;
        case 11:
            this->getCube().F_p();
            break;
        case 12:
            this->getCube().B_p();
            break;
        case 13:
            this->getCube().R();
            this->getCube().R();
            break;
        case 14:
            this->getCube().L();
            this->getCube().L();
            break;
        case 15:
            this->getCube().U();
            this->getCube().U();
            break;
        case 16:
            this->getCube().D();
            this->getCube().D();
            break;
        case 17:
            this->getCube().F();
            this->getCube().F();
            break;
        case 18:
            this->getCube().B();
            this->getCube().B();
            break;
        case 19:
            this->getCube().r();
            break;
        case 20:
            this->getCube().l();
            break;
        case 21:
            this->getCube().u();
            break;
        case 22:
            this->getCube().d();
            break;
        case 23:
            this->getCube().f();
            break;
        case 24:
            this->getCube().b();
            break;
        case 25:
            this->getCube().r_p();
            break;
        case 26:
            this->getCube().l_p();
            break;
        case 27:
            this->getCube().u_p();
            break;
        case 28:
            this->getCube().d_p();
            break;
        case 29:
            this->getCube().f_p();
            break;
        case 30:
            this->getCube().b_p();
            break;
        case 31:
            this->getCube().M();
            break;
        case 32:
            this->getCube().E();
            break;
        case 33:
            this->getCube().S();
            break;
        case 34:
            this->getCube().x();
            break;
        case 35:
            this->getCube().y();
            break;
        case 36:
            this->getCube().z();
            break;
        case 37:
            this->getCube().M_p();
            break;
        case 38:
            this->getCube().E_p();
            break;
        case 39:
            this->getCube().S_p();
            break;
        case 40:
            this->getCube().x_p();
            break;
        case 41:
            this->getCube().y_p();
            break;
        case 42:
            this->getCube().z_p();
            break;
        default:
            break;
    }
}

std::string CFOP::getCrossData() const
{
    return crossData;
}

bool CFOP::isCrossFinish()
{
	return this->getCube().getDownFace().getCubieTwo() == this->getCube().getDownFace().getCubieFive()
		&& this->getCube().getDownFace().getCubieFour() == this->getCube().getDownFace().getCubieFive()
		&& this->getCube().getDownFace().getCubieSix() == this->getCube().getDownFace().getCubieFive()
		&& this->getCube().getDownFace().getCubieEight() == this->getCube().getDownFace().getCubieFive()
		&& this->getCube().getFrontFace().getCubieEight() == this->getCube().getFrontFace().getCubieFive()
		&& this->getCube().getRightFace().getCubieEight() == this->getCube().getRightFace().getCubieFive()
		&& this->getCube().getLeftFace().getCubieEight() == this->getCube().getLeftFace().getCubieFive()
		&& this->getCube().getBackFace().getCubieTwo() == this->getCube().getBackFace().getCubieFive();
}

void CFOP::solveCross()
{
	while (!isCrossFinish())
	{
        searchCrossSolution();
		crossDepth++;
	}
}

void CFOP::searchCrossSolution()
{
    for (int i = 1; i <= 18; i++) 
    {   
        // There are 18 possible moves to check
        turn(i); // Simulate making one move (based on the index 'i')
        crossArray[crossStep] = i; // Store the move index in the crossArray
        if (isCrossFinish()) 
        { 
            // Check if the cross is complete
            crossFinish = true;
            crossData += getCrossString(crossArray); // Convert move indices to string 'crossData'
        }
        else if (crossStep < crossDepth) 
        { 
            // If not yet reached the allowed depth
            crossStep++; // Go one level deeper
            searchCrossSolution(); // Recursively try more moves
        }

        // If cross isn't finished, undo the move and backtrack
        if (!crossFinish) 
        {
            if (i > 12)
                turn(i); // For moves 13-18, undo by repeating the move
            else if (i < 7)
                turn(i + 6); // For moves 1-6, undo by performing the opposite move
            else 
                turn(i - 6); // For moves 7-12, undo by performing the opposite move

            // When reaching the end of the loop, reset this step and backtrack
            if (i == 18) 
            {
                crossArray[crossStep] = 0;
                crossStep = crossStep > 0 ? crossStep - 1 : 0;
            }
        }
        else
            break; // Stop once the cross is solved
    }
}

std::string CFOP::getCrossString(const std::vector<int>& crossArray)
{
    std::string tmpCrossData = "";
    for (auto index : crossArray)
    {
        tmpCrossData += mpMove[index];
        tmpCrossData += " ";
    }
    return tmpCrossData;
}

void CFOP::solveF2l()
{
    while (f2lIndex < 4)
    {
        if (!isF2lPairFinish())
        {
            if (!f2lAlgo())
            {
                // Move pair of corner and edge to match 41 f2l algo
                handleSpecialF2l();

                // Apply the move to create f2l cases in 41 f2l 
                applyF2lPairSolution(f2lArray[f2lIndex]);

                // Update f2lData
                f2lData += f2lArray[f2lIndex];
                f2lArray[f2lIndex].clear();

                // When pair of f2l is match
                // 41 f2l algo will work fine
                f2lAlgo();
            }
            // Add y' when an f2l pair is finished
            if(f2lIndex < 3)
                f2lArray[f2lIndex] += "y' ";

            applyF2lPairSolution(f2lArray[f2lIndex]);

            // Update f2lData
            f2lData += f2lArray[f2lIndex];
        }
        else
        {
            // Add y' when an f2l pair is finished
            if(f2lIndex < 3)
                f2lArray[f2lIndex] += "y' ";
            applyF2lPairSolution(f2lArray[f2lIndex]);
        }
        f2lIndex++;
    }
}

std::string CFOP::getF2lData()
{
    return f2lData;
}

void CFOP::applyF2lPairSolution(const std::string& f2lSol)
{
    std::stringstream ss(f2lSol);
    std::string move;
    while (ss >> move)
    {
        for (const auto& val : mpMove)
        {
            if (val.second == move)
                turn(val.first);
        }
    }
}

bool CFOP::f2lAlgo()
{
    // F2L 01, 02, 05, 06, 09, 10, 11, 15, 32, 33
    if (this->getCube().getFrontFace().getCubieThree() == this->getCube().getDownFace().getCubieFive()
        && this->getCube().getUpFace().getCubieNine() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getRightFace().getCubieOne() == this->getCube().getRightFace().getCubieFive())
    {
        if (upSixFrontRight()) // F2L 01
        {
            f2lArray[f2lIndex] += "U R U' R' ";
            return true;
        }
        else if (upFourRightFront()) // F2L 02
        {
            f2lArray[f2lIndex] += "F' U' F ";
            return true;
        }
        else if (upTwoFrontRight()) // F2L 05
        {
            f2lArray[f2lIndex] += "U' R U R' U2 R U' R' ";
            return true;
        }
        else if (upFourFrontRight()) // F2L 06
        {
            f2lArray[f2lIndex] += "U' R U2 R' U2 R U' R' ";
            return true;
        }
        else if (upTwoRightFront()) // F2L 09
        {
            f2lArray[f2lIndex] += "F R U R' U' F' R U' R' ";
            return true;
        }
        else if (upSixRightFront()) // F2L 10
        {
            f2lArray[f2lIndex] += "U' R U2 R' y' U R' U' R ";
            return true;
        }
        else if (upEightRightFront()) // F2L 11
        {
            f2lArray[f2lIndex] += "d R' U R U' R' U' R d' ";
            return true;
        }
        else if (upEightFrontRight()) // F2L 15
        {
            f2lArray[f2lIndex] += "U R' F R F' U R U R' ";
            return true;
        }
        else if (frontSixFrontRight()) // F2L 32
        {
            f2lArray[f2lIndex] += "U' R U' R' U2 R U' R' ";
            return true;
        }
        else if (frontSixRightFront()) // F2L 33
        {
            f2lArray[f2lIndex] += "U R U R' U2 R U R' ";
            return true;
        }
    } // F2L 03, 04, 07, 08, 12, 13, 14, 17, 35, 36
    else if (this->getCube().getFrontFace().getCubieThree() == this->getCube().getFrontFace().getCubieFive()
         && this->getCube().getUpFace().getCubieNine() == this->getCube().getRightFace().getCubieFive()
         && this->getCube().getRightFace().getCubieOne() == this->getCube().getDownFace().getCubieFive()) 
    {
         if (upEightRightFront()) // F2L 03
         {
            f2lArray[f2lIndex] += "F R' F' R ";
            return true;
         }
         else if (upTwoFrontRight()) // F2L 04
         {
             f2lArray[f2lIndex] += "R U R' ";
             return true;
         }
         else if (upFourRightFront()) // F2L 07
         {
             f2lArray[f2lIndex] += "U F' U' F U2 F' U F ";
             return true;
         }
         else if (upTwoRightFront()) // F2L 08
         {
             f2lArray[f2lIndex] += "d R' U2 R U R' U2 R d' ";
             return true;
         }
         else if (upFourFrontRight()) // F2L 12
         {
             f2lArray[f2lIndex] += "U' R U R' U R U R' ";
             return true;
         }
         else if (upEightFrontRight()) // F2L 13
         {
             f2lArray[f2lIndex] += "R' U2 R2 U R2 U R ";
             return true;
         }
         else if (upSixFrontRight()) // F2L 14
         {
             f2lArray[f2lIndex] += "U' R U' R' U R U R' ";
             return true;
         }
         else if (upSixRightFront()) // F2L 17
         {
             f2lArray[f2lIndex] += "R U' R' U2 F' U' F ";
             return true;
         }
         else if (frontSixFrontRight()) // F2L 35
         {
             f2lArray[f2lIndex] += "U R U R' U2 R U R' ";
             return true;
         }
         else if (frontSixRightFront()) // F2L 36
         {
             f2lArray[f2lIndex] += "U F' U' F U' R U R' ";
             return true;
         }
    } // F2L 16, 18, 19, 20, 21, 22, 23, 24, 31, 34
    else if (this->getCube().getFrontFace().getCubieThree() == this->getCube().getRightFace().getCubieFive()
         && this->getCube().getUpFace().getCubieNine() == this->getCube().getDownFace().getCubieFive()
         && this->getCube().getRightFace().getCubieOne() == this->getCube().getFrontFace().getCubieFive())
    {
         if (upSixFrontRight()) // F2L 16
         {
             f2lArray[f2lIndex] += "R U2 R' U' R U R' ";
             return true;
         }
         else if (upEightRightFront()) // F2L 18
         {
             f2lArray[f2lIndex] += "R' F R F' R U' R' U R U' R' ";
             return true;
         }
         else if (upTwoFrontRight()) // F2L 19
         {
             f2lArray[f2lIndex] += "U R U2 R' U R U' R' ";
             return true;
         }
         else if (upFourFrontRight()) // F2L 20
         {
             f2lArray[f2lIndex] += "U2 R U R' U R U' R' ";
             return true;
         }
         else if (upFourRightFront()) // F2L 21
         {
             f2lArray[f2lIndex] += "U' R U' R2 F R F' R U' R' ";
             return true;
         }
         else if (upTwoRightFront()) // F2L 22
         {
             f2lArray[f2lIndex] += "F' L' U2 L F ";
             return true;
         }
         else if (upEightFrontRight()) // F2L 23
         {
             f2lArray[f2lIndex] += "U' R U R' d R' U' R d' ";
             return true;
         }
         else if (upSixRightFront()) // F2L 24
         {
             f2lArray[f2lIndex] += "F U R U' R' F' R U' R' ";
             return true;
         }
         else if (frontSixRightFront()) // F2L 31
         {
             f2lArray[f2lIndex] += "U' R' F R F' R U' R' ";
             return true;
         }
         else if (frontSixFrontRight()) // F2L 34
         {
             f2lArray[f2lIndex] += "R2 U R2 U R2 U2 R2 ";
             return true;
         }
    } // F2L 25 28 39
    else if (this->getCube().getFrontFace().getCubieNine() == this->getCube().getFrontFace().getCubieFive()
         && this->getCube().getRightFace().getCubieSeven() == this->getCube().getRightFace().getCubieFive()
         && this->getCube().getDownFace().getCubieThree() == this->getCube().getDownFace().getCubieFive())
    {
         if (upSixFrontRight()) // F2L 25
         {
             f2lArray[f2lIndex] += "U' R' F R F' R U R' ";
             return true;
         }
         else if (upEightFrontRight()) // F2L 28
         {
             f2lArray[f2lIndex] += "U R U' R' F R' F' R ";
             return true;
         }
         else if (frontSixRightFront()) // F2L 39
         {
             f2lArray[f2lIndex] += "R2 U2 F R2 F' U2 R' U R' ";
             return true;
         }
    } // F2L 26 27 37 38 
    else if (this->getCube().getFrontFace().getCubieNine() == this->getCube().getDownFace().getCubieFive()
         && this->getCube().getRightFace().getCubieSeven() == this->getCube().getFrontFace().getCubieFive()
         && this->getCube().getDownFace().getCubieThree() == this->getCube().getRightFace().getCubieFive())
    {
         if (upSixFrontRight()) // F2L 26
         {
             f2lArray[f2lIndex] += "R U' R' U R U' R' ";
             return true;
         }
         else if (upEightRightFront()) // F2L 27
         {
             f2lArray[f2lIndex] += "R' F R F' U R U' R' ";
             return true;
         }
         else if (frontSixFrontRight()) // F2L 37
         {
             f2lArray[f2lIndex] += "R U' R' U' R U R' U2 R U' R' ";
             return true;
         }
         else if (frontSixRightFront()) // F2L 38
         {
             f2lArray[f2lIndex] += "F' L' U2 L F R U R' ";
             return true;
         }
    } // F2L 29 30 40 41
    else if (this->getCube().getFrontFace().getCubieNine() == this->getCube().getRightFace().getCubieFive()
         && this->getCube().getDownFace().getCubieThree() == this->getCube().getFrontFace().getCubieFive()
         && this->getCube().getRightFace().getCubieSeven() == this->getCube().getDownFace().getCubieFive())
    {
         if (upEightRightFront()) // F2L 29
         {
             f2lArray[f2lIndex] += "F' U F U' F' U F ";
             return true;
         }
         else if (upSixFrontRight()) // F2L 30
         {
             f2lArray[f2lIndex] += "R U R' U' R U R' ";
             return true;
         }
         else if (frontSixFrontRight()) // F2L 40
         {
             f2lArray[f2lIndex] += "R U2 R U R' U R U2 R2 ";
             return true;
         }
         else if (frontSixRightFront()) // F2L 41
         {
             f2lArray[f2lIndex] += "R U' R' F' L' U2 L F ";
             return true;
         }
    }
    return false;
}

bool CFOP::isF2lPairFinish()
{
    return this->getCube().getFrontFace().getCubieNine() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getDownFace().getCubieThree() == this->getCube().getDownFace().getCubieFive()
        && this->getCube().getRightFace().getCubieSeven() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getFrontFace().getCubieSix() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getRightFace().getCubieFour() == this->getCube().getRightFace().getCubieFive();
}

/*
    Handle cases when 41 f2l don't match
*/
void CFOP::handleSpecialF2l()
{
    // Cases when corner is in the front right-bottom
    if (isCornerCorrect(this->getCube().getFrontFace().getCubieNine(), this->getCube().getDownFace().getCubieThree(), this->getCube().getRightFace().getCubieSeven()))
    {
        // Move edge to match 41 f2l
        if (frontFourFrontRight())
            f2lArray[f2lIndex] += "L' U2 L "; 
        else if (frontFourRightFront())
            f2lArray[f2lIndex] += "L' U' L "; 
        else if (backFourFrontRight())
            f2lArray[f2lIndex] += "L U2 L' "; 
        else if (backFourRightFront())
            f2lArray[f2lIndex] += "L U' L' "; 
        else if (backSixFrontRight())
            f2lArray[f2lIndex] += "R' U R U' ";
        else if (backSixRightFront())
            f2lArray[f2lIndex] += "R' U R "; 
        else if (upTwoFrontRight() || upSixRightFront())
            f2lArray[f2lIndex] += "U ";
        else if (upTwoRightFront() || upFourFrontRight())
            f2lArray[f2lIndex] += "U2 ";
        else if (upFourRightFront() || upEightFrontRight())
            f2lArray[f2lIndex] += "U' ";
    } 
    // Case when corner is in the front left-bottom
    else if (isCornerCorrect(this->getCube().getFrontFace().getCubieSeven(), this->getCube().getLeftFace().getCubieNine(), this->getCube().getDownFace().getCubieOne()))
    {   
        // Move f2l pair to match 41 f2l
        if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U' L ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U' L2 U' L ";
        else if (isEdgeCorrect(this->getCube().getRightFace().getCubieSix(), this->getCube().getBackFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U' L R' U R ";
        else if (isEdgeCorrect(this->getCube().getUpFace().getCubieTwo(), this->getCube().getBackFace().getCubieEight()))
            f2lArray[f2lIndex] += "U L' U' L ";
        else
            f2lArray[f2lIndex] += "L' U' L ";
    }
    // Case when corner is in the back left-bottom
    else if (isCornerCorrect(this->getCube().getLeftFace().getCubieSeven(), this->getCube().getDownFace().getCubieSeven(), this->getCube().getBackFace().getCubieOne()))
    {
        // Move f2l pair to match 41 f2l
        if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U L2 U2 L' ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U2 L' ";
        else if (isEdgeCorrect(this->getCube().getRightFace().getCubieSix(), this->getCube().getBackFace().getCubieSix()))
            f2lArray[f2lIndex] += "L U2 L' R' U R ";
        else if (isEdgeCorrect(this->getCube().getUpFace().getCubieSix(), this->getCube().getRightFace().getCubieTwo()))
            f2lArray[f2lIndex] += "L U' L' U2 ";
        /*else if (isEdgeCorrect(this->getCube().getFrontFace().getCubieSix(), this->getCube().getRightFace().getCubieFour())
            || isEdgeCorrect(this->getCube().getUpFace().getCubieEight(), this->getCube().getFrontFace().getCubieTwo())
            || isEdgeCorrect(this->getCube().getUpFace().getCubieFour(), this->getCube().getLeftFace().getCubieTwo())
            || isEdgeCorrect(this->getCube().getUpFace().getCubieTwo(), this->getCube().getBackFace().getCubieEight()))
            f2lArray[f2lIndex] += "L U2 L' ";*/
        // 
        // --> Replace with else
        else
            f2lArray[f2lIndex] += "L U2 L' ";
    }
    // Case when corner is in the back right-bottom
    else if (isCornerCorrect(this->getCube().getRightFace().getCubieNine(), this->getCube().getDownFace().getCubieNine(), this->getCube().getBackFace().getCubieThree()))
    {
        // Move f2l pair to match 41 f2l
        if (isEdgeCorrect(this->getCube().getUpFace().getCubieTwo(), this->getCube().getBackFace().getCubieEight()))
            f2lArray[f2lIndex] += "R' U2 R U' ";
        else if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "R' U2 R L' U2 L ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U' L' R' U R' U ";
        else if (isEdgeCorrect(this->getCube().getBackFace().getCubieSix(), this->getCube().getRightFace().getCubieSix()))
            f2lArray[f2lIndex] += "R' U R U ";
        else
            f2lArray[f2lIndex] += "R' U R U ";
    }
    // Case when corner is on the upper layer 
    else if (isCornerCorrect(this->getCube().getUpFace().getCubieSeven(), this->getCube().getFrontFace().getCubieOne(), this->getCube().getLeftFace().getCubieThree()))
    {
        if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U2 L ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U' L' U' ";
        else if (isEdgeCorrect(this->getCube().getRightFace().getCubieSix(), this->getCube().getBackFace().getCubieSix()))
            f2lArray[f2lIndex] += "R' U R U2 ";
        else
            f2lArray[f2lIndex] += "U' ";
    }
    else if (isCornerCorrect(this->getCube().getUpFace().getCubieOne(), this->getCube().getLeftFace().getCubieOne(), this->getCube().getBackFace().getCubieSeven()))
    {
        if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U  L U2 ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U' L' ";
        else if (isEdgeCorrect(this->getCube().getRightFace().getCubieSix(), this->getCube().getBackFace().getCubieSix()))
            f2lArray[f2lIndex] += "R' U' R U' ";
        else
            f2lArray[f2lIndex] += "U2 ";
    }
    else if (isCornerCorrect(this->getCube().getUpFace().getCubieThree(), this->getCube().getRightFace().getCubieThree(), this->getCube().getBackFace().getCubieNine()))
    {
        if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U  L ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U L' ";
        else if (isEdgeCorrect(this->getCube().getRightFace().getCubieSix(), this->getCube().getBackFace().getCubieSix()))
            f2lArray[f2lIndex] += "R' U' R U' ";
        else
            f2lArray[f2lIndex] += "U ";
    }
    else if (isCornerCorrect(this->getCube().getUpFace().getCubieNine(), this->getCube().getFrontFace().getCubieThree(), this->getCube().getRightFace().getCubieOne()))
    {
        if (isEdgeCorrect(this->getCube().getFrontFace().getCubieFour(), this->getCube().getLeftFace().getCubieSix()))
            f2lArray[f2lIndex] += "L' U' L U ";
        else if (isEdgeCorrect(this->getCube().getLeftFace().getCubieFour(), this->getCube().getBackFace().getCubieFour()))
            f2lArray[f2lIndex] += "L U L' U2 ";
        else if (isEdgeCorrect(this->getCube().getRightFace().getCubieSix(), this->getCube().getBackFace().getCubieSix()))
            f2lArray[f2lIndex] += "R' U R ";
    }
}

// Handle multiple cases of corner vairations
const bool CFOP::isCornerCorrect(const Color& colorCubieOne, const Color& colorCubieTwo, const Color& colorCubieThree)
{
    const Color frontCenterColor = this->getCube().getFrontFace().getCubieFive();
    const Color rightCenterColor = this->getCube().getRightFace().getCubieFive();
    const Color downCenterColor = this->getCube().getDownFace().getCubieFive();

    return ((colorCubieOne == frontCenterColor) || (colorCubieOne == rightCenterColor) || (colorCubieOne == downCenterColor))
        && ((colorCubieTwo == frontCenterColor) || (colorCubieTwo == rightCenterColor) || (colorCubieTwo == downCenterColor))
        && ((colorCubieThree == frontCenterColor) || (colorCubieThree == rightCenterColor) || (colorCubieThree == downCenterColor));
}

// Handle 2 cases of edge
const bool CFOP::isEdgeCorrect(const Color& colorCubieOne, const Color& colorCubieTwo)
{
    const Color frontCenterColor = this->getCube().getFrontFace().getCubieFive();
    const Color rightCenterColor = this->getCube().getRightFace().getCubieFive();

    return ((colorCubieOne == frontCenterColor) || (colorCubieOne == rightCenterColor))
        && ((colorCubieTwo == frontCenterColor) || (colorCubieTwo == rightCenterColor));
}

// Up face edge position
bool CFOP::upTwoFrontRight()
{
    return this->getCube().getUpFace().getCubieTwo() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getBackFace().getCubieEight() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::upTwoRightFront()
{
    return this->getCube().getUpFace().getCubieTwo() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getBackFace().getCubieEight() == this->getCube().getFrontFace().getCubieFive();
}

bool CFOP::upFourFrontRight()
{
    return this->getCube().getUpFace().getCubieFour() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getLeftFace().getCubieTwo() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::upFourRightFront()
{
    return this->getCube().getUpFace().getCubieFour() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getLeftFace().getCubieTwo() == this->getCube().getFrontFace().getCubieFive();
}

bool CFOP::upSixFrontRight()
{
    return this->getCube().getUpFace().getCubieSix() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getRightFace().getCubieTwo() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::upSixRightFront()
{
    return this->getCube().getUpFace().getCubieSix() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getRightFace().getCubieTwo() == this->getCube().getFrontFace().getCubieFive();
}

bool CFOP::upEightFrontRight()
{
    return this->getCube().getUpFace().getCubieEight() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getFrontFace().getCubieTwo() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::upEightRightFront()
{
    return this->getCube().getUpFace().getCubieEight() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getFrontFace().getCubieTwo() == this->getCube().getFrontFace().getCubieFive();
}

// Front face edge position
bool CFOP::frontFourFrontRight()
{
    return this->getCube().getFrontFace().getCubieFour() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getLeftFace().getCubieSix() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::frontFourRightFront()
{
    return this->getCube().getFrontFace().getCubieFour() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getLeftFace().getCubieSix() == this->getCube().getFrontFace().getCubieFive();
}

bool CFOP::frontSixFrontRight()
{
    return this->getCube().getFrontFace().getCubieSix() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getRightFace().getCubieFour() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::frontSixRightFront()
{
    return this->getCube().getFrontFace().getCubieSix() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getRightFace().getCubieFour() == this->getCube().getFrontFace().getCubieFive();
}

// Back face edge position
bool CFOP::backFourFrontRight()
{
    return this->getCube().getBackFace().getCubieFour() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getLeftFace().getCubieFour() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::backFourRightFront()
{
    return this->getCube().getBackFace().getCubieFour() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getLeftFace().getCubieFour() == this->getCube().getFrontFace().getCubieFive();
}

bool CFOP::backSixFrontRight()
{
    return this->getCube().getBackFace().getCubieSix() == this->getCube().getFrontFace().getCubieFive()
        && this->getCube().getRightFace().getCubieSix() == this->getCube().getRightFace().getCubieFive();
}
bool CFOP::backSixRightFront()
{
    return this->getCube().getBackFace().getCubieSix() == this->getCube().getRightFace().getCubieFive()
        && this->getCube().getRightFace().getCubieSix() == this->getCube().getFrontFace().getCubieFive();
}
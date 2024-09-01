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

    // OLL
    ollData = "";
    ollString = "";

    // PLL
    pllData = "";
    pllString = "";
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

/*
    Cross
*/

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

/*
    F2L
*/

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
            f2lArray[f2lIndex] += "y' ";

            applyF2lPairSolution(f2lArray[f2lIndex]);

            // Update f2lData
            f2lData += f2lArray[f2lIndex];
        }
        else
        {
            // Add y' when an f2l pair is finished
            f2lArray[f2lIndex] += "y' ";
            applyF2lPairSolution(f2lArray[f2lIndex]);

            // Update f2lData
            f2lData += f2lArray[f2lIndex];
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
            f2lArray[f2lIndex] += "U' R U2 R' y' U R' U' R y ";
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

/*
    OLL
*/

void CFOP::solveOLL()
{
    if (!isUpFaceFinish(this->getCube().getUpFace()))
    {
        for (int i = 0; i < 4; ++i) // 4 times rotation to find accurate OLL case
        {
            if (!handleOLL())
            {
                turn(41);
                ollData += "y' ";
            }
            else
            {
                ollData += ollString;
                applyOllSolution(ollString);
                break;
            }
        }
    }
}

std::string CFOP::getOllData() const
{
    return ollData;
}

bool CFOP::checkUpLayerCubie(const Color& cubieColor1, const Color& cubieColor2, const Color& cubieColor3, const Color& cubieColor4, const Color& cubieColor5, const Color& cubieColor6, const Color& cubieColor7, const Color& cubieColor8)
{
    Color upLayerColor = this->getCube().getUpFace().getCubieFive();
    return cubieColor1 == upLayerColor
        && cubieColor2 == upLayerColor
        && cubieColor3 == upLayerColor
        && cubieColor4 == upLayerColor
        && cubieColor5 == upLayerColor
        && cubieColor6 == upLayerColor
        && cubieColor7 == upLayerColor
        && cubieColor8 == upLayerColor;
}
bool CFOP::handleOLL()
{
    // Up face
    Color u1 = this->getCube().getUpFace().getCubieOne();
    Color u2 = this->getCube().getUpFace().getCubieTwo();
    Color u3 = this->getCube().getUpFace().getCubieThree();
    Color u4 = this->getCube().getUpFace().getCubieFour();
    Color u6 = this->getCube().getUpFace().getCubieSix();
    Color u7 = this->getCube().getUpFace().getCubieSeven();
    Color u8 = this->getCube().getUpFace().getCubieEight();
    Color u9 = this->getCube().getUpFace().getCubieNine();

    // Front face
    Color f1 = this->getCube().getFrontFace().getCubieOne();
    Color f2 = this->getCube().getFrontFace().getCubieTwo();
    Color f3 = this->getCube().getFrontFace().getCubieThree();

    // Left face
    Color l1 = this->getCube().getLeftFace().getCubieOne();
    Color l2 = this->getCube().getLeftFace().getCubieTwo();
    Color l3 = this->getCube().getLeftFace().getCubieThree();

    // Right face
    Color r1 = this->getCube().getRightFace().getCubieOne();
    Color r2 = this->getCube().getRightFace().getCubieTwo();
    Color r3 = this->getCube().getRightFace().getCubieThree();

    // Back face
    Color b7 = this->getCube().getBackFace().getCubieSeven();
    Color b8 = this->getCube().getBackFace().getCubieEight();
    Color b9 = this->getCube().getBackFace().getCubieNine();

    if (checkUpLayerCubie(f1, f2, r2, b7, u2, u3, u4, u9)) // OLL 29
    {
        ollString += "R U R' U' R U' R' F' U' F R U R' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r2, r3, l1, u2, u4, u7, u9)) // OLL 30
    {
        ollString += "F R' F R2 U' R' U' R U R' F2 ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r2, b7, b9, u2, u4, u7, u9)) // OLL 41
    {
        ollString += "R U R' U R U2 R' F R U R' U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f3, r2, b8, u1, u3, u4, u8)) // OLl 42
    {
        ollString += "R' U' R U' R' U2 R F R U R' U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, b7, b8, u3, u4, u6, u7)) // OLL 39
    {
        ollString += "L F' L' U' L U F U' L' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, l3, b8, b9, u1, u4, u6, u9)) // OLL 40
    {
        ollString += "R' F R U R' U' F' U R ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r3, l1, b8, u4, u6, u7, u9)) // OLL 34
    {
        ollString += "R U R2 U' R' F R U R U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(r1, r2, r3, l2, u1, u2, u7, u8)) // OLL 46
    {
        ollString += "R' U' R' F R F' U R ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r2, u1, u2, u3, u4, u7, u9)) // OLL 28
    {
        ollString += "r U R' U' r' R U R U' R' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, b8, u1, u3, u4, u6, u7, u9)) // OLL 57
    {
        ollString += "R U R' U' M' U R U' r' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f3, b7, b9, u2, u4, u6, u8)) // OLL 21
    {
        ollString += "R U2 R' U' R U R' U' R U' R' ";
        return true;
    }
    else if (checkUpLayerCubie(f3, l1, l3, b9, u2, u4, u6, u8)) // OLL 22
    {
        ollString += "R U2 R2 U' R2 U' R2 U2 R ";
        return true;
    }
    else if (checkUpLayerCubie(b7, b9, u2, u4, u6, u7, u8, u9)) // OLL 23
    {
        ollString += "R2 D' R U2 R' D R U2 R ";
        return true;
    }
    else if (checkUpLayerCubie(f1, b7, u2, u3, u4, u6, u8, u9)) // OLL 24
    {
        ollString += "r U R' U' r' F R F' ";
        return true;
    }
    else if (checkUpLayerCubie(f3, l1, u2, u3, u4, u6, u7, u8)) // OLL 25
    {
        ollString += "F' r U R' U' r' F R ";
        return true;
    }
    else if (checkUpLayerCubie(f1, r1, l1, u2, u3, u4, u6, u8)) // OLL 26
    {
        ollString += "R U2 R' U' R U' R' ";
        return true;
    }
    else if (checkUpLayerCubie(f3, r3, b7, u2, u4, u6, u7, u8)) // OLL 27
    {
        ollString += "R U R' U R U2 R' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, r2, r3, l1, l2, l3, b8)) // OLL 1
    {
        ollString += "R U2 R2 F R F' U2 R' F R F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, r2, l2, l3, b7, b8, b9)) // OLL 2
    {
        ollString += "r U r' U2 r U2 R' U2 R U' r' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, r2, r3, l2, b7, b8, u7)) // OLL 3
    {
        ollString += "r' R2 U R' U r U2 r' U M' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r2, l1, l2, b8, b9, u9)) // OLL 4
    {
        ollString += "M U' r U2 r' U' R U' R' M' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r2, r3, l2, b8, u1, u9)) // OLL 17
    {
        ollString += "F R' F' R2 r' U R U' R' U' M' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, f3, r2, l2, b8, u1, u3)) // OLL 18
    {
        ollString += "r U R' U R U2 r2 U' R U' R' U2 r ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, r2, l2, l3, b8, u1, u3)) // OLL 19
    {
        ollString += "r' R U R U R' U' M' R' F R F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r2, l2, b8, u1, u3, u7, u9)) // OLL 20
    {
        ollString += "r U R' U' M M U R U' R' U' M' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r2, l1, b9, u2, u4, u9)) // OLL 9
    {
        ollString += "R U R' U' R' F R2 U R' U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f3, r2, l3, b7, b8, u3, u4, u8)) // OLL 10
    {
        ollString += "R U R' U R' F R F' R U2 R' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, r3, l2, b8, u1, u6, u8, u9)) // OLL 35
    {
        ollString += "R U2 R2 F R F' R U2 R' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r2, r3, u1, u2, u4, u9)) // OLL 37
    {
        ollString += "F R' F' R U R U' R' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r1, r3, b7, b8, u4, u6)) // OLL 51
    {
        ollString += "F U R U' R' U R U' R' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, r1, r2, r3, l2, b7, u2, u8)) // OLL 52
    {
        ollString += "R U R' U R U' B U' B' R' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, f3, b7, b8, b9, u4, u6)) // OLL 55
    {
        ollString += "R' F R U R U' R2 F' R2 U' R' U R U R' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, r3, l1, l3, b8, u4, u6)) // OLL 56
    {
        ollString += "r' U' r U' R' U R U' R' U R r' U r ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, r3, b7, b8, u4, u6, u7)) // OLL 13
    {
        ollString += "F U R U' R2 F' R U R U' R' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, l1, b8, b9, u4, u6, u9)) // OLL 14
    {
        ollString += "R' F R U R' F' R F U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, l3, r3, b8, u1, u4, u6)) // OLL 15
    {
        ollString += "l' U' l L' U' L U l' U l ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r1, l1, b8, u3, u4, u6)) // OLL 16
    {
        ollString += "r U r' R U R' U' r U' r' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, l2, b7, u2, u3, u6, u9)) // OLL 31
    {
        ollString += "R' U' F U R U' R' F' R ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, r2, b9, u1, u2, u4, u7)) // OLL 32
    {
        ollString += "L U F' U' L' U L F L' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, l1, l2, l3, u2, u3, u6, u9)) // OLL 43
    {
        ollString += "F' U' L' U L F ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, r2, r3, u1, u2, u4, u7)) // OLL 44
    {
        ollString += "F U R U' R' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r1, r3, l2, b7, u2, u6)) // OLL 47
    {
        ollString += "R' U' R' F R F' R' F R F' U R ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, r2, l1, l3, b9, u2, u4)) // OLL 48
    {
        ollString += "F R U R' U' R U R' U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, l1, l2, l3, b9, u2, u6)) // OLL 49
    {
        ollData += "r U' r r U r r U r r U' r ";
        return true;
    }
    else if (checkUpLayerCubie(f3, l1, l2, l3, b8, b9, u6, u8)) // OLL 50
    {
        ollString += "r' U r r U' r r U' r r U r' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, f3, l2, b7, b9, u2, u6)) // OLL 53
    {
        ollString += "l' U2 L U L' U' L U L' U l ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, f3, r2, b7, b9, u2, u4)) // OLL 54
    {
        ollString += "r U2 R' U' R U R' U' R U' r' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, r2, r3, b7, u2, u4, u7)) // OLL 7
    {
        ollString += "r U R' U R U2 r' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, l1, l2, b9, u2, u6, u9)) // OLL 8
    {
        ollString += "l' U' L U' L' U2 l ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, l3, r2, b7, u2, u3, u4)) // OLL 11
    {
        ollString += "r U R' U R' F R F' R U2 r' ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r1, l2, b9, u1, u2, u6)) // OLL 12
    {
        ollString += "M' R' U' R U' R' U2 R U' R r' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, f3, r2, r3, l3, u1, u2, u4)) // OLL 5
    {
        ollString += "l' U2 L U L' U l ";
        return true;
    }
    else if (checkUpLayerCubie(f1, f2, r1, l1, l2, u2, u3, u6)) // OLL 6
    {
        ollString += "r U2 R' U' R U' r' ";
        return true;
    } 
    else if (checkUpLayerCubie(f1, f2, b7, b8, u3, u4, u6, u9)) // OLL 33
    {
        ollString += "R U R' U' R' F R F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, l1, l3, b8, u3, u4, u6, u9)) // OLL 45
    {
        ollString += "F R U R' U' F' ";
        return true;
    }
    else if (checkUpLayerCubie(f2, l2, l3, b9, u1, u2, u6, u9)) // OLL 36
    {
        ollString += "L' U' L U' L' U L U L F' L' F ";
        return true;
    }
    else if (checkUpLayerCubie(f2, r1, r2, b7, u2, u3, u4, u7)) // OLL 38
    {
        ollString += "R U R' U R U' R' U' R' F R F' ";
        return true;
    }

    return false;
}

bool CFOP::isUpFaceFinish(const Face& face)
{
    Color upFaceCenterColor = face.getCubieFive();
    return this->getCube().getUpFace().getCubieOne() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieTwo() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieThree() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieFour() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieSix() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieSeven() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieEight() == upFaceCenterColor
        && this->getCube().getUpFace().getCubieNine() == upFaceCenterColor;
}

void CFOP::applyOllSolution(const std::string& ollSolution)
{
    std::stringstream ss(ollSolution);
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

/*
    PLL
*/

void CFOP::solvePll()
{
    if (!isLastLayerFinish())
    {
        for (int i = 0; i < 4; ++i) // 4 times rotation to find accurate OLL case
        {
            if (!handlePll())
            {
                turn(41);
                pllData += "y' ";
            }
            else
            {
                pllData += pllString;
                applyPllSolution(pllString);
                break;
            }
        }
    }

    // Finish cube when pll is done
    if (this->getCube().getFrontFace().getCubieFive() == this->getCube().getRightFace().getCubieOne())
    {
        pllData += " U ";
        this->getCube().U();
    }
    else if (this->getCube().getFrontFace().getCubieFive() == this->getCube().getLeftFace().getCubieOne())
    {
        pllData += " U' ";
        this->getCube().U_p();
    }
    else if (this->getCube().getFrontFace().getCubieFive() == this->getCube().getBackFace().getCubieSeven())
    {
        pllData += " U2 ";
        this->getCube().U();
        this->getCube().U();
    }
}

std::string CFOP::getPllData() const
{
    return pllData;
}

bool CFOP::isLastLayerFinish()
{
    // Front layer
    Color f1 = this->getCube().getFrontFace().getCubieOne();
    Color f2 = this->getCube().getFrontFace().getCubieTwo();
    Color f3 = this->getCube().getFrontFace().getCubieThree();
    Color f5 = this->getCube().getFrontFace().getCubieFive();

    // Right face
    Color r1 = this->getCube().getRightFace().getCubieOne();
    Color r2 = this->getCube().getRightFace().getCubieTwo();
    Color r3 = this->getCube().getRightFace().getCubieThree();
    Color r5 = this->getCube().getRightFace().getCubieFive();

    // Left face
    Color l1 = this->getCube().getLeftFace().getCubieOne();
    Color l2 = this->getCube().getLeftFace().getCubieTwo();
    Color l3 = this->getCube().getLeftFace().getCubieThree();
    Color l5 = this->getCube().getLeftFace().getCubieFive();

    // Back face
    Color b7 = this->getCube().getBackFace().getCubieSeven();
    Color b8 = this->getCube().getBackFace().getCubieEight();
    Color b9 = this->getCube().getBackFace().getCubieNine();
    Color b5 = this->getCube().getBackFace().getCubieFive();

    return (f1 == f5 && f2 == f5 && f3 == f5)
        && (r1 == r5 && r2 == r5 && r3 == r5)
        && (l1 == l5 && l2 == l5 && l3 == l5)
        && (b7 == b5 && b8 == b5 && b9 == b5);
}

void CFOP::applyPllSolution(const std::string& pllSolution)
{
    std::stringstream ss(pllSolution);
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

bool CFOP::handlePll()
{
    // Front layer
    Color f1 = this->getCube().getFrontFace().getCubieOne();
    Color f2 = this->getCube().getFrontFace().getCubieTwo();
    Color f3 = this->getCube().getFrontFace().getCubieThree();
    Color f5 = this->getCube().getFrontFace().getCubieFive();

    // Right face
    Color r1 = this->getCube().getRightFace().getCubieOne();
    Color r2 = this->getCube().getRightFace().getCubieTwo();
    Color r3 = this->getCube().getRightFace().getCubieThree();
    Color r5 = this->getCube().getRightFace().getCubieFive();

    // Left face
    Color l1 = this->getCube().getLeftFace().getCubieOne();
    Color l2 = this->getCube().getLeftFace().getCubieTwo();
    Color l3 = this->getCube().getLeftFace().getCubieThree();
    Color l5 = this->getCube().getLeftFace().getCubieFive();

    // Back face
    Color b7 = this->getCube().getBackFace().getCubieSeven();
    Color b8 = this->getCube().getBackFace().getCubieEight();
    Color b9 = this->getCube().getBackFace().getCubieNine();
    Color b5 = this->getCube().getBackFace().getCubieFive();

    // PLL H
    if (f1 == b8 && b7 == f2 && r1 == l2 && l1 == r2 && twoColorEqual(f1, f2, f3) && twoColorEqual(r1, r2, r3) && twoColorEqual(l1, l2, l3) && twoColorEqual(b7, b8, b9))
    {
        pllString += "M M U M M U2 M M U M M ";
        return true;
    } 
    // PLL Ua
    else if (f2 == r1 && r2 == l1 && l2 == f1 && threeColorEqual(b7, b8, b9) && twoColorEqual(l1, l2, l3) && twoColorEqual(f1, f2, f3) && twoColorEqual(r1, r2, r3))
    {
        pllString += "M M U M U2 M' U M M ";
        return true;
    }
    // PLL Ub
    else if (f2 == l1 && l2 == r1 && r2 == f1 && threeColorEqual(b7, b8, b9) && twoColorEqual(l1, l2, l3) && twoColorEqual(f1, f2, f3) && twoColorEqual(r1, r2, r3))
    {
        pllString += "M M U' M U2 M' U' M M ";
        return true;
    }
    // PLL Z
    else if (f2 == l1 && l2 == f1 && r2 == b7 && b8 == r1 && twoColorEqual(f1, f2, f3) && twoColorEqual(l1, l2, l3) && twoColorEqual(r1, r2, r3) && twoColorEqual(b7, b8, b9))
    {
        pllString += "M' U M M U M M U M' U2 M M ";
        return true;
    }
    // PLL E
    else if (f3 == r2 && r1 == b8 && r3 == f2 && b9 == r2 && f1 == l2 && l3 == b8 && l1 == f2 && b7 == l2)
    {
        pllString += "x' R U' R' D R U R' D' R U R' D R U' R' D' x ";
        return true;
    }
    // PLL Na
    else if (f1 == b7 && r1 == l3 && b9 == f3 && l1 == r3 && twoColorEqual(f3, f1, f2) && twoColorEqual(r3, r1, r2) && twoColorEqual(b7, b9, b8) && twoColorEqual(l3, l1, l2))
    {
        pllString += "R U R' U R U R' F' R U R' U' R' F R2 U' R' U2 R U' R' ";
        return true;
    }
    // PLL Nb
    else if (f3 == b9 && r3 == l1 && b7 == f1 && l1 == r3 && twoColorEqual(f1, f3, f2) && twoColorEqual(r1, r3, r2) && twoColorEqual(b9, b7, b8) && twoColorEqual(l1, l3, l2))
    {
        pllString += "R' U R U' R' F' U' F R U R' F R' F' R U' R ";
        return true;
    }
    // PLL V
    else if (f3 == r2 && b9 == r2 && r1 == l2 && r3 == b8 && b7 == f1 && f1 == f2 && l2 == l3 && twoColorEqual(f1, f3, f2) && twoColorEqual(l2, l1, l3))
    {
        pllString += "R' U R' U' y R' F' R2 U' R' U R' F R F ";
        return true;
    } 
    // PLL Y
    else if(twoColorEqual(f1, f3, f2) && twoColorEqual(r2, r1, r3) && f3 == b9 && r1 == b8 && b7 == f1 && l3 == r1 && l2 == f3 && l1 == r2)
    {
        pllString += "F R U' R' U' R U R' F' R U R' U' R' F R F' ";
        return true;
    }
    // PLL Aa
    else if (twoColorEqual(f2, f1, f3) && twoColorEqual(r1, r3, r2) && f1 == l2 && f1 == r3 && b7 == r1 && b8 == l1 && b9 == f2)
    {
        pllString += "x L2 D2 L' U' L D2 L' U L' x' ";
        return true;
    }
    // PLL Ab
    else if (twoColorEqual(r2, r1, r3) && twoColorEqual(b8, b7, b9) && r1 == b7 && f3 == b9 && f2 == l1 && f1 == r3 && l3 == f2)
    {
        pllString += "x' L2 D2 L U L' D2 L U' L x ";
        return true;
    }
    // PLL F
    else if (threeColorEqual(l1, l2, l3) && threeColorNotEqual(f1, f2, f3) && threeColorNotEqual(r1, r2, r3) && threeColorNotEqual(b7, b8, b9) && f2 == b7 && f3 == b9 && b8 == f1 && b9 == f3)
    {
        pllString += "R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R ";
        return true;
    }
    // PLL Ga
    else if (twoColorEqual(f2, f1, f3) && twoColorEqual(l1, l2, l3) && threeColorNotEqual(r1, r2, r3) && threeColorNotEqual(b7, b8, b9))
    {
        pllString += "R2 U R' U R' U' R U' R2 U' D R' U R D' ";
        return true;
    } 
    // PLL Gb
    else if (twoColorEqual(l1, l2, l3) && twoColorEqual(r2, r1, r3) && threeColorNotEqual(f1, f2, f3) && threeColorNotEqual(b7, b8, b9) && f1 == r3 && f2 == b7 && f3 == b9)
    {
        pllString += "R' U' R U D' R2 U R' U R U' R U' R2 D ";
        return true;
    }
    // PLL Gc
    else if (twoColorEqual(l1, l2, l3) && twoColorEqual(b8, b7, b9) && threeColorNotEqual(f1, f2, f3) && threeColorNotEqual(r1, r2, r3))
    {
        pllString += "R2 U' R U' R U R' U R2 U D' R U' R' D ";
        return true;
    }
    // PLL Gd
    else if (twoColorEqual(l1, l2, l3) && twoColorEqual(r1, r3, r2) && threeColorNotEqual(f1, f2, f3) && threeColorNotEqual(b7, b8, b9))
    {
        pllString += "R U R' U' D R2 U' R U' R' U R' U R2 D' ";
        return true;
    }
    // PLL Ja
    else if (threeColorEqual(l1, l2, l3) && twoColorEqual(f1, f3, f2) && twoColorEqual(r1, r3, r2) && twoColorEqual(b8, b7, b9))
    {
        pllString += "x R2 F R F' R U2 r' U r U2 x' ";
        return true;
    }
    // PLL Jb
    else if (threeColorEqual(l1, l2, l3) && twoColorEqual(f2, f1, f3) && twoColorEqual(r2, r1, r3) && twoColorEqual(b7, b9, b8))
    {
        pllString += "R U R' F' R U R' U' R' F R2 U' R' ";
        return true;
    }
    // PLL Ra
    else if (twoColorEqual(f1, f3, f2) && twoColorEqual(l1, l2, l3) && r1 == b7 && r2 == b9 && r3 == f1)
    {
        pllString += "R U' R' U' R U R D R' U' R D' R' U2 R' ";
        return true;
    } 
    // PLL Rb
    else if (twoColorEqual(l1, l2, l3) && twoColorEqual(b7, b9, b8) && f1 == l2 && f2 == l1 && f3 == r2)
    {
        pllString += "R2 F R U R U' R' F' R U2 R' U2 R ";
        return true;
    } 
    // PLL T
    else if (twoColorEqual(l1, l2, l3) && twoColorEqual(f1, f3, f2) && twoColorEqual(b7, b9, b8) && threeColorNotEqual(r1, r2, r3) && f3 == l2 && f3 == b9 && r2 == l1 && r2 == l3 && r1 == b7 && r3 == f1)
    {
        pllString += "R U R' U' R' F R2 U' R' U' R U R' F' ";
        return true;
    }

    return false;
}

bool CFOP::twoColorEqual(const Color& color1, const Color& color2, const Color& color3)
{
    return color1 == color3
        && color1 != color2;
}

bool CFOP::threeColorEqual(const Color& color1, const Color& color2, const Color& color3)
{
    return color1 == color2
        && color1 == color3;
}

bool CFOP::threeColorNotEqual(const Color& color1, const Color& color2, const Color& color3)
{
    return color1 != color2
        && color1 != color3;
}

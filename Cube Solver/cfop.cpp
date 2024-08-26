#include "cfop.h"

CFOP::CFOP() : ColorDetection()
{
	this->run();

    // Cross
    crossData = "";
    crossArray = std::vector<int>(8);
    crossDepth = crossStep = 0;
    crossFinish = false;
    mpCrossMove = {
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
        {18, "B2"}
    };
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
    for (int i = 1; i <= 18; i++) { // There are 18 possible moves to check
        turn(i); // Simulate making one move (based on the index 'i')
        crossArray[crossStep] = i; // Store the move index in the crossArray
        if (isCrossFinish()) { // Check if the cross is complete
            crossFinish = true;
            crossData = getCrossString(crossArray); // Convert move indices to string 'crossData'
        }
        else if (crossStep < crossDepth) { // If not yet reached the allowed depth
            crossStep++; // Go one level deeper
            searchCrossSolution(); // Recursively try more moves
        }

        // If cross isn't finished, undo the move and backtrack
        if (!crossFinish) {
            if (i > 12) {
                turn(i); // For moves 13-18, undo by repeating the move
            }
            else if (i < 7) {
                turn(i + 6); // For moves 1-6, undo by performing the opposite move
            }
            else {
                turn(i - 6); // For moves 7-12, undo by performing the opposite move
            }

            // When reaching the end of the loop, reset this step and backtrack
            if (i == 18) {
                crossArray[crossStep] = 0;
                crossStep = crossStep > 0 ? crossStep - 1 : 0;
            }
        }
        else {
            break; // Stop once the cross is solved
        }
    }
}

std::string CFOP::getCrossString(const std::vector<int>& crossArray)
{
    std::string tmpCrossData = "";
    for (auto index : crossArray)
    {
        tmpCrossData += mpCrossMove[index];
        tmpCrossData += " ";
    }
    return tmpCrossData;
}
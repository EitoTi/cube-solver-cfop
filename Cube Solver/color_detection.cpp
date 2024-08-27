#include "color_detection.h"

ColorDetection::ColorDetection() : cap(0), previewFrame(800, 640, CV_8UC3, cv::Scalar(255, 255, 255)), solutionFrame(750, 640, CV_8UC3, cv::Scalar(255, 255, 255)) {}

std::map<std::string, std::vector<cv::Scalar>>& ColorDetection::getState()
{
    return state;
}

Rubik& ColorDetection::getCube()
{
    return rubikCube;
}

const cv::Mat& ColorDetection::getPreviewFrame()
{
    return previewFrame;
}

void ColorDetection::visualClockWise(const std::string side)
{
    cv::Scalar tmpColor01;
    cv::Scalar tmpColor02;
    cv::Scalar tmpColor03;

    // Basic face rotations
    if (side == "front")
    {
        tmpColor01 = state["up"][6];
        tmpColor02 = state["up"][7];
        tmpColor03 = state["up"][8];

        state["up"][6] = state["left"][0];
        state["up"][7] = state["left"][3];
        state["up"][8] = state["left"][6];

        state["left"][0] = state["down"][2];
        state["left"][3] = state["down"][1];
        state["left"][6] = state["down"][0];

        state["down"][2] = state["right"][8];
        state["down"][1] = state["right"][5];
        state["down"][0] = state["right"][2];

        state["right"][8] = tmpColor01;
        state["right"][5] = tmpColor02;
        state["right"][2] = tmpColor03;
    }
    else if (side == "down")
    {
        tmpColor01 = state["front"][6];
        tmpColor02 = state["front"][7];
        tmpColor03 = state["front"][8];

        state["front"][6] = state["left"][6];
        state["front"][7] = state["left"][7];
        state["front"][8] = state["left"][8];

        state["left"][6] = state["back"][2];
        state["left"][7] = state["back"][1];
        state["left"][8] = state["back"][0];

        state["back"][2] = state["right"][6];
        state["back"][1] = state["right"][7];
        state["back"][0] = state["right"][8];

        state["right"][6] = tmpColor01;
        state["right"][7] = tmpColor02;
        state["right"][8] = tmpColor03;
    }
    else if (side == "back")
    {
        tmpColor01 = state["up"][0];
        tmpColor02 = state["up"][1];
        tmpColor03 = state["up"][2];

        state["up"][0] = state["right"][6];
        state["up"][1] = state["right"][3];
        state["up"][2] = state["right"][0];

        state["right"][6] = state["down"][8];
        state["right"][3] = state["down"][7];
        state["right"][0] = state["down"][6];

        state["down"][8] = state["left"][2];
        state["down"][7] = state["left"][5];
        state["down"][6] = state["left"][8];

        state["left"][2] = tmpColor01;
        state["left"][5] = tmpColor02;
        state["left"][8] = tmpColor03;
    }
    else if (side == "up")
    {
        tmpColor01 = state["front"][0];
        tmpColor02 = state["front"][1];
        tmpColor03 = state["front"][2];

        state["front"][0] = state["right"][0];
        state["front"][1] = state["right"][1];
        state["front"][2] = state["right"][2];

        state["right"][0] = state["back"][8];
        state["right"][1] = state["back"][7];
        state["right"][2] = state["back"][6];

        state["back"][8] = state["left"][0];
        state["back"][7] = state["left"][1];
        state["back"][6] = state["left"][2];

        state["left"][0] = tmpColor01;
        state["left"][1] = tmpColor02;
        state["left"][2] = tmpColor03;
    }
    else if (side == "right")
    {
        tmpColor01 = state["front"][0];
        tmpColor02 = state["front"][3];
        tmpColor03 = state["front"][6];

        state["front"][0] = state["down"][0];
        state["front"][3] = state["down"][3];
        state["front"][6] = state["down"][6];

        state["down"][0] = state["back"][0];
        state["down"][3] = state["back"][3];
        state["down"][6] = state["back"][6];

        state["back"][0] = state["up"][0];
        state["back"][3] = state["up"][3];
        state["back"][6] = state["up"][6];

        state["up"][0] = tmpColor01;
        state["up"][3] = tmpColor02;
        state["up"][6] = tmpColor03;
    }
    else if (side == "left")
    {
        tmpColor01 = state["front"][2];
        tmpColor02 = state["front"][5];
        tmpColor03 = state["front"][8];

        state["front"][2] = state["up"][2];
        state["front"][5] = state["up"][5];
        state["front"][8] = state["up"][8];

        state["up"][2] = state["back"][2];
        state["up"][5] = state["back"][5];
        state["up"][8] = state["back"][8];

        state["back"][2] = state["down"][2];
        state["back"][5] = state["down"][5];
        state["back"][8] = state["down"][8];

        state["down"][2] = tmpColor01;
        state["down"][5] = tmpColor02;
        state["down"][8] = tmpColor03;
    }
    else if (side == "M")
    {
        tmpColor01 = state["up"][1];
        tmpColor02 = state["up"][4];
        tmpColor03 = state["up"][7];

        state["up"][1] = state["back"][1];
        state["up"][4] = state["back"][4];
        state["up"][7] = state["back"][7];

        state["back"][1] = state["down"][1];
        state["back"][4] = state["down"][4];
        state["back"][7] = state["down"][7];

        state["down"][1] = state["front"][1];
        state["down"][4] = state["front"][4];
        state["down"][7] = state["front"][7];

        state["front"][1] = tmpColor01;
        state["front"][4] = tmpColor02;
        state["front"][7] = tmpColor03;
    }
    else if (side == "E")
    {
        tmpColor01 = state["front"][3];
        tmpColor02 = state["front"][4];
        tmpColor03 = state["front"][5];

        state["front"][3] = state["left"][3];
        state["front"][4] = state["left"][4];
        state["front"][5] = state["left"][5];

        state["left"][3] = state["back"][5];
        state["left"][4] = state["back"][4];
        state["left"][5] = state["back"][3];

        state["back"][5] = state["right"][3];
        state["back"][4] = state["right"][4];
        state["back"][3] = state["right"][5];

        state["right"][3] = tmpColor01;
        state["right"][4] = tmpColor02;
        state["right"][5] = tmpColor03;
    }
    else if (side == "S")
    {
        tmpColor01 = state["up"][3];
        tmpColor02 = state["up"][4];
        tmpColor03 = state["up"][5];

        state["up"][3] = state["left"][1];
        state["up"][4] = state["left"][4];
        state["up"][5] = state["left"][7];

        state["left"][7] = state["down"][3];
        state["left"][4] = state["down"][4];
        state["left"][1] = state["down"][5];

        state["down"][3] = state["right"][1];
        state["down"][4] = state["right"][4];
        state["down"][5] = state["right"][7];

        state["right"][1] = tmpColor03;
        state["right"][4] = tmpColor02;
        state["right"][7] = tmpColor01;
    }
    else if (side == "u")
    {
        visualClockWise("up");
        visualCounterClockWise("E");
    }
    else if (side == "f")
    {
        visualClockWise("front");
        visualClockWise("S");
    }
    else if (side == "d")
    {
        visualClockWise("down");
        visualClockWise("E");
    }
    else if (side == "b")
    {
        visualClockWise("back");
        visualCounterClockWise("S");
    }
    else if (side == "r")
    {
        visualClockWise("right");
        visualCounterClockWise("M");
    }
    else if (side == "l")
    {
        visualClockWise("left");
        visualClockWise("M");
    }
    else if (side == "x")
    {
        visualClockWise("r");
        visualCounterClockWise("left");
    }
    else if (side == "y")
    {
        visualClockWise("up");
        visualCounterClockWise("d");
    }
    else if (side == "z")
    {
        visualClockWise("f");
        visualCounterClockWise("back");
    }


    // Rotate main face clockwise
    if (side == "up" || side == "front" || side == "down" || side == "back" || side == "right" || side == "left")
    {
        tmpColor01 = state[side][0];
        tmpColor02 = state[side][1];
        state[side][0] = state[side][2];
        state[side][1] = state[side][5];
        state[side][2] = state[side][8];
        state[side][5] = state[side][7];
        state[side][8] = state[side][6];
        state[side][7] = state[side][3];
        state[side][6] = tmpColor01;
        state[side][3] = tmpColor02;
    }
}

void ColorDetection::visualCounterClockWise(const std::string side)
{
    cv::Scalar tmpColor01;
    cv::Scalar tmpColor02;
    cv::Scalar tmpColor03;

    // Rotate all adjacent edges counter-clockwise
    if (side == "front")
    {
        tmpColor01 = state["up"][6];
        tmpColor02 = state["up"][7];
        tmpColor03 = state["up"][8];

        state["up"][6] = state["right"][8];
        state["up"][7] = state["right"][5];
        state["up"][8] = state["right"][2];

        state["right"][2] = state["down"][0];
        state["right"][5] = state["down"][1];
        state["right"][8] = state["down"][2];

        state["down"][2] = state["left"][0];
        state["down"][1] = state["left"][3];
        state["down"][0] = state["left"][6];

        state["left"][0] = tmpColor01;
        state["left"][3] = tmpColor02;
        state["left"][6] = tmpColor03;
    }
    else if (side == "down")
    {
        tmpColor01 = state["front"][6];
        tmpColor02 = state["front"][7];
        tmpColor03 = state["front"][8];

        state["front"][6] = state["right"][6];
        state["front"][7] = state["right"][7];
        state["front"][8] = state["right"][8];

        state["right"][6] = state["back"][2];
        state["right"][7] = state["back"][1];
        state["right"][8] = state["back"][0];

        state["back"][2] = state["left"][6];
        state["back"][1] = state["left"][7];
        state["back"][0] = state["left"][8];

        state["left"][6] = tmpColor01;
        state["left"][7] = tmpColor02;
        state["left"][8] = tmpColor03;
    }
    else if (side == "back")
    {
        tmpColor01 = state["up"][0];
        tmpColor02 = state["up"][1];
        tmpColor03 = state["up"][2];

        state["up"][0] = state["left"][2];
        state["up"][1] = state["left"][5];
        state["up"][2] = state["left"][8];

        state["left"][2] = state["down"][8];
        state["left"][5] = state["down"][7];
        state["left"][8] = state["down"][6];

        state["down"][8] = state["right"][6];
        state["down"][7] = state["right"][3];
        state["down"][6] = state["right"][0];

        state["right"][6] = tmpColor01;
        state["right"][3] = tmpColor02;
        state["right"][0] = tmpColor03;
    }
    else if (side == "up")
    {
        tmpColor01 = state["front"][0];
        tmpColor02 = state["front"][1];
        tmpColor03 = state["front"][2];

        state["front"][0] = state["left"][0];
        state["front"][1] = state["left"][1];
        state["front"][2] = state["left"][2];

        state["left"][0] = state["back"][8];
        state["left"][1] = state["back"][7];
        state["left"][2] = state["back"][6];

        state["back"][8] = state["right"][0];
        state["back"][7] = state["right"][1];
        state["back"][6] = state["right"][2];

        state["right"][0] = tmpColor01;
        state["right"][1] = tmpColor02;
        state["right"][2] = tmpColor03;
    }
    else if (side == "right")
    {
        tmpColor01 = state["up"][0];
        tmpColor02 = state["up"][3];
        tmpColor03 = state["up"][6];

        state["up"][0] = state["back"][0];
        state["up"][3] = state["back"][3];
        state["up"][6] = state["back"][6];

        state["back"][0] = state["down"][0];
        state["back"][3] = state["down"][3];
        state["back"][6] = state["down"][6];

        state["down"][0] = state["front"][0];
        state["down"][3] = state["front"][3];
        state["down"][6] = state["front"][6];

        state["front"][0] = tmpColor01;
        state["front"][3] = tmpColor02;
        state["front"][6] = tmpColor03;
    }
    else if (side == "left")
    {
        tmpColor01 = state["front"][2];
        tmpColor02 = state["front"][5];
        tmpColor03 = state["front"][8];

        state["front"][2] = state["down"][2];
        state["front"][5] = state["down"][5];
        state["front"][8] = state["down"][8];

        state["down"][2] = state["back"][2];
        state["down"][5] = state["back"][5];
        state["down"][8] = state["back"][8];

        state["back"][2] = state["up"][2];
        state["back"][5] = state["up"][5];
        state["back"][8] = state["up"][8];

        state["up"][2] = tmpColor01;
        state["up"][5] = tmpColor02;
        state["up"][8] = tmpColor03;
    }
    else if (side == "M")
    {
        tmpColor01 = state["up"][1];
        tmpColor02 = state["up"][4];
        tmpColor03 = state["up"][7];

        state["up"][1] = state["front"][1];
        state["up"][4] = state["front"][4];
        state["up"][7] = state["front"][7];

        state["front"][1] = state["down"][1];
        state["front"][4] = state["down"][4];
        state["front"][7] = state["down"][7];

        state["down"][1] = state["back"][1];
        state["down"][4] = state["back"][4];
        state["down"][7] = state["back"][7];

        state["back"][1] = tmpColor01;
        state["back"][4] = tmpColor02;
        state["back"][7] = tmpColor03;
    }
    else if (side == "E")
    {
        tmpColor01 = state["front"][3];
        tmpColor02 = state["front"][4];
        tmpColor03 = state["front"][5];

        state["front"][3] = state["right"][3];
        state["front"][4] = state["right"][4];
        state["front"][5] = state["right"][5];

        state["right"][3] = state["back"][5];
        state["right"][4] = state["back"][4];
        state["right"][5] = state["back"][3];

        state["back"][5] = state["left"][3];
        state["back"][4] = state["left"][4];
        state["back"][3] = state["left"][5];

        state["left"][3] = tmpColor01;
        state["left"][4] = tmpColor02;
        state["left"][5] = tmpColor03;
    }
    else if (side == "S")
    {
        tmpColor01 = state["up"][3];
        tmpColor02 = state["up"][4];
        tmpColor03 = state["up"][5];

        state["up"][3] = state["right"][7];
        state["up"][4] = state["right"][4];
        state["up"][5] = state["right"][1];

        state["right"][7] = state["down"][5];
        state["right"][4] = state["down"][4];
        state["right"][1] = state["down"][3];

        state["down"][5] = state["left"][1];
        state["down"][4] = state["left"][4];
        state["down"][3] = state["left"][7];

        state["left"][1] = tmpColor01;
        state["left"][4] = tmpColor02;
        state["left"][7] = tmpColor03;
    }
    else if (side == "u")
    {
        visualCounterClockWise("up");
        visualClockWise("E");
    }
    else if (side == "f")
    {
        visualCounterClockWise("front");
        visualCounterClockWise("S");
    }
    else if (side == "d")
    {
        visualCounterClockWise("down");
        visualCounterClockWise("E");
    }
    else if (side == "b")
    {
        visualCounterClockWise("back");
        visualClockWise("S");
    }
    else if (side == "r")
    {
        visualCounterClockWise("right");
        visualClockWise("M");
    }
    else if (side == "l")
    {
        visualCounterClockWise("left");
        visualCounterClockWise("M");
    }
    else if (side == "x")
    {
        visualCounterClockWise("r");
        visualClockWise("left");
    }
    else if (side == "y")
    {
        visualClockWise("d");
        visualCounterClockWise("up");
    }
    else if (side == "z")
    {
        visualCounterClockWise("f");
        visualClockWise("back");
    }


    // Rotate main face counter-clockwise
    if (side == "up" || side == "front" || side == "down" || side == "back" || side == "right" || side == "left")
    {
        tmpColor01 = state[side][0];
        tmpColor02 = state[side][1];
        state[side][0] = state[side][6];
        state[side][1] = state[side][3];
        state[side][6] = state[side][8];
        state[side][3] = state[side][7];
        state[side][8] = state[side][2];
        state[side][7] = state[side][5];
        state[side][2] = tmpColor01;
        state[side][5] = tmpColor02;
    }
}

std::string ColorDetection::colorDetect(int h, int s, int v)
{
    if ((h > 30 && h < 40) && (s > 150 && s < 180) && (v > 185 && v < 255))
        return "yellow";
    else if ((h >= 53 && h <= 85) && (s >= 100 && s <= 255) && (v >= 100 && v <= 255))
        return "green";
    else if ((h >= 85 && h <= 130) && (s >= 100 && s <= 255) && (v >= 100 && v <= 255))
        return "blue";
    else if (h <= 6 && s > 5)
        return "red";
    else if ((h >= 10 && h < 25) && (s >= 150 && s <= 255) && (v >= 150 && v <= 255))
        return "orange";
    else if ((s >= 0 && s <= 20) && (v >= 200 && v <= 255))
        return "white";
    return "white";
}

void ColorDetection::drawSticker(cv::Mat& img, const std::vector<std::vector<std::pair<int, int>>>& sticker)
{
    for (const auto& row : sticker)
        for (const auto& pairs : row)
        {
            int x = pairs.first;
            int y = pairs.second;
            cv::Rect roi(cv::Point(x, y), cv::Size(30, 30));
            rectangle(img, roi, cv::Scalar(255, 255, 255), 2);
        }
}

void ColorDetection::drawPreviewSticker(cv::Mat& img, const std::vector<std::vector<std::pair<int, int>>> faceName[], const int& faceNum)
{
    std::vector<std::string> faceNotation = { "U", "F", "D", "B", "R", "L" };
    int faceNotationIndex = 0;
    for (int i = 0; i < faceNum; ++i)
        for (int row = 0; row < faceName[i].size(); ++row)
            for (int col = 0; col < faceName[i][row].size(); ++col)
            {
                std::pair<int, int> pairs = faceName[i][row][col];
                int x = pairs.first;
                int y = pairs.second;
                cv::Rect roi(cv::Point(x, y), cv::Size(40, 40));
                rectangle(img, roi, cv::Scalar(0, 0, 0), 2);

                if (row == 1 && col == 1)
                {
                    // Offset for text positioning
                    int baseline = 0;
                    cv::Size textSize = cv::getTextSize(faceNotation[faceNotationIndex], cv::FONT_HERSHEY_SIMPLEX, 1, 2, &baseline);
                    int textX = x + 20 - textSize.width / 2;   // Center horizontally
                    int textY = y + 20 + textSize.height / 2;  // Center vertically

                    putText(img, faceNotation[faceNotationIndex++], cv::Point(textX, textY), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
                }
            }
}

void ColorDetection::fillSticker(cv::Mat& img, const std::vector<std::vector<std::pair<int, int>>>& faceName, int faceIndex, const std::vector<cv::Scalar>& cubiesColor)
{
    std::vector<std::string> faceNotation = { "U", "F", "D", "B", "R", "L" };
    int cubieIndex = 0;

    for (int row = 0; row < faceName.size(); ++row)
        for (int col = 0; col < faceName[row].size(); ++col)
        {
            if (cubieIndex < cubiesColor.size())
            {
                std::pair<int, int> pairs = faceName[row][col];
                int x = pairs.first;
                int y = pairs.second;
                cv::Rect roi(cv::Point(x, y), cv::Size(40, 40));

                // Draw filled rectangle
                rectangle(img, roi, cubiesColor[cubieIndex], cv::FILLED);

                // Draw border around the rectangle
                rectangle(img, roi, cv::Scalar(0, 0, 0), 2);

                // Draw face notation in the center square
                if (row == 1 && col == 1)
                {
                    int baseline = 0;
                    cv::Size textSize = cv::getTextSize(faceNotation[faceIndex], cv::FONT_HERSHEY_SIMPLEX, 1, 2, &baseline);
                    int textX = x + 20 - textSize.width / 2;   // Center horizontally
                    int textY = y + 20 + textSize.height / 2;  // Center vertically
                    putText(img, faceNotation[faceIndex], cv::Point(textX, textY), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
                }
                cubieIndex++;
            }
        }
}

void ColorDetection::fillSolutionSticker(cv::Mat& img, std::map<std::string, std::vector<std::vector<std::pair<int, int>>>> faceCoordinates, std::map<std::string, std::vector<cv::Scalar>> state)
{
    for (const auto& cubeState : state)
    {
        const std::string& side = cubeState.first;
        const std::vector<cv::Scalar> colors = cubeState.second;
        const std::vector<std::vector<std::pair<int, int>>> stickerCoordinate = faceCoordinates[side];

        int num = 0;
        for (const auto& row : stickerCoordinate)
            for (const auto& coord : row)
            {
                int x = coord.first;
                int y = coord.second;

                rectangle(img, cv::Point(x, y), cv::Point(x + 40, y + 40), colors[num], cv::FILLED);
                num++;
            }
    }
}

Color ColorDetection::mapScalarToColor(const cv::Scalar& color)
{
    if (color == cv::Scalar(0, 255, 255)) return Yellow;
    if (color == cv::Scalar(255, 0, 0)) return Blue;
    if (color == cv::Scalar(0, 0, 255)) return Red;
    if (color == cv::Scalar(0, 255, 0)) return Green;
    if (color == cv::Scalar(0, 128, 255)) return Orange;
    if (color == cv::Scalar(255, 255, 255)) return White;
    return White; // default to White if no match
}

void ColorDetection::updateRubikCube(Rubik& rubikCube, const std::vector<cv::Scalar> faceColors[], int currentFace)
{
    for (int i = 0; i < currentFace; ++i)
    {
        Face* face = nullptr;

        switch (i) {
        case 0: face = &rubikCube.getUpFace(); break;
        case 1: face = &rubikCube.getFrontFace(); break;
        case 2: face = &rubikCube.getDownFace(); break;
        case 3: face = &rubikCube.getBackFace(); break;
        case 4: face = &rubikCube.getRightFace(); break;
        case 5: face = &rubikCube.getLeftFace(); break;
        }

        if (face != nullptr)
        {
            face->setCubieOne(mapScalarToColor(faceColors[i][2]));
            face->setCubieTwo(mapScalarToColor(faceColors[i][1]));
            face->setCubieThree(mapScalarToColor(faceColors[i][0]));
            face->setCubieFour(mapScalarToColor(faceColors[i][5]));
            face->setCubieFive(mapScalarToColor(faceColors[i][4]));
            face->setCubieSix(mapScalarToColor(faceColors[i][3]));
            face->setCubieSeven(mapScalarToColor(faceColors[i][8]));
            face->setCubieEight(mapScalarToColor(faceColors[i][7]));
            face->setCubieNine(mapScalarToColor(faceColors[i][6]));
        }
    }
}

void ColorDetection::run()
{
    while (true)
    {
        cap.read(img);
        flip(img, imgFlip, 1);

        drawSticker(imgFlip, stickerPosition);
        drawSticker(imgFlip, stickerCapture);

        cvtColor(imgFlip, imgHSV, cv::COLOR_BGR2HSV);

        std::vector<std::vector<int>> hsv;

        for (const auto& row : stickerPosition)
            for (const auto& pairs : row)
            {
                int x = pairs.first + 10;
                int y = pairs.second + 10;

                // Get h, s, v
                cv::Vec3b hsvPixel = imgHSV.at<cv::Vec3b>(y, x);
                hsv.push_back({ hsvPixel[0], hsvPixel[1], hsvPixel[2] });
            }

        // Debug print to verify HSV values
        /*for (const auto& h : hsv)
        {
            std::cout << "H: " << h[0] << ", S: " << h[1] << ", V: " << h[2] << std::endl;
        }*/

        std::vector<cv::Scalar> cubiesColor;
        int tmp = 0;
        for (const auto& row : stickerCapture)
            for (const auto& pairs : row) {
                std::string color = colorDetect(hsv[tmp][0], hsv[tmp][1], hsv[tmp][2]);
                int x = pairs.first;
                int y = pairs.second;
                cv::Rect roi(cv::Point(x, y), cv::Size(30, 30));
                rectangle(imgFlip, roi, getColor[color], cv::FILLED);
                cubiesColor.push_back(getColor[color]); // color of 9 cubies of a face
                tmp++;
            }

        // Map face indices to state keys
        std::vector<std::string> faceKeys = { "up", "front", "down", "back", "right", "left" };

        // Press 's' to save current face color and update the state map
        char key = cv::waitKey(1);
        if (key == 's' && currentFace < 6)
        {
            faceColor[currentFace] = cubiesColor; // save detected colors for the face

            // Update the state map
            std::vector<cv::Scalar>& currentFaceColors = faceColor[currentFace];
            for (int i = 0; i < 9; ++i) {
                state[faceKeys[currentFace]][i] = currentFaceColors[i];
            }

            std::cout << "Saved colors for face " << currentFace + 1 << std::endl;
            currentFace++;
        }

        // Press 'r' to rescan the current face and update the state map
        if (key == 'r' && currentFace > 0)
        {
            currentFace--;
            faceColor[currentFace] = cubiesColor; // update the colors for the face

            // Update the state map again
            std::vector<cv::Scalar>& currentFaceColors = faceColor[currentFace];
            for (int i = 0; i < 9; ++i) {
                state[faceKeys[currentFace]][i] = currentFaceColors[i];
            }

            std::cout << "Rescanned and updated colors for face " << currentFace + 1 << std::endl;
        }

        // Test preview frame
        const int faceNum = 6;
        const std::vector<std::vector<std::pair<int, int>>> faceName[faceNum] = { upFaceCoordinates, frontFaceCoordinates, downFaceCoordinates, backFaceCoordinates, rightFaceCoordinates, leftFaceCoordinates };
        drawPreviewSticker(previewFrame, faceName, faceNum);

        // Test fill stickers on preview frame
        for (int i = 0; i < currentFace; ++i)
            fillSticker(previewFrame, faceName[i], i, faceColor[i]);

        // Update the Rubik object with the detected colors
        updateRubikCube(rubikCube, faceColor, currentFace);

        cv::imshow("frame", imgFlip);
        cv::imshow("Preview frame", previewFrame);

        // Press 'q' to exit loop and close windows
        if (key == 'q')
        {
            /*cv::destroyWindow("frame");
            cv::destroyWindow("Preview frame");*/
            break;
        }
    }
}

void ColorDetection::process(std::string solutionData)
{
    std::map<std::string, std::function<void()>> performMove;

    // F, F', F2
    performMove["F"] = [&]() { visualClockWise("front"); };
    performMove["F'"] = [&]() { visualCounterClockWise("front"); };
    performMove["F2"] = [&]() { visualClockWise("front"); visualClockWise("front"); };

    // D, D', D2
    performMove["D"] = [&]() { visualClockWise("down"); };
    performMove["D'"] = [&]() { visualCounterClockWise("down"); };
    performMove["D2"] = [&]() { visualClockWise("down"); visualClockWise("down"); };

    // B, B', B2
    performMove["B"] = [&]() { visualClockWise("back"); };
    performMove["B'"] = [&]() { visualCounterClockWise("back"); };
    performMove["B2"] = [&]() { visualClockWise("back"); visualClockWise("back"); };

    // U, U', U2
    performMove["U"] = [&]() { visualClockWise("up"); };
    performMove["U'"] = [&]() { visualCounterClockWise("up"); };
    performMove["U2"] = [&]() { visualClockWise("up"); visualClockWise("up"); };

    // R, R', R2
    performMove["R"] = [&]() { visualClockWise("right"); };
    performMove["R'"] = [&]() { visualCounterClockWise("right"); };
    performMove["R2"] = [&]() { visualClockWise("right"); visualClockWise("right"); };

    // L, L', L2
    performMove["L"] = [&]() { visualClockWise("left"); };
    performMove["L'"] = [&]() { visualCounterClockWise("left"); };
    performMove["L2"] = [&]() { visualClockWise("left"); visualClockWise("left"); };

    // M, M', M2
    performMove["M"] = [&]() { visualClockWise("M"); };
    performMove["M'"] = [&]() { visualCounterClockWise("M"); };
    performMove["M2"] = [&]() { visualClockWise("M"); visualClockWise("M"); };

    // E, E', E2
    performMove["E"] = [&]() { visualClockWise("E"); };
    performMove["E'"] = [&]() { visualCounterClockWise("E"); };
    performMove["E2"] = [&]() { visualClockWise("E"); visualClockWise("E"); };

    // S, S', S2
    performMove["S"] = [&]() { visualClockWise("S"); };
    performMove["S'"] = [&]() { visualCounterClockWise("S"); };
    performMove["S2"] = [&]() { visualClockWise("S"); visualClockWise("S"); };

    // u, u', u2
    performMove["u"] = [&]() { visualClockWise("u"); };
    performMove["u'"] = [&]() { visualCounterClockWise("u"); };
    performMove["u2"] = [&]() { visualClockWise("u"); visualClockWise("u"); };

    // f, f', f2
    performMove["f"] = [&]() { visualClockWise("f"); };
    performMove["f'"] = [&]() { visualCounterClockWise("f"); };
    performMove["f2"] = [&]() { visualClockWise("f"); visualClockWise("f"); };

    // d, d', d2
    performMove["d"] = [&]() { visualClockWise("d"); };
    performMove["d'"] = [&]() { visualCounterClockWise("d"); };
    performMove["d2"] = [&]() { visualClockWise("d"); visualClockWise("d"); };

    // b, b', b2
    performMove["b"] = [&]() { visualClockWise("b"); };
    performMove["b'"] = [&]() { visualCounterClockWise("b"); };
    performMove["b2"] = [&]() { visualClockWise("b"); visualClockWise("b"); };

    // r, r', r2
    performMove["r"] = [&]() { visualClockWise("r"); };
    performMove["r'"] = [&]() { visualCounterClockWise("r"); };
    performMove["r2"] = [&]() { visualClockWise("r"); visualClockWise("r"); };

    // l, l', l2
    performMove["l"] = [&]() { visualClockWise("l"); };
    performMove["l'"] = [&]() { visualCounterClockWise("l"); };
    performMove["l2"] = [&]() { visualClockWise("l"); visualClockWise("l"); };

    // x, x', x2
    performMove["x"] = [&]() { visualClockWise("x"); };
    performMove["x'"] = [&]() { visualCounterClockWise("x"); };
    performMove["x2"] = [&]() { visualClockWise("x"); visualClockWise("x"); };

    // y, y', y2
    performMove["y"] = [&]() { visualClockWise("y"); };
    performMove["y'"] = [&]() { visualCounterClockWise("y"); };
    performMove["y2"] = [&]() { visualClockWise("y"); visualClockWise("y"); };

    // z, z', z2
    performMove["z"] = [&]() { visualClockWise("z"); };
    performMove["z'"] = [&]() { visualCounterClockWise("z"); };
    performMove["z2"] = [&]() { visualClockWise("z"); visualClockWise("z"); };

    std::stringstream ss(solutionData);
    std::string move;

    const int faceNum = 6;
    const std::vector<std::vector<std::pair<int, int>>> faceName[faceNum] = { upFaceCoordinates, frontFaceCoordinates, downFaceCoordinates, backFaceCoordinates, rightFaceCoordinates, leftFaceCoordinates };

    // Initial rendering
    fillSolutionSticker(solutionFrame, faceCoordinates, state);
    drawPreviewSticker(solutionFrame, faceName, faceNum);
    imshow("solution", solutionFrame);

    // Wait for a key press to perform the move
    cv::waitKey(0);

    std::vector<cv::Mat> solution;

    while (ss >> move) {
        // Validate the move
        if (performMove.find(move) != performMove.end()) {

            // Execute the move
            performMove[move]();

            // Update the stickers after the move
            fillSolutionSticker(solutionFrame, faceCoordinates, state);
            drawPreviewSticker(solutionFrame, faceName, faceNum);

            // Show the updated frame
            imshow("solution", solutionFrame);

            // Save the current frame in the solution vector for debug (optional)
            solution.push_back(solutionFrame.clone());

            // Wait for another key press to close or proceed
            cv::waitKey(0);
        }
        else {
            std::cerr << "Invalid move: " << move << std::endl;
        }
    }
}
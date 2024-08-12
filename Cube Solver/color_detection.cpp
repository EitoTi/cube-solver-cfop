#include "color_detection.h"

ColorDetection::ColorDetection() : cap(0), previewFrame(750, 640, CV_8UC3, cv::Scalar(255, 255, 255)) {}

Rubik& ColorDetection::getCube()
{
    return rubikCube;
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

        // Press 's' to save current face color
        char key = cv::waitKey(1);
        if (key == 's' && currentFace < 6)
        {
            faceColor[currentFace++] = cubiesColor; // each face color contains 9 cubies
            std::cout << "Saved colors for face " << currentFace << std::endl;
        }

        // Test preview frame
        const int faceNum = 6;
        const std::vector<std::vector<std::pair<int, int>>> faceName[faceNum] = { upFace, frontFace, downFace, backFace, rightFace, leftFace };
        drawPreviewSticker(previewFrame, faceName, faceNum);

        // Test fill stickers on preview frame
        for (int i = 0; i < currentFace; ++i)
            fillSticker(previewFrame, faceName[i], i, faceColor[i]);

        // Update the Rubik object with the detected colors
        updateRubikCube(rubikCube, faceColor, currentFace);

        cv::imshow("frame", imgFlip);
        cv::imshow("Preview frame", previewFrame);

        // Press 'q' to exit loop
        if (key == 'q')
            break;
    }
}
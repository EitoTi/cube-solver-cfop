#pragma once
#ifndef _COLOR_DETECTION
#include "library.h"
#include "rubik.h"

class ColorDetection
{
private:
    Rubik rubikCube; // Rubik's Cube object

    cv::VideoCapture cap;
    cv::Mat img, imgFlip, imgHSV;

    // frame to show output of color detection
    cv::Mat previewFrame, solutionFrame;

    // Storage for the colors of each face
    std::vector<cv::Scalar> faceColor[6];
    int currentFace = 0;

    /////////////////////////////////// Face Coordinates Map ///////////////////////////////////

    std::map<std::string, std::vector<std::vector<std::pair<int, int>>>> faceCoordinates = {
        { "left", {
            {{50, 280}, {94, 280}, {138, 280}},
            {{50, 324}, {94, 324}, {138, 324}},
            {{50, 368}, {94, 368}, {138, 368}}
        }},
        { "front", {
            {{188, 280}, {232, 280}, {276, 280}},
            {{188, 324}, {232, 324}, {276, 324}},
            {{188, 368}, {232, 368}, {276, 368}}
        }},
        { "right", {
            {{326, 280}, {370, 280}, {414, 280}},
            {{326, 324}, {370, 324}, {414, 324}},
            {{326, 368}, {370, 368}, {414, 368}}
        }},
        { "up", {
            {{188, 128}, {232, 128}, {276, 128}},
            {{188, 172}, {232, 172}, {276, 172}},
            {{188, 216}, {232, 216}, {276, 216}}
        }},
        { "down", {
            {{188, 434}, {232, 434}, {276, 434}},
            {{188, 478}, {232, 478}, {276, 478}},
            {{188, 522}, {232, 522}, {276, 522}}
        }},
        { "back", {
            {{464, 280}, {508, 280}, {552, 280}},
            {{464, 324}, {508, 324}, {552, 324}},
            {{464, 368}, {508, 368}, {552, 368}}
        }}
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////// Coordinates of 6 faces of rubik's cube /////////////////////////////////

    std::vector<std::vector<std::pair<int, int>>> leftFaceCoordinates = {
        {{50, 280}, {94, 280}, {138, 280}},
        {{50, 324}, {94, 324}, {138, 324}},
        {{50, 368}, {94, 368}, {138, 368}}
    };

    std::vector<std::vector<std::pair<int, int>>> frontFaceCoordinates = {
        {{188, 280}, {232, 280}, {276, 280}},
        {{188, 324}, {232, 324}, {276, 324}},
        {{188, 368}, {232, 368}, {276, 368}}
    };

    std::vector<std::vector<std::pair<int, int>>> rightFaceCoordinates = {
        {{326, 280}, {370, 280}, {414, 280}},
        {{326, 324}, {370, 324}, {414, 324}},
        {{326, 368}, {370, 368}, {414, 368}}
    };

    std::vector<std::vector<std::pair<int, int>>> upFaceCoordinates = {
        {{188, 128}, {232, 128}, {276, 128}},
        {{188, 172}, {232, 172}, {276, 172}},
        {{188, 216}, {232, 216}, {276, 216}}
    };

    std::vector<std::vector<std::pair<int, int>>> downFaceCoordinates = {
        {{188, 434}, {232, 434}, {276, 434}},
        {{188, 478}, {232, 478}, {276, 478}},
        {{188, 522}, {232, 522}, {276, 522}}
    };

    std::vector<std::vector<std::pair<int, int>>> backFaceCoordinates = {
        {{464, 280}, {508, 280}, {552, 280}},
        {{464, 324}, {508, 324}, {552, 324}},
        {{464, 368}, {508, 368}, {552, 368}}
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////


    // State used for future solving graphical demonstration
    // Initialize the state with default white color
    std::map<std::string, std::vector<cv::Scalar>> state = {
        {"up", {cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}}},

        {"front", {cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                  cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                  cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}}},

        {"down", {cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                 cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                 cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}}},

        {"back", {cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                 cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                 cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}}},

        {"right", {cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                  cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                  cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}}},

        {"left", {cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                 cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255},
                 cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}, cv::Scalar{255, 255, 255}}}
    };

    // Color map
    std::map<std::string, cv::Scalar> getColor = {
        {"red", cv::Scalar(0, 0, 255)},
        {"orange", cv::Scalar(0, 128, 255)},
        {"blue", cv::Scalar(255, 0, 0)},
        {"green", cv::Scalar(0, 255, 0)},
        {"yellow", cv::Scalar(0, 255, 255)},
        {"white", cv::Scalar(255, 255, 255)}
    };

    // Positions to place cube to capture stickers
    std::vector<std::vector<std::pair<int, int>>> stickerPosition = {
        {{320, 160}, {420, 160}, {520, 160}},
        {{320, 260}, {420, 260}, {520, 260}},
        {{320, 360}, {420, 360}, {520, 360}}
    };

    // Show the result colors (top-left frame)
    std::vector<std::vector<std::pair<int, int>>> stickerCapture = {
        {{20, 20}, {54, 20}, {88, 20}},
        {{20, 54}, {54, 54}, {88, 54}},
        {{20, 88}, {54, 88}, {88, 88}}
    };

public:
    ColorDetection();

    // Get state after real-time color detection
    std::map<std::string, std::vector<cv::Scalar>>& getState();

    // Get cube scrambled after real-time color detection
    Rubik& getCube();

    // Return a clone to avoid modifying the original preview frame
    const cv::Mat& getPreviewFrame();

    // Graphical representation of cube
    void visualClockWise(const std::string);
    void visualCounterClockWise(const std::string);

    std::string colorDetect(int, int, int);

    void drawSticker(cv::Mat&, const std::vector<std::vector<std::pair<int, int>>>&);

    void drawPreviewSticker(cv::Mat&, const std::vector<std::vector<std::pair<int, int>>>[], const int&);

    // Fill sticker color on preview frame
    void fillSticker(cv::Mat&, const std::vector<std::vector<std::pair<int, int>>>&, int, const std::vector<cv::Scalar>&);

    // Fill sticker color on solution frame
    void fillSolutionSticker(cv::Mat&, std::map<std::string, std::vector<std::vector<std::pair<int, int>>>>, std::map<std::string, std::vector<cv::Scalar>>);

    // Mapping Detected Colors to Enum
    Color mapScalarToColor(const cv::Scalar&);

    // Update real-time color of the rubik's cube
    void updateRubikCube(Rubik&, const std::vector<cv::Scalar>[], int);

    void run();

    // Display and update solution frame after each move
    void process(std::string);
};
#endif // !_COLOR_DETECTION
#include "Utils.hpp"
#include "raylib.h"
#include <cmath>
#include <math.h>

// ################ Math (Trigonometry)

// Returns the angle direction from 2 vectors
float PatternEditor::PointDirection(Vector2 source, Vector2 destination) {

    float radians = atan2(destination.y - source.y, destination.x - source.x);
    float degrees = radians * (180.0f / PI); // -180:180

    return std::fmodf(((degrees * -1.0f) + 360.0f), 360.0f); // convert to 0:359 and return
};

// Return the distance in pixels between 2 vectors
float PatternEditor::PointDistance(Vector2 source, Vector2 destination) {

    return pow(source.x - destination.x, 2.0f) + pow(source.y - destination.y, 2.0f);
};

float PatternEditor::LengthDirX(float length, float angle) {

    return length * cos(angle * (PI / 180.0f));
};

float PatternEditor::LengthDirY(float length, float angle) {

    return (length * sin(angle * (PI / 180.0f))) * -1.0f;
};

// Translate any number to 0-360 (always positive)
float PatternEditor::NormalizeAngle(float angle) {

    angle = std::fmodf(angle, 360.0f);
    if (angle < 0.0f) angle+= 360.0f;

    return angle;
}

// Get the difference between 2 angles
float PatternEditor::AngleDifference(float angle1, float angle2) {

    // limit to 0/360
    angle1 = NormalizeAngle(angle1);
    angle2 = NormalizeAngle(angle2);

    float angleDifference = std::abs(angle1 - angle2);

    if (angleDifference > 180.0f) {

        angleDifference = 360.0f - angleDifference;
        angleDifference *= Sign(angle1 - angle2);
    } else {

        angleDifference *= Sign(angle2 - angle1);
    }

    return angleDifference;
}


// ################ Math (General)

// return -1 for negative numbers, 1 for positive numbers and 0 for 0
float PatternEditor::Sign(float number) {
    return (number > 0) - (number < 0);
}
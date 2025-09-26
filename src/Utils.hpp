#pragma once

#include "raylib.h"

namespace PatternEditor {

    // Math Trigonometry
    float PointDirection(Vector2 source, Vector2 destination);
    float PointDistance(Vector2 source, Vector2 destination);
    float LengthDirX(float length, float angle);
    float LengthDirY(float length, float angle);
    float AngleDifference(float angle1, float angle2);
    float NormalizeAngle(float angle);

    // General Math
    float Sign(float number);
};
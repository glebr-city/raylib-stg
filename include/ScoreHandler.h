//
// Created by g on 14/02/2026.
//

#ifndef RAYLIB_STG_SCOREHANDLER_H
#define RAYLIB_STG_SCOREHANDLER_H
#include <cmath>
#include <string>

#include "raylib.h"
class ScoreHandler {
  private:
  static const Color scoreColour;
  static const Color multiplierColour;
  static std::string scoreStr;
  static u_long currentScore;
  static float currentMultiplier;
  static void setString() {
    scoreStr = std::to_string(currentScore);
    if (scoreStr.length() > 3) {
      for (long i = scoreStr.length() - 3; i > 0; i -= 3) {
        scoreStr.insert(i, ".");
      }
    }
  }
  public:

  static void setMultiplier(const float _multiplier) {
    currentMultiplier = _multiplier;
  }

  static float getMultiplier() {
    return currentMultiplier;
  }

  static void addScore(const int score) {
    currentScore += static_cast<u_long>(score);
    setString();
  }

  static void doPreStep() {
    DrawText(scoreStr.c_str(), 0, 0, 0, scoreColour);
    if (currentMultiplier > 1) {
      std::string tempStr = "x" + std::to_string(static_cast<int>(std::round(currentMultiplier * 100)));
      tempStr.insert(tempStr.length() - 2, ".");
      DrawText(tempStr.c_str(), 0, 8, 0, multiplierColour);
    }
  }
};
#endif //RAYLIB_STG_SCOREHANDLER_H
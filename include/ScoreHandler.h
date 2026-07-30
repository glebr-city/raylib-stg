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
  static std::string scoreStr;
  static u_long currentScore;
  static float currentMultiplier;
  static void setString() {
    scoreStr = std::to_string(currentScore);
    if (scoreStr.length() > 3) {
      for (long i = static_cast<long>(scoreStr.length()) - 3; i > 0; i -= 3) {
        scoreStr.insert(i, ".");
      }
    }
  }
  public:
  static void resetScore() {
    currentMultiplier = 1;
    currentScore = 0;
    setString();
  }
  static std::string getString() {
    return scoreStr;
  }
  static void setMultiplier(const float _multiplier) {
    currentMultiplier = _multiplier;
  }

  static float getMultiplier() {
    return currentMultiplier;
  }

  static void addScore(const u_int score, const bool useMultiplier = true) {
    currentScore += useMultiplier ? static_cast<u_long>(currentMultiplier) * static_cast<u_long>(score) : static_cast<u_long>(score);
    setString();
  }


};
#endif //RAYLIB_STG_SCOREHANDLER_H
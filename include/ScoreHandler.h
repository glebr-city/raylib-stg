//
// Created by g on 14/02/2026.
//

#ifndef RAYLIB_STG_SCOREHANDLER_H
#define RAYLIB_STG_SCOREHANDLER_H
#include <string>

#include "raylib.h"
inline u_long currentScore = 10000000000;
class ScoreHandler {
  private:
  static std::string scoreStr;
  static void setString() {
    scoreStr = std::to_string(currentScore);
    if (scoreStr.length() > 3) {
      for (long i = scoreStr.length() - 3; i > 0; i -= 3) {
        scoreStr.insert(i, ".");
      }
    }
  }
  public:
  static void addScore(const int score) {
    currentScore += score;
    setString();
  }

  static void doPreStep() {
    DrawText(scoreStr.c_str(), 0, 0, 0, WHITE);
  }
};
#endif //RAYLIB_STG_SCOREHANDLER_H
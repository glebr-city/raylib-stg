//
// Created by n on 30/07/2026.
//

#ifndef RAYLIB_STG_RNGHANDLER_H
#define RAYLIB_STG_RNGHANDLER_H
#include <cstdint>
#include <sys/types.h>

#include "InputHandler.h"

static constexpr uint_fast16_t RNG_SEED_MAX = UINT16_MAX;
static constexpr uint_fast16_t RNG_SEED_MAX_HALF = UINT16_MAX / 2;
class RNGHandler
{
private:
  static uint_fast16_t seed; //The current RNG seed;
  public:

  static void InitSeed() //Sets the seed to 0; call when the game starts.
  {
    seed = 0;
  }
  static void StepSeed() //Increments the seed in pseudo-random fashion; call this as often as possible.
  {
    if (InputHandler::CheckInputsDown(INPUT_LEFT))
      seed += 2447;
    if (InputHandler::CheckInputsDown(INPUT_RIGHT))
      seed += 3119;
    if (InputHandler::CheckInputsDown(INPUT_UP))
      seed += 5099;
    if (InputHandler::CheckInputsDown(INPUT_DOWN))
      seed += 7001;
    if (InputHandler::CheckInputsDown(INPUT_FIRE))
      seed += 8513;
    seed += seed % 9463;
  }
  static uint_fast16_t GetSeed() // Returns the current RNG seed (0 to 65535).
  {
    return seed;
  }
};
#endif //RAYLIB_STG_RNGHANDLER_H
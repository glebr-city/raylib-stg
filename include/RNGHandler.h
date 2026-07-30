//
// Created by n on 30/07/2026.
//

#ifndef RAYLIB_STG_RNGHANDLER_H
#define RAYLIB_STG_RNGHANDLER_H
#include <sys/types.h>

class RNGHandler
{
private:
  static u_int seed; //The current RNG seed;
  public:

  static void InitSeed() //Sets the seed to 0; call when the game starts.
  {
    seed = 0;
  }
  static void StepSeed() //Increments the seed in pseudo-random fashion; call this as often as possible.
  {
    seed++;
  }
  static u_int GetSeed() // Returns the current RNG seed (0 to 4294967295).
  {
    return seed;
  }
};
#endif //RAYLIB_STG_RNGHANDLER_H
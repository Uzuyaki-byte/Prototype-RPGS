#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include "common.h"
#include "player.h"
#include "vehicle.h"
#include <stdbool.h>

typedef struct {
  Player players[3];
  int activePlayerIdx;
  Vehicle vehicles[MAX_VEHICLES];
  float cameraAngleH;
  float cameraAngleV;
  float cameraDistance;
} SaveData;

bool SaveGame(const SaveData *data, int slot);
bool LoadGame(SaveData *data, int slot);

#endif

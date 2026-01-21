#include "save_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void EnsureDirectory(const char *path) {
  char tmp[256];
  char *p = NULL;
  size_t len;

  snprintf(tmp, sizeof(tmp), "%s", path);
  len = strlen(tmp);
  if (tmp[len - 1] == '/')
    tmp[len - 1] = 0;
  for (p = tmp + 1; *p; p++) {
    if (*p == '/') {
      *p = 0;
      mkdir(tmp, S_IRWXU);
      *p = '/';
    }
  }
  mkdir(tmp, S_IRWXU);
}

static void GetSaveFilePath(char *buffer, size_t size, int slot) {
  const char *home = getenv("HOME");
  if (home) {
    snprintf(buffer, size, "%s/Documents/Prototype-RPGS", home);
    EnsureDirectory(buffer);
    char filename[32];
    snprintf(filename, sizeof(filename), "/save_slot%d.dat", slot);
    strncat(buffer, filename, size - strlen(buffer) - 1);
  } else {
    snprintf(buffer, size, "save_slot%d.dat", slot);
  }
}

bool SaveGame(const SaveData *data, int slot) {
  char path[512];
  GetSaveFilePath(path, sizeof(path), slot);

  FILE *file = fopen(path, "wb");
  if (!file) {
    TraceLog(LOG_ERROR, "Failed to open save file for writing: %s", path);
    return false;
  }

  size_t written = fwrite(data, sizeof(SaveData), 1, file);
  fclose(file);

  if (written != 1) {
    TraceLog(LOG_ERROR, "Failed to write save data to: %s", path);
    return false;
  }

  TraceLog(LOG_INFO, "Game saved successfully to: %s (Slot %d)", path, slot);
  return true;
}

bool LoadGame(SaveData *data, int slot) {
  char path[512];
  GetSaveFilePath(path, sizeof(path), slot);

  FILE *file = fopen(path, "rb");
  if (!file) {
    TraceLog(LOG_WARNING, "No save file found at: %s (Slot %d)", path, slot);
    return false;
  }

  size_t read = fread(data, sizeof(SaveData), 1, file);
  fclose(file);

  if (read != 1) {
    TraceLog(LOG_ERROR, "Failed to read save data from: %s (Slot %d)", path,
             slot);
    return false;
  }

  TraceLog(LOG_INFO, "Game loaded successfully from: %s (Slot %d)", path, slot);
  return true;
}

#ifndef CONSOLE_H
#define CONSOLE_H

#include "common.h"
#include "player.h"
#include "vehicle.h"

#define MAX_INPUT_CHARS 32

typedef struct {
    bool active;
    char input[MAX_INPUT_CHARS + 1];
    int count;
} CheatConsole;

void InitConsole(CheatConsole *console);
void UpdateConsole(CheatConsole *console, Player *player, Vehicle *vehicles);
void DrawConsole(CheatConsole console);

#endif

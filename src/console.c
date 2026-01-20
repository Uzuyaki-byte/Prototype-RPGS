#include "console.h"
#include <string.h>
#include <ctype.h>

void InitConsole(CheatConsole *console) {
    console->active = false;
    memset(console->input, 0, sizeof(console->input));
    console->count = 0;
}

static void ExecuteCommand(const char *cmd, Player *player, Vehicle *vehicles) {
    char upper[MAX_INPUT_CHARS + 1];
    int i = 0;
    while (cmd[i] && i < MAX_INPUT_CHARS) {
        upper[i] = toupper(cmd[i]);
        i++;
    }
    upper[i] = '\0';

    if (strcmp(upper, "FAST") == 0) {
        player->speed = 60.0f;
    } else if (strcmp(upper, "SLOW") == 0) {
        player->speed = 5.0f;
    } else if (strcmp(upper, "NORMAL") == 0) {
        player->speed = 15.0f;
    } else if (strcmp(upper, "NY") == 0) {
        player->position = (Vector3){ 500, 2, 500 };
    } else if (strcmp(upper, "DHAKA") == 0) {
        player->position = (Vector3){ 1500, 2, 500 };
    } else if (strcmp(upper, "SHENZEN") == 0) {
        player->position = (Vector3){ 2500, 2, 500 };
    } else if (strcmp(upper, "CAR") == 0) {
        for (int j = 0; j < MAX_VEHICLES; j++) {
            if (!vehicles[j].active) {
                vehicles[j].active = true;
                vehicles[j].position = (Vector3){ player->position.x + 10, 2, player->position.z + 10 };
                vehicles[j].speed = 40.0f;
                vehicles[j].size = (Vector3){ 8, 4, 12 };
                vehicles[j].color = BLUE;
                break;
            }
        }
    }
}

void UpdateConsole(CheatConsole *console, Player *player, Vehicle *vehicles) {
    if (IsKeyPressed(KEY_GRAVE)) {
        console->active = !console->active;
        if (console->active) EnableCursor();
        else DisableCursor();
    }

    if (!console->active) return;

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (console->count < MAX_INPUT_CHARS)) {
            console->input[console->count++] = (char)key;
            console->input[console->count] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (console->count > 0) {
            console->count--;
            console->input[console->count] = '\0';
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        ExecuteCommand(console->input, player, vehicles);
        console->count = 0;
        console->input[0] = '\0';
        console->active = false;
        DisableCursor();
    }
}

void DrawConsole(CheatConsole console) {
    if (!console.active) return;

    DrawRectangle(0, 0, GetScreenWidth(), 60, Fade(BLACK, 0.7f));
    DrawRectangleLines(10, 10, GetScreenWidth() - 20, 40, GRAY);
    DrawText("CHEAT CONSOLE:", 20, 20, 20, RAYWHITE);
    DrawText(console.input, 200, 20, 20, YELLOW);
    
    if ((GetTime() - (int)GetTime()) < 0.5) {
        DrawRectangle(200 + MeasureText(console.input, 20), 20, 10, 20, YELLOW);
    }
}

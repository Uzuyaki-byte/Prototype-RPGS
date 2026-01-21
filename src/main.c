#include "city.h"
#include "common.h"
#include "console.h"
#include "metro.h"
#include "player.h"
#include "save_system.h"
#include "vehicle.h"

int main(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetExitKey(KEY_NULL);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sosta Yakuza - Modular Prototype");

  bool cursorLocked = true;
  DisableCursor();

  Player players[3];
  for (int i = 0; i < 3; i++) {
    InitPlayer(&players[i]);
    players[i].position = (Vector3){10.0f * i, 0.0f, 10.0f * i};
    if (i == 1)
      players[i].color = GREEN;
    if (i == 2)
      players[i].color = GOLD;
  }
  int activePlayerIdx = 0;
  bool switchingChar = false;
  int selectedCharIdx = 0;
  int currentSaveSlot = 1;

  float cameraAngleH = 0.0f;
  float cameraAngleV = 20.0f;
  float cameraDistance = 40.0f;

  Camera3D camera = {0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Metro metro = {(Vector3){100, 2, 1000},
                 (Vector3){60, 20, 150},
                 (Vector3){100, 2, 1000},
                 (Vector3){2900, 2, 1000},
                 0.05f,
                 0.0f,
                 true,
                 LIME};

  Vehicle vehicles[MAX_VEHICLES] = {0};

  CheatConsole console;
  InitConsole(&console);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    UpdateConsole(&console, &players[activePlayerIdx], vehicles);

    if (!console.active) {
      if (IsKeyDown(KEY_LEFT_ALT)) {
        if (!switchingChar) {
          switchingChar = true;
          EnableCursor();
          selectedCharIdx = activePlayerIdx;
        }

        Vector2 mousePos = GetMousePosition();
        float centerX = SCREEN_WIDTH / 2.0f;

        for (int i = 0; i < 3; i++) {
          Rectangle r = {centerX - 160 + i * 110, SCREEN_HEIGHT - 100, 100, 80};
          if (CheckCollisionPointRec(mousePos, r))
            selectedCharIdx = i;
        }
      } else {
        if (switchingChar) {
          activePlayerIdx = selectedCharIdx;
          switchingChar = false;
          if (cursorLocked)
            DisableCursor();
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
          cursorLocked = !cursorLocked;
          if (cursorLocked)
            DisableCursor();
          else
            EnableCursor();
        }

        if (cursorLocked) {
          Vector2 delta = GetMouseDelta();
          cameraAngleH -= delta.x * 0.1f;
          cameraAngleV += delta.y * 0.1f;
          if (cameraAngleV > 80.0f)
            cameraAngleV = 80.0f;
          if (cameraAngleV < -10.0f)
            cameraAngleV = -10.0f;
        }

        if (IsKeyPressed(KEY_F)) {
          Player *p = &players[activePlayerIdx];
          if (p->inVehicle) {
            int vIdx = p->vehicleIdx;
            p->inVehicle = false;
            p->position =
                Vector3Add(vehicles[vIdx].position, (Vector3){5, 0, 0});
            p->vehicleIdx = -1;
          } else {
            int nearest = -1;
            float minDist = 15.0f;
            for (int i = 0; i < MAX_VEHICLES; i++) {
              if (vehicles[i].active) {
                float dist = Vector3Distance(p->position, vehicles[i].position);
                if (dist < minDist) {
                  minDist = dist;
                  nearest = i;
                }
              }
            }
            if (nearest != -1) {
              p->inVehicle = true;
              p->vehicleIdx = nearest;
            }
          }
        } // Added this closing brace for KEY_F
        if (IsKeyPressed(KEY_ONE))
          currentSaveSlot = 1;
        if (IsKeyPressed(KEY_TWO))
          currentSaveSlot = 2;
        if (IsKeyPressed(KEY_THREE))
          currentSaveSlot = 3;
        if (IsKeyPressed(KEY_FOUR))
          currentSaveSlot = 4;
        if (IsKeyPressed(KEY_FIVE))
          currentSaveSlot = 5;

        if (IsKeyPressed(KEY_F5)) {
          SaveData data;
          for (int i = 0; i < 3; i++)
            data.players[i] = players[i];
          data.activePlayerIdx = activePlayerIdx;
          for (int i = 0; i < MAX_VEHICLES; i++)
            data.vehicles[i] = vehicles[i];
          data.cameraAngleH = cameraAngleH;
          data.cameraAngleV = cameraAngleV;
          data.cameraDistance = cameraDistance;
          SaveGame(&data, currentSaveSlot);
        }

        if (IsKeyPressed(KEY_F6)) {
          SaveData data;
          if (LoadGame(&data, currentSaveSlot)) {
            for (int i = 0; i < 3; i++)
              players[i] = data.players[i];
            activePlayerIdx = data.activePlayerIdx;
            for (int i = 0; i < MAX_VEHICLES; i++)
              vehicles[i] = data.vehicles[i];
            cameraAngleH = data.cameraAngleH;
            cameraAngleV = data.cameraAngleV;
            cameraDistance = data.cameraDistance;
          }
        }
      }
    }

    Vector3 targetPos =
        players[activePlayerIdx].inVehicle
            ? vehicles[players[activePlayerIdx].vehicleIdx].position
            : players[activePlayerIdx].position;
    camera.position.x = targetPos.x + cameraDistance *
                                          cosf(cameraAngleV * DEG2RAD) *
                                          sinf(cameraAngleH * DEG2RAD);
    camera.position.y =
        targetPos.y + cameraDistance * sinf(cameraAngleV * DEG2RAD);
    camera.position.z = targetPos.z + cameraDistance *
                                          cosf(cameraAngleV * DEG2RAD) *
                                          cosf(cameraAngleH * DEG2RAD);
    camera.target = targetPos;

    Vector3 forward =
        Vector3Normalize(Vector3Subtract(targetPos, camera.position));
    forward.y = 0;
    forward = Vector3Normalize(forward);
    Vector3 right = (Vector3){-forward.z, 0.0f, forward.x};

    if (!console.active && !switchingChar) {
      for (int i = 0; i < 3; i++) {
        if (players[i].inVehicle) {
          int vIdx = players[i].vehicleIdx;
          if (i == activePlayerIdx) {
            UpdateVehicle(&vehicles[vIdx], forward, right, dt);
          }
          players[i].position = vehicles[vIdx].position;
        } else if (i == activePlayerIdx) {
          UpdatePlayer(&players[i], forward, right, dt);
        }
      }
      UpdateMetro(&metro, &players[activePlayerIdx], dt);
    }

    BeginDrawing();
    ClearBackground(SKYBLUE);

    BeginMode3D(camera);
    DrawGrid(60, 50.0f);
    DrawCity3D();
    DrawMetro(metro);
    for (int i = 0; i < 3; i++) {
      if (!players[i].inVehicle)
        DrawPlayer(players[i]);
    }
    for (int i = 0; i < MAX_VEHICLES; i++) {
      if (vehicles[i].active)
        DrawVehicle(vehicles[i]);
    }
    EndMode3D();

    if (switchingChar) {
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 100});
      float centerX = SCREEN_WIDTH / 2.0f;
      float bottomY = SCREEN_HEIGHT - 60;

      for (int i = 0; i < 3; i++) {
        Color c = (i == 0) ? RED : (i == 1 ? GREEN : GOLD);
        Rectangle r = {centerX - 160 + i * 110, bottomY - 40, 100, 80};
        DrawRectangleRec(
            r, (i == selectedCharIdx) ? WHITE : (Color){200, 200, 200, 150});
        DrawRectangleLinesEx(r, 3, c);
        const char *names[] = {"PLAYER 1", "PLAYER 2", "PLAYER 3"};
        DrawText(names[i], r.x + 10, r.y + 30, 10, BLACK);
      }
    }

    DrawConsole(console);

    // Draw active save slot UI
    DrawRectangle(10, 10, 180, 40, (Color){0, 0, 0, 150});
    DrawText(TextFormat("SAVE SLOT: %d", currentSaveSlot), 20, 20, 20,
             RAYWHITE);
    DrawText("Keys 1-5 to switch", 20, 55, 15, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

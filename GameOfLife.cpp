#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define X_OFFSET 100
#define Y_OFFSET 100
#define WIDTH 1920
#define HEIGHT 1080
#define SPEED_2D 10.0f
#define ZOOM_SPEED 0.01f
#define SQUARE_SIDE 1

#define GAME_LIFE

int grid[(int)(WIDTH / SQUARE_SIDE)][(int)(HEIGHT / SQUARE_SIDE)];

int getNeighbours(int x, int y) {
  int cnt = 0;

  /*
  x + 1, y
  x - 1, y
  x, y + 1
  x, y-1
  x + 1, y + 1
  x - 1, y - 1
  x + 1, y - 1
  x - 1, y + 1
  */

  // Condn 1
  if (x + 1 < (int)(WIDTH / SQUARE_SIDE)) {
    if (grid[x + 1][y] == 1) {

      // std::cout << "\nTriggered x+1 y"
      //           << "\n";
      cnt++;
    }
  }

  // Condn 2
  if (x - 1 > -1) {
    if (grid[x - 1][y] == 1) {

      // std::cout << "\nTriggered x-1 y"
      //           << "\n";
      cnt++;
    }
  }
  // Condn 3
  if (y + 1 < (int)(HEIGHT / SQUARE_SIDE)) {
    if (grid[x][y + 1] == 1) {
      // std::cout << "\nTriggered x y+1"
      //           << "\n";
      cnt++;
    }
  }
  // Condn 4
  if (y - 1 > -1) {
    if (grid[x][y - 1] == 1) {
      // std::cout << "\nTriggered x y-1"
      //           << "\n";
      cnt++;
    }
  }

  // Condn 5
  if (x + 1 < (int)(WIDTH / SQUARE_SIDE) &&
      y + 1 < (int)(HEIGHT / SQUARE_SIDE)) {
    if (grid[x + 1][y + 1] == 1) {

      // std::cout << "\nTriggered x+1 y+1"
      //           << "\n";
      cnt++;
    }
  }

  // Condn 6
  if (x - 1 > -1 && y - 1 > -1) {
    if (grid[x - 1][y - 1] == 1) {

      // std::cout << "\nTriggered x-1 y-1"
      //           << "\n";
      cnt++;
    }
  }

  // Condn 7
  if (x + 1 < (int)(WIDTH / SQUARE_SIDE) && y - 1 > -1) {
    if (grid[x + 1][y - 1] == 1) {
      // std::cout << "\nTriggered x+1 y-1"
      //           << "\n";
      cnt++;
    }
  }

  // Condn 8
  if (x - 1 > -1 && y + 1 < (int)(HEIGHT / SQUARE_SIDE)) {
    if (grid[x - 1][y + 1] == 1) {
      // std::cout << "\nTriggered x-1 y+1"
      //           << "\n";
      cnt++;
    }
  }
  return cnt;
}

void updateGrid() {
  int temp_grid[(int)(WIDTH / SQUARE_SIDE)][(int)(HEIGHT / SQUARE_SIDE)];
  for (int i = 0; i < (int)(WIDTH / SQUARE_SIDE); ++i) {
    for (int j = 0; j < (int)(HEIGHT / SQUARE_SIDE); ++j) {
      // std::cout << "On coordinate: " << i << " " << j << ": " << grid[i][j]
      //           << "--> " << getNeighbours(i, j) << "\n";
      if (grid[i][j] == 0) {
        if (getNeighbours(i, j) <= 2 || getNeighbours(i, j) > 3) {
          // std::cout << "Triggered1: " << i << " " << j << " "
          //           << getNeighbours(i, j) << "\n";
          temp_grid[i][j] = 0;
        } else {
          temp_grid[i][j] = 1;
          // std::cout << "Triggered2: " << i << " " << j << getNeighbours(i, j)
          //           << "\n";
        }
      }
      if (grid[i][j] == 1) {
        if (getNeighbours(i, j) == 2 || getNeighbours(i, j) == 3) {

          // std::cout << "Triggered3: " << i << " " << j << getNeighbours(i, j)
          //           << "\n";
          temp_grid[i][j] = 1;
        } else {

          // std::cout << "Triggered4: " << i << " " << j << getNeighbours(i, j)
          //           << "\n";
          temp_grid[i][j] = 0;
        }
      }
    }
  }

  for (int i = 0; i < (int)(WIDTH / SQUARE_SIDE); ++i) {
    for (int j = 0; j < (int)(HEIGHT / SQUARE_SIDE); ++j) {
      grid[i][j] = temp_grid[i][j];
      // std::cout << "temp_grid[" << i << "][" << j << "]: " << temp_grid[i][j]
      //           << "\n";
    }
  }
}

void initialize_grid() {

  for (int i = 0; i < (int)(WIDTH / SQUARE_SIDE); ++i) {
    for (int j = 0; j < (int)(HEIGHT / SQUARE_SIDE); ++j) {
      grid[i][j] = rand() % 2;
      // grid[i][j] = 0;
      // grid[i][j] = 1;
      // if (total_initialzed > (HEIGHT * 400))
      //   break;
    }
  }
  // grid[1][2] = 1;
  // grid[2][3] = 1;
  // grid[3][1] = 1;
  // grid[3][2] = 1;
  // grid[3][3] = 1;
}

int main() {
  srand(time(0));
  initialize_grid();

#if 0
  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      grid[i][j] = 0;
    }
    // std::cout << "\n";
  }

  grid[0][0] = 0;
  grid[0][1] = 0;
  grid[0][2] = 1;
  grid[1][0] = 0;
  grid[1][1] = 1;
  grid[1][2] = 0;
  grid[2][0] = 1;
  grid[2][1] = 0;
  grid[2][2] = 0;
#endif
#if 0

  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << "\n";
  }
  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      std::cout << "No. of neighbours of " << i << " " << j << " : "
                << getNeighbours(i, j) << "\n";
    }
    std::cout << "\n";
  }

  std::cout << "\n\n\n\n";
  updateGrid();

  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << "\n";
  }
#endif

#if 1

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's of Game of life");

  Camera2D cam = {0};
  cam.zoom = 1;
  bool update = 1;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    int mousePosition_x = GetMouseX();
    int mousePosition_y = GetMouseY();

    // camera.target = (Vector2){(int)(WIDTH / 2), (int)(HEIGHT / 2)};

    int FPS = GetFPS();
    std::string fps = "FPS: " + std::to_string(FPS);
    if (update) {

      updateGrid();
    }

    // translate based on right click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f / cam.zoom);

      cam.target = Vector2Add(cam.target, delta);
    }

    // zoom based on wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
      // get the world point that is under the mouse
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);
      // std::cout << mouseWorldPos.x << " " << mouseWorldPos.y << "\n";

      // set the offset to where the mouse is
      cam.offset = GetMousePosition();

      // set the target to match, so that the camera maps the world space point
      // under the cursor to the screen space point under the cursor at any zoom
      cam.target = mouseWorldPos;

      // zoom
      cam.zoom += wheel * 0.125f;
      if (cam.zoom < 0.125f)
        cam.zoom = 0.125f;
    }
    if (IsKeyDown(KEY_UP)) {
      cam.target = GetScreenToWorld2D(
          (Vector2){(int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2)}, cam);
      cam.offset = (Vector2){(int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2)};
      cam.zoom += ZOOM_SPEED;
    }
    if (IsKeyDown(KEY_DOWN)) {
      cam.target = GetScreenToWorld2D((Vector2){400, 300}, cam);
      cam.offset = (Vector2){400, 300};
      // std::cout << cam.offset.x << " " << cam.offset.y << "\n";
      cam.zoom -= ZOOM_SPEED;
      if (cam.zoom < 0.125f)
        cam.zoom = 0.125f;
    }
    if (IsKeyDown(KEY_D)) {
      cam.target.x += SPEED_2D;
      cam.offset.x -= SPEED_2D;
      // cam.offset.x += 1.0f;
    }
    if (IsKeyDown(KEY_A)) {
      cam.target.x -= SPEED_2D;
      cam.offset.x += SPEED_2D;
      // cam.offset = GetMousePosition();
    }
    if (IsKeyDown(KEY_W)) {
      cam.target.y -= SPEED_2D;
      cam.offset.y += SPEED_2D;
      // cam.offset = GetMousePosition();
    }
    if (IsKeyDown(KEY_S)) {
      cam.target.y += SPEED_2D;
      cam.offset.y -= SPEED_2D;
      // cam.offset = GetMousePosition();
    }
    if (IsKeyPressed(KEY_R)) {
      initialize_grid();
    }
    if (IsKeyPressed(KEY_SPACE)) {
      update ^= 1;
    }

    BeginDrawing();
    BeginMode2D(cam);

#ifdef GAME_LIFE
    ClearBackground(BLACK);
    DrawText("Conway's Game of Life", 10, 10, 50, GRAY);
    DrawText(fps.c_str(), WIDTH - 200, 10, 50, RED);

    for (int i = 0; i < (int)(WIDTH / SQUARE_SIDE); ++i) {
      for (int j = 0; j < (int)(HEIGHT / SQUARE_SIDE); ++j) {
        if (grid[i][j])
          // DrawPixel(i, j + Y_OFFSET, Fade(WHITE, 0.5f));
          DrawRectangle(i * SQUARE_SIDE, Y_OFFSET + (j * SQUARE_SIDE),
                        SQUARE_SIDE, SQUARE_SIDE, WHITE);
      }
    }
#endif

#ifdef TEST

    ClearBackground(BLACK);
    DrawText(fps.c_str(), 700, 10, 20, RED);
    // rec.x = !(rec.x == WIDTH) ? ((int)(rec.x + 10) % WIDTH) : -100;
    Rectangle rec = {200, 200, 100, 100};
    DrawRectangleRec(rec, Fade(GREEN, 0.5f));
#endif

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
#endif

  return 0;
}

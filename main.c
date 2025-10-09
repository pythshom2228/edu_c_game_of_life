#include <stdbool.h>
#include <stdlib.h>

#include "raylib.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "game of life"
#define TARGET_FPS 60
#define BG_COLOR WHITE

#define CELL_SIZE 10
#define CELL_COLOR BLACK

#define GRID_COLS (SCREEN_WIDTH / CELL_SIZE)
#define GRID_ROWS (SCREEN_HEIGHT / CELL_SIZE)
#define GRID_COLOR GRAY

typedef unsigned char cell_t;

static cell_t grid_a[GRID_ROWS][GRID_COLS];
static cell_t grid_b[GRID_ROWS][GRID_COLS];

static cell_t (*grid)[GRID_COLS] = grid_a;
static cell_t (*next_grid)[GRID_COLS] = grid_b;

static bool running = false;

static void clear_grid(void);
static void randomize_grid(void);

static void input(void);
static void update(float dt);
static void render(void);

static void render_cells(void);
static void render_grid(void);
static void render_hud(void);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    if (!IsWindowReady()) {
        TraceLog(LOG_ERROR, "failed to create window");
        return EXIT_FAILURE;
    }
    SetTargetFPS(TARGET_FPS);

    clear_grid();

    while (!WindowShouldClose()) {
        input();
        update(GetFrameTime());
        render();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}

static void clear_grid(void) {
    for (int y = 0; y < GRID_ROWS; ++y) {
        for (int x = 0; x < GRID_COLS; ++x) {
            grid[y][x] = 0;
        }
    }
}

static void input(void) {
    if (IsKeyPressed(KEY_SPACE)) {
        running = !running;
    }

    if (IsKeyPressed(KEY_R)) {
        randomize_grid();
    }

    if (IsKeyPressed(KEY_C)) {
        clear_grid();
    }

    const bool is_lmb = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    const bool is_rmb = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    if (is_lmb || is_rmb) {
        const int mx = GetMouseX() / CELL_SIZE;
        const int my = GetMouseY() / CELL_SIZE;
        grid[my][mx] = is_lmb ? 1 : 0;
    }
}

static void update(float dt) {
    // TODO: impl
}

static void randomize_grid(void) {
    for (int y = 0; y < GRID_ROWS; ++y) {
        for (int x = 0; x < GRID_COLS; ++x) {
            grid[y][x] = GetRandomValue(0, 4) == 0 ? 1 : 0; // 20%
        }
    }
}

static void render(void) {
    BeginDrawing();
    ClearBackground(BG_COLOR);
    render_cells();
    render_grid();
    render_hud();
    EndDrawing();
}

static void render_cells(void) {
    for (int y = 0; y < GRID_ROWS; ++y) {
        for (int x = 0; x < GRID_COLS; ++x) {
            if (grid[y][x] == 1) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_COLOR);
            }
        }
    }
}

static void render_grid(void) {
    for (int x = 0; x <= GRID_COLS; ++x) {
        DrawLine(x * CELL_SIZE, 0, x * CELL_SIZE, SCREEN_HEIGHT, GRID_COLOR);
    }
    for (int y = 0; y <= GRID_COLS; ++y) {
        DrawLine(0, y * CELL_SIZE, SCREEN_WIDTH, y * CELL_SIZE, GRID_COLOR);
    }
}

static void render_hud(void) {
    // TODO: impl
}

#include <SDL2/SDL.h>
#include <iostream>

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{600};
constexpr int maxFrameRate{60}; // Maximum desired frame rate (FPS)
constexpr int maxFrameTime{
    1000 / maxFrameRate}; // Maximum time allowed per frame (in milliseconds)
//

constexpr int PLATFORM_TILE_WIDTH{50};
constexpr int PLATFORM_TILE_HEIGHT{20};
constexpr int NUM_PLATFORM_TILES{18}; // Update the number of platform tiles

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Video failed to load: " << SDL_GetError() << '\n';
    return 1;
  } else {
    std::cout << "SDL Video is ready to go.\n";
  }

  SDL_Window *window = SDL_CreateWindow(
      "2D Classic Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  // Define positions of platform tiles
  SDL_Rect platformTiles[NUM_PLATFORM_TILES];
  // Update the positions of platform tiles based on the design
  platformTiles[0] = {0, SCREEN_HEIGHT - PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[1] = {3 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[2] = {4 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 2 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[3] = {5 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 3 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[4] = {6 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 3 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[5] = {7 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 4 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[6] = {8 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 4 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[7] = {9 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 5 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[8] = {10 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 5 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[9] = {11 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 6 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[10] = {12 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 6 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[11] = {13 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 7 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[12] = {14 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 7 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[13] = {15 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 8 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[14] = {16 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 8 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[15] = {17 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 9 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[16] = {18 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 9 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};
  platformTiles[17] = {19 * PLATFORM_TILE_WIDTH, SCREEN_HEIGHT - 10 * PLATFORM_TILE_HEIGHT, PLATFORM_TILE_WIDTH, PLATFORM_TILE_HEIGHT};

  SDL_Rect player{100, 100, 50, 50};
  int playerSpeedX{0}; // Horizontal speed
  int playerSpeedY{10}; // Vertical speed
  bool isJumping{false};
  int jumpForce{20};
  int gravity{1};
  bool gameIsRunning{true};

  Uint32 previousTime = SDL_GetTicks();
  Uint32 lag = 0;

  while (gameIsRunning) {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - previousTime;
    previousTime = currentTime;
    lag += elapsedTime;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameIsRunning = false;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          gameIsRunning = false;
          std::cout << "Escape key is pressed.\n";
          break;
        case SDLK_w:
          if (!isJumping) {
            isJumping = true;
            playerSpeedY = -jumpForce;
          }
          break;
        case SDLK_a:
          playerSpeedX = -5; // Move left
          break;
        case SDLK_d:
          playerSpeedX = 5; // Move right
          break;
        }
      } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
          // Handle key release if needed
          break;
        case SDLK_a:
        case SDLK_d:
          playerSpeedX = 0; // Stop horizontal movement
          break;
        }
      }
    }
    playerSpeedY += gravity;

        // playerSpeedY += gravity;
    while (lag >= maxFrameTime) {
      // Apply gravity
      if (isJumping) {
        playerSpeedY += gravity;
      }

      // Apply vertical speed
      player.y += playerSpeedY;

      // Land on the ground
      if (player.y + player.h >= SCREEN_HEIGHT) {
        player.y = SCREEN_HEIGHT - player.h;
        playerSpeedY = 0;
        isJumping = false;
      }

      // Apply horizontal speed
      player.x += playerSpeedX;

      // Check for collision with screen boundaries
      if (player.x < 0) {
        player.x = 0;
      } else if (player.x + player.w > SCREEN_WIDTH) {
        player.x = SCREEN_WIDTH - player.w;
      }

      lag -= maxFrameTime;
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Inside the main game loop, after clearing the renderer
    for (int i = 0; i < NUM_PLATFORM_TILES; ++i) {
      // Set render draw color for platform tiles
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      // Draw platform tile
      SDL_RenderFillRect(renderer, &platformTiles[i]);
    }
    // Inside the main game loop, after updating the player's position but
    // before rendering the player
    for (int i = 0; i < NUM_PLATFORM_TILES; ++i) {
      // Check for collision between player and platform tile
      if (SDL_HasIntersection(&player, &platformTiles[i])) {
        // Adjust player's position to remain on top of platform
        if (player.y + player.h > platformTiles[i].y && playerSpeedY > 0) {
          player.y = platformTiles[i].y - player.h;
          playerSpeedY = 0;  // Stop player from falling further
          isJumping = false; // Reset jumping state
        }
      }
    }
// Inside the main game loop, after updating the player's position
for (int i = 0; i < NUM_PLATFORM_TILES; ++i) {
    // Check if player collides with platform tile
    if (player.y + player.h >= platformTiles[i].y && player.y < platformTiles[i].y + platformTiles[i].h
        && player.x + player.w > platformTiles[i].x && player.x < platformTiles[i].x + platformTiles[i].w) {
        // Adjust player's position to prevent falling through platform
        player.y = platformTiles[i].y - player.h;
        playerSpeedY = 0; // Stop player from falling further
        isJumping = false; // Reset jump state
    }
}

    // Draw the player
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &player);

    // Present the frame
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    Uint32 frameTime = SDL_GetTicks() - currentTime;
    if (frameTime < maxFrameTime) {
      SDL_Delay(maxFrameTime - frameTime);
    }
  }

  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

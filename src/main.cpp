#include <SDL2/SDL.h>
#include <iostream>
constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{600};
int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Video failed to load: " << SDL_GetError() << '\n';
    return 1;
  } else {
    std::cout << "SDL Video is ready.\n";
  }

  SDL_Window *window{nullptr};
  window = SDL_CreateWindow("2d classic platformer", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer{nullptr};
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Rect player{100, 100, 50, 50};
  int playerSpeedX{10};
  int playerSpeedY{0};

  bool isJumping{false};
  int jumpForce{20};
  int gravity{1};

  bool gameIsRunning{true};
  while (gameIsRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      const Uint8 *state{SDL_GetKeyboardState(NULL)};
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escapy key pressed.\n";
      }

      // up
      if (state[SDL_SCANCODE_W]) {
        isJumping = true;
      }
      // down
      if (state[SDL_SCANCODE_S]) {
        player.y += playerSpeedY;
      }
      // left
      if (state[SDL_SCANCODE_A]) {
        player.x -= playerSpeedX;
      }
      // right
      if (state[SDL_SCANCODE_D]) {
        player.x += playerSpeedX;
      }
      if (isJumping) {
        player.y -= jumpForce;
        jumpForce -= gravity;
      }
      if (jumpForce < 0) {
        isJumping = false;
        jumpForce = 20;
      }
    }

    playerSpeedY += 1;
    player.y += playerSpeedY;
    if (player.y + player.h >= SCREEN_HEIGHT) {
      player.y =
          SCREEN_HEIGHT - player.h; // Set player's position to the ground level
      playerSpeedY = 0; // Reset vertical speed when player hits the ground
    }

    // check right boundary collision detection and resolution
    if (player.x + player.w >= SCREEN_WIDTH) {
      player.x = SCREEN_WIDTH - player.w;
      // playerSpeedX = 0;
    }
    // check left boundary collision detection and resolution
    if (player.x <= 0) {
      player.x = 0;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &player);

    SDL_RenderPresent(renderer);
  }
  // clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

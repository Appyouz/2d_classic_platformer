#include <SDL2/SDL.h>
#include <iostream>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Video failed to load: " << SDL_GetError() << '\n';
    return 1;
  } else {
    std::cout << "SDL Video is ready.\n";
  }

  SDL_Window *window{nullptr};
  window =
      SDL_CreateWindow("2d classic platformer", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1024, 720, SDL_WINDOW_SHOWN);

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
  int playerSpeed{10};

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
        player.y -= playerSpeed;
      }
      // down
      if (state[SDL_SCANCODE_S]) {
        player.y += playerSpeed;
      }
      // left
      if (state[SDL_SCANCODE_A]) {
        player.x -= playerSpeed;
      }
      // right
      if (state[SDL_SCANCODE_D]) {
        player.x += playerSpeed;
      }
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

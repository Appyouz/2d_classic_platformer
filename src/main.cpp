
#include <SDL2/SDL.h>
#include <iostream>

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{600};
constexpr int maxFrameRate{60}; // Maximum desired frame rate (FPS)
constexpr int maxFrameTime{1000 / maxFrameRate}; // Maximum time allowed per frame (in milliseconds)

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

    SDL_Rect player{100, 100, 50, 50};
    int playerSpeedX{10};
    int playerSpeedY{0};
    bool isJumping{false};
    int jumpForce{20};
    int gravity{1};
    int acceleration{30};
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
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
                gameIsRunning = false;
                std::cout << "Escape key is pressed.\n";
            }

            bool keyIsPressed_W = state[SDL_SCANCODE_W];
            bool keyIsPressed_A = state[SDL_SCANCODE_A];
            bool keyIsPressed_D = state[SDL_SCANCODE_D];

            if (keyIsPressed_W && !isJumping) {
                isJumping = true;
                playerSpeedY = -jumpForce;
            }

            if (keyIsPressed_A) {
                player.x -= playerSpeedX;
                if (isJumping) {
                    player.x -= acceleration;
                }
            }

            if (keyIsPressed_D) {
                player.x += playerSpeedX;
                if (isJumping) {
                    player.x += acceleration;
                }
            }
        }

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

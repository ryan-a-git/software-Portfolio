#include <SDL2/SDL.h>


int HEIGHT = 2560;
int WIDTH = 2560;
int SCREEN_HEIGHT = 1440;
int SCREEN_WIDTH = 2560;
long double min = -1.0;
long double max = 2.0;
int MAX_ITERATIONS = 200;

long double map(long double x, long double in_min, long double in_max,
                long double out_min, long double out_max) {
                    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;


    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    std::atexit(SDL_Quit);

    while(true) {
        SDL_RenderPresent(renderer);
        for( int px = 0; px < WIDTH; px++) {

            if(SDL_PollEvent(&event) && event.type == SDL_QUIT) {
                return 0;
            }

            for( int py = 0; py < HEIGHT; py++) {
                long double x0 = map(px, 0, WIDTH, min, max);
                long double y0 = map(py, 0, HEIGHT, min, max);

                long double x = 0.0;
                long double y = 0.0;

                long double x2 = 0.0;
                long double y2 = 0.0;

                int iteration = 0;

                while(x2 + y2 <= 4 && iteration < MAX_ITERATIONS) {
                    y = 2 * x * y + y0;
                    x = x2 - y2 + x0;
                    x2 = x * x;
                    y2 = y * y;
                    iteration++;
                }

                //std::cout << "iteration: " << iteration << " max iteration: "
                //<< MAX_ITERATIONS << std::endl;
                int bright = map(iteration, 0, MAX_ITERATIONS, 0, 255);
                //std::cout << "Bright: " << bright << " x: " << px << " y: " << py << std::endl;



                if (iteration == MAX_ITERATIONS) {
                    bright = 0;
                }

                int red = map(bright * bright, 0, 255 * 255, 0, 255);
                int green = bright;
                int blue = map(sqrt(bright), 0, sqrt(255), 0, 255);




                SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
                SDL_RenderDrawPoint(renderer, px, py);
                
            }

        }

    }


    return 0;
}
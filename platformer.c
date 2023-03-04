#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define WIDTH 50
#define HEIGHT 10

// Game character
struct Character {
    int x;
    int y;
};

// Game state
struct GameState {
    struct Character player;
    int score;
    bool game_over;
};

// Draw the game board
void draw_board(struct GameState state) {
    system("clear"); // clear the console

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == state.player.y && x == state.player.x) {
                printf("O"); // draw the player
            } else if (y == HEIGHT - 1) {
                printf("-"); // draw the ground
            } else {
                printf(" "); // draw empty space
            }
        }
        printf("\n"); // end of row
    }
    printf("Score: %d\n", state.score);
}

// Update the game state
void update_state(struct GameState *state, int dx, int dy) {
    // Move the player
    state->player.x += dx;
    state->player.y += dy;

    // Check for game over condition
    if (state->player.y == HEIGHT - 1) {
        state->game_over = true;
    }

    // Update the score
    state->score++;
}

int main() {
    // Initialize the game state
    struct GameState state = {
        .player = { .x = 0, .y = HEIGHT - 2 },
        .score = 0,
        .game_over = false
    };

    // Main game loop
    while (!state.game_over) {
        // Draw the game board
        draw_board(state);

        // Get user input
        int dx = 0;
        printf("Move left (a) or right (d): ");
        char input = getchar();
        getchar(); // clear the newline character
        if (input == 'a') {
            dx = -1;
        } else if (input == 'd') {
            dx = 1;
        }

        // Update the game state
        update_state(&state, dx, 0);

        // Wait for a short time (50 ms)
        usleep(50000);
    }

    // Game over
    draw_board(state);
    printf("Game over! Score: %d\n", state.score);

    return 0;
}

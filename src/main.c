#include "SFML/Graphics/Color.h"
#include <matrix.h>
#include <stdio.h>

int main() {
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode){1280, 720, 32}, "Matrix Rain", sfDefaultStyle, NULL);

    loadFont(window);

    sfClock *clock1 = sfClock_create();
    sfClock *clock2 = sfClock_create();
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)) {
                sfRenderWindow_close(window);
            }
        }

        sfRenderWindow_clear(window, sfBlack);

        if (sfTime_asMilliseconds(sfClock_getElapsedTime(clock1)) >= 150.0f) {
            randomChar();
            sfClock_restart(clock1);
        }

        if (sfTime_asSeconds(sfClock_getElapsedTime(clock2)) >= (1.0f / 75.0f)) {
            moveText(window);
            sfClock_restart(clock2);
        }

        renderMatrix(window);

        sfRenderWindow_display(window);
    }

    freeMemory();
}

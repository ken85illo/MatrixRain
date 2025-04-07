#include <matrix.h>
#include <stdlib.h>
#include <time.h>

const char charArray[45] = "abcdefghijklmnopqrstuvwxyz`1234567890~!@#$^&?";
char fallingChar[2];
sfFont *font = NULL;
sfText **text = NULL;
float *speed = NULL;
int speedMin = 50;
int speedMax = 500;
int amountOfRain = 100;
int amountOfChar = 20;

void loadFont(sfRenderWindow *window) {
    srand(time(0));
    font = sfFont_createFromFile("include/arial.ttf");
    text = (sfText **)malloc((amountOfRain * amountOfChar) * sizeof(sfText *));
    speed = (float *)malloc((amountOfRain) * sizeof(float));

    for (int i = 0; i < amountOfRain; i++) {
        speed[i] = ((rand() % (speedMax - speedMin)) + speedMin) / 100.0f;
        for (int j = 0; j < amountOfChar; j++) {
            text[i * amountOfChar + j] = sfText_create();
            sfText_setFont(text[i * amountOfChar + j], font);
            if (j < 3) {
                sfText_setColor(text[i * amountOfChar + j],
                                sfColor_fromRGB(255 - (50 * j), 255 - (50 * j), 255 - (50 * j)));
            } else if (j > amountOfChar - 6) {
                sfText_setColor(text[i * amountOfChar + j],
                                sfColor_fromRGBA(0, 200, 0, 255 + (45 * (amountOfChar - 6 - j))));
            } else {
                sfText_setColor(text[i * amountOfChar + j], sfColor_fromRGB(0, 200, 0));
            }
            sfText_setStyle(text[i * amountOfChar + j], sfTextBold);
            sfText_setCharacterSize(text[i * amountOfChar + j], 15);
            if (j == 0) {
                sfText_setPosition(text[i * amountOfChar],
                                   (sfVector2f){(float)(rand() % sfRenderWindow_getSize(window).x),
                                                sfText_getCharacterSize(text[0]) * -1.0f * (j + 1)});
            } else {
                sfText_setPosition(text[i * amountOfChar + j],
                                   (sfVector2f){sfText_getPosition(text[i * amountOfChar]).x,
                                                sfText_getCharacterSize(text[0]) * -1.0f * (j + 1)});
            }
        }
    }
}

void randomChar() {
    for (int i = 0; i < amountOfChar * amountOfRain; i++) {
        fallingChar[0] = charArray[rand() % (sizeof(charArray) / sizeof(charArray[0]))];
        fallingChar[1] = '\0';

        sfText_setString(text[i], fallingChar);
    }
}

void moveText(sfRenderWindow *window) {
    for (int i = 0; i < amountOfRain; i++) {
        for (int j = 0; j < amountOfChar; j++) {
            if (sfText_getPosition(text[i * amountOfChar + j]).y > sfRenderWindow_getSize(window).y) {
                if (j == 0) {
                    sfText_setPosition(text[i * amountOfChar],
                                       (sfVector2f){(float)(rand() % sfRenderWindow_getSize(window).x),
                                                    sfText_getCharacterSize(text[0]) * -1.0f});
                } else if (j != 0) {
                    sfText_setPosition(text[i * amountOfChar + j],
                                       (sfVector2f){sfText_getPosition(text[i * amountOfChar]).x,
                                                    sfText_getCharacterSize(text[0]) * -1.0f});
                }
            } else {
                sfText_setPosition(text[i * amountOfChar + j],
                                   (sfVector2f){sfText_getPosition(text[i * amountOfChar + j]).x,
                                                sfText_getPosition(text[i * amountOfChar + j]).y + speed[i]});
            }
        }
    }
}

void renderMatrix(sfRenderWindow *window) {
    for (int i = 0; i < amountOfChar * amountOfRain; i++) {
        sfRenderWindow_drawText(window, text[i], NULL);
    }
}

void freeMemory() {
    free(text);
    free(speed);
}

#ifndef GAME_H
#define GAME_H
#include "GFX/Graphics.h"
#include "Controls/Keyboard.h"

#include "GFX/Font.h"

#include <vector>

class Game
{
public:
    Game(Keyboard &kbd);
    ~Game();

    void Tick();

private:
    void Update();
    void Render();
    void Input();

private:
    Graphics cGraphics;
    Keyboard& cKeyboard;

    Font cFont;

    Bitmap cSampleImage;
    Bitmap cSampleImage2;

    int cNumberOfImages;

    int cScore;

    int cStartTime;

    int cFrameMs;
};

#endif
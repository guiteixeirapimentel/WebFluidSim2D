#include "Game.h"
#include <iostream>
#include <chrono>

Game::Game(Keyboard &kbd)
    : cKeyboard(kbd),
      cGraphics(800, 600),
      cFont("assets/Consolas13x24.bmp", 13, 24),
      cSampleImage("assets/sample_640×426.bmp"),
      cSampleImage2("assets/Consolas13x24.bmp"),
      cScore(0),
      cNumberOfImages(0),
      cStartTime(std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count()),
      cFrameMs(1)
{

}

Game::~Game()
{
}

void Game::Tick()
{
    int startFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count();
    Input();
    Update();

    cGraphics.Init();
    Render();
    cGraphics.Present(false);

    cFrameMs += std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count() - startFrameTime;
    cFrameMs /= 2;
}

void Game::Update()
{
    cScore = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count() -
             cStartTime;


}

void Game::Render()
{
    for(int i = 0; i < 3; i++)
        cSampleImage.Draw({ i*10, i*10 }, cGraphics);
    // cSampleImage2.Draw({ 10, 10 }, cGraphics);
        

    const std::string msPerFrameString = "Ms per Frame" + std::to_string(cFrameMs);
    const int stringWidthPixels = msPerFrameString.length() * cFont.GetWidth();

    cFont.DrawString({0, 0}, "Score: " + std::to_string(cScore), {255, 255, 255, 255}, cGraphics);
    cFont.DrawString({ int(cGraphics.GetWidth()) - stringWidthPixels-8, 0}, 
        msPerFrameString, 
        {255, 255, 255, 255}, cGraphics);

    const std::string FPS = "FPS" + std::to_string(1000.0 / cFrameMs);
    const int stringFPSWidthPixels = FPS.length() * cFont.GetWidth();

    cFont.DrawString({ int(cGraphics.GetWidth()) - stringFPSWidthPixels-8, int(cFont.GetHeight() + 8)}, 
        FPS, 
        {255, 255, 255, 255}, cGraphics);


    cFont.DrawString({ 0, int(cFont.GetHeight() + 8)}, 
        std::to_string(cNumberOfImages), 
        {255, 255, 255, 255}, cGraphics);

    for(int i = 0; i < 10; i++)
        cSampleImage2.Draw({ 10*i, 10 }, cGraphics);
}

void Game::Input()
{
    Keyboard::KeyEvent ev;
    while ((ev = cKeyboard.PeekAndPopEvent()))
    {
        // do events
    }

    if(cKeyboard.IsKeyPressed(SDLK_UP))
    {
        if(cNumberOfImages < 10)
            cNumberOfImages++;
    }

    if (cKeyboard.IsKeyPressed(SDLK_w))
    {
        if (cKeyboard.IsKeyPressed(SDLK_a))
        {
        }
        else if (cKeyboard.IsKeyPressed(SDLK_d))
        {
        }
        else
        {
        }
    }
    else if (cKeyboard.IsKeyPressed(SDLK_s))
    {
        if (cKeyboard.IsKeyPressed(SDLK_a))
        {
        }
        else if (cKeyboard.IsKeyPressed(SDLK_d))
        {
        }
        else
        {
        }
    }
    else if (cKeyboard.IsKeyPressed(SDLK_a))
    {
    }
    else if (cKeyboard.IsKeyPressed(SDLK_d))
    {
    }
}

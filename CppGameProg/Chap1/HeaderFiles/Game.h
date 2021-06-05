#pragma once
#include "SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	//ゲームの初期化
	bool Initialize();
	//ゲームオーバーまでゲームループを実行
	void RunLoop();
	//ゲームのシャットダウン
	void Shutdown();
private:
	//ゲームループのためのヘルパー関数群
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//SDLが作るウィンドウ
	SDL_Window* mWindow;
	//ゲームの続行を指示する
	bool mIsRunning;

	//パドルの位置
	Vector2 mPaddlePos;
	//ボールの位置
	Vector2 mBallPos;
};

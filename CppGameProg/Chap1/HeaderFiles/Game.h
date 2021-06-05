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

	//壁の厚さ
	int thickness;

	//パドルの位置
	Vector2 mPaddlePos;
	//パドルの高さ
	int paddleH;
	//パドルを動かす
	int mPaddleDir;

	//ボールの位置
	Vector2 mBallPos;
	//ボールの速度
	Vector2 mBallVel;

	//デルタタイム
	Uint32 mTicksCount;

	
};

#pragma once
#include "SDL.h"
#include <vector>

struct Vector2
{
	float x;
	float y;
};

struct Ball
{
	Vector2 pos;
	Vector2 vel;
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
	Vector2 mPaddleRPos;
	//パドルの高さ
	int paddleH;
	//パドルを動かす
	int mPaddleDir;
	int mPaddleRDir;

	//ボールの位置
	Vector2 mBallPos;
	//ボールの速度
	Vector2 mBallVel;
	//ボールの構造体
	std::vector<Ball> balls;
	Ball ball;

	//デルタタイム
	Uint32 mTicksCount;

	
};

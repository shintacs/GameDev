#include "Game.h";
#include <iostream>

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
	, ball()
{

}

//レンダラーの初期化
SDL_Renderer* mRenderer;

bool Game::Initialize()
{
	//SDLライブラリの初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("SDLを初期化できません。:%s", SDL_GetError());
		return false;
	}

	//ウィンドウの作成
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ Chap1", //ウィンドウのタイトル
		100,	//ウィンドウ左上隅のx座標
		100,	//ウィンドウ左上隅のy座標
		1024,	//ウィンドウの幅
		768,	//ウィンドウの高さ
		0		//フラグ
	);
	if (!mWindow)
	{
		SDL_Log("ウィンドウの作成に失敗しました。: %s", SDL_GetError());
		return false;
	}

	//レンダラーの初期化　垂直同期を有効にする
	mRenderer = SDL_CreateRenderer(//引数の追加
		mWindow,	//作成するレンダラーの描画対象となるウィンドウ
		-1,			//通常は-1 グラフィックスドライバーの指定
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mPaddleRPos.x = 999.0f;
	mPaddleRPos.y = mPaddlePos.y;

	for (int i = 0; i < 3; i++)
	{
		mBallPos.x = 1024.0f / 2.0f;
		mBallPos.y = 768.0f / 2.0f;
		mBallVel.x = i*150 -200.0f;
		mBallVel.y = i*45 + 235.0f;

		ball.pos = mBallPos;
		ball.vel = mBallVel;

		balls.push_back(ball);
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);	//ウィンドウの破棄
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();	//SDLを終わらせる
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	//キューにイベントがあれば繰り返す
	while (SDL_PollEvent(&event))	//eventにはキューから取り出したイベントの情報が入る
	{
		switch (event.type)
		{
			//各種のイベント設定
			//SDL_QUITイベントなら、ループを終える
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	//キーボードの現在の状態を取得
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}

	mPaddleRDir = 0;
	if (state[SDL_SCANCODE_I])
	{
		mPaddleRDir -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddleRDir += 1;
	}
}

void Game::GenerateOutput()
{
	//描画色の指定
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		//R
		0,		//G
		255,	//B
		255		//A
	);
	//バックバッファを現在の描画色でクリア
	SDL_RenderClear(mRenderer);

	//描画色を白に変える
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	thickness = 15;	//壁の厚み

	//長方形の壁の設定
	SDL_Rect wall{
		0,			//左上隅のX
		0,			//左上隅のy
		1024,		//幅(あまり固定の大きさに決めるのは良くない)
		thickness	//高さ
	};
	//下の壁
	SDL_Rect wallD{
		0,
		768 - thickness,
		1024,
		thickness
	};
	//右の壁
	/*SDL_Rect wallR{
		1024 - thickness,
		0,
		thickness,
		768
	};*/

	//長方形を描く
	SDL_RenderFillRect(mRenderer, &wall);
	SDL_RenderFillRect(mRenderer, &wallD);
	//SDL_RenderFillRect(mRenderer, &wallR);

	//ボールの設定。SDL_Rectは左上の座標で定義する
	SDL_Rect ball1{
		static_cast<int>(balls[0].pos.x - thickness / 2),
		static_cast<int>(balls[0].pos.y - thickness / 2),
		thickness,
		thickness
	};

	SDL_Rect ball2{
		static_cast<int>(balls[1].pos.x - thickness / 2),
		static_cast<int>(balls[1].pos.y - thickness / 2),
		thickness,
		thickness
	};

	SDL_Rect ball3{
		static_cast<int>(balls[2].pos.x - thickness / 2),
		static_cast<int>(balls[2].pos.y - thickness / 2),
		thickness,
		thickness
	};

	//ボールを描く
	SDL_RenderFillRect(mRenderer, &ball1);
	SDL_RenderFillRect(mRenderer, &ball2);
	SDL_RenderFillRect(mRenderer, &ball3);

	paddleH = 100;
	//パドルの設定
	SDL_Rect paddle1{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		paddleH
	};

	SDL_Rect paddle2{
		static_cast<int>(mPaddleRPos.x),
		static_cast<int>(mPaddleRPos.y - paddleH / 2),
		thickness,
		paddleH
	};

	//パドルを描く
	SDL_RenderFillRect(mRenderer, &paddle1);
	SDL_RenderFillRect(mRenderer, &paddle2);

	//フロントバッファとバックバッファの交換
	SDL_RenderPresent(mRenderer);
}

void Game::UpdateGame()
{
	//フレーム制限（前のフレームから16msが経過するまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	//deltatimeは前のフレームとの時刻の差を秒に変換した値
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//時刻を変更（次のフレームのために）
	mTicksCount = SDL_GetTicks();

	//デルタタイムを最大値で制限する
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	//デルタタイムに基づいてパドルを更新する
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
	}

	if (mPaddleRDir != 0)
	{
		mPaddleRPos.y += mPaddleRDir * 300.0f * deltaTime;
	}

	//パドルのy座標に境界条件の制約を加える
	if (mPaddleDir != 0)
	{//左のパドルの境界条件
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		//パドルが画面から出ないようにする
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	if (mPaddleRDir != 0)
	{//右のパドルの境界条件
		mPaddleRPos.y += mPaddleRDir * 300.0f * deltaTime;
		//パドルが画面から出ないようにする
		if (mPaddleRPos.y < (paddleH / 2.0f + thickness))
		{
			mPaddleRPos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddleRPos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddleRPos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	for (int i = 0; i < 3; i++) {//各ボールの更新
		mBallPos.x = balls[i].pos.x + balls[i].vel.x * deltaTime;
		mBallPos.y = balls[i].pos.y + balls[i].vel.y * deltaTime;
		mBallVel.x = balls[i].vel.x;
		mBallVel.y = balls[i].vel.y;

		//ボールの衝突後の挙動(ボールが上の壁と衝突し、しかもボールが上向きに動いているとき
		if (balls[i].pos.y <= thickness && balls[i].vel.y < 0.0f)
		{
			mBallVel.y = balls[i].vel.y * -1;
		}

		//下の壁
		if (balls[i].pos.y >= (768.0f - thickness) && balls[i].vel.y > 0.0f)
		{
			mBallVel.y = balls[i].vel.y * -1;
		}

		float diff = balls[i].pos.y - mPaddlePos.y;
		float diffr = balls[i].pos.y - mPaddleRPos.y;
		diff = (diff > 0.0f) ? diff : -diff;
		diffr = (diffr > 0.0f) ? diffr : -diffr;

		//パドルとの衝突
		if (diff <= paddleH / 2.0f &&	//yの差が十分に小さく
			balls[i].pos.x <= 25.0f && balls[i].pos.x >= 20.0f &&	//ボールが正しい位置にあり
			balls[i].vel.x < 0.0f)	//ボールが左向きに動いていれば
		{
			mBallVel.x = balls[i].vel.x * -1.0f;
		}

		if (diffr <= paddleH / 2.0f &&	//yの差が十分に小さく
			balls[i].pos.x <= 1004.0f && balls[i].pos.x >= 999.0f &&	//ボールが正しい位置にあり
			balls[i].vel.x > 0.0f)	//ボールが右向きに動いていれば
		{
			mBallVel.x = balls[i].vel.x * -1.0f;
		}
		
		ball.pos = mBallPos;
		ball.vel = mBallVel;
		balls[i] = ball;
	}
	
	/*
	//ボールの位置を速度に応じて動かす
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	//ボールの衝突後の挙動(ボールが上の壁と衝突し、しかもボールが上向きに動いているとき
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	//右の壁
	if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1;
	}
	//下の壁
	if (mBallPos.y >= (768.0f - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	float diff = mBallPos.y - mPaddlePos.y;
	float diffr = mBallPos.y - mPaddleRPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	diffr = (diffr > 0.0f) ? diffr : -diffr;

	//パドルとの衝突
	if (diff <= paddleH / 2.0f &&	//yの差が十分に小さく
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&	//ボールが正しい位置にあり
		mBallVel.x < 0.0f)	//ボールが左向きに動いていれば
	{
		mBallVel.x *= -1.0f;
	}

	if (diffr <= paddleH / 2.0f &&	//yの差が十分に小さく
		mBallPos.x <= 1004.0f && mBallPos.x >= 999.0f &&	//ボールが正しい位置にあり
		mBallVel.x > 0.0f)	//ボールが右向きに動いていれば
	{
		mBallVel.x *= -1.0f;
	}
	*/
}

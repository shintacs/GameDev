#include "Game.h";

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
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
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

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
	SDL_Rect wallR{
		1024 - thickness,
		0,
		thickness,
		768
	};

	//長方形を描く
	SDL_RenderFillRect(mRenderer, &wall);
	SDL_RenderFillRect(mRenderer, &wallD);
	SDL_RenderFillRect(mRenderer, &wallR);

	//ボールの設定。SDL_Rectは左上の座標で定義する
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};

	//ボールを描く
	SDL_RenderFillRect(mRenderer, &ball);

	paddleH = 100;
	//パドルの設定
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		paddleH
	};

	//パドルを描く
	SDL_RenderFillRect(mRenderer, &paddle);

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

	//パドルのy座標に境界条件の制約を加える
	if (mPaddleDir != 0)
	{
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
	diff = (diff > 0.0f) ? diff : -diff;

	//パドルとの衝突
	if (diff <= paddleH / 2.0f &&	//yの差が十分に小さく
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&	//ボールが正しい位置にあり
		mBallVel.x < 0.0f)	//ボールが左向きに動いていれば
	{
		mBallVel.x *= -1.0f;
	}
}

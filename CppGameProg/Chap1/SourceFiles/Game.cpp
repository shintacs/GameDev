#include "Game.h";

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
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

	mPaddlePos.x = 100.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

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
		//UpdateGame();
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
	//フロントバッファとバックバッファの交換
	SDL_RenderPresent(mRenderer);

	//描画色を白に変える
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	const int thickness = 15;	//壁の厚み

	//長方形の壁を描く
	SDL_Rect wall{
		0,			//左上隅のX
		0,			//左上隅のy
		1024,		//幅(あまり固定の大きさに決めるのは良くない)
		thickness	//高さ
	};

	//長方形を描く
	SDL_RenderFillRect(mRenderer, &wall);

	//ボールの描写。SDL_Rectは左上の座標で定義する
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};

	//パドルを描く
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2),
		static_cast<int>(mPaddlePos.y - thickness / 2),
		thickness,
		100
	};
}

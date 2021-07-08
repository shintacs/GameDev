#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("SDLを初期化できません。: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter2)", 100, 100, 1024, 768, 0);
	if (mWindow)
	{
		SDL_Log("ウィンドウの作成に失敗しました。: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("レンダラーの作成に失敗しました。: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("SDL_imageを初期化できません。: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();	//TicksCountってなんだ？

	return false;
}

void Game::Runloop()
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
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

//動かすときに必要なものを入れるようにする（多分教科書の方で指示があると思う）

void Game::UpdateGame()
{
	//デルタタイムの計算
	//最後のフレームから16msだけ待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	//すべてのアクタを更新
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor -> Update(deltaTime);
	}

	//待ちになっていたアクターをmActorsに移動
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//死んだアクターを一時配列に追加
	std::vector<Actor*> deadActors;

	//死んだアクターを消去（mActorsから除去する）
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::UnloadData()
{
	//アクターの消去
	//~ActorはRemoveActorを呼ぶため、異なる形式のループを使う必要がある
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	//テクスチャの消去
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();

}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	//テクスチャがすでにマップにあるか確認
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//ファイルからのロード
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			//テクスチャのロードに失敗
			SDL_Log("テクスチャファイルのロードに失敗 %s", fileName.c_str());
			return nullptr;
		}

		//サーフェスからテクスチャを作成
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("テクスチャへの変換に失敗 %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//アクターの更新中なら待ちに追加
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	//ペンディングアクターか判定
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//最後のベクターと交換し、ポップ（コピーの消去を回避するため）
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	//アクターか判定
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//ベクターの最後と交換し、ポップ（コピーの消去を回避するため）
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

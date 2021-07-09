#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void Runloop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	//テクスチャマップのロード
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//ゲーム内のすべてのアクター
	std::vector<class Actor*> mActors;
	//ペンディングアクター
	std::vector<class Actor*> mPendingActors;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	//現在アクターをアップデートしているかトラックする
	bool mUpdatingActors;
};

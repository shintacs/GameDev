#pragma once

#include "SpriteComponent.h"
#include "Actor.h"
#include "Math.h"
#include <vector>

class BGSpriteComponent :public SpriteComponent
{
public:
	//描画順序の初期値は下げる（背景にするため）
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	//更新と描画は親からオーバーライドする
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	//背景用テクスチャを設定する
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	//画面サイズとスクロール速度の設定/取得
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	//個々の背景画像とオフセットをカプセル化する構造体
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

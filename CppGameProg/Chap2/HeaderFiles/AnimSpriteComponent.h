#pragma once

#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent :public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	//フレームごとにアニメーションを更新する
	void Update(float deltaTime) override;
	//キーボードの入力を受け取る
	void ProcessKeyboard(const uint8_t* state);
	//アニメーションに使うテクスチャを設定する
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	//アニメーションのFPSを設定/取得
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	//アニメーションでのすべてのテクスチャ
	std::vector<SDL_Texture*> mAnimTextures;
	//現在表示しているフレーム
	float mCurrFrame;
	//アニメーションのフレームレート
	float mAnimFPS;
	//表示するアニメーションの範囲
	float mStart;
	float mEnd;
};

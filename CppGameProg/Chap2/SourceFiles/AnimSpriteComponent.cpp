#include "AnimSpriteComponent.h"
#include "Math.h"
#include <iostream>

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
	, mStart(0.0f)
	, mEnd(4.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	if (mAnimTextures.size() > 0)
	{
		//フレームレートとデルタタイムに基づいて
		//カレントフレームを更新する
		mCurrFrame += mAnimFPS * deltaTime;

		//必要に応じてカレントフレームを巻き戻す
		while (mCurrFrame >= mEnd)
		{
			mCurrFrame -= mEnd;
			mCurrFrame += mStart;
		}

		//現時点のテクスチャを設定する
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::ProcessKeyboard(const uint8_t* state)
{
	if (state[SDL_SCANCODE_K])
	{
		mStart = 5.0f;
		mEnd = 17.0f;
	}
	if (state[SDL_SCANCODE_L])
	{
		mStart = 0.0f;
		mEnd = 4.0f;
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		//アクティブなテクスチャを最初のフレームにセット
		mCurrFrame = mStart;
		SetTexture(mAnimTextures[mCurrFrame]);
	}
}

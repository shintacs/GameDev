#pragma once
#include "SDL.h"
#include "Component.h"

class SpriteComponent :public Component
{
public:
	//描画順序が低いほど遠くに描かれる
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	int GetDraworder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	//描画するテクスチャ
	SDL_Texture* mTexture;
	//画家のアルゴリズムで使う描画順序
	int mDrawOrder;
	//テクスチャの幅と高さ
	int mTexWidth;
	int mTexHeight;
};

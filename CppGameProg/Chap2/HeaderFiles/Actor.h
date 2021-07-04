#pragma once
#include "Math.h"
#include <vector>

struct Vector2 
{
	float x;
	float y;
};

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	//コンストラクタ、デストラクタ
	Actor(class Game* game);
	virtual ~Actor();

	//ゲームから呼び出される更新関数（オーバーライド不可）
	void Update(float deltaTiime);
	//アクタが持つ全コンポーネントを更新（オーバーライド不可）
	void UpdateComponents(float deltaTime);
	//アクター独自の更新処理（オーバーライド可能）
	virtual void UpdateActor(float deltaTime);

	//ゲッター/セッター
	const Vector2& GetPosition() const { return mPosition;}
	void SetPosition(const Vector2& pos) { mPosition = pos;}
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	void RemoveComponent(class Component* component);
private:
	//アクターの状態
	State mState;	//列挙型のState
	//座標変換
	Vector2 mPosition;	//アクターの中心位置
	float mScale;	//アクターのスケール
	float mRotation;	//回転の角度(radian)
	//アクターがもつコンポーネント
	std::vector<class Component*> mComponents;
	class Game* mGame;
};

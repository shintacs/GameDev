#pragma once
#include <vector>
#include "Math.h"

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
	//アクター独自の更新処理（オーバーライド不可）
	virtual void UpdateActor(float deltaTime);

	//ゲッター/セッター

};

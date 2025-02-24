// Copyright (c) 2024, Noirkun All rights reserved.


#include "InGameGameMode.h"

#include "GameIns.h"
#include "InputPlayerController.h"

AInGameGameMode::AInGameGameMode()
{
	//プレイヤーコントローラーを設定
	PlayerControllerClass = AInputPlayerController::StaticClass();
}

void AInGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	//GameInsのインスタンスを取得
	GameIns = UGameIns::GetGameInstance();
	if (GameIns == nullptr)
	{
		return;
	}
	//ゲーム開始
	GameStart();

	HitCarEvent.AddDynamic(this, &AInGameGameMode::OnHitCar);
}

/**
 * @brief ゲーム開始
 */
void AInGameGameMode::GameStart()
{
	//各車のスピードやゲームエンドのフラグを設定
	GameIns->BlueCarSpeed = 1000.0f;
	GameIns->RedCarSpeed = 1000.0f;
	bGameEnd = false;
	//ABaseCarのIsHitをfalseに設定
	ABaseCar::SetIsHit(false);
	
}

//車が当たった時の処理
void AInGameGameMode::OnHitCar()
{
	bGameEnd = true;
	UE_LOG(LogTemp,Warning,TEXT("GameMode::Hit"));
}

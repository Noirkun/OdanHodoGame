// Copyright (c) 2024, Noirkun All rights reserved.


#include "InGameGameMode.h"

#include "GameIns.h"
#include "InputPlayerController.h"
#include "Kismet/GameplayStatics.h"

AInGameGameMode::AInGameGameMode()
{
	//プレイヤーコントローラーを設定
	PlayerControllerClass = AInputPlayerController::StaticClass();

	//Tickを有効にする
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
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

void AInGameGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetWorld()->IsPaused()でゲームが一時停止しているかどうかを確認
	UE_LOG(LogTemp,Warning,TEXT("GetWorld()->IsPaused():%d"),GetWorld()->IsPaused());
	
	//ゲームが終了していない場合,ゲームが一時停止していない場合
	if (!bGameEnd && !UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UE_LOG(LogTemp,Warning,TEXT("GameMode::Tick"));
		UpdateGameTime();
	}
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
	//ゲーム開始時間を取得
	StartTime = GetWorld()->GetTimeSeconds();
	
}

//車が当たった時の処理
void AInGameGameMode::OnHitCar()
{
	bGameEnd = true;
	UE_LOG(LogTemp,Warning,TEXT("GameMode::Hit"));

}

//ゲーム経過時間を更新する関数
void AInGameGameMode::UpdateGameTime()
{
	// ゲーム経過時間を加算
	GameTime = GetWorld()->GetTimeSeconds() - StartTime;
}

// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameGameMode.generated.h"

class UGameIns;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitCarEvent);
/**
 * ゲーム用のゲームモードクラス
 */
UCLASS()
class ODANHODOGAME_API AInGameGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AInGameGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	//ゲーム開始時の処理
	void GameStart();
	//車が当たった時の処理
	UFUNCTION()
	void OnHitCar();
	
	//ゲーム経過時間を更新する関数
	void UpdateGameTime();

	UPROPERTY()
	UGameIns* GameIns = nullptr;
	
	//ゲーム終了フラグ
	bool bGameEnd = false;
	
	//ゲーム開始時間
	float StartTime = 0.0f;

public:
	//車が当たった時のイベント
	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FHitCarEvent HitCarEvent;

	//ゲームの経過時間
	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
	float GameTime = 0.0f;

	//ゲームが終了したかどうかを取得する関数
	UFUNCTION(BlueprintPure, Category = "GameMode")
	bool GetGameEnd() const {return bGameEnd;}
};

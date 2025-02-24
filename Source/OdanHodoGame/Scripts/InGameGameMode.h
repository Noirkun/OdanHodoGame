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

private:
	void GameStart();
	
	UFUNCTION()
	void OnHitCar();

	UPROPERTY()
	UGameIns* GameIns = nullptr;
	
	//ゲーム終了フラグ
	bool bGameEnd = false;

public:
	//車が当たった時のイベント
	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FHitCarEvent HitCarEvent;

	//ゲームが終了した場合True
	bool GetGameEnd() const {return bGameEnd;}
};

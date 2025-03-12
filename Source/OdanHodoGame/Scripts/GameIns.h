// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Car/BaseCar.h"
#include "Engine/GameInstance.h"
#include "GameIns.generated.h"

enum class ECarColor : uint8;
/**
 * ゲーム全体で使う情報を管理するクラス
 */
UCLASS()
class ODANHODOGAME_API UGameIns : public UGameInstance
{
	GENERATED_BODY()

public:

	static UGameIns* GetGameInstance();

	//青の車の速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite,BlueprintSetter=SetBlueCarSpeed, Category = "GameIns", meta = (ClampMin = "0.0", ClampMax = "2000.0"))
	float BlueCarSpeed = 100.0f;
	//赤の車の速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite,BlueprintSetter=SetRedCarSpeed, Category = "GameIns", meta = (ClampMin = "0.0", ClampMax = "2000.0"))
	float RedCarSpeed = 100.0f;

	// 青い車のマックススピード
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameIns")
	float BlueCarMaxSpeed = 2000.0f;

	// 赤い車のマックススピード
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameIns")
	float RedCarMaxSpeed = 2000.0f;
	
	//青の車の速度をセットする関数
	UFUNCTION(BlueprintCallable, Category = "GameIns")
	void SetBlueCarSpeed(float Speed);

	//赤の車の速度をセットする関数
	UFUNCTION(BlueprintCallable, Category = "GameIns")
	void SetRedCarSpeed(float Speed);
	
	//青の車の速度を追加する関数
	UFUNCTION(BlueprintCallable, Category = "GameIns")
	void AddBlueCarSpeed(float AddSpeed);

	//赤の車の速度を追加する関数
	UFUNCTION(BlueprintCallable, Category = "GameIns")
	void AddRedCarSpeed(float AddSpeed);
	
	//選んでいる車の色
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameIns")
	ECarColor SelectPlayerCarColor = ECarColor::ECC_Blue;

	//現在プレイしているマップ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Level")
	TSoftObjectPtr<UWorld> PlayStageLevel;

	//MasterVolume・BGMVolume・SEVolumeを保存する変数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float MasterVolume = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float BGMVolume = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SEVolume = 1.0f;

	//プレイしているマップをセットする関数
	void SetPlayStageLevel(const TSoftObjectPtr<UWorld>& InStageLevel){ PlayStageLevel = InStageLevel; }
};

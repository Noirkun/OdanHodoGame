// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Styling/SlateBrush.h"
#include "StageDataAsset.generated.h"

/**
 * ステージセレクト用のデータを纏めるデータアセット
 */

USTRUCT(BlueprintType)
struct FStageStruct: public FTableRowBase
{
	GENERATED_BODY()

	//コンストラクト
	FStageStruct(): StageLevel(nullptr)
	{
	}

	FStageStruct(TSoftObjectPtr<UWorld> InStageLevel, FSlateBrush InIconImage): StageLevel(InStageLevel), StageImage(InIconImage){}
	
	// ステージ用のレベル
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> StageLevel;

	// ステージ用の画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush StageImage;
};

UCLASS()
class ODANHODOGAME_API UStageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// 実際のデータ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data Setting")
	TArray<FStageStruct> StageData;

	// データ取り込み用ファンクション
	UFUNCTION(CallInEditor)
	void LoadData();
};

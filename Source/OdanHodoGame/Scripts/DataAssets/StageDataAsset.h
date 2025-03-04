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
	FStageStruct(): StageLevel(nullptr), StageImage(nullptr)
	{
	}

	FStageStruct(FText StageName,TSoftObjectPtr<UWorld> InStageLevel, UTexture2D* InIconImage):
	StageName(StageName), StageLevel(InStageLevel), StageImage(InIconImage){}
	
	// ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText StageName;
	
	// ステージ用のレベル
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> StageLevel;

	// ステージ用の画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* StageImage;
};

UCLASS()
class ODANHODOGAME_API UStageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// 実際のデータ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data Setting")
	TArray<FStageStruct> StageData;

	/* データ取り込み用ファンクション
	UFUNCTION(CallInEditor)
	void LoadData();
	*/
	int32 GetStageDataNum() const;
};

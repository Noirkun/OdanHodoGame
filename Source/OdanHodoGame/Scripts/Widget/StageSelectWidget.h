// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OdanHodoGame/Scripts/DataAssets/StageDataAsset.h"
#include "StageSelectWidget.generated.h"

/**
 * ステージ選択用のWidgetクラス
 */
UCLASS()
class ODANHODOGAME_API UStageSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	//ステージデータアセット
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Setting")
	UStageDataAsset* StageDataAsset = nullptr;

	//StageDataAssetのデータ分ループする関数
	UFUNCTION()
	void LoopStageData(FStageStruct StageData);

	//BPでLoopstageを出す関数
	UFUNCTION(BlueprintImplementableEvent, Category = "StageSelect",meta = (ToolTip = "ステージの数だけループを行う関数"))
	void BP_LoopStageData(FStageStruct StageData);
	
};

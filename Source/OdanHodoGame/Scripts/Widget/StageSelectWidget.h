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

	//BPでLoopstageを出す関数
	UFUNCTION(BlueprintImplementableEvent, Category = "StageSelect",meta = (ToolTip = "ステージの数だけループを行う関数"))
	void BP_LoopStageData(FStageStruct StageData);

	//選ばれているステージのIndex
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Data Setting")
	int32 ForceIndex = 0;
private:
	//ステージデータアセット
	UPROPERTY(EditAnywhere, Category = "Data Setting")
	UStageDataAsset* StageDataAsset = nullptr;
	
	//StageDataAssetのデータ分ループする関数
	UFUNCTION()
	void LoopStageData(FStageStruct StageData);
	
	//! @brief HorizontalBoxのポジションを変える関数
	//! @param InXPos HorizontalBoxのX座標
	//! @param InYPos HorizontalBoxのY座標
	//! @param StageWidget ステージ画像のXサイズ
	//! @param PosXOffset X座標のオフセット
	//! @param PosX X座標の戻り値
	//! @param PosY Y座標の戻り値
	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void ScrollStageList(float InXPos,float InYPos,float StageWidget, float PosXOffset, float& PosX, float& PosY);
	
	
	
};

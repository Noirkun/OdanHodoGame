// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OdanHodoGame/Scripts/DataAssets/StageDataAsset.h"
#include "StageSelectWidget.generated.h"

class UTextBlock;
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
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Data Setting")
	int32 ForceIndex = 0;

	//選ばれているステージの名前
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Data Setting")
	FText ForceStageName;

	//選ばれているステージのレベル
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Data Setting")
	TSoftObjectPtr<UWorld> ForceStageLevel;

	//ステージの名前を表示するWidget
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* TitleText = nullptr;
	
private:
	//ステージデータアセット
	UPROPERTY(EditAnywhere, Category = "Data Setting")
	UStageDataAsset* StageDataAsset = nullptr;

	//ステージデータの数
	int32 StageDataNum = 0;
	
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

	//次のリストウィジェットに移動する関数
	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void NextListWidget();

	//前のリストウィジェットに移動する関数
	UFUNCTION(BlueprintCallable, Category = "StageSelect")
	void PrevListWidget();

	
	
};

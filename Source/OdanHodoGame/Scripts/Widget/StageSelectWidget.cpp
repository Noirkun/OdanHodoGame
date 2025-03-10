// Copyright (c) 2024, Noirkun All rights reserved.


#include "StageSelectWidget.h"
#include "Components/TextBlock.h"
#include "OdanHodoGame/Scripts/GameIns.h"

void UStageSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//ゲームインスタンスを取得
	GameIns = UGameIns::GetGameInstance();
	//ステージデータの数だけループ
	for (auto StageData : StageDataAsset->StageData)
	{
		LoopStageData(StageData);
		StageDataNum++;
		UE_LOG(LogTemp,Warning,TEXT("StageDataNum:%d"),StageDataNum);
	}
	//選ばれているステージの名前をステージデータの名前にする
	ForceStageName=StageDataAsset->StageData[ForceIndex].StageName;
	//選ばれているステージのレベルをステージデータのレベルにする
	ForceStageLevel=StageDataAsset->StageData[ForceIndex].StageLevel;

	//ステージの名前を表示するWidgetにステージの名前を入れる
	TitleText->SetText(ForceStageName);
	//ステージのレベルをゲームインスタンスに設定
	GameIns->SetPlayStageLevel(ForceStageLevel);
	
}

//BPでLoopstageを出す関数
void UStageSelectWidget::LoopStageData(FStageStruct StageData)
{
	BP_LoopStageData(StageData);
}

//HorizontalBoxのポジションを変える関数
void UStageSelectWidget::ScrollStageList(float InXPos, float InYPos, float StageWidget, float PosXOffset, float& PosX,
	float& PosY)
{
	//そのままHorizontalBoxのY軸を入れる
	PosY = InYPos;
	//選んでいるステージのIndexを元にポジションを計算
	float TempDestination=ForceIndex*StageWidget + PosXOffset;
	//X軸の移動の計算結果をいれる
	PosX=InXPos+(TempDestination-=InXPos)*0.1f;
}

//次のリストウィジェットに移動する関数
void UStageSelectWidget::NextListWidget()
{
	UE_LOG(LogTemp,Warning,TEXT("ForceIndex:%d"),ForceIndex);
	UE_LOG(LogTemp,Warning,TEXT("StageDataNum:%d"),StageDataNum);
	//選ばれているステージのIndexを増やす
	ForceIndex++;
	
	//選ばれているステージのIndexがステージデータの数より大きい場合
	if(ForceIndex>=StageDataNum)
	{
		//選ばれているステージのIndexを0に戻す
		ForceIndex = 0;
		//選ばれているステージの名前をステージデータの名前にする
		ForceStageName=StageDataAsset->StageData[ForceIndex].StageName;
		//選ばれているステージのレベルをステージデータのレベルにする
		ForceStageLevel=StageDataAsset->StageData[ForceIndex].StageLevel;
		//ゲームインスタンスにステージのレベルを設定
		GameIns->SetPlayStageLevel(ForceStageLevel);
	}
	else
	{
		//選ばれているステージの名前をステージデータの名前にする
		ForceStageName=StageDataAsset->StageData[ForceIndex].StageName;
		//選ばれているステージのレベルをステージデータのレベルにする
		ForceStageLevel=StageDataAsset->StageData[ForceIndex].StageLevel;
		//ゲームインスタンスにステージのレベルを設定
		GameIns->SetPlayStageLevel(ForceStageLevel);
	}
}

//前のリストウィジェットに移動する関数
void UStageSelectWidget::PrevListWidget()
{
	UE_LOG(LogTemp,Warning,TEXT("ForceIndex:%d"),ForceIndex);
	UE_LOG(LogTemp,Warning,TEXT("StageDataNum:%d"),StageDataNum);
	//選ばれているステージのIndexを減らす
	ForceIndex--;

	UE_LOG(LogTemp,Warning,TEXT("ForceIndex:%d"),ForceIndex);
	//選ばれているステージのIndexが0より小さい場合
	if(ForceIndex<0)
	{
		//選ばれているステージのIndexをステージデータの数-1にする
		ForceIndex = StageDataNum-1;
		//選ばれているステージの名前をステージデータの名前にする
		ForceStageName=StageDataAsset->StageData[ForceIndex].StageName;
		//選ばれているステージのレベルをステージデータのレベルにする
		ForceStageLevel=StageDataAsset->StageData[ForceIndex].StageLevel;
		//ゲームインスタンスにステージのレベルを設定
		GameIns->SetPlayStageLevel(ForceStageLevel);
	}
	else
	{
		//選ばれているステージの名前をステージデータの名前にする
		ForceStageName=StageDataAsset->StageData[ForceIndex].StageName;
		//選ばれているステージのレベルをステージデータのレベルにする
		ForceStageLevel=StageDataAsset->StageData[ForceIndex].StageLevel;
		//ゲームインスタンスにステージのレベルを設定
		GameIns->SetPlayStageLevel(ForceStageLevel);
	}
}



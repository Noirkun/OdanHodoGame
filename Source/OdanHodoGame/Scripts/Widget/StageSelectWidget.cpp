// Copyright (c) 2024, Noirkun All rights reserved.


#include "StageSelectWidget.h"


void UStageSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//ステージデータの数だけループ
	for (auto StageData : StageDataAsset->StageData)
	{
		LoopStageData(StageData);
	}
}

void UStageSelectWidget::LoopStageData(FStageStruct StageData)
{
	//BP用の関数を呼び出す
	BP_LoopStageData(StageData);
}

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



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

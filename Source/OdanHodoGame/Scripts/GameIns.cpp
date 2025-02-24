// Copyright (c) 2024, Noirkun All rights reserved.


#include "GameIns.h"


UGameIns* UGameIns::GetGameInstance()
{
	UGameIns* Instance = nullptr;

	if(GEngine)
	{
		//ワールド上にあるViewportを経由してInstanceを取得
		FWorldContext* WorldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		Instance = Cast<UGameIns>(WorldContext->OwningGameInstance);
	}
	return Instance;
}

void UGameIns::SetBlueCarSpeed(float Speed)
{
	//最大スピードよりも大きい場合は最大スピードにする
	if(BlueCarMaxSpeed < Speed)
	{
		BlueCarSpeed = BlueCarMaxSpeed;
	}
	else
	{
		BlueCarSpeed = Speed;
	}
	//0より小さい場合は0にする
	if(BlueCarSpeed+Speed < 0.0f)
	{
		BlueCarSpeed = 0.0f;
	}
}

void UGameIns::SetRedCarSpeed(float Speed)
{
	//最大スピードよりも大きい場合は最大スピードにする
	if(RedCarMaxSpeed < Speed)
	{
		RedCarSpeed = RedCarMaxSpeed;
	}
	else
	{
		RedCarSpeed = Speed;
	}
	//0より小さい場合は0にする
	if(BlueCarSpeed+Speed < 0.0f)
	{
		BlueCarSpeed = 0.0f;
	}
}

void UGameIns::AddBlueCarSpeed(float AddSpeed)
{
	//最大スピードよりも大きい場合は最大スピードにする
	if(BlueCarMaxSpeed < BlueCarSpeed + AddSpeed)
	{
		BlueCarSpeed = BlueCarMaxSpeed;
	}
	else
	{
		BlueCarSpeed += AddSpeed;
	}
	//0より小さい場合は0にする
	if(BlueCarSpeed+AddSpeed < 0.0f)
	{
		BlueCarSpeed = 0.0f;
	}
}

void UGameIns::AddRedCarSpeed(float AddSpeed)
{
	//最大スピードよりも大きい場合は最大スピードにする
	if(RedCarMaxSpeed < RedCarSpeed + AddSpeed)
	{
		RedCarSpeed = RedCarMaxSpeed;
	}
	else
	{
		RedCarSpeed += AddSpeed;
	}
	//0より小さい場合は0にする
	if(BlueCarSpeed+AddSpeed < 0.0f)
	{
		BlueCarSpeed = 0.0f;
	}
}

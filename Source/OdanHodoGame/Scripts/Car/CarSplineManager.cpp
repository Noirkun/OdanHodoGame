// Copyright (c) 2024, Noirkun All rights reserved.


#include "CarSplineManager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SplineComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "OdanHodoGame/Scripts/InGameGameMode.h"
#include "OdanHodoGame/Scripts/Car/BaseCar.h"

ACarSplineManager::ACarSplineManager()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject< USceneComponent >( TEXT( "RootComponent" ) );

	//PathからNS_Splineを取得してSplineNiagaraSystemに設定する
	if(UNiagaraSystem* SplineNiagaraObject=LoadObject<UNiagaraSystem>(NULL,TEXT("/Game/Game/Niagara/NS_Spline.NS_Spline")))
	{
		SplineNiagaraSystem=SplineNiagaraObject;
	}
	else
	{
		//Pathにアセットがない場合はエラーログを出力
		UE_LOG(LogTemp,Error,TEXT("CarSplineManager.cpp::SplineのNiagaraSystemが設定されていません。"));
	}
	
}

void ACarSplineManager::BeginPlay()
{
	Super::BeginPlay();

	//Hitした際のイベントをバインド
	TObjectPtr<AInGameGameMode> GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode((this)));
	GameMode->HitCarEvent.AddDynamic(this, &ACarSplineManager::OnHitEvent);

	// CarSplineInfoListのサイズをチェック
	if (CarSplineInfoList.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CarSplineManager.cpp::CarSplineInfoListが空です。"));
		return;
	}
	//CarSplineInfoListのサイズ分だけ車を生成
	for (int i=0;i<CarSplineInfoList.Num();i++)
	{
		if (!CarSplineInfoList.IsValidIndex(i))
		{
			UE_LOG(LogTemp, Error, TEXT("CarSplineManager.cpp::CarSplineInfoListのIndexが不正です。"));
			return;
		}
		UE_LOG(LogTemp,Warning,TEXT("CarSplineManager.cpp::SplineのPath：%s"),*CarSplineInfoList[i].SplineComponent->GetName());
		//NiagaraSystemの生成
		UNiagaraComponent* SplineNiagaraComponent=UNiagaraFunctionLibrary::SpawnSystemAttached(SplineNiagaraSystem,RootComponent,NAME_None,
			CarSplineInfoList[i].SplineComponent->SplineComponent->GetLocationAtSplinePoint(0,ESplineCoordinateSpace::World),
			CarSplineInfoList[i].SplineComponent->SplineComponent->GetRotationAtSplinePoint(0,ESplineCoordinateSpace::World),
			EAttachLocation::KeepRelativeOffset,true);
		//生成に失敗した場合はエラーログを出力
		if(SplineNiagaraComponent==nullptr)
		{
			UE_LOG(LogTemp,Error,TEXT("CarSplineManager.cpp::NiagaraSystemの生成に失敗しました。"));
			return;
		}
		//作ったコンポーネントを配列に追加
		NiagaraComponentArray.Add(SplineNiagaraComponent);
		//SplineNiagaraComponentにTargetPathという名前でスプラインのポイントの位置をセット
		UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(SplineNiagaraComponent,TEXT("TargetPath"),
				GetSplinePointLocations(CarSplineInfoList[i].SplineComponent->SplineComponent));
		
		//車の色によってNiagaraの色を変更
		switch (CarSplineInfoList[i].CarColor)
		{
		case ECarColor::ECC_Blue:
			SplineNiagaraComponent->SetColorParameter(TEXT("Car Color"),FLinearColor(0.0f,0.0f,1.0f));
			break;
		case ECarColor::ECC_Red:
			SplineNiagaraComponent->SetColorParameter(TEXT("Car Color"),FLinearColor(1.0f,0.0f,0.0f));
			break;
		}
		
		//タイマーの生成
		GameMode->GetWorld()->GetTimerManager().SetTimer(CarSplineInfoList[i].TimerHandle,[this,i]()
			{

			//ラムダ式でSpawnCarを呼び出し
SpawnCar(CarSplineInfoList[i].CarColor,CarSplineInfoList[i].SplineComponent);

			},CarSplineInfoList[i].CarSpawnTime,true);
	}
}

void ACarSplineManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//NiagaraComponentArrayのサイズ分だけNiagaraComponentを削除する
	for (int i=0;i<NiagaraComponentArray.Num();i++)
	{
		if (!NiagaraComponentArray.IsValidIndex(i))
		{
			UE_LOG(LogTemp, Error, TEXT("CarSplineManager.cpp::NiagaraComponentArrayのIndexがないものを指定しています。"));
			return;
		}
		NiagaraComponentArray[i]->DestroyComponent();
	}

	//CarSplineInfoListのサイズ分だけタイマーを削除する
	for (int i=0;i<CarSplineInfoList.Num();i++)
	{
		GetWorld()->GetTimerManager().ClearTimer(CarSplineInfoList[i].TimerHandle);
	}
}

//車を生成
void ACarSplineManager::SpawnCar(ECarColor _CarColor, ACarSpline* _SplineComponent)
{
	TObjectPtr<AInGameGameMode> GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode((this)));

	if (!_SplineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ACarSplineManager::SpawnCar - SplineComponentがありません"));
		return;
	}
	if (!GameMode->GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("ACarSplineManager::SpawnCar - GetWorld()が無効です"));
		return;
	}
	if(!ABaseCar::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("ACarSplineManager::SpawnCar - ABaseCarクラスがありません"));
		return;
	}
	
	//車の生成
	FTransform SplineTransform = _SplineComponent->GetActorTransform();
	TObjectPtr<AActor> SpawnActor;
	//自分で選択したクラスを使うかどうか
	if(bIsBaseCarClass)
	{
		//CustomBaseCarClassがあるかどうかをチェック
		if(CustomBaseCarClass)
		{
			//CustomBaseCarClassを使って車を生成
			SpawnActor = GameMode->GetWorld()->SpawnActor(CustomBaseCarClass, &SplineTransform);
		}
		//CustomBaseCarClassがない場合
		else
		{
			//ABaseCarクラスを使って車を生成
			SpawnActor = GameMode->GetWorld()->SpawnActor(ABaseCar::StaticClass(), &SplineTransform);
			UE_LOG(LogTemp, Error, TEXT("ACarSplineManager::SpawnCar - CustomBaseCarClassがないのでABaseCarクラスを使いスポーンしました"));
			return;
		}
	}
	//自分で選択したクラスを使わない場合
	else
	{
		//ABaseCarクラスを使って車を生成
		SpawnActor = GameMode->GetWorld()->SpawnActor(ABaseCar::StaticClass(), &SplineTransform);
	}

	//生成に失敗した場合はエラーログを出力
	if (!SpawnActor)
	{
		UE_LOG(LogTemp, Error, TEXT("ACarSplineManager::SpawnCar - 車が生成できませんでした"));
		return;
	}
	//生成した車がABaseCarクラスかどうかをチェック
	TObjectPtr<ABaseCar> CarActor = Cast<ABaseCar>(SpawnActor);
	if (!CarActor)
	{
		UE_LOG(LogTemp, Error, TEXT("ACarSplineManager::SpawnCar - 車がABaseCarクラスではありません"));
		return;
	}
	//車のInit関数を呼び出し
	CarActor->Init(_CarColor, _SplineComponent->SplineComponent);

}

void ACarSplineManager::OnHitEvent()
{
	//車のスポーンを止める
	for (int i=0;i<CarSplineInfoList.Num();i++)
	{
		GetWorld()->GetTimerManager().ClearTimer(CarSplineInfoList[i].TimerHandle);
	}
}

//スプラインの全てのポイントの位置を取得
TArray<FVector> ACarSplineManager::GetSplinePointLocations(USplineComponent* SplineComponent)
{
	TArray<FVector> SplinePointLocations;
	
	for(int i=0;i<SplineComponent->GetNumberOfSplinePoints();i++)
	{
		SplinePointLocations.Add(SplineComponent->GetLocationAtSplinePoint(i,ESplineCoordinateSpace::World));
	}
	return SplinePointLocations;
}

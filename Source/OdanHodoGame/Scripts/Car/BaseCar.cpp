// Copyright (c) 2024, Noirkun All rights reserved.


#include "BaseCar.h"
#include "../GameIns.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OdanHodoGame/Scripts/InGameGameMode.h"


// bHit 変数の初期化
bool ABaseCar::bHit = false;

// Sets default values
ABaseCar::ABaseCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//DefaultSceneRootの設定
	DefaultSceneRoot = CreateDefaultSubobject< USceneComponent >( TEXT( "DefaultSceneRoot" ) );
	RootComponent = DefaultSceneRoot;
	//SkeletalMeshComponentの設定
	CarMesh = CreateDefaultSubobject< USkeletalMeshComponent >( TEXT( "CarMesh" ) );
	CarMesh->SetupAttachment( RootComponent );
	CarMesh->SetSimulatePhysics(true);
	CarMesh->SetGenerateOverlapEvents(true);
	CarMesh->SetCollisionProfileName(TEXT("Vehicle"));
	CarMesh->PhysicsTransformUpdateMode = EPhysicsTransformUpdateMode::Type::ComponentTransformIsKinematic;
	
	//タグの追加
	Tags.Add(FName("Car"));
	//コリジョンの設定
	CarMesh->SetCollisionProfileName(TEXT("BlockAll"));
	CarMesh->SetSimulatePhysics(true);
	CarMesh->SetGenerateOverlapEvents(true);
	//Hitイベントを有効にする
	CarMesh->BodyInstance.SetInstanceNotifyRBCollision(true);

}

// Called when the game starts or when spawned
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();

	//コリジョンのイベントを追加
	CarMesh->OnComponentHit.AddDynamic(this, &ABaseCar::OnCarHitEvent);
	
}

//SpawnActorで呼び出したときに初期化する用の関数
void ABaseCar::Init(ECarColor _CarColor,TObjectPtr<class USplineComponent> _SplineComponent)
{
	//CarColorとSplineComponentを初期化
	CarColor=_CarColor;
	SplineComponent=_SplineComponent;
	USkeletalMesh* CarSkeletalMesh= LoadObject<USkeletalMesh>(NULL,TEXT("/Game/Vehicles/SportsCar/SKM_SportsCar.SKM_SportsCar"));
	//SkeletalMeshの設定
	CarMesh->SetSkeletalMesh(CarSkeletalMesh);

	//マテリアルの更新
	UpdateMaterial();
	//初期化完了
	bIsInit=true;
}



void ABaseCar::OnCarHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(!bHit)
	{
		TObjectPtr<AInGameGameMode> GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode((this)));
		UE_LOG(LogTemp,Warning,TEXT("Hit::OllHit"));
		if(GameMode==nullptr)
		{
			return;
		}
		//車が当たった時の処理を呼び出し
		if(OtherActor->ActorHasTag("Car"))
		{
			bHit=true;
			GameMode->HitCarEvent.Broadcast();
			UE_LOG(LogTemp,Warning,TEXT("Hit::Hit"));
		}
	}
}


void ABaseCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//初期化されていない場合は処理を行わない
	if(bIsInit==false)
	{
		return;
	}
	//現在の距離を更新
	if (CarColor == ECarColor::ECC_Blue || CarColor == ECarColor::ECC_Red)
	{
		SetCurrentDistance(CarColor, DeltaTime);
	}

}

/**
 * @brief 現在の距離を更新
 * @param _CarColor 車の色
 * @param _DeltaTime 経過時間
 */
void ABaseCar::SetCurrentDistance(ECarColor _CarColor, float _DeltaTime)
{
	//GameInsのインスタンスを取得
	UGameIns* GameIns = UGameIns::GetGameInstance();

	if(GameIns==nullptr)
	{
		return;
	}
	//CarColorによって速度を変更
	switch (_CarColor)
	{
		case ECarColor::ECC_Blue:
			CurrentDistance=CurrentDistance+(GameIns->BlueCarSpeed*_DeltaTime);
			break;

		case ECarColor::ECC_Red:
			CurrentDistance=CurrentDistance+(GameIns->RedCarSpeed*_DeltaTime);
			break;
	}

	//スプラインの位置と回転を取得し、車の位置をその場所に指定する
	CarMesh->SetWorldLocation(SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistance,ESplineCoordinateSpace::World),false,nullptr,ETeleportType::TeleportPhysics);
	CarMesh->SetWorldRotation(SplineComponent->GetRotationAtDistanceAlongSpline(CurrentDistance,ESplineCoordinateSpace::World),false,nullptr,ETeleportType::TeleportPhysics);
	//スプラインの長さを超えたら車を削除する
	if(SplineComponent->GetSplineLength()<=CurrentDistance)
	{
		Destroy();
	}
	
}

/**
 * @brief 車のマテリアルの更新
 */
void ABaseCar::UpdateMaterial()
{
	//マテリアルダイナミックインスタンスの作成
	if(CarMesh->GetMaterial(2)==nullptr)
	{
		return;
	}
	UMaterialInstanceDynamic* CarMaterialInstance = CarMesh->CreateDynamicMaterialInstance(2,CarMesh->GetMaterial(2));

	CarMesh->SetMaterial(2,CarMaterialInstance);
	//CarColorによってマテリアルの色を変更
	switch (CarColor)
	{
	case ECarColor::ECC_Blue:
		//MetalPartsTintの色を変更
		CarMaterialInstance->SetVectorParameterValue(FName("MetalPartsTint"),FLinearColor(0.0f,0.0f,1.0f));
		break;

	case ECarColor::ECC_Red:
		//MetalPartsTintの色を変更
		CarMaterialInstance->SetVectorParameterValue(FName("MetalPartsTint"),FLinearColor(1.0f,0.0f,0.0f));
		break;
	}
}
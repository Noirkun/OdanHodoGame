//// Copyright (c) 2024, Noirkun All rights reserved.


#include "SplineMovementComponent.h"

#include "Components/SplineComponent.h"

// Sets default values for this component's properties
USplineMovementComponent::USplineMovementComponent(): OwnerActor(GetOwner())
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick . bCanEverTick = true;

	// ...
}


// Called when the game starts
void USplineMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!SplineReference.OtherActor.IsValid())
	{
		return;
	}
	// アクターの参照からスプラインコンポーネントを取得
	//SplineComponent = Cast<USplineComponent>(SplineReference.GetComponent(nullptr));
	
	SplineComponent = Cast<USplineComponent>(SplineReference.OtherActor->GetComponentByClass(USplineComponent::StaticClass()));
}


// Called every frame
void USplineMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// スプラインコンポーネントが設定されていなければ何もせずreturn
	if (!SplineComponent.IsValid())
	{
		//UE_LOG(LogTemp, Warning, TEXT("SplineComponent is not valid."));
		return;
	}

	// コンポーネントを所持するアクターのポインタがなければ取得する
	if (OwnerActor == nullptr)
	{
		OwnerActor = GetOwner();
	}

	// 今回のフレームで移動する距離を算出
	float AddDistance = MoveSpeed * DeltaTime;

	// 現在の移動距離に上で算出した距離を足す
	CurrentMovedSplineDistance += AddDistance;

	// スプラインの全長を求める
	float SplineLength = SplineComponent->GetSplineLength();
	// 移動距離がスプラインの全長を超えていたらループさせる
	CurrentMovedSplineDistance = FMath::Fmod(CurrentMovedSplineDistance, SplineLength);

	// 移動距離からスプライン上のワールド座標を算出
	FVector TargetLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentMovedSplineDistance, ESplineCoordinateSpace::World);

	// 所持アクターの現在座標からTargetLocationに向けて補間をかけて移動させる
	FVector NextLocation = FMath::VInterpConstantTo(OwnerActor->GetActorLocation(), TargetLocation, DeltaTime, InterpSpeed);

	// 所持アクターに計算した座標に移動させる
	OwnerActor->SetActorLocation(NextLocation);
}


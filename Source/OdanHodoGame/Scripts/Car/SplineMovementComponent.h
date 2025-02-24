// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SplineMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODANHODOGAME_API USplineMovementComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USplineMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// スプラインを持つアクターの参照
	UPROPERTY(EditAnywhere)
	FComponentReference SplineReference;

	// 移動速度
	UPROPERTY(EditAnywhere)
	float MoveSpeed { 100.0f };

	// 補間速度
	UPROPERTY(EditAnywhere)
	float InterpSpeed{ 100.0f };

private:

	// コンポーネントを所持するアクター
	UPROPERTY()
	AActor* OwnerActor;
	
	// 移動用スプラインコンポーネント
	TWeakObjectPtr<class USplineComponent> SplineComponent;
	
	// スプライン上での移動距離
	float CurrentMovedSplineDistance{ 0.0f };

};

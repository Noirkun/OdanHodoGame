// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCar.generated.h"


/**
 * @brief 車の種類用のEnum
 */
UENUM(BlueprintType)
enum class ECarColor: uint8
{
	ECC_Blue UMETA(DisplayName = "Blue"),
	ECC_Red UMETA(DisplayName = "Red")
};

/**
 * 車の基底クラス
 */
UCLASS()
class ODANHODOGAME_API ABaseCar : public AActor
{
	GENERATED_BODY()

public:	
	ABaseCar();
	void Init(ECarColor _CarColor, TObjectPtr<class USplineComponent> _SplineComponent);

protected:
	UFUNCTION()
	void OnCarHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void BeginPlay() override;

	//車がぶつかったか
	static bool bHit;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static void SetIsHit(bool _bHit) {bHit=_bHit;}
	static bool GetIsHit() {return bHit;}

	
	//車の色
	UPROPERTY(BlueprintReadOnly)
	ECarColor CarColor=ECarColor::ECC_Blue;
	//つけるコンポーネント
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> CarMesh;
	
private:

	//現在の距離を更新
	void SetCurrentDistance(ECarColor _CarColor, float _DeltaTime);
	//マテリアルの更新
	void UpdateMaterial();
	
	//スプラインコンポーネント
	UPROPERTY()
	TObjectPtr<class USplineComponent> SplineComponent;

	//現在の距離
	UPROPERTY()
	float CurrentDistance = 0.0f;

	bool bIsInit=false;


	
};

// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCar.h"
#include "CarSpline.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "CarSplineManager.generated.h"


class UNiagaraComponent;
//class UNiagaraSystem;
// 車の生成で使う情報
USTRUCT(BlueprintType)
struct FCarSplineInfo
{
	GENERATED_BODY()

	//スプライン用のActor
	UPROPERTY(EditAnywhere,Category = "Car")
	TObjectPtr<ACarSpline> SplineComponent;
	
	//車の色
	UPROPERTY(EditAnywhere,Category = "Car")
	ECarColor CarColor = ECarColor::ECC_Blue;

	//車の生成間隔
	UPROPERTY(EditAnywhere,Category = "Car")
	float CarSpawnTime = 5.0f;

	//タイマー使う際に対応させるハンドル
	UPROPERTY()
	FTimerHandle TimerHandle;
};

/**
 * 車の生成を管理するクラス
 */
UCLASS()
class ODANHODOGAME_API ACarSplineManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACarSplineManager();
protected:
	UFUNCTION()

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:

	//自分で選択したクラスを使うかどうか
	UPROPERTY()
	bool bIsBaseCarClass = false;
	//デフォルト以外のスポーンさせるBaseCarを継承したBP
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsBaseCarClass"),Category = "Car")
	TSoftClassPtr<ABaseCar> CustomBaseCarClass;

	//スプラインに沿うNiagara
	UPROPERTY(EditDefaultsOnly,Category = "Car")
	UNiagaraSystem* SplineNiagaraSystem=LoadObject<UNiagaraSystem>(NULL,TEXT("/Game/Game/Niagara/NS_Spline.NS_Spline"));

	//車の情報を格納するリスト
	UPROPERTY(EditAnywhere,Category = "Car",meta = (TitleProperty = "CarColor"))
	TArray<FCarSplineInfo> CarSplineInfoList;

	//スポーンしたNiagaraComponentを格納する配列
	UPROPERTY(VisibleAnywhere,EditFixedSize,Category = "Effect")
	TArray<UNiagaraComponent*> NiagaraComponentArray;


	
	//車を生成
	UFUNCTION()
	void SpawnCar(ECarColor _CarColor, ACarSpline* _SplineComponent);

	//車が当たった時のイベント
	UFUNCTION()
	void OnHitEvent();
	
	//スプラインの全てのポイントの位置を取得する関数
	TArray<FVector> GetSplinePointLocations(USplineComponent* SplineComponent);
};

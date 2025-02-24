// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "CarSpline.generated.h"

/**
 *	車の移動ルート用のスプラインのアクタークラス
 */
UCLASS()
class ODANHODOGAME_API ACarSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarSpline();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	//スプライン
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;


};

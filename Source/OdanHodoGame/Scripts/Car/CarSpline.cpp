// Copyright (c) 2024, Noirkun All rights reserved.


#include "CarSpline.h"


ACarSpline::ACarSpline()
{
	PrimaryActorTick.bCanEverTick = true;

	//DefaultSceneRootの設定
	DefaultSceneRoot = CreateDefaultSubobject< USceneComponent >( TEXT( "RootComponent" ) );
	RootComponent = DefaultSceneRoot;

	//SplineComponentの設定
	SplineComponent = CreateDefaultSubobject< USplineComponent >( TEXT( "SplineComponent" ) );
	SplineComponent->SetupAttachment( RootComponent );

}

// Copyright (c) 2024, Noirkun All rights reserved.


#include "InputPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameIns.h"
#include "InGameGameMode.h"
#include "Car/BaseCar.h"
#include "Kismet/GameplayStatics.h"

AInputPlayerController::AInputPlayerController()
{
	
}

void AInputPlayerController::BeginPlay()
{
	Super::BeginPlay();
}



void AInputPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 入力を有効にする
	EnableInput(this);

	if (InputComponent)
	{
		// EnhancedInputComponentを取得する
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			//InputActionに関数をバインドする
			EnhancedInputComponent->BindAction(UpInput,ETriggerEvent::Triggered, this, &AInputPlayerController::OnUpInputPressed);
			EnhancedInputComponent->BindAction(DownInput, ETriggerEvent::Triggered, this, &AInputPlayerController::OnDownInputPressed);
			EnhancedInputComponent->BindAction(ChangeColorInput, ETriggerEvent::Triggered, this, &AInputPlayerController::OnChangeColorInputPressed);
		}

		// subsystemを取得する
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			// マッピングコンテキストを追加する
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

//UpInputが押された時の処理
void AInputPlayerController::OnUpInputPressed()
{
	//ゲームモードとゲームインスタンスを取得
	TObjectPtr<AInGameGameMode> GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(this));
	UGameIns* GameIns = UGameIns::GetGameInstance();
	
	if(GameMode)
	{
		//ボタンを押す際のSEを再生
		if(ButtonPressedSound)
		{
			UGameplayStatics::PlaySound2D(this, ButtonPressedSound);
		}
		//ゲームが終了していない場合
		if (!GameMode->GetGameEnd())
		{
			//選択されてる車のスピードを上げる
			switch (GameIns->SelectPlayerCarColor)
			{
				case ECarColor::ECC_Blue:
					GameIns->AddBlueCarSpeed(100.0f);
					break;
				case ECarColor::ECC_Red:
					GameIns->AddRedCarSpeed(100.0f);
					break;
				default:
					return;
			}
		}
	}
}

//DownInputが押された時の処理
void AInputPlayerController::OnDownInputPressed()
{
	//ゲームモードとゲームインスタンスを取得
	TObjectPtr<AInGameGameMode> GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(this));
	UGameIns* GameIns = UGameIns::GetGameInstance();
	
	if(GameMode)
	{
		//ゲームが終了していない場合
		if (!GameMode->GetGameEnd())
		{
			//ボタンを押す際のSEを再生
			if(ButtonPressedSound)
			{
				UGameplayStatics::PlaySound2D(this, ButtonPressedSound);
			}
			//選択されてる車のスピードを下げる
			switch (GameIns->SelectPlayerCarColor)
			{
			case ECarColor::ECC_Blue:
				GameIns->AddBlueCarSpeed(-100.0f);
				break;
			case ECarColor::ECC_Red:
				GameIns->AddRedCarSpeed(-100.0f);
				break;
			default:
				return;
			}
		}
	}
	
}

//ChangeColorInputが押された時の処理
void AInputPlayerController::OnChangeColorInputPressed()
{
	TObjectPtr<AInGameGameMode> GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(this));
	UGameIns* GameIns = UGameIns::GetGameInstance();

	if(GameMode)
	{
		//ゲームが終了していない場合
		if (!GameMode->GetGameEnd())
		{
			//ボタンを押す際のSEを再生
			if(ButtonPressedSound)
			{
				UGameplayStatics::PlaySound2D(this, ColorButtonPressedSound);
			}
			//選択されてる車の色を変更
			switch (GameIns->SelectPlayerCarColor)
			{
				case ECarColor::ECC_Blue:
					GameIns->SelectPlayerCarColor = ECarColor::ECC_Red;
					break;
				case ECarColor::ECC_Red:
					GameIns->SelectPlayerCarColor = ECarColor::ECC_Blue;
					break;
				default:
					return;
			}
		}
	}

}

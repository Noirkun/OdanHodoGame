// Copyright (c) 2024, Noirkun All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * プレイヤーの入力を管理するプレイヤーコントローラークラス
 */
UCLASS()
class ODANHODOGAME_API AInputPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AInputPlayerController();

protected:

	virtual void BeginPlay() override;


	virtual void SetupInputComponent() override;

	//インプットマッピング
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	//UpのInputAction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UpInput;

	//DownのInputAction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* DownInput;

	//ChangeColorのInputAction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ChangeColorInput;

	//ボタンを押す際のSE
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	USoundBase* ButtonPressedSound;

	//カラーボタンを押す際のSE
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	USoundBase* ColorButtonPressedSound;

	//Bindする関数
	void OnUpInputPressed();
	void OnDownInputPressed();
	void OnChangeColorInputPressed();

};

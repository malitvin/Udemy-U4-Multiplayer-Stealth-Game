// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode")
	void OnMissionCompleted(APawn* InstigatorPawn);

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

	UPROPERTY(EditDefaultsOnly, Category = "CameraPan")
	float _cameraPanOutTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "CameraPan")
	TEnumAsByte<EViewTargetBlendFunction> _blendType;
};




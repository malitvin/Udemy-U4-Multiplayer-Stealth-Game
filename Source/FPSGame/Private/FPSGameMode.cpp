// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* Instigator, bool bMissionSuccess)
{
	if (Instigator)
	{
		Instigator->DisableInput(nullptr);
		OnMissionCompleted(Instigator,bMissionSuccess);

		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			//Change view target for any actor found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];
				APlayerController* player = Cast<APlayerController>(Instigator->GetController());
				if (player)
				{
					player->SetViewTargetWithBlend(NewViewTarget, _cameraPanOutTime, _blendType);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectating Viewpoint class is nullptr.  Please update GameMode class with valid class."));
		}
	}
}

// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* Instigator, bool bMissionSuccess)
{
	if (Instigator)
	{
		OnMissionCompleted(Instigator,bMissionSuccess);

		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			//Change view target for any actor found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				//iterate over all player controllers
				for (FConstPlayerControllerIterator i = GetWorld()->GetPlayerControllerIterator(); i; i++)
				{
					APlayerController* PC = i->Get();
					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, _cameraPanOutTime, _blendType);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectating Viewpoint class is nullptr.  Please update GameMode class with valid class."));
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastOnMissionComplete(Instigator, bMissionSuccess);
	}
}

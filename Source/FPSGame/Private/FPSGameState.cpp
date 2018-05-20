// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"



void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool MissionSuccess)
{
	/*
	for (FConstPawnIterator i = GetWorld()->GetPawnIterator(); i;i++)
	{
		APawn* Pawn = i->Get();
		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}
	*/

	for (FConstPlayerControllerIterator i = GetWorld()->GetPlayerControllerIterator(); i; i++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(i->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, MissionSuccess);

			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(PC);
			}
		}
	}
}

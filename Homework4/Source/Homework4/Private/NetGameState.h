// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

class ANetPlayerState;
class ANetGameMode;


/**
 *
 */
UCLASS()
class ANetGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ANetGameState();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Winner)
	int WinningPlayer;

	UFUNCTION()
	void OnRep_Winner();

	UFUNCTION(BlueprintImplementableEvent)
	void OnVictory();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRestart();

	UFUNCTION(NetMulticast, Reliable)
	void TriggerRestart();

	UFUNCTION(BlueprintCallable)
	ANetPlayerState* GetPlayerStateByIndex(int PlayerIndex);

	UPROPERTY(BlueprintReadOnly)
	float GameTimer;

	FTimerHandle TimerHandle_GameTimer;

	UFUNCTION(BlueprintCallable)
	void StartGameTimer();

	UFUNCTION(NetMulticast, Reliable)
	void StopGameTimer();

	void UpdateGameTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimerDisplay();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RemainingTime)
	float RemainingTime;

	UFUNCTION()
	void OnRep_RemainingTime();
};
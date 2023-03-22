// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API USGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	USGGameInstance();

protected:

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;

	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName ServerName, bool bSucceeded);
	virtual void OnFindSessionComplete(bool bSucceeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void CreateServer();

	UFUNCTION(BlueprintCallable)
	void JoinServer();
};

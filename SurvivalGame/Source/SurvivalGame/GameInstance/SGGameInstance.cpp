// Fill out your copyright notice in the Description page of Project Settings.


#include "SGGameInstance.h"

#include "CreateSessionCallbackProxyAdvanced.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

USGGameInstance::USGGameInstance()
{
	
}

void USGGameInstance::Init()
{
	Super::Init();
	
	if(IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &USGGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USGGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &USGGameInstance::OnJoinSessionComplete);
		}
	}
	
}

void USGGameInstance::OnCreateSessionComplete(FName ServerName, bool bSucceeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, success - %d"), bSucceeded);
	if(bSucceeded)
	{
		GetWorld()->ServerTravel("/Game/Maps/M_Gym?listen");
	}
}

void USGGameInstance::OnFindSessionComplete(bool bSucceeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete, success - %d"), bSucceeded);
	if(bSucceeded)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = OnlineSessionSearch->SearchResults;
		
		UE_LOG(LogTemp, Warning, TEXT("SearchResults, session count - %d"), SearchResults.Num());
		
		if(SearchResults.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Joining server"));
			SessionInterface->JoinSession(0, "My session", SearchResults[0]);
		}
	}
}

void USGGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete"));
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if(JoinAddress != "")
		{
			PC->ClientTravel(JoinAddress, TRAVEL_Absolute);
		}
	}
}

void USGGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Create server"));
	
	FOnlineSessionSettings OnlineSessionSettings;
	OnlineSessionSettings.bAllowJoinInProgress = true;
	OnlineSessionSettings.bIsLANMatch = false;
	OnlineSessionSettings.bIsDedicated = true;
	OnlineSessionSettings.bShouldAdvertise = true;
	OnlineSessionSettings.bUsesPresence = true;
	OnlineSessionSettings.NumPublicConnections = 5;
	OnlineSessionSettings.bUseLobbiesIfAvailable = true;
	OnlineSessionSettings.bAllowInvites = true;
	
	SessionInterface->CreateSession(0, FName("MySession"), OnlineSessionSettings);
}

void USGGameInstance::JoinServer()
{
	OnlineSessionSearch = MakeShareable(new FOnlineSessionSearch());
	OnlineSessionSearch->bIsLanQuery = false;
	OnlineSessionSearch->MaxSearchResults = 150000;
	OnlineSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	
	SessionInterface->FindSessions(0, OnlineSessionSearch.ToSharedRef());
}

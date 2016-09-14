#pragma once

#include "GameFramework/Actor.h"
#include "Networking.h"
#include "CustomSendData.h"
#include "UDPReceiver.generated.h"

UCLASS()
class AUDPReceiver : public AActor
{
	GENERATED_UCLASS_BODY()

		//====================================================
		//		Data Received Events!
public:
	/** Data has been received!! */
	UFUNCTION(BlueprintImplementableEvent, Category = LiulongUDPReceiver)
		void BPEvent_DataReceived(const FCustomSendData& ReceivedData);

	//====================================================

public:
	FSocket* ListenSocket;

	FUdpSocketReceiver* UDPReceiver = nullptr;
	void Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt);

	bool StartUDPReceiver(
		const FString& YourChosenSocketName,
		const int32 ThePort,
		const FString& TheIP = "0.0.0.0"
		);

	//ScreenMsg
	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}


public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
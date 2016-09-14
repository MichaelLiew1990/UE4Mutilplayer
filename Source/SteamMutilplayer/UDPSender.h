#pragma once

#include "GameFramework/Actor.h"
#include "Networking.h"
#include "CustomSendData.h"
#include "UDPSender.generated.h"


UCLASS()
class AUDPSender : public AActor
{
	GENERATED_UCLASS_BODY()

		bool IsUDP;

	UFUNCTION(BlueprintCallable, Category = LiulongUDPSender)
		bool UDPSender_SendCustomData(FCustomSendData sendData);

public:
	TSharedPtr<FInternetAddr>	RemoteAddr;
	FSocket* SenderSocket;

	bool StartUDPSender(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
		);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Liulong UDP Sender")
		bool ShowOnScreenDebugMessages;


	//ScreenMsg
	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}


public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
#pragma once

#include "CustomSendData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FCustomSendData
{
	GENERATED_USTRUCT_BODY()
		FCustomSendData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		FString Name = "Victory!";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		int32 Count = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		float Scale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
		FLinearColor Color = FLinearColor::Red;
};

FORCEINLINE FArchive& operator<<(FArchive &Ar, FCustomSendData& TheStruct)
{
	Ar << TheStruct.Name;
	Ar << TheStruct.Count;
	Ar << TheStruct.Scale;
	Ar << TheStruct.Color;

	return Ar;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TextureToByteHelper.generated.h"


UCLASS( Blueprintable )
class KIP01_API UTextureToByteHelper : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTextureToByteHelper();

	/*Boundary level for the header*/
	UPROPERTY(BlueprintReadOnly, Category = "Boundaries")
	//FString BoundaryLabel = FString(TEXT("UnrealEngineBoundary-")) + FString::FromInt(FMath::Rand());
	FString BoundaryLabel;

	/*Boundary level for begining of every payload*/
	UPROPERTY(BlueprintReadOnly, Category = "Boundaries")
	//FString BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
	FString BoundaryBegin;

	/*Boundary level for the end of payload*/
	UPROPERTY(BLueprintReadOnly, Category = "Boundaries")
	//FString BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));
	FString BoundaryEnd;

	//Functions
	/* Conver the file in the path to bytes array*/
	UFUNCTION(BlueprintCallable, Category = "FileManagement")
	void Convert(bool& Ok, FString& OutBoundary, TArray<uint8>& OutReqBody, FString FullFilePath);

    /* Initialize helper with default boundary labels */
    UFUNCTION(BlueprintCallable, Category = "Initialization")
    void Initialize();	
};

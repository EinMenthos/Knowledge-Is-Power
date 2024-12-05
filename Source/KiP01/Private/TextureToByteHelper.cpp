// Fill out your copyright notice in the Description page of Project Settings.


#include "TextureToByteHelper.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"

// Sets default values for this component's properties
UTextureToByteHelper::UTextureToByteHelper()
{
    Initialize();
}

void UTextureToByteHelper::Initialize()
{
    BoundaryLabel = FString(TEXT("UnrealEngineBoundary-")) + FString::FromInt(FMath::Rand());
    BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
    BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));
    UE_LOG(LogTemp, Log, TEXT("Object initialized!"));

}

void UTextureToByteHelper::Convert(bool& Ok, FString& OutBoundary, TArray<uint8>& OutReqBody, FString FullFilePath)
{
    FString FileNameL = FPaths::GetCleanFilename(FullFilePath);
    FString BodyL;

    TArray<uint8> FileRawData;
    bool OkL = FFileHelper::LoadFileToArray(FileRawData, *FullFilePath);

    if (OkL)
    {
        BodyL += BoundaryBegin;
        BodyL += "Content-Disposition: form-data; name=\"file\"; filename=\"" + FileNameL + "\"\r\n";
        BodyL += "Content-Type: application/octet-stream\r\n\r\n";

        TArray<uint8> BodyData;
        FTCHARToUTF8 Converter(*BodyL);
        BodyData.Append((const uint8*)&Converter.Get()[0], Converter.Length());
        BodyData.Append(FileRawData);

        FTCHARToUTF8 FinalBoundaryConverter(*BoundaryEnd);
        BodyData.Append((const uint8*)&FinalBoundaryConverter.Get()[0], FinalBoundaryConverter.Length());

        OutBoundary = BoundaryLabel;
        OutReqBody = BodyData;
    }

    Ok = OkL;
}

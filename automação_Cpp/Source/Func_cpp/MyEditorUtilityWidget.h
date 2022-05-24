// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/ReflectionCapture.h"
#include "Engine/SkyLight.h"
#include "Engine/Texture.h"

#include "MyEditorUtilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUNC_CPP_API UMyEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FString FolderPath = FString("/Game");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bRecursive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrganizeWorldOutliner")//aqui vc vai ajustar as classes e nome de pastas que voce quer inserir
	TMap<UClass*, FName> FolderMap = {
		{AStaticMeshActor::StaticClass(), "Static Meshes"},
		{AReflectionCapture::StaticClass(), "ReflectionCaptures"},
		{ASkyLight::StaticClass(), "Lights"}
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureParams")
	bool bSetRGB = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureParams")
	TEnumAsByte<TextureCompressionSettings> Compression = TEnumAsByte<TextureCompressionSettings>(TextureCompressionSettings::TC_Masks);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "textureParams")//parametros do Set texture paramateres
	TArray<FString> LinearColorPattern = {
		TEXT("_ORM"),
		TEXT("_OcclusionRoughnessMetallic"),
		TEXT("_Metallic"),
		TEXT("_Roughness"),
		TEXT("_Mask")
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchAndReplace")
	FString SearchPattern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchAndReplace")
	FString ReplacePattern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchAndReplace")
	TEnumAsByte<ESearchCase::Type> SearchCase;//caso sensitivo � se as letras maiusculas e minisculas vao fazer diferen�a ou nao

	UFUNCTION(CallInEditor, BlueprintCallable)
	void OrganizeWorldOutliner();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void DeleteNullSMActors();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void SetTextureParameter();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void SearchAndReplace();
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void DeleteEmptyFolder();
};

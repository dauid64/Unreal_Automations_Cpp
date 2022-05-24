// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEditorUtilityWidget.h"
#include "EditorLevelLibrary.h"
#include "EditorAssetLibrary.h"

#pragma region OrganizeWorldOutliner
void UMyEditorUtilityWidget::OrganizeWorldOutliner()
{
	TArray<AActor*> AllActors = UEditorLevelLibrary::GetAllLevelActors();
	for (AActor* Actor : AllActors)//for para pegar todos os actors do array
	{
		if (ensure(Actor))
		{
			const FName* FolderName = FolderMap.Find(Actor->GetClass());//se ele encontrar no foldermap a classe do actor
			if (ensure(FolderName))
			{
				Actor->SetFolderPath(*FolderName);//ele o adiciona na pasta correspondente
			}
		}
	}
}
#pragma endregion

#pragma region DeleteNullSMActors

void UMyEditorUtilityWidget::DeleteNullSMActors()
{
	TArray<AActor*> AllActors = UEditorLevelLibrary::GetAllLevelActors();//pegando todos os actors e colocando no array
	for (AActor* Actor : AllActors)//verificando um por um
	{
		if (ensure(Actor))//verificando se existe um actor
		{
			AStaticMeshActor* StaticMeshActor = dynamic_cast<AStaticMeshActor*>(Actor);
			if (ensure(StaticMeshActor))
			{
				UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();//obtendo o static mesh component
				if (ensure(StaticMeshComponent) && nullptr == StaticMeshComponent->GetStaticMesh())//verificando se tem ou nao o static mesh component, se nao, deletar
				{
					Actor->Destroy();//destruindo o actor
				}
			}
		}
	}
}

#pragma endregion

#pragma region SetTextureParameter

void UMyEditorUtilityWidget::SetTextureParameter()
{
	TArray<FString> AssetsInPath = UEditorAssetLibrary::ListAssets(FolderPath, bRecursive, false);
	for (FString AssetPath : AssetsInPath)
	{
		for (FString Pattern : LinearColorPattern)
		{
			if (AssetPath.Contains(Pattern))
			{
				UObject* Object = UEditorAssetLibrary::LoadAsset(AssetPath);
				if (!ensure(Object))
				{
					return;
				}
				UTexture2D* Texture = dynamic_cast<UTexture2D*>(Object);
				if (ensure(Texture))
				{
				Texture->SRGB = bSetRGB;//desligando o RGB
				Texture->CompressionSettings = Compression;//adicionando a mask
				}
			}
		}
	}
}

#pragma endregion

#pragma region SearchAndReplace

void UMyEditorUtilityWidget::SearchAndReplace()
{
	TArray<FString> AssetsInPath = UEditorAssetLibrary::ListAssets(FolderPath, bRecursive, false);//Pegando todos os assets
	for (FString AssetPath : AssetsInPath)
	{
		FString FileName = FPaths::GetCleanFilename(AssetPath);
		if (FileName.Contains(SearchPattern, SearchCase))
		{
			FString NewAssetName = FileName.Replace(*SearchPattern, *ReplacePattern, SearchCase);
			FString NewAssetPath = FPaths::Combine(FPaths::GetPath(AssetPath), NewAssetName);
			UEditorAssetLibrary::RenameAsset(AssetPath, NewAssetPath);//renomeando os assets
		}
	}
}

#pragma endregion

#pragma region DeleteEmptyFolders

void UMyEditorUtilityWidget::DeleteEmptyFolder()
{
	TArray<FString> AssetsInPath = UEditorAssetLibrary::ListAssets(FolderPath, bRecursive, true);
	for (FString Asset : AssetsInPath)
	{
		if (!UEditorAssetLibrary::DoesDirectoryHaveAssets(Asset, bRecursive))
		{
			UEditorAssetLibrary::DeleteDirectory(Asset);
		}
	}
}

#pragma endregion
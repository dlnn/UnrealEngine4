// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Paper2DEditorPrivatePCH.h"

#include "AtlasAssetTypeActions.h"
#include "AssetData.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

//////////////////////////////////////////////////////////////////////////
// FAtlasAssetTypeActions

FText FAtlasAssetTypeActions::GetName() const
{
	return LOCTEXT("FAtlasAssetTypeActionsName", "Sprite Atlas Group");
}

FColor FAtlasAssetTypeActions::GetTypeColor() const
{
	return FColor(0, 255, 255);
}

UClass* FAtlasAssetTypeActions::GetSupportedClass() const
{
	return UPaperSpriteAtlas::StaticClass();
}

void FAtlasAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	//@TODO: Atlas will need a custom editor at some point
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}

uint32 FAtlasAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FAtlasAssetTypeActions::GetAssetDescription(const FAssetData& AssetData) const
{
	if (const FString* pDescription = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UPaperSpriteAtlas, AtlasDescription)))
	{
		if (!pDescription->IsEmpty())
		{
			const FString DescriptionStr(*pDescription);
			return FText::FromString(DescriptionStr.Replace(TEXT("\\n"), TEXT("\n")));
		}
	}

	return FText::GetEmpty();
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
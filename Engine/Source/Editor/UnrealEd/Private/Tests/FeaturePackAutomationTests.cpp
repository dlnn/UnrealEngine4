// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnrealEd.h"

#include "Tests/AutomationTestSettings.h"

#if WITH_EDITOR
#include "FileHelpers.h"
#include "LevelEditor.h"
#include "AutomationEditorCommon.h"
#endif

#include "AssetSelection.h"
#include "AutomationCommon.h"
#include "AutomationTest.h"
#include "FeaturePackContentSource.h"

DEFINE_LOG_CATEGORY_STATIC(FeaturePackAutomationTestLog, Log, All);

// 
// namespace FeaturePackAutomationTests
// {
// }

/**
 * Feature Pack validity test
 */
IMPLEMENT_SIMPLE_AUTOMATION_TEST( FFeaturePackValidityTest, "System.Editor.Content.FeaturePackValidityTest", EAutomationTestFlags::ATF_Editor )

/** 
 * Scans feature pack folder and verifies that all feature packs therein are parsed successfully.
 *
 * @param Parameters - Unused for this test
 * @return	TRUE if the test was successful, FALSE otherwise
 */
bool FFeaturePackValidityTest::RunTest(const FString& Parameters)
{
	FString FeaturePackPath = FPaths::FeaturePackDir();
	FeaturePackPath += TEXT("*.upack");
	int32 FailCount = 0;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	TArray<FString> FeaturePacks;
	IFileManager::Get().FindFiles(FeaturePacks, *FeaturePackPath, true, false );

	for (auto FeaturePackFile : FeaturePacks)
	{
		TUniquePtr<FFeaturePackContentSource> NewContentSource = MakeUnique<FFeaturePackContentSource>(FPaths::FeaturePackDir() + FeaturePackFile, true);
		if (NewContentSource->IsDataValid() == false)
		{
			FailCount++;
			for (int32 iError = 0; iError < NewContentSource->ParseErrors.Num() ; iError++)
			{
				AddError(NewContentSource->ParseErrors[iError]);
			}
			
		}
	}
	
	return FailCount==0;
}

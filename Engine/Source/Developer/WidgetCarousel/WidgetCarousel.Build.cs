// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WidgetCarousel : ModuleRules
{
	public WidgetCarousel(TargetInfo Target)
	{
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"Slate",
				"SlateCore",
				"InputCore",
				"EditorStyle",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"Developer/WidgetCarousel/Private",
			}
		);
	}
}

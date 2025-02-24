// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OdanHodoGame : ModuleRules
{
	public OdanHodoGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "PhysicsCore", "Niagara","SlateCore" });
	}
}

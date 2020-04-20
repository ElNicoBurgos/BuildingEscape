// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BuildingEscape_4_20Target : TargetRules
{
	public BuildingEscape_4_20Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "BuildingEscape_4_20" } );
	}
}

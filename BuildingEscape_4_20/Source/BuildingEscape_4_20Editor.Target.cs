// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BuildingEscape_4_20EditorTarget : TargetRules
{
	public BuildingEscape_4_20EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        bUseUnityBuild = false;
        bUsePCHFiles = false;
		ExtraModuleNames.AddRange( new string[] { "BuildingEscape_4_20" } );
	}
}

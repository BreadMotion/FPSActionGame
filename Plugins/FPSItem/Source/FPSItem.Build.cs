using UnrealBuildTool;

public class FPSItem : ModuleRules
{
    public FPSItem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "GameplayTasks",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                //"CoreModule", // あなたの Core モジュール名に合わせる
            }
        );

        // PublicIncludePaths.AddRange(new string[] { "FPSCore/Source/Core/" });
        // PrivateIncludePaths.AddRange(new string[] { "FPSCore/Source/Core/" });
    }
}

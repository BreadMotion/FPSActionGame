using UnrealBuildTool;

public class FPSCore : ModuleRules
{
    public FPSCore(ReadOnlyTargetRules Target) : base(Target)
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
                "FPSSystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                //"CoreModule", // あなたの Core モジュール名に合わせる
            }
        );

        PublicIncludePaths.AddRange(new string[] { "FPSSystem/Source" });
        // PrivateIncludePaths.AddRange(new string[] { "FPSCore/Source/Core/" });
    }
}

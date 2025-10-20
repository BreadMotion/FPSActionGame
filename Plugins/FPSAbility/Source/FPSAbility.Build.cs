using UnrealBuildTool;

public class FPSAbility : ModuleRules
{
    public FPSAbility(ReadOnlyTargetRules Target) : base(Target)
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

        // PublicIncludePaths.AddRange(new string[] { "System/Public" });
        // PrivateIncludePaths.AddRange(new string[] { "System/Private" });
    }
}

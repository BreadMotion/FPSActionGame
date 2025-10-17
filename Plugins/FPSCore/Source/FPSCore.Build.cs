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
            }
        );

        PublicIncludePaths.AddRange(new string[] { "FPSSystem/Source" });
    }
}

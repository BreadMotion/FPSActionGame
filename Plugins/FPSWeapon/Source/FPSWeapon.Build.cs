using UnrealBuildTool;

public class FPSWeapon : ModuleRules
{
    public FPSWeapon(ReadOnlyTargetRules Target) : base(Target)
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
            }
        );

        // PublicIncludePaths.AddRange(new string[] { "FPSCore/Source/Core/" });
        // PrivateIncludePaths.AddRange(new string[] { "FPSCore/Source/Core/" });
    }
}

#pragma once
#include "CoreMinimal.h"
#include "FPSSystem/BaseSystem.h"
#include "FPSData/BaseData.h"
#include "DataSystem.generated.h"

/**
 * @class UDataSystem
 * @brief データ管理を行うサブシステムクラス
 */
UCLASS()
class FPSACTIONGAME_API UDataSystem : public UBaseSystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& _collection) override;
	virtual void Deinitialize() override;

private:
	TArray<UBaseData> m_dataArray;
};

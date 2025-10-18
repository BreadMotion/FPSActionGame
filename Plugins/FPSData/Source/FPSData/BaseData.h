#pragma once
#include "CoreMinimal.h"
#include "BaseData.generated.h"

/**
 * @class FBaseData
 * @brief 基本データクラス
 * @details
 * - 基本的なデータ構造
 */ 
UCLASS(BlueprintType)
class FPSDATA_API UBaseData : public UObject 
{
	GENERATED_BODY()

public:
	UBaseData();
	~UBaseData();

public:
	/** @brief データID */
	UPROPERTY()
	uint8 m_dataID;
	
	/** @brief データカテゴリID */
	UPROPERTY()
	uint8 m_categoryID;

	/** @brief 無視属性 */
	UPROPERTY()
	bool m_ignore;
};

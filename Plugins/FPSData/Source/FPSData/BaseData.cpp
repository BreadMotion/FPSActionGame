#include "BaseData.h"

/**
 * @brief コンストラクタ
 * @details
 * - データID初期化
 * - カテゴリID初期化
 * - 無視フラグ初期化
 */
UBaseData::UBaseData()
{
	m_dataID = 0;
	m_categoryID = 0;
	m_ignore = 0;
}

/**
 * @brief デストラクタ
 */
UBaseData::~UBaseData()
{
}

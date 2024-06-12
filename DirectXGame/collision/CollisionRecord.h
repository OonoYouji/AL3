#pragma once

#include <cmath>
#include <vector>

/// <summary>
/// 衝突記録クラス
/// </summary>
class CollisionRecord {
public:

	CollisionRecord();
	~CollisionRecord();

public:

	/// <summary>
	/// ログの追加
	/// </summary>
	/// <param name="log"></param>
	void AddLog(uint32_t log);
	
	/// <summary>
	/// ログを確認
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	bool CheckLog(uint32_t number);

	/// <summary>
	/// ログの消去
	/// </summary>
	void Clear();

private:

	std::vector<uint32_t> logs_;

};



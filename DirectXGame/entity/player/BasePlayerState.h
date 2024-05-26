#pragma once 


class Player;

/// <summary>
/// Playerの行動の基底クラス
/// </summary>
class BasePlayerState {
public:

	virtual ~BasePlayerState() = default;

	virtual void Update(Player* player) = 0;

};
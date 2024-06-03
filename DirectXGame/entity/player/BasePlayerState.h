#pragma once 


class Player;

/// <summary>
/// Playerの行動の基底クラス
/// </summary>
class BasePlayerState {
public:

	virtual ~BasePlayerState() = default;

	virtual void Update() = 0;

	void SetPlayer(Player* player) {
		pPlayer_ = player;
	}

protected:

	Player* pPlayer_ = nullptr;

};
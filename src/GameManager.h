#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h";

class GameManager
{
public:
protected:
private:
	int iTurns;
	int iScore;

	Player player;

public:
	GameManager();
	~GameManager() = default;

	static GameManager* GetInstance();

	void Init();
	void Run();
	Player& GetPlayer();
	int GetRemainingTurns() const;
	void RemoveTurns(int _turns);
	void AddScore(int _iScore);
protected:
private:
};

#endif // GAMEMANAGER_H


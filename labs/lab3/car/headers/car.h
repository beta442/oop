#include "std_lib.h"

enum class Gear
{
	REAR = -1,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
};

enum struct MoveDirection
{
	BACKWARD = -1,
	STAY,
	FORWARD,
};

class CCar
{
public:
	CCar();
	~CCar();

	bool IsTurnedOn();
	MoveDirection GetDirection();
	Gear GetGear();
	int GetSpeed();

	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool TurnOffEngine();
	bool TurnOnEngine();

private:
	bool m_isEngineOn;
	MoveDirection m_direction;
	Gear m_gear;
	int m_speed;
};

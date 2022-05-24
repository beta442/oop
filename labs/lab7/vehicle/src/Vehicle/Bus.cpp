#include "../../headers/Vehicle/Bus.h"

Bus::Bus(size_t maxCapacity)
	: VehicleImpl<IPerson, IBus>(maxCapacity)
{
}

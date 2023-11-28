#include "Header.h"
#include "CF.h"

#include <chrono>
#include <thread>

int main()
{
	printf(
		"PAGE %i FOR TODAY'S DATA\n"
		, getDate() + 15
	);

	latitudeSunMerPas();

	while (true)
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

	return 0;
}
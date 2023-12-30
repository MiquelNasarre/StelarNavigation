#include "CF.h"

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

float* inputCoor()
{
	float* angles = (float*)calloc(2, sizeof(float));

	float deg, min;
	char p;

	printf("latitude    ");
	scanf("%f %f %c", &deg, &min, &p);

	angles[0] = deg + min / 60.f;
	if (p == 'S' || p == 's')
		angles[0] *= -1.f;

	printf("Longitude   ");
	scanf("%f %f %c", &deg, &min, &p);

	angles[1] = deg + min / 60.f;
	if (p == 'E' || p == 'e')
		angles[1] *= -1.f;

	return angles;
}

float inputTime(const char* text, bool seconds)
{
	float hour, min, sec;

	printf("%s", text);

	if (seconds)
	{
		scanf("%f %f %f", &hour, &min, &sec);

		return hour + min / 60.f + sec / 3600.f;
	}
	else
	{
		scanf("%f %f", &hour, &min);

		return hour + min / 60.f;
	}

}

int getDate(bool print)
{
	time_t now = time(0);

	if (print)
		printf("%s", ctime(&now));

	long long days = now / 86400 - 365 * 53 - 12;

	return int(days);
}
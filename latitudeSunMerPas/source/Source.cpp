#include "Header.h"
#include "CF.h"
#include <iostream>

void latitudeSunMerPas()
{
	printf("\nPROGRAM\n1: TIME OF PASSAGE\n2: LATITUDE BY ALTITUDE & DECLINATION\n");

	int i;
	scanf("%i", &i);

	switch (i)
	{
	case 1:
		calculateTimePassage();
		break;
	case 2:
		calculateLatitude();
		break;
	default:
		printf("Invalid number");
		break;
	}
}

void calculateTimePassage()
{
	printf("\nALMANACH TIME PASSAGE\t");
	float t = inputTime("");

	float L, Lmin;
	char c;

	printf("\nESTIMATED LONGITUDE\t");
	scanf("%f %f %c", &L, &Lmin, &c);
	
	L += Lmin / 60.f;
	if (c == 'E' || c == 'e')
		L *= -1;

	float T = t + L / 15.f;

	if (T >= 24.f)
		T -= 24.f;
	if (T < 0.f)
		T += 24;

	printf(
		"\nYOUR TIME OF PASSAGE\n"
		"%ih %.1fmin\t %ih %imin %isec\n"

		, int(T), (T - int(T)) * 60.f
		, int(T), int((T - int(T)) * 60.f), int(((T - int(T)) * 60.f - int((T - int(T)) * 60.f)) * 60)
	);
}

void calculateLatitude()
{
	printf("\nINTERPOLATE DECLINATION\n");

	float t0 = inputTime("TIME\t");

	float d0, d0min;

	printf("DEC\t");
	scanf("%f %f", &d0, &d0min);

	printf("\n");

	float t1 = inputTime();

	float d1, d1min;

	printf("DEC\t");
	scanf("%f %f", &d1, &d1min);

	float t = inputTime("\nCURRENT TIME\t");

	if (d0 >= 0)
		d0 += d0min / 60.f;
	else
		d0 -= d0min / 60.f;

	if (d1 >= 0)
		d1 += d1min / 60.f;
	else
		d1 -= d1min / 60.f;

	if (t0 > t1)
		t1 += 24.f;

	float d = (d1 * (t - t0) - d0 * (t - t1)) / (t1 - t0);

	float a, amin;

	printf("\nALTITUDE\t");
	scanf("%f %f", &a, &amin);

	a += amin / 60.f;

	float l = 90 - a + d;

	char c = 'N';
	if (l < 0)
	{
		c = 'S';
		l *= -1;
	}

	printf(
		"\nYOUR LATITUDE\n"
		"%.3f%c %c\t%i%c %.2f%c %c\n"
		, l, 248, c
		, int(l), 248, (l - int(l)) * 60.f, '\'', c
	);

}

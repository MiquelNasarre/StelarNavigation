#include "Header.h"
#include "CF.h"

#include <stdio.h>
#include <iostream>

float* tripCalculator(bool simple)
{
	float* Coor;

	float time;
	float speed;
	float course;

	if (!simple)
		printf(
			"\nTo be able to calculate your estimated position we're going to need multiple\n"
			"things. First your last known position, the time it was at that moment, the\n"
			"boat speed and the course.\n"
			"Once that is known we can add as many legs as needed providing speeds, direction\n"
			"and time stamps for each of them.\n"

		);

	printf("\nLAST KNOWN POSITION\n\n");

	Coor = inputCoor();

	printf("\n");

	time = inputTime("TIME\t");

	printf("SPEED\t");
	scanf("%f", &speed);

	printf("COURSE\t");
	scanf("%f", &course);

	if (!simple)
		printf(
			"\nNow here you can enter as much course changes as you want giving the time, speed\n"
			"and direction of every interval. If you kept the same course all the way write 0.\n"
		);

	printf("\nCOURSE CHANGES\t");

	unsigned int n;

	scanf("%u", &n);

	float* waypoints = (float*)calloc(n * 3, sizeof(float));

	for (unsigned int i = 0; i < n; i++)
	{
		printf("\nWAYPOINT %u\n", i + 1);

		waypoints[3 * i] = inputTime("TIME\t");

		printf("SPEED\t");
		scanf("%f", &waypoints[3 * i + 1]);

		printf("COURSE\t");
		scanf("%f", &waypoints[3 * i + 2]);
	}

	if (!simple)
		printf("\nFinally we need to know the current time to calculate your current estimated position.\n\n");

	float timef = inputTime("\nCURRENT TIME   ");

	printf("\n");

	for (unsigned int i = 0; i <= n; i++)
	{
		float dt = timef - time;
		if (i != n)
			dt = waypoints[3 * i] - time;
		if (dt < 0)
			dt += 24.f;

		float v = speed;
		float li = Coor[0];
		float Li = Coor[1];
		float c = deg_rad * course;

		float d = v * dt;
		float dl = d * cosf(c) / 60.f;
		float lf = li + dl;

		float dL = d * sinf(c) / cosf(((li + lf) / 2.f) * deg_rad) / 60.f;
		float Lf = Li - dL;

		if (lf > 90 || lf < -90)
			printf(
				"The approximations won't work correctly for courses this close to the poles,\n"
				"for that consider using more apropiate methods, like ortodromic routing"
			);

		if (Lf > 180)
			Lf -= 360;
		if (Lf < -180)
			Lf += 360;

		char lat = 'N';
		char lon = 'W';

		if (lf < 0)
			lat = 'S';

		if (Lf < 0)
			lon = 'E';

		if (i == n)
		{
			const char* zl = "";
			const char* zL = "";

			if ((fabs(lf) - int(fabs(lf))) * 60 < 10.f)
				zl = "0";
			if ((fabs(Lf) - int(fabs(Lf))) * 60 < 10.f)
				zL = "0";

			printf(
				"\nFINAL POSITION\n"
				"%.3f%c %c\t%i%c %s%.2f%c %c\n"
				"%.3f%c %c\t%i%c %s%.2f%c %c\n"

				, fabs(lf), 248, lat, int(fabs(lf)), 248, zl, (fabs(lf) - int(fabs(lf))) * 60, '\'', lat
				, fabs(Lf), 248, lon, int(fabs(Lf)), 248, zL, (fabs(Lf) - int(fabs(Lf))) * 60, '\'', lon
			);

			Coor[0] = lf;
			Coor[1] = Lf;
		}
		else
		{
			const char* zl = "";
			const char* zL = "";

			if ((fabs(lf) - int(fabs(lf))) * 60 < 10.f)
				zl = "0";
			if ((fabs(Lf) - int(fabs(Lf))) * 60 < 10.f)
				zL = "0";

			printf(
				"\nWAYPOINT %u\n"
				"%.3f%c %c\t%i%c %s%.2f%c %c\n"
				"%.3f%c %c\t%i%c %s%.2f%c %c\n"

				, i + 1
				, fabs(lf), 248, lat, int(fabs(lf)), 248, zl, (fabs(lf) - int(fabs(lf))) * 60, '\'', lat
				, fabs(Lf), 248, lon, int(fabs(Lf)), 248, zL, (fabs(Lf) - int(fabs(Lf))) * 60, '\'', lon
			);

			time = waypoints[3 * i];
			speed = waypoints[3 * i + 1];
			course = waypoints[3 * i + 2];
			Coor[0] = lf;
			Coor[1] = Lf;
		}
	}

	if (simple)
		return Coor;

	printf("\n\nFor more imformation press any key and enter\n");
	char a[20];
	scanf("%s", a);

	printf(
		"\n\nFor calculating every step of the way we will use the position, the course, the speed and\n"
		"the time that have passed during that particular course.\n\n"

		"Variables:\n"
		"   d for distance covered\n"
		"   li for initial latitude\n"
		"   lf for final latitude\n"
		"   dl for diference in latitude\n"
		"   Li for initial longitude\n"
		"   Lf for final longitude\n"
		"   dL for diference in longitude\n"
		"   dt for diference in time\n"
		"   v for speed\n"
		"   c for course angle\n\n"

		"Solving and aproximations:\n\n"

		"d = v * dt\n"
		"dl = d * sin(c)\n"
		"lf = li + dl\n\n"

		"once we know the final latitude we can use it to aproximate de diference in\n"
		"Longitude. Because the distiance between meridian is not the same for diferent\n"
		"latitudes we will assume that this distance is give by the mean of the initial\n"
		"and final latitude.\n"
		"Therefore we obtain the following formula for the difference in Longitude:\n\n"

		"dL = d * cos(c) / cos((li + lf) / 2)\n"
		"Lf = Li + dl\n\n"

		"Now our new position is given by ( lf , Lf )\n"
		"If we apply this to the data given we obtain:\n"
	);

	return Coor;
}
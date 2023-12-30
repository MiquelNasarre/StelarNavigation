#include "Header.h"
#include "CF.h"

#include <stdio.h>
#include <iostream>

void distanceCourse(bool simple)
{
	float** coordinates;

	if(!simple)
		printf(
			"\nTo calculate the distance and the course from one point\n"
			"to another we just need to know the coordinates of both\n"
			"points.\n"
			"Given that your trip could have multiple waypoints in\n"
			"between for conveninece you may specify first how many\n"
			"in between points you want to add.\n"
		);

	int n;

	printf("\nNUMBER OF IN BETWEEN POINTS   ");
	scanf("%i", &n);

	if (n < 0)
	{
		printf("INVALID NUMBER");
		return distanceCourse(simple);
	}

	if (!simple)
		printf(
			"\nNow we just need the coordinates for all the points and\n"
			"using some basic spherical formulas we can figure out the\n"
			"distance and course in every step of the trip.\n"
		);

	coordinates = (float**)calloc(n + 2, sizeof(void*));

	for (int i = 0; i < n + 2; i++)
	{
		if (i == 0)
			printf("\nINITIAL POSITION\n");
		else if (i == n + 1)
			printf("\nFINAL POSITION\n");
		else
			printf("\nWAYPOINT %i\n", i);

		coordinates[i] = inputCoor();
	}

	float d = 0;

	for (int i = 0; i < n + 1; i++)
	{
		if (i == 0)
			printf("\nINITIAL POSITION -> ");
		else
			printf("\nWAYPOINT %i\t -> ", i);

		if (i == n)
			printf("FINAL POSITION\n");
		else
			printf("WAYPOINT %i\n", i + 1);

		float li = deg_rad * coordinates[i][0];
		float lf = deg_rad * coordinates[i + 1][0];
		float dL = deg_rad * (coordinates[i + 1][1] - coordinates[i][1]);

		float D = 60.f * rad_deg * acosf(sinf(li) * sinf(lf) + cosf(li) * cosf(lf) * cosf(dL));
		float C = rad_deg * atanf(sinf(dL) / (sinf(li) * cosf(dL) - tanf(lf) * cosf(li)));

		if (C < 0)
			C += 180.f;
		if (dL > 0)
			C += 180.f;

		printf(
			"DISTANCE\t%.2fnm\n"
			"COURSE\t\t%.2f%c\n",
			D, C, 248
		);

		d += D;
	}

	float li = deg_rad * coordinates[0][0];
	float lf = deg_rad * coordinates[n + 1][0];
	float dL = deg_rad * (coordinates[n + 1][1] - coordinates[0][1]);

	float D = 60.f * rad_deg * acosf(sinf(li) * sinf(lf) + cosf(li) * cosf(lf) * cosf(dL));
	float C = rad_deg * atanf(sinf(dL) / (sinf(li) * cosf(dL) - tanf(lf) * cosf(li)));

	if (C < 0)
		C += 180.f;
	if (dL > 0)
		C += 180.f;

	printf(
		"\nTOTAL DISTANCE\t%.2fnm\n"
		"\nSHORTEST PAHT \t%.2fnm    %.2f%c\n", 
		d, D, C, 248
	);
}
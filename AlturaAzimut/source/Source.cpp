#include "Header.h"
#include "CF.h"

#include <iostream>
#include <stdio.h>

float altitudeF(float l, float L, float d, float h)
{
	float P;

	if (L - h > 180.f)
		P = 360.f + h - L;

	else if (h - L > 180.f)
		P = 360.f + L - h;

	else if (L > h)
		P = L - h;

	else if (h > L)
		P = h - L;


	l *= 2 * 3.141592f / 360.f;
	L *= 2 * 3.141592f / 360.f;
	d *= 2 * 3.141592f / 360.f;
	P *= 2 * 3.141592f / 360.f;
	return 360.f / 2 / 3.141592f * asinf(sinf(d) * sinf(l) + cosf(l) * cosf(d) * cosf(P));
}

float azimuthF(float l, float L, float d, float h)
{
	float P;
	bool Case;

	if (L - h > 180.f)
	{
		P = 360.f + h - L;
		Case = true;
	}

	else if (h - L > 180.f)
	{
		P = 360.f + L - h;
		Case = false;
	}
	else if (L > h)
	{
		P = L - h;
		Case = false;
	}
	else if (h > L)
	{
		P = h - L;
		Case = true;
	}

	l *= 2 * 3.141592f / 360.f;
	L *= 2 * 3.141592f / 360.f;
	d *= 2 * 3.141592f / 360.f;
	P *= 2 * 3.141592f / 360.f;

	float Z = 360.f / 2 / 3.141592f * atanf(sinf(P) / (tanf(d) * cosf(l) - sinf(l) * cosf(P)));

	if (Z < 0)
		Z += 180.f;

	if (Case)
		Z = 360.f - Z;

	return Z;
}

//	Display functions

float* LI_GHA_DEC(bool simple)
{
	if (!simple)
		printf(
			"Linearly interpolating s star's position in the celestial sphere is a\n"
			"very tedious task, so here's a little program that can do it for you ;)\n\n"

			"Just introduce two different times with the object's hour angle and\n"
			"declination, and also the time you want to know the values for\n\n"
		);

	float t0 = inputTime("TIME\t");

	float h0, h0min, d0, d0min;

	printf("GHA\t");
	scanf("%f %f", &h0, &h0min);

	printf("DEC\t");
	scanf("%f %f", &d0, &d0min);

	printf("\n");

	float t1 = inputTime("TIME\t");

	float h1, h1min, d1, d1min;

	printf("GHA\t");
	scanf("%f %f", &h1, &h1min);

	printf("DEC\t");
	scanf("%f %f", &d1, &d1min);

	if (!simple)
		printf(
			"\n Now for interpolation we need to know the current time or the time the\n"
			"observation is going to take place, this time for precision you alse have\n"
			"to provide the seconds.\n"
		);

	float t = inputTime("\nCURRENT TIME\t", true);


	if (h0 >= 0)
		h0 += h0min / 60.f;
	else
		h0 -= h0min / 60.f;

	if (h1 >= 0)
		h1 += h1min / 60.f;
	else
		h1 -= h1min / 60.f;

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

	if (h0 > h1)
		h1 += 360.f;

	float d = (d1 * (t - t0) - d0 * (t - t1)) / (t1 - t0);
	float h = (h1 * (t - t0) - h0 * (t - t1)) / (t1 - t0);

	if (h > 360.f)
		h -= 360.f;

	printf(
		"\nGHA   %.3f%c\t%i%c %.2f%c"
		"\nDEC   %.3f%c\t%i%c %.2f%c\n"

		, h, 248, int(h), 248, fabs(h - int(h)) * 60, '\''
		, d, 248, int(d), 248, fabs(d - int(d)) * 60, '\''
	);

	float* ret = (float*)calloc(2, sizeof(float));
	ret[0] = h;
	ret[1] = d;

	return ret;
}

float* LI_GHA_SA(bool simple)
{
	if (!simple)
		printf(
			"When calculating the position for a star you need to linearly interpolate\n"
			"Aries hour angle and later add the sideric angle.\n\n"

			"Introduce two different times with their aries hour angle and the sideric angle,\n"
			"and also the time you want to know the hour angle for and the star's declination.\n\n"
		);

	float t0 = inputTime("TIME\t");

	float h0, h0min;

	printf("GHA\t");
	scanf("%f %f", &h0, &h0min);

	printf("\n");

	float t1 = inputTime();

	float h1, h1min;

	printf("GHA\t");
	scanf("%f %f", &h1, &h1min);

	if (!simple)
		printf(
			"\n Now for interpolation we need to know the current time or the time the\n"
			"observation is going to take place, this time for precision you alse have\n"
			"to provide the seconds.\n"
		);

	float t = inputTime("\nCURRENT TIME\t", true);

	float SA, SAmin;

	printf("\nSIDERIC ANGLE\t");
	scanf("%f %f", &SA, &SAmin);

	if (!simple)
		printf(
			"\nTo get the full star coordinates provide the stars declination as well\n"
		);

	float d, dmin;

	printf("DECLINATION\t");
	scanf("%f %f", &d, &dmin);


	if (h0 >= 0)
		h0 += h0min / 60.f;
	else
		h0 -= h0min / 60.f;

	if (h1 >= 0)
		h1 += h1min / 60.f;
	else
		h1 -= h1min / 60.f;

	if (d >= 0)
		d += dmin / 60.f;
	else
		d -= dmin / 60.f;

	if (SA >= 0)
		SA += SAmin / 60.f;
	else
		SA -= SAmin / 60.f;

	if (t0 > t1)
		t1 += 24.f;

	if (h0 > h1)
		h1 += 360.f;

	float h = (h1 * (t - t0) - h0 * (t - t1)) / (t1 - t0) + SA;

	if (h > 360.f)
		h -= 360.f;

	printf(
		"\nGHA   %.3f%c\t%i%c %.2f%c"
		"\nDEC   %.3f%c\t%i%c %.2f%c\n"

		, h, 248, int(h), 248, (h - int(h)) * 60, '\''
		, d, 248, int(d), 248, (d - int(d)) * 60, '\''
	);

	float* ret = (float*)calloc(2, sizeof(float));
	ret[0] = h;
	ret[1] = d;

	return ret;
}

void fullObservation()
{
	printf("\nESTIMATED POSITION\n\n");
	float* pos = inputCoor();

	int i;
	printf("\nINTERPOLATE OBJECT COORDINATES\nTYPE 1: STAR\nTYPE 2: OTHER\nTYPE?  ");
	scanf("%i", &i);

	printf("\n");

	float* ghadec;
	switch (i)
	{
	case 1:
		ghadec = LI_GHA_SA(true);
		break;
	case 2:
		ghadec = LI_GHA_DEC(true);
		break;
	default:
		printf("invalid type");
		return;
	}

	printf(
		"\nDATA GATHERED\n\n"

		"l = %.3f%c\n"
		"L = %.3f%c\n"
		"d = %.3f%c\n"
		"H = %.3f%c\n"

		, pos[0], 248
		, pos[1], 248
		, ghadec[1], 248
		, ghadec[0], 248
	);

	const float ad = altitudeF(pos[0], pos[1], ghadec[1], ghadec[0]);
	const float az = azimuthF(pos[0], pos[1], ghadec[1], ghadec[0]);

	printf(
		"\nOBTAINED ALTITUDE AND AZIMUTH\n\n"

		"a = %.3f%c\t%i%c %.2f%c\n"
		"Z = %.3f%c\t%i%c %.2f%c\n\n"

		, ad, 248, int(ad), 248, fabs(ad - int(ad)) * 60, '\''
		, az, 248, int(az), 248, fabs(az - int(az)) * 60, '\''
	);

}

#include "Header.h"
#include "CF.h"
#include <iostream>

void polarLatitude()
{

	printf("\nESTIMATED LONGITUDE\n\n");

	float L, Lmin;
	char c;

	scanf("%f %f %c", &L, &Lmin, &c);

	L += Lmin / 60.f;
	if (c == 'e' || c == 'E')
		L *= -1;

	printf("\nARIES GHA\n\n");

	float h, hmin;

	scanf("%f %f", &h, &hmin);

	h += hmin / 60.f;

	printf("\nMEASURED POLARIS ALTITUDE\n\n");

	float a, amin;

	scanf("%f %f", &a, &amin);

	a += amin / 60.f;

	float l = calculateLatitude(a, h, L);

	printf("\nYOUR LATITUDE IS\n\n%.3f%c N\t%i%c %.2f%c\n", l, 248, int(l), 248, (l - int(l)) * 60.f, '\'');
}

float calculateLatitude(float a, float gh, float L)
{
	//	The sideric angle and declination is data obtained for the almanach for December 2023

	float sa = 314.f + 3.7f / 60.f;
	float d = 89.f + 22.1f / 60.f;

	float h = gh - L + sa;
	if (h > 360)
		h -= 360.f;
	if (h < 0)
		h += 360.f;
	if (h > 180)
		h = 360 - h;

	h *= deg_rad;
	d *= deg_rad;
	a *= deg_rad;

	float t = asinf(sinf(h) / cosf(a) * cosf(d));

	float l = 90.f - 2 * rad_deg * atanf(cosf((t + h) / 2.f) / cosf((t - h) / 2.f) / tanf((d + a) / 2.f));
	

	return l;
}

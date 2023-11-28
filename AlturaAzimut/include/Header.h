#pragma once

float altitudeF(float latitude, float Longitude, float declination, float hourAngle);

float azimuthF(float latitude, float Longitude, float declination, float hourAngle);

//	Display Functions

float* LI_GHA_DEC(bool simplified = false);

float* LI_GHA_SA(bool simplified = false);

void fullObservation();
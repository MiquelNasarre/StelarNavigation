#pragma once
#define rad_deg ( 360.f / 2.f / 3.141592f )
#define deg_rad ( 2.f * 3.141592f / 360.f )

float* inputCoor();

float inputTime(const char* text = "Time:\t", bool seconds = false);

int getDate(bool print = true);
#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include <string>
#include "AbrirMalla.h"
using namespace std;

class ClassHacienda
{
	AbrirMalla nombreAsignado = AbrirMalla("./mallas/down_mesh/casa/source/casa_obj/Mineways2Skfb.obj");

public:
	ClassHacienda();

	void DibujarHacienda();
};


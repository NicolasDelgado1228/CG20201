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

class ClassFogata
{
	AbrirMalla nombreAsignado = AbrirMalla("./mallas/down_mesh/fogatica/Fireplace/Obj/fireplace.obj");

public:
	ClassFogata();

	void DibujarFogata();
};

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

class ClassTree
{
	AbrirMalla nombreAsignado = AbrirMalla("./mallas/down_mesh/vegetacion/arboles.obj");

public:
	ClassTree();

	void DibujarTree();
};


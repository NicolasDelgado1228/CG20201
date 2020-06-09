#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "AbrirMalla.h"

class ClassVaca
{

	AbrirMalla nombreAsignado = AbrirMalla("./mallas/down_mesh/minecraft-cow/vacas.obj");

public:
	ClassVaca();

	void DibujarVaca();

	//void DibujarVaca(GLfloat x, GLfloat y, GLfloat z);
};


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

class ClassPiso
{
	AbrirMalla nombreAsignado = AbrirMalla("./mallas/down_mesh/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/Grass_Block3.obj");
	
public:
	ClassPiso();

	void DibujarPiso();
};


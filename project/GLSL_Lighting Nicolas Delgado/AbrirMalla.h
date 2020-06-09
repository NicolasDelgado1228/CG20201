#pragma once
#include "glm/glm.h"
#include <stdio.h>
#include <iostream>
#include "FreeImage.h"

class AbrirMalla
{
public:
	GLMmodel* objmodel_ptr;

	AbrirMalla(char*);
	void DibujarMalla();
	void DibujarMallaTextura();
	~AbrirMalla();
};
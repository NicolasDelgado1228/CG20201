#include "AbrirMalla.h"

AbrirMalla::AbrirMalla(char* malla)
{
	objmodel_ptr = NULL;

	if (!objmodel_ptr) {
		objmodel_ptr = glmReadOBJ(malla);
		if (!objmodel_ptr)
			exit(0);

		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);

	}


}

AbrirMalla::~AbrirMalla() {
	objmodel_ptr = NULL;
}

void AbrirMalla::DibujarMalla() {
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
}

void AbrirMalla::DibujarMallaTextura() {
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
}
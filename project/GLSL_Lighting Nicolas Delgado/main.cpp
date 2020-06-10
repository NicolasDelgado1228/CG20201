//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

/************************************************************************************************************************
                                     PROYECTO DE COMPUTACON GRAFICA
                                             REALIZADO POR:
                                            NICOLAS DELGADO
************************************************************************************************************************/


#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "AbrirMalla.h"
#include "ClassZanahoria.h"
#include "ClassPiso.h"
#include "ClassBanca.h"
#include "ClassTree.h"
#include "ClassVasija.h"
#include "ClassVaca.h"
#include "ClassHacienda.h"          //Se cree que la malla de la hacienda da problemas en el programa
#include "ClassFogata.h"
#include "FreeImage.h"              //Para textura

//-----------------------------------------------------------------------------

#define DELTA 0.05
#define BETTA 0.1
#define NUM_ARBOLES  10

class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;        //Para textura
    cwc::glShader* shader;          //Para textura
    cwc::glShader* shaderTextura;   //Para textura
    GLuint ProgramObject;
    clock_t time0, time1;
    float timer010;                 // timer counting 0->1->0
    bool bUp, rot;                  // flag if counting up or down. Necesario para los controles de navegacion.
    ClassZanahoria* miZana;
    ClassPiso* miPiso;              //Objeto con textura (piso de minecraft)
    ClassBanca* miBanca;            //Objeto banca
    ClassTree* miTree;              //Arboles de la escena
    ClassVasija* miVasija;          //Vasija de la escena (objeto hecho a mano en Blender).
    ClassVaca* miVaca;              //Vacas del minecraft en la escena
    ClassFogata* miFogata;          //Fogata donde hacían asaditos en la hacienda cañasgordas
    ClassHacienda* miHacienda;      //Se esta pensando si añadir o no la malla de la hacienda (se cree que da errores)
    GLuint texid;                   //id de la textura
    GLfloat movimientoY;
    GLfloat movimientoX;
    GLfloat movimientoZ;
    bool Yup, Ydown;
    bool Xup, Xdown;
    bool Zup, Zdown;
    GLfloat movXZ[2], rotY;
    BOOLEAN statusAxes[6];

public:
    myWindow() {}

    /*FUNCION PARA LOS CONTROLES DE NAVEGACION*/
    void movementControl() {

        if (statusAxes[0]) movXZ[0] = movXZ[0] - DELTA;    // Se mueve hacia la izquierda
        if (statusAxes[1]) movXZ[0] = movXZ[0] + DELTA;    // Se mueve a la derecha
        if (statusAxes[2]) rotY = ((rotY - BETTA) < 0) ? 360 : rotY - BETTA;
        if (statusAxes[3]) rotY = ((rotY + BETTA) > 360) ? BETTA : rotY + BETTA;
        if (statusAxes[4]) movXZ[1] = movXZ[1] - DELTA;    // Se mueve hacia adelante
        if (statusAxes[5]) movXZ[1] = movXZ[1] + DELTA;    // Se mueve hacia atras
    }

    void initialize_textures(void)
    {
        int w, h;
        GLubyte* data = 0;
        //data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
        //std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

        //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/down_mesh/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png", 0),
            "./mallas/down_mesh/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/Grass_Block_TEX.png");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }



    virtual void OnRender(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //timer010 = 0.09; //for screenshot!
        glPushMatrix();

        movementControl();

        BOOLEAN result = false;
        for (int i = 0; i < 6; i++) {
            if (!result) result = statusAxes[i];
        }
        glTranslatef(0.0f, 0.0f, -4.0f);
        glTranslatef(movXZ[0], 0.0f, movXZ[1]);
        glRotatef(rotY, 0.0, 1.0, 0.0);

        //control TX locales
        glPushMatrix();
        if (shader) shader->begin();

        //posiciona y dibuja la huerta de zanahorias
        glPushMatrix();
        glTranslatef(-3.2f, 2.15f, 2.8f);
        glScalef(4.0f, 4.0f, 4.0f);
        miZana->DibujarZanahoria();
        glPopMatrix();


        //posiciona y dibuja la banca para el asadito en la hacienda
        glPushMatrix();
        glTranslatef(2.0f, 2.4f, 0.0f);
        glScalef(2.5f, 2.5f, 2.5f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        miBanca->DibujarBanca();
        glPopMatrix();
        
        //posiciona y dibuja los arboles
        glPushMatrix();
        glTranslatef(-3.0f, 2.8f, -1.0f);
        glScalef(3.5f, 3.5f, 3.5f);
        miTree->DibujarTree();
        glPopMatrix();

        
        //posiciona y dibuja la hacienda
        glPushMatrix();
        glTranslatef(3.0f, 3.5f, -2.5f);         //ESTA MALLA GENERA ERRORES
        glScalef(1.8f, 1.8f, 1.8f);
        glRotated(-50.0f,0.0f,1.0f,0.0f);
        miHacienda->DibujarHacienda();
        glPopMatrix();
        

        //posiciona y dibuja la fogata
        glPushMatrix();
        //controlMovimiento();
        glTranslatef(movimientoX, movimientoY, movimientoZ);
        glTranslatef(0.6f, 2.35f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        miFogata->DibujarFogata();
        glPopMatrix();
        
        //posiciona y dibuja la vasija
        glPushMatrix();
        glTranslatef(0.7f, 2.4f, 2.9f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.25f, 0.25f, 0.25f);
        miVasija->DibujarVasija();
        glPopMatrix();

        //posiciona y dibuja el ganado de la hacienda cañasgordas
        glPushMatrix();
        glTranslatef(0.0f, 2.42f, 1.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        miVaca->DibujarVaca();
        glPopMatrix();

        if (shader) shader->end();

        /*** Para Textura: llamado al shader para objetos texturizados***/
        if (shaderTextura) shaderTextura->begin();

            //posiciona y dibuja el piso de minecraft (objeto con textura)
            glPushMatrix();
            glTranslatef(0.0f, 2.0f, 0.0f);
            glScalef(5.0f, 5.0f, 5.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            
            glBindTexture(GL_TEXTURE_2D, texid);
            miPiso->DibujarPiso();
            glPopMatrix();
      //glutSolidTeapot(1.0);
      if (shaderTextura) shaderTextura->end();

        glPopMatrix();

        //Acomoda los buffers
        glutSwapBuffers();
        glPopMatrix();

        UpdateTimer();

        Repaint();
    }

    virtual void OnIdle() {}

    // When OnInit is called, a render context (in this case GLUT-Window) 
    // is already available!

    virtual void OnInit()
    {
        movimientoY = 0.0f;
        movimientoX = 0.0f;
        movimientoZ = 0.0f;
        Yup = false;
        Ydown = false;
        Xup = false;
        Xdown = false;
        Zdown = false;
        Zup = false;


        //Se dibujan todos los objetos de la escena
        miZana = new ClassZanahoria();
        miPiso = new ClassPiso();
        miBanca = new ClassBanca();
        miTree = new ClassTree();
        miVasija = new ClassVasija();
        miVaca = new ClassVaca();
        miFogata = new ClassFogata();
        miHacienda = new ClassHacienda();

        glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
        if (shader == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader->GetProgramObject();
        }

        //Para Textura: abre los shaders para texturas
        shaderTextura = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt");
        if (shaderTextura == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shaderTextura->GetProgramObject();
        }
        time0 = clock();
        timer010 = 0.0f;
        bUp = true;
        rot = false;

        for (int i = 0; i < 6; i++) {
            statusAxes[i] = false;
        }

        movXZ[0] = 0;
        movXZ[1] = 0;
        rotY = 0;

        initialize_textures();
        DemoLight();

    }

    virtual void OnResize(int w, int h)
    {
        if (h == 0) h = 1;
        float ratio = 1.0f * (float)w / (float)h;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, w, h);

        gluPerspective(45, ratio, 1, 500);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(10.0f, 10.0f, 10.0f,
            0.0, 0.0, 0.0,
            0.0f, 1.0f, 0.0f);
    }
    virtual void OnClose(void) {}
    virtual void OnMouseDown(int button, int x, int y) {}
    virtual void OnMouseUp(int button, int x, int y) {}
    virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) {}

    virtual void OnKeyDown(int nKey, char cAscii)
    {
        if (cAscii == 27) {           // 0x1b = ESC
            this->Close();            // Close Window!
        }

        switch (cAscii) {
        case 'w': statusAxes[5] = true;
            break;
        case 's': statusAxes[4] = true;
            break;
        case 'd': statusAxes[0] = true;
            break;
        case 'a': statusAxes[1] = true;
            break;
        case 'e': statusAxes[2] = true;
            break;
        case 'q': statusAxes[3] = true;
            break;
        }

    };

    virtual void OnKeyUp(int nKey, char cAscii)
    {
        if (cAscii == 's')      // s: Shader
            shader->enable();
        else if (cAscii == 'f') // f: Fixed Function
            shader->disable();

        switch (cAscii) {
        case 'w': statusAxes[5] = false;
            break;
        case 's': statusAxes[4] = false;
            break;
        case 'd': statusAxes[0] = false;
            break;
        case 'a': statusAxes[1] = false;
            break;
        case 'e': statusAxes[2] = false;
            break;
        case 'q': statusAxes[3] = false;
            break;
        }
    }

    void UpdateTimer()
    {
        time1 = clock();
        float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
        delta = delta / 4;
        if (delta > 0.00005f)
        {
            time0 = clock();
            if (bUp)
            {
                timer010 += delta;
                if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
            }
            else
            {
                timer010 -= delta;
                if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
            }
        }
    }

    void DemoLight(void)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        /*
        // Light model parameters:
        // -------------------------------------------

        GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

        // -------------------------------------------
        // Spotlight Attenuation

        GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
        GLint spot_exponent = 30;
        GLint spot_cutoff = 180;

        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
        glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
        glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

        GLfloat Kc = 1.0;
        GLfloat Kl = 0.0;
        GLfloat Kq = 0.0;

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


        // ------------------------------------------- 
        // Lighting parameters:

        GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
        GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
        GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
        GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

        // -------------------------------------------
        // Material parameters:

        GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
        GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
        GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
        GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
        GLfloat material_Se = 20.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
        */
    }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
    virtual void OnInit() { std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
    myApplication* pApp = new myApplication;
    myWindow* myWin = new myWindow();

    pApp->run();
    delete pApp;
    return 0;
}

//-----------------------------------------------------------------------------


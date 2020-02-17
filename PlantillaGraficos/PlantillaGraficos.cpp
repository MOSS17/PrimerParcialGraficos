// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <math.h>

#include <iostream>

#include <random>
#include <time.h>

using namespace std;

//Declarar una ventana
GLFWwindow* window;
float posXTriangulo = 0.0f , posYTriangulo = 0.0f;
float rotacionTriangulo = 0.0f;
float escalaTriangulo = 0.5f;

float posXCuadrado = 0.5f, posYCuadrado = 0.5f;

float posXRojo = -0.5f, posYRojo = -0.5;
float posXAzul = 0.2f, posYAzul = 0.5;
float posXRosa = -0.5f, posYRosa = 0.5;
float posXVerde = 0.5f, posYVerde = -0.5;

double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;
double velocidadRotacion = 60;

//glColor3f(0.2, 0.6, 0.1);
float rojoTriangulo = 0.2f;
float verdeTriangulo = 0.6f;
float azulTriangulo = 0.1f;

default_random_engine generator;
uniform_real_distribution<double> distribution(-1, 1); //doubles from -1 to 1


  

/* generate secret number between 1 and 10: */
int iSecret = rand() % 5 + 1;

bool colision = false;

void teclado_callback(GLFWwindow* window,
	int key, int scancode, int action, int mods) {

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT) 
		&& key == GLFW_KEY_RIGHT) {
		posXTriangulo += 0.01f;
	}

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT)
		&& key == GLFW_KEY_LEFT) {
		posXTriangulo -= 0.01f;
	}

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT)
		&& key == GLFW_KEY_UP) {
		posYTriangulo += 0.01f;
	}

	if (
		(action == GLFW_PRESS || action == GLFW_REPEAT)
		&& key == GLFW_KEY_DOWN) {
		posYTriangulo -= 0.01f;
	}



}

void checarColisiones() {
    double random_number = distribution(generator);
	if (
		//Orilla derecha del triangulo es mayor que
		//la orilla izquierda del cuadrado
		posXTriangulo + 0.05f >= posXVerde - 0.05f &&
		//Orilla izquierda del triangulo es menor que
		//la orilla derecha del cuadrado
		posXTriangulo - 0.05f <= posXVerde + 0.05f &&
		//Orilla superior triangulo mayor que
		//la orilla inferior del cuadrado
		posYTriangulo + 0.05f >= posYVerde- 0.05f &&
		//Orilla inferior triangulo menor que
		//la orilla superior del cuadrado
		posYTriangulo - 0.05f <= posYVerde+ 0.05f 
		) {
        // Aumentar tamaño del triangulo con cada colision
        escalaTriangulo += 0.05;

        // Generar el objeto en otra posición
        posXVerde = random_number;
        random_number = distribution(generator);
        posYVerde = random_number;

        // Generar el rojo en otra posición
        posXRojo = random_number;
        random_number = distribution(generator);
        posYRojo = random_number;

        iSecret = rand() % 5 + 1;
		//exit(1);
	}
    if (
        //Orilla derecha del triangulo es mayor que
        //la orilla izquierda del cuadrado
        posXTriangulo + 0.05f >= posXAzul - 0.05f &&
        //Orilla izquierda del triangulo es menor que
        //la orilla derecha del cuadrado
        posXTriangulo - 0.05f <= posXAzul + 0.05f &&
        //Orilla superior triangulo mayor que
        //la orilla inferior del cuadrado
        posYTriangulo + 0.05f >= posYAzul - 0.05f &&
        //Orilla inferior triangulo menor que
        //la orilla superior del cuadrado
        posYTriangulo - 0.05f <= posYAzul + 0.05f
        ) {
        // Aumentar tamaño del triangulo con cada colision
        velocidadTriangulo += 0.1;

        // Generar el objeto en otra posición
        posXAzul = random_number;
        random_number = distribution(generator);
        posYAzul = random_number;

        // Generar el rojo en otra posición
        posXRojo = random_number;
        random_number = distribution(generator);
        posYRojo = random_number;

        iSecret = rand() % 5 + 1;
    }
    if (
        //Orilla derecha del triangulo es mayor que
        //la orilla izquierda del cuadrado
        posXTriangulo + 0.05f >= posXRosa - 0.05f &&
        //Orilla izquierda del triangulo es menor que
        //la orilla derecha del cuadrado
        posXTriangulo - 0.05f <= posXRosa + 0.05f &&
        //Orilla superior triangulo mayor que
        //la orilla inferior del cuadrado
        posYTriangulo + 0.05f >= posYRosa - 0.05f &&
        //Orilla inferior triangulo menor que
        //la orilla superior del cuadrado
        posYTriangulo - 0.05f <= posYRosa + 0.05f
        ) {
        // Aumentar tamaño del triangulo con cada colision
        velocidadTriangulo *= -1;

        // Generar el objeto en otra posición
        posXRosa = random_number;
        random_number = distribution(generator);
        posYRosa = random_number;

        // Generar el rojo en otra posición
        posXRojo = random_number;
        random_number = distribution(generator);
        posYRojo = random_number;

        iSecret = rand() % 5 + 1;
    }
    if (
        //Orilla derecha del triangulo es mayor que
        //la orilla izquierda del cuadrado
        posXTriangulo + 0.05f >= posXRojo - 0.05f &&
        //Orilla izquierda del triangulo es menor que
        //la orilla derecha del cuadrado
        posXTriangulo - 0.05f <= posXRojo+ 0.05f &&
        //Orilla superior triangulo mayor que
        //la orilla inferior del cuadrado
        posYTriangulo + 0.05f >= posYRojo - 0.05f &&
        //Orilla inferior triangulo menor que
        //la orilla superior del cuadrado
        posYTriangulo - 0.05f <= posYRojo+ 0.05f
        ) {


        exit(1);
    }
}

void actualizar() {
	tiempoActual = glfwGetTime();

	checarColisiones();

	double tiempoDiferencial = 
		tiempoActual - tiempoAnterior;

    // Siempre avanza
    posYTriangulo += (velocidadTriangulo * sin((rotacionTriangulo + 90.0) * 3.1416 / 180)) * tiempoDiferencial;
    posXTriangulo += (velocidadTriangulo * cos((rotacionTriangulo + 90.0) * 3.1416 / 180)) * tiempoDiferencial;

    int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
    if (estadoIzquierda == GLFW_PRESS) {
        rotacionTriangulo += velocidadRotacion * tiempoDiferencial;
    }

	int estadoDerecha =
		glfwGetKey(window, GLFW_KEY_RIGHT);
    if (estadoDerecha == GLFW_PRESS) {
        rotacionTriangulo -= velocidadRotacion * tiempoDiferencial;
    }
    // Reset angulo
    if (rotacionTriangulo >= 360) {
        rotacionTriangulo = 0;
    }

    if (rotacionTriangulo <= -360) {
        rotacionTriangulo = 0;
    }

	tiempoAnterior = tiempoActual;
}

void dibujarTriangulo() {
	glPushMatrix();
    if (posXTriangulo >= 1.15) {
        posXTriangulo = -1.1;
    }
    if (posXTriangulo <= -1.15) {
        posXTriangulo = 1.1;
    }

    if (posYTriangulo >= 1.15) {
        posYTriangulo = -1.1;
    }
    if (posYTriangulo <= -1.15) {
        posYTriangulo = 1.1;
    }

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);
    glRotatef(rotacionTriangulo, 0, 0, 1);  
    glScalef(escalaTriangulo, escalaTriangulo, escalaTriangulo);

	glBegin(GL_TRIANGLES);

	glColor3f(rojoTriangulo, verdeTriangulo, azulTriangulo);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();
	glPopMatrix();
}

/*
void dibujarCuadrado() {
	glPushMatrix();

	glTranslatef(posXCuadrado, posYCuadrado, 0.0f);

	glBegin(GL_QUADS);

	glColor3f(0.7f, 0.2f, 0.5f);
	glVertex3f(-0.15f, 0.15f, 0.0f);
	glVertex3f(0.15f, 0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);

	glEnd();
	glPopMatrix();
}
*/


void dibujarFigura1(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.3f, 0.5f, 0.9f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura2(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.3f, 0.5f, 0.9f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura3(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.3f, 0.5f, 0.9f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura4(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.3f, 0.5f, 0.9f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura5(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.3f, 0.5f, 0.9f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura6(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.4f, 0.7f, 0.2f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura7(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.4f, 0.7f, 0.2f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura8(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.4f, 0.7f, 0.2f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura9(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.4f, 0.7f, 0.2f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura10(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.2f, 0.5f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura11(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.2f, 0.5f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura12(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.2f, 0.5f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura13(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.2f, 0.5f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura14(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.2f, 0.5f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura15(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura16(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura17(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura18(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura19(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(0.4f, 0.7f, 0.2f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujarFigura20(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x + cx, y + cy, 1.0f);

    }
    glEnd();
}

void dibujar() {
	dibujarTriangulo();
    /*
    // Figuras Azules
	dibujarFigura1(0.1, 0.1, 0.05, 3);
	dibujarFigura2(0.2, 0.2, 0.05, 4);
	dibujarFigura3(0.3, 0.3, 0.05, 5);
	dibujarFigura4(0.4, 0.4, 0.05, 6);
	dibujarFigura5(0.5, 0.5, 0.05, 7);

    // Figuras Verdes
	dibujarFigura6(0.6, 0.6, 0.05, 8);
	dibujarFigura7(0.7, 0.7, 0.05, 9);
	dibujarFigura8(0.8, 0.8, 0.05, 10);
	dibujarFigura9(0.9, 0.9, 0.05, 100);
    dibujarFigura19(0.1, -0.1, 0.05, 11);

    // Figuras Rosas
	dibujarFigura10(-0.1, -0.1, 0.05, 3);
	dibujarFigura11(-0.2, -0.2, 0.05, 4);
	dibujarFigura12(-0.3, -0.3, 0.05, 5);
	dibujarFigura13(-0.4, -0.4, 0.05, 6);
	dibujarFigura14(-0.5, -0.5, 0.05, 7);

    // Figuras Rojas
	dibujarFigura15(-0.6, -0.6, 0.05, 8);
	dibujarFigura16(-0.7, -0.7, 0.05, 9);
	dibujarFigura17(-0.8, -0.8, 0.05, 10);
	dibujarFigura18(-0.9, -0.9, 0.05, 100);
	dibujarFigura20(-0.1, 0.1, 0.05, 11);
    */

    // Dibujar figura azul
    switch (iSecret)
    {
    case 1:
        dibujarFigura1(posXAzul, posYAzul, 0.05, 3);
        break;
    case 2:
        dibujarFigura2(posXAzul, posYAzul, 0.05, 4);
        break;
    case 3:
        dibujarFigura3(posXAzul, posYAzul, 0.05, 5);
        break;
    case 4:
        dibujarFigura4(posXAzul, posYAzul, 0.05, 6);
        break;
    case 5:
        dibujarFigura5(posXAzul, posYAzul, 0.05, 7);
        break;
    default:
        break;
    }

    // Dibujar figura verde
    switch (iSecret)
    {
    case 1:
        dibujarFigura6(posXVerde, posYVerde, 0.05, 8);
        break;
    case 2:
        dibujarFigura7(posXVerde, posYVerde, 0.05, 9);
        break;
    case 3:
        dibujarFigura8(posXVerde, posYVerde, 0.05, 10);
        break;
    case 4:
        dibujarFigura9(posXVerde, posYVerde, 0.05, 100);
        break;
    case 5:
        dibujarFigura19(posXVerde, posYVerde, 0.05, 11);
        break;
    default:
        break;
    }
    // Dibujar figura rosa
    switch (iSecret)
    {
    case 1:
        dibujarFigura10(posXRosa, posYRosa, 0.05, 3);
        break;
    case 2:
        dibujarFigura11(posXRosa, posYRosa, 0.05, 4);
        break;
    case 3:
        dibujarFigura12(posXRosa, posYRosa, 0.05, 5);
        break;
    case 4:
        dibujarFigura13(posXRosa, posYRosa, 0.05, 6);
        break;
    case 5:
        dibujarFigura14(posXRosa, posYRosa, 0.05, 7);
        break;
    default:
        break;
    }
    // Dibujar figura roja
    switch (iSecret)
    {
    case 1:
        dibujarFigura15(posXRojo, posYRojo, 0.05, 8);
        break;
    case 2:
        dibujarFigura16(posXRojo, posYRojo, 0.05, 9);
        break;
    case 3:
        dibujarFigura17(posXRojo, posYRojo, 0.05, 10);
        break;
    case 4:
        dibujarFigura18(posXRojo, posYRojo, 0.05, 100);
        break;
    case 5:
        dibujarFigura20(posXRojo, posYRojo, 0.05, 11);
        break;
    default:
        break;
    }
}

int main()
{
    /* initialize random seed: */
    srand(time(NULL));

	//Si no se pudo iniciar GLFW
	//Terminamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//inicializamos la ventana
	window =
		glfwCreateWindow(600, 600, "Ventana",
			NULL, NULL);
	//Si no se pudo crear la venata
	//Terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto
	//Se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado
	//se llama a la función teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;
	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(1.0f, 0.8f, 0.0f, 1.0f);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | 
			GL_DEPTH_BUFFER_BIT);

		//Actualizar valores y dibujar
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despúes del ciclo de dibujo
	//Eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}

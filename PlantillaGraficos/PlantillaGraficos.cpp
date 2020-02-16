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

using namespace std;

//Declarar una ventana
GLFWwindow* window;
float posXTriangulo = 0.0f , posYTriangulo = 0.0f;

float posXCuadrado = 0.5f, posYCuadrado = 0.5f;
float rotacionTriangulo = 0.0f;
float escalaTriangulo = 0.5f;

double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;
double velocidadRotacion = 60;

//glColor3f(0.2, 0.6, 0.1);
float rojoTriangulo = 0.2f;
float verdeTriangulo = 0.6f;
float azulTriangulo = 0.1f;

default_random_engine generator;
uniform_real_distribution<double> distribution(-1, 1); //doubles from -1 to 1

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
		posXTriangulo + 0.15f >= posXCuadrado - 0.15f &&
		//Orilla izquierda del triangulo es menor que
		//la orilla derecha del cuadrado
		posXTriangulo - 0.15f <= posXCuadrado + 0.15f &&
		//Orilla superior triangulo mayor que
		//la orilla inferior del cuadrado
		posYTriangulo + 0.15f >= posYCuadrado - 0.15f &&
		//Orilla inferior triangulo menor que
		//la orilla superior del cuadrado
		posYTriangulo - 0.15f <= posYCuadrado + 0.15f 
		) {
        // Aumentar tamaño del triangulo con cada colision
        escalaTriangulo += 0.05;

        // Generar el objeto en otra posición
        posXCuadrado = random_number;
        cout << "\n" << random_number;
        random_number = distribution(generator);
        posYCuadrado = random_number;
        cout << "\n" << random_number;

        if (!colision) {
            colision = true;
        }
		//exit(1);
	}
	else {
		rojoTriangulo = 0.2f;
		verdeTriangulo = 0.6f;
		azulTriangulo = 0.1f;
        if (colision) {
            colision = false;
        }
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

void dibujar() {
	dibujarCuadrado();
	dibujarTriangulo();
}

int main()
{
    

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

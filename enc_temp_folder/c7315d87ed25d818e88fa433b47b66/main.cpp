

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include "sphere.h"
#include "stb_image.h"
#include "curveObject.h"
#include "cube.h"
#include <iostream>
#include <stdlib.h>
#include<windows.h>  

using namespace std;


//functions_sourav
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void shiri(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[], int steps);
void Grasses(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void CoffeMachine(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void CafeFoodCounter(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void CafeShop(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Baloon(Shader ourShader, Shader sphereShader, glm::mat4 moveMatrix, glm::vec3 rotationAxis, glm::vec3 ambient, glm::vec4 color, float rotation, Cube cube[]);
void dotdot(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void drawCube(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, float spec, float shininess);
void SpotLightWithCurve(Shader ourShader, Shader lightingShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[], GLfloat reverseCurve[]);
void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void SecondFloorShamne(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void ChotoBlocks(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void TubeLight(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void SquareBati(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Pillars(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube cube[]);
void Table(Shader ourShader, glm::mat4 moveMatrix, float rotation, bool square, Cube cube[]);
void Chair(Shader ourShader, glm::mat4 moveMatrix, float rotation, Cube all_cubes[]);
void RotateChairY(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[]);
void SwimmingPool(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Tent(Shader ourShader, glm::mat4 moveMatrix, glm::mat4 forTableChair, glm::vec4 color, Cube all_cubes[], bool isRotate);
void Street(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void TrafficLight(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Mati(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void TentY(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[]);
void TentX(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[]);
void Tent1(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
void Boro_Raste(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]);
//notun_function



unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float dorja1_rotationY = 0.0f;
float window_translate = 0.8125f;
float rotateAngleTest_Y = 0.0;
float globalBallonRotation = 0.0f;
float globalBallonStep = 3.0f;
bool isglobalBallonOn = 1.0f;


float globalDotStep = 0.01 ;
float globalDownDotStep = 0.01;
bool isglobalDotOn = 1.0f;
bool isDownglobalDoon = true;

// camera               8.0   1.0   18.1
Camera camera(glm::vec3(8.0f, 1.0f, 18.1f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 2.5;
float lookAtX = 0.0, lookAtY = 1.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


glm::vec3 lightPositions[] = {
		glm::vec3(7.0 + 5, 3.01 - 1, -20 + 0.36),
		glm::vec3(-8.0f, 8.0f, 8.0f),
		glm::vec3(-8.0f, 8.0f, -8.0f),
		glm::vec3(8.0f, 8.0f, -8.0f),
		glm::vec3(15.0, 5.0, 17.0),
		glm::vec3(-2.3f, .5f, 4.8f) ,

		glm::vec3(0.1f, 3.2f, 13.5f) ,//spotlight1
		glm::vec3(4.30f, 3.0, -5.0f - 2), //spotlight2
		glm::vec3(4.30f , 3.0, -5.0f - 4) //spotlight3
};

glm::vec3 lightDirections[] = {
	glm::vec3(0.4f, -0.2f, 1.0f)
};


PointLight pointLight0(

	lightPositions[0].x, lightPositions[0].y, lightPositions[0].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	1       // light number
);

PointLight pointLight1(

	lightPositions[0].x, lightPositions[0].y, lightPositions[0].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	1       // light number
);

PointLight pointLight2(

	lightPositions[1].x, lightPositions[1].y, lightPositions[1].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	2       // light number
);

PointLight pointLight3(

	lightPositions[2].x, lightPositions[2].y, lightPositions[2].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	3       // light number
);

PointLight pointLight4(

	lightPositions[3].x, lightPositions[3].y, lightPositions[3].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	4       // light number
);

PointLight pointLight5(

	lightPositions[4].x, lightPositions[4].y, lightPositions[4].z,  // position
	0.05f, 0.05f, 0.05f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	5       // light number
);

DirectionalLight directionalLight(

	-lightPositions[4].x, -lightPositions[4].y, -lightPositions[4].z,  // direction
	0.4f, 0.4f, 0.4f,     // ambient
	0.4f, 0.4f, 0.4f,     // diffuse
	.2f, .2f, 0.2f,        // specular
	1           // light number
);

DirectionalLight directionalLight2(

	lightPositions[4].x, lightPositions[4].y, lightPositions[4].z,  // direction
	0.4f, 0.4f, 0.4f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	1           // light number
);

SpotLight spotLight(

	lightPositions[6].x, lightPositions[6].y, lightPositions[6].z,  // position
	0.0f, 1.0f, 1.0f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	0.0, -3.0, 0.0,  // direction
	8.5f,   // cutoff
	15.5f,   // outer cutoff
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	1       // light number
);

SpotLight spotLight2(

	lightPositions[7].x, lightPositions[7].y, lightPositions[7].z,  // position
	1.0f, 1.0f, 1.0f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	0.0, -3.0, 0.0,  // direction
	8.5f,   // cutoff
	15.5f,   // outer cutoff
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	2      // light number
);

SpotLight spotLight3(

	lightPositions[8].x, lightPositions[8].y, lightPositions[8].z,  // position
	1.0f, 1.0f, 1.0f,     // ambient
	0.8f, 0.8f, 0.8f,     // diffuse
	1.0f, 1.0f, 1.0f,        // specular
	0.0, -3.0, 0.0,  // direction
	8.5f,   // cutoff
	15.5f,   // outer cutoff
	1.0f,   //k_c
	0.09f,  //k_l
	0.032f, //k_q
	3      // light number
);



// texture
float extra = 4.0f;
float TXmin = 0.0f;
float TXmax = 1.0f + extra;
float TYmin = 0.0f;
float TYmax = 1.0f + extra;



//rotate
bool isRotating = false;
float fanSpeed = 8.0f;

bool lightingOn = true;
float ambientOn = 1.0;
float diffuseOn = 1.0;
float specularOn = 1.0;
bool dark = false;

float directionalLightOn = 1.0;
float pointLightOn = 0.0;
float spotLightOn = 0.0;


// Textures
unsigned int texture0, texture1, redBrickTex, texture3, texture4, tilesTex, texture6, texture7, woodtex, glasstex, tabletex, marbeltex, coffeetex;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cafeteria - Pial 1807040", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
	Shader ourShader("vertexShader.vs", "fragmentShader.fs");
	Shader lightingShader("vertexShaderLight.vs", "fragmentShaderLight.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes


	float cube_vertices[] = {
		// positions      // normals         // texture coords
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,
		0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmax,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,

		0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax,
		0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, TXmin, TYmin,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, TXmin, TYmax,

		0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,
		0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
		0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

		0.0f, 0.0f, 0.5f, -1.0f, 0.0f, 0.0f, TXmax, TYmin,
		0.0f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, TXmax, TYmax,
		0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax,
		0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin,

		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
		0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

		0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
		0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
		0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
		0.0f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, TXmin, TYmax
	};
	unsigned int cube_indices[] = {
		0, 3, 2,
		2, 1, 0,

		4, 5, 7,
		7, 6, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	//curve er point
	GLfloat points[] = {
-1.0250, 0.79, 5.1000,
-1.0250, .50, 5.1000,
0.0000, .50, 5.10
	};

	GLfloat blank[] = {
0.1,0.1,0.1
	};

	GLfloat reverseCurve[]{


-0.9500, 0.3000, 5.1000,
-0.9100, 0.8750, 5.1000,
-0.6950, 1.3700, 5.1000,
-0.3000, 1.7600, 5.1000,
-0.0150, 1.8800, 5.1000,

	};
	GLfloat treeCuve[] = {
-0.0500, 2.2050, 5.1000,
-0.1100, 2.2150, 5.1000,
-0.1850, 2.1950, 5.1000,
-0.2350, 2.1400, 5.1000,
-0.2450, 2.0400, 5.1000,
-0.2550, 1.9400, 5.1000,
-0.2650, 1.8450, 5.1000,
-0.2650, 1.7200, 5.1000,
-0.2650, 1.5700, 5.1000,
-0.2650, 1.4600, 5.1000,
-0.2700, 1.3300, 5.1000,
-0.2650, 1.1650, 5.1000,
-0.2650, 1.0350, 5.1000,
-0.2700, 0.8650, 5.1000,
-0.2850, 0.7200, 5.1000,
-0.3050, 0.6200, 5.1000,
-0.3150, 0.4700, 5.1000,
-0.3200, 0.3050, 5.1000,
-0.3600, 0.1700, 5.1000,
-0.3850, 0.1000, 5.1000,
-0.4100, 0.0200, 5.1000,
-0.4450, -0.0450, 5.1000,
-0.4600, -0.0750, 5.1000,
	};

	GLfloat leafCurve[] = {
-0.0100, 2.3600, 5.1000,
-0.0550, 2.3600, 5.1000,
-0.1550, 2.3800, 5.1000,
-0.2900, 2.3700, 5.1000,
-0.3900, 2.3350, 5.1000,
-0.4150, 2.2350, 5.1000,
-0.4450, 2.1200, 5.1000,
-0.5000, 2.0900, 5.1000,
-0.5700, 2.0800, 5.1000,
-0.6350, 2.0700, 5.1000,
-0.7000, 2.0450, 5.1000,
-0.8000, 2.0100, 5.1000,
-0.8650, 1.9800, 5.1000,
-0.9100, 1.9300, 5.1000,
-0.9200, 1.8900, 5.1000,
-0.9400, 1.7750, 5.1000,
-0.9300, 1.5650, 5.1000,
-0.9150, 1.5200, 5.1000,
-0.8150, 1.4450, 5.1000,
-0.7250, 1.4000, 5.1000,
-0.6000, 1.3650, 5.1000,
-0.4650, 1.3550, 5.1000,
-0.3700, 1.3550, 5.1000,
-0.2800, 1.3550, 5.1000,
-0.2300, 1.3550, 5.1000,
-0.1800, 1.3650, 5.1000,
-0.1250, 1.3750, 5.1000,
-0.1150, 1.3800, 5.1000,
-0.0650, 1.3850, 5.1000,
	};

	GLfloat bodyCurve[] = {
	-0.1300, 2.1900, 5.1000,
	-0.2100, 2.1850, 5.1000,
	-0.2700, 2.1850, 5.1000,
	-0.3450, 2.1500, 5.1000,
	-0.3750, 2.0800, 5.1000,
	-0.3900, 1.9450, 5.1000,
	-0.4300, 1.7800, 5.1000,
	-0.4850, 1.6200, 5.1000,
	-0.5450, 1.4600, 5.1000,
	-0.6150, 1.2700, 5.1000,
	-0.7000, 1.1500, 5.1000,
	-0.7850, 1.0600, 5.1000,
	-0.7450, 0.7400, 5.1000,
	-0.7400, 0.7350, 5.1000,
	-0.8100, 0.8850, 5.1000,
	-0.5550, 0.5800, 5.1000,
	-0.2050, 0.4800, 5.1000,
	-0.1050, 0.4700, 5.1000,
	-0.0350, 0.4650, 5.1000,
	};
	GLfloat legCurve[] = {
0.0650, 1.8500, 5.1000,
-0.0500, 1.8650, 5.1000,
-0.1900, 1.8450, 5.1000,
-0.2700, 1.8250, 5.1000,
-0.3050, 1.7350, 5.1000,
-0.3050, 1.5350, 5.1000,
-0.2700, 1.3400, 5.1000,
-0.2500, 1.2000, 5.1000,
-0.2950, 1.0750, 5.1000,
-0.2300, 1.0700, 5.1000,
-0.2550, 0.9300, 5.1000,
-0.3150, 0.8650, 5.1000,
-0.2600, 0.7550, 5.1000,
-0.2350, 0.6900, 5.1000,
-0.1950, 0.5450, 5.1000,
-0.1450, 0.4000, 5.1000,
-0.0750, 0.2950, 5.1000,
-0.0500, 0.1950, 5.1000,
-0.0300, 0.1350, 5.1000,
0.0150, 0.1100, 5.1000,
0.0550, 0.0900, 5.1000,
0.0850, 0.0650, 5.1000,
0.1150, 0.0400, 5.1000,
0.1500, 0.0200, 5.1000,
	};
	GLfloat	lampPoints[] = {
-0.1400, 1.6450, 5.1000,
-0.3850, 1.6350, 5.1000,
-0.5350, 1.2250, 5.1000,
-0.6600, 0.9500, 5.1000,
-0.2800, 0.9200, 5.1000,
	};
	GLfloat nunu[] = {
		-2.5, 0.0, 0.0699664838575533,
-2.4494949494949494, 0.3999795933984513, -0.01012979346400629,
-2.398989898989899, 0.56276316271451, 0.06817652393044826,
-2.3484848484848486, 0.6856793029687731, -0.021747911532846678,
-2.297979797979798, 0.7876197450350676, -0.09549539575694568,
-2.2474747474747474, 0.8759387227749009, 0.04743609898383214,
-2.196969696969697, 0.9544251968499168, -0.04409913026434982,
-2.1464646464646466, 1.025339599228244, 0.07632394072811474,
-2.095959595959596, 1.0901606111702657, -0.08961961980900318,
-2.0454545454545454, 1.149919149152138, 0.012245329149518341,
-1.9949494949494948, 1.2053683951657617, -0.043445414676939346,
-1.9444444444444444, 1.2570787221094177, 0.07034570963354128,
-1.893939393939394, 1.3054944986992738, 0.09731821393334256,
-1.8434343434343434, 1.3509699795798373, 0.04291672972144117,
-1.7929292929292928, 1.3937929948008356, -0.015954669172370275,
-1.7424242424242424, 1.4342011595393007, 0.004277923727732572,
-1.691919191919192, 1.4723933057202907, -0.06147463275240237,
-1.6414141414141414, 1.5085377537450075, -0.06797037089902819,
-1.5909090909090908, 1.5427784316797402, 0.015577891806439606,
-1.5404040404040404, 1.5752394900701356, -0.06833473099233636,
-1.4898989898989898, 1.6060288415637811, 0.05325084420435655,
-1.4393939393939394, 1.635240916755399, 0.044570288025213595,
-1.3888888888888888, 1.6629588385661962, 0.027128407849106723,
-1.3383838383838385, 1.6892561584134846, 0.0834940589766053,
-1.2878787878787878, 1.7141982574219334, 0.05241001837548184,
-1.2373737373737375, 1.7378434882914398, -0.07354005316178824,
-1.1868686868686869, 1.760244114003391, 0.006210924516653213,
-1.1363636363636365, 1.7814470856604931, -0.057681454619683686,
-1.0858585858585859, 1.801494691685491, 0.030974385027055046,
-1.0353535353535355, 1.8204251032030399, 9.757494092696439e-05,
-0.9848484848484849, 1.838272834921588, -0.019324831982828222,
-0.9343434343434345, 1.8550691366867065, 0.059054360913139314,
-0.8838383838383839, 1.8708423277236728, -0.009861420410962538,
-0.8333333333333333, 1.8856180831641267, -0.0807029848028975,
-0.7828282828282829, 1.8994196805726316, -0.04075781720639731,
-0.7323232323232323, 1.9122682127190678, 0.053001738427881445,
-0.6818181818181819, 1.9241827716833386, -0.04336963829169165,
-0.6313131313131313, 1.9351806084570582, 0.03272403635796428,
-0.5808080808080809, 1.9452772714683997, -0.03888899354798217,
-0.5303030303030303, 1.9544867268602544, -0.03634047554581024,
-0.47979797979797967, 1.9628214628672516, -0.013801712784428516,
-0.4292929292929295, 1.97029258024026, 0.06391018426545217,
-0.3787878787878789, 1.9769098703394048, -0.021251348730181127,
-0.3282828282828283, 1.9826818822440884, -0.06695943665450407,
-0.2777777777777777, 1.9876159799998132, 0.02935896308348579,
-0.22727272727272751, 1.9917183909278768, -0.09034252154626383,
-0.1767676767676769, 1.9949942457581429, -0.02901837833116401,
-0.1262626262626263, 1.9974476112013375, -0.067126138097452,
-0.07575757575757569, 1.999081515450987, 0.085643494847261,
-0.025252525252525082, 1.9998979669922556, 0.07994385756209613,
0.025252525252525082, 1.9998979669922556, -0.0016372238580262266,
0.07575757575757569, 1.999081515450987, 0.03273292585416937,
0.1262626262626263, 1.9974476112013375, 0.09435637786127879,
0.1767676767676769, 1.9949942457581429, 0.09824306173034228,
0.22727272727272707, 1.9917183909278768, -0.04876313303549267,
0.2777777777777777, 1.9876159799998132, 0.06593379027580115,
0.3282828282828283, 1.9826818822440884, 0.022793222918573303,
0.3787878787878789, 1.9769098703394048, 0.07542295190405618,
0.42929292929292906, 1.97029258024026, -0.09428952385044514,
0.47979797979797967, 1.9628214628672516, -0.01190748848224385,
0.5303030303030303, 1.9544867268602544, 0.08393509772820423,
0.5808080808080809, 1.9452772714683997, -0.06562537920411565,
0.631313131313131, 1.9351806084570582, -0.04477653724841486,
0.6818181818181817, 1.9241827716833386, 0.02462658898510879,
0.7323232323232323, 1.9122682127190678, 0.02290008792293305,
0.7828282828282829, 1.8994196805726316, 0.07570163957367101,
0.8333333333333335, 1.8856180831641267, 0.0385580164043022,
0.8838383838383836, 1.8708423277236728, -0.01056300071268386,
0.9343434343434343, 1.8550691366867065, -0.015867473843106092,
0.9848484848484849, 1.838272834921588, 0.018940527543793967,
1.0353535353535355, 1.8204251032030399, -0.061011352197926465,
1.0858585858585856, 1.8014946916854913, 0.09011044151631725,
1.1363636363636362, 1.7814470856604931, 0.013890507413416284,
1.1868686868686869, 1.760244114003391, 0.023130074172138457,
1.2373737373737375, 1.7378434882914398, -0.07820286243908776,
1.2878787878787876, 1.7141982574219337, -0.08125428190725029,
1.3383838383838382, 1.6892561584134849, 0.05442155801390133,
1.3888888888888888, 1.6629588385661962, 0.07140343660813733,
1.4393939393939394, 1.635240916755399, 0.02802625910802381,
1.4898989898989896, 1.6060288415637811, -0.007370905200411018,
1.5404040404040407, 1.5752394900701354, 0.06008804473701365,
1.5909090909090908, 1.5427784316797402, 0.08433448452398529,
1.641414141414141, 1.508537753745008, -0.09973198890907756,
1.691919191919192, 1.4723933057202907, -0.012214384092956679,
1.7424242424242422, 1.4342011595393012, -0.09689611426236062,
1.7929292929292933, 1.3937929948008352, 0.0024723225732684873,
1.8434343434343434, 1.3509699795798373, -0.05742471329858692,
1.8939393939393936, 1.305494498699274, -0.026070948386197793,
1.9444444444444446, 1.2570787221094175, 0.006611894106567082,
1.9949494949494948, 1.2053683951657617, -0.06126187760441815,
2.045454545454545, 1.1499191491521383, 0.09800642253796907,
2.095959595959596, 1.0901606111702657, 0.0732431383655873,
2.146464646464646, 1.0253395992282444, 0.01455251793450485,
2.1969696969696972, 0.9544251968499161, 0.08662939440429146,
2.2474747474747474, 0.8759387227749009, 0.0967063970863424,
2.2979797979797976, 0.7876197450350687, 0.01084944989027481,
2.3484848484848486, 0.6856793029687731, -0.09462730884670652,
2.398989898989899, 0.56276316271451, 0.0068581977418784995,
2.44949494949495, 0.3999795933984502, 0.09793899322674537,
2.5, 0.0, 0.016733349681673837,
-2.5, -0.0, 0.0699664838575533,
-2.4494949494949494, -0.3999795933984513, -0.01012979346400629,
-2.398989898989899, -0.56276316271451, 0.06817652393044826,
-2.3484848484848486, -0.6856793029687731, -0.021747911532846678,
-2.297979797979798, -0.7876197450350676, -0.09549539575694568,
-2.2474747474747474, -0.8759387227749009, 0.04743609898383214,
-2.196969696969697, -0.9544251968499168, -0.04409913026434982,
-2.1464646464646466, -1.025339599228244, 0.07632394072811474,
-2.095959595959596, -1.0901606111702657, -0.08961961980900318,
-2.0454545454545454, -1.149919149152138, 0.012245329149518341,
-1.9949494949494948, -1.2053683951657617, -0.043445414676939346,
-1.9444444444444444, -1.2570787221094177, 0.07034570963354128,
-1.893939393939394, -1.3054944986992738, 0.09731821393334256,
-1.8434343434343434, -1.3509699795798373, 0.04291672972144117,
-1.7929292929292928, -1.3937929948008356, -0.015954669172370275,
-1.7424242424242424, -1.4342011595393007, 0.004277923727732572,
-1.691919191919192, -1.4723933057202907, -0.06147463275240237,
-1.6414141414141414, -1.5085377537450075, -0.06797037089902819,
-1.5909090909090908, -1.5427784316797402, 0.015577891806439606,
-1.5404040404040404, -1.5752394900701356, -0.06833473099233636,
-1.4898989898989898, -1.6060288415637811, 0.05325084420435655,
-1.4393939393939394, -1.635240916755399, 0.044570288025213595,
-1.3888888888888888, -1.6629588385661962, 0.027128407849106723,
-1.3383838383838385, -1.6892561584134846, 0.0834940589766053,
-1.2878787878787878, -1.7141982574219334, 0.05241001837548184,
-1.2373737373737375, -1.7378434882914398, -0.07354005316178824,
-1.1868686868686869, -1.760244114003391, 0.006210924516653213,
-1.1363636363636365, -1.7814470856604931, -0.057681454619683686,
-1.0858585858585859, -1.801494691685491, 0.030974385027055046,
-1.0353535353535355, -1.8204251032030399, 9.757494092696439e-05,
-0.9848484848484849, -1.838272834921588, -0.019324831982828222,
-0.9343434343434345, -1.8550691366867065, 0.059054360913139314,
-0.8838383838383839, -1.8708423277236728, -0.009861420410962538,
-0.8333333333333333, -1.8856180831641267, -0.0807029848028975,
-0.7828282828282829, -1.8994196805726316, -0.04075781720639731,
-0.7323232323232323, -1.9122682127190678, 0.053001738427881445,
-0.6818181818181819, -1.9241827716833386, -0.04336963829169165,
-0.6313131313131313, -1.9351806084570582, 0.03272403635796428,
-0.5808080808080809, -1.9452772714683997, -0.03888899354798217,
-0.5303030303030303, -1.9544867268602544, -0.03634047554581024,
-0.47979797979797967, -1.9628214628672516, -0.013801712784428516,
-0.4292929292929295, -1.97029258024026, 0.06391018426545217,
-0.3787878787878789, -1.9769098703394048, -0.021251348730181127,
-0.3282828282828283, -1.9826818822440884, -0.06695943665450407,
-0.2777777777777777, -1.9876159799998132, 0.02935896308348579,
-0.22727272727272751, -1.9917183909278768, -0.09034252154626383,
-0.1767676767676769, -1.9949942457581429, -0.02901837833116401,
-0.1262626262626263, -1.9974476112013375, -0.067126138097452,
-0.07575757575757569, -1.999081515450987, 0.085643494847261,
-0.025252525252525082, -1.9998979669922556, 0.07994385756209613,
0.025252525252525082, -1.9998979669922556, -0.0016372238580262266,
0.07575757575757569, -1.999081515450987, 0.03273292585416937,
0.1262626262626263, -1.9974476112013375, 0.09435637786127879,
0.1767676767676769, -1.9949942457581429, 0.09824306173034228,
0.22727272727272707, -1.9917183909278768, -0.04876313303549267,
0.2777777777777777, -1.9876159799998132, 0.06593379027580115,
0.3282828282828283, -1.9826818822440884, 0.022793222918573303,
0.3787878787878789, -1.9769098703394048, 0.07542295190405618,
0.42929292929292906, -1.97029258024026, -0.09428952385044514,
0.47979797979797967, -1.9628214628672516, -0.01190748848224385,
0.5303030303030303, -1.9544867268602544, 0.08393509772820423,
0.5808080808080809, -1.9452772714683997, -0.06562537920411565,
0.631313131313131, -1.9351806084570582, -0.04477653724841486,
0.6818181818181817, -1.9241827716833386, 0.02462658898510879,
0.7323232323232323, -1.9122682127190678, 0.02290008792293305,
0.7828282828282829, -1.8994196805726316, 0.07570163957367101,
0.8333333333333335, -1.8856180831641267, 0.0385580164043022,
0.8838383838383836, -1.8708423277236728, -0.01056300071268386,
0.9343434343434343, -1.8550691366867065, -0.015867473843106092,
0.9848484848484849, -1.838272834921588, 0.018940527543793967,
1.0353535353535355, -1.8204251032030399, -0.061011352197926465,
1.0858585858585856, -1.8014946916854913, 0.09011044151631725,
1.1363636363636362, -1.7814470856604931, 0.013890507413416284,
1.1868686868686869, -1.760244114003391, 0.023130074172138457,
1.2373737373737375, -1.7378434882914398, -0.07820286243908776,
1.2878787878787876, -1.7141982574219337, -0.08125428190725029,
1.3383838383838382, -1.6892561584134849, 0.05442155801390133,
1.3888888888888888, -1.6629588385661962, 0.07140343660813733,
1.4393939393939394, -1.635240916755399, 0.02802625910802381,
1.4898989898989896, -1.6060288415637811, -0.007370905200411018,
1.5404040404040407, -1.5752394900701354, 0.06008804473701365,
1.5909090909090908, -1.5427784316797402, 0.08433448452398529,
1.641414141414141, -1.508537753745008, -0.09973198890907756,
1.691919191919192, -1.4723933057202907, -0.012214384092956679,
1.7424242424242422, -1.4342011595393012, -0.09689611426236062,
1.7929292929292933, -1.3937929948008352, 0.0024723225732684873,
1.8434343434343434, -1.3509699795798373, -0.05742471329858692,
1.8939393939393936, -1.305494498699274, -0.026070948386197793,
1.9444444444444446, -1.2570787221094175, 0.006611894106567082,
1.9949494949494948, -1.2053683951657617, -0.06126187760441815,
2.045454545454545, -1.1499191491521383, 0.09800642253796907,
2.095959595959596, -1.0901606111702657, 0.0732431383655873,
2.146464646464646, -1.0253395992282444, 0.01455251793450485,
2.1969696969696972, -0.9544251968499161, 0.08662939440429146,
2.2474747474747474, -0.8759387227749009, 0.0967063970863424,
2.2979797979797976, -0.7876197450350687, 0.01084944989027481,
2.3484848484848486, -0.6856793029687731, -0.09462730884670652,
2.398989898989899, -0.56276316271451, 0.0068581977418784995,
2.44949494949495, -0.3999795933984502, 0.09793899322674537,
2.5, -0.0, 0.016733349681673837
	};
	GLfloat wine_glass[] = {
		-0.4450,2.1100,5.1000,
-0.4450,2.0500,5.1000,
-0.4450,1.9950,5.1000,
-0.4450,1.9400,5.1000,
-0.4300,1.8100,5.1000,
-0.3800,1.7800,5.1000,
-0.3050,1.7150,5.1000,
-0.2050,1.6450,5.1000,
-0.0750,1.5900,5.1000,
0.0250,1.5500,5.1000,
0.0250,1.4900,5.1000,
0.0300,1.4200,5.1000,
0.0300,1.3550,5.1000,
0.0350,1.2550,5.1000,
0.0200,1.1950,5.1000,
0.0300,1.1350,5.1000,
0.0400,1.0950,5.1000,
0.0300,1.0500,5.1000,
-0.0200,1.0450,5.1000,
-0.1300,1.0500,5.1000,

	};
	unsigned int cubeVAO, cubeVBO, cubeEBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &cubeEBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

	// position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//vertex normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
	glEnableVertexAttribArray(2);

	//light's VAO
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	//ourShader.use();



	// Texture loading

	//Texture 0
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("transparent.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture 0" << endl;
	}
	stbi_image_free(data);



	float testBallon = 0.0;
	float testDot = 0.0;

	string diffuseMapPath;
	string specularMapPath = "";
	// Draw Cubes 
	unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

	diffuseMapPath = "new_grass.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_grass = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "green-coffee.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_coffee = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "pillar.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_pillar = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "table.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_table = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	//swimming_pool_tiles
	diffuseMapPath = "tiles.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_tiles = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	//tent_floor
	diffuseMapPath = "wood.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_wood = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "table_top.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_table_top = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "tent_wall.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_tent_wall = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "pool.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_pool = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "door.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_door = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "door2.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_door_2 = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	diffuseMapPath = "soil.jpg";
	diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	Cube cube_soil = Cube(diffMap, specMap, 92.0f, 0.0f, 0.0f, 10.0f, 10.0f);

	//notun_texture



	Cube all_cubes[] = { cube_grass , cube_coffee , cube_pillar, cube_table, cube_tiles, cube_wood, cube_table_top, cube_tent_wall, cube_pool, cube_door, cube_door_2, cube_soil };


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// activate shader
		lightingShaderWithTexture.use();
		glBindVertexArray(cubeVAO);

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
		lightingShaderWithTexture.setMat4("projection", projection);


		////testing rotating around lookat point
		//const float radius = 2.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//glm::mat4 view;
		//view = glm::lookAt(glm::vec3(camX, 1.0, camZ), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		// camera/view transformation
		//glm::mat4 view = basic_camera.createViewMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		lightingShaderWithTexture.setMat4("view", view);


		//**************lighting**************
		lightingShader.use();

		// light shader
		pointLight1.setUpPointLight(lightingShader);
		pointLight2.setUpPointLight(lightingShader);
		pointLight3.setUpPointLight(lightingShader);
		pointLight4.setUpPointLight(lightingShader);
		pointLight5.setUpPointLight(lightingShader);
		directionalLight.setUpLight(lightingShaderWithTexture);
		spotLight.setUpLight(lightingShaderWithTexture);



		pointLight0.setUpPointLight(lightingShader);
		directionalLight2.setUpLight(lightingShader);
		spotLight2.setUpLight(lightingShaderWithTexture);

		//lightingShader.use();
		spotLight3.setUpLight(lightingShaderWithTexture);

		lightingShader.use();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		//Setting up Directional Light
		directionalLight.setUpLight(lightingShaderWithTexture);
		if (!directionalLightOn)
			directionalLight.turnOff();
		if (!ambientOn)
			directionalLight.turnAmbientOff();
		if (!diffuseOn)
			directionalLight.turnDiffuseOff();
		if (!specularOn)
			directionalLight.turnSpecularOff();

		//Setting up Point Light
		{
			pointLight1.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight1.turnOff();
			if (!ambientOn)
				pointLight1.turnAmbientOff();
			if (!diffuseOn)
				pointLight1.turnDiffuseOff();
			if (!specularOn)
				pointLight1.turnSpecularOff();

			pointLight2.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight2.turnOff();
			if (!ambientOn)
				pointLight2.turnAmbientOff();
			if (!diffuseOn)
				pointLight2.turnDiffuseOff();
			if (!specularOn)
				pointLight2.turnSpecularOff();

			pointLight3.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight3.turnOff();
			if (!ambientOn)
				pointLight3.turnAmbientOff();
			if (!diffuseOn)
				pointLight3.turnDiffuseOff();
			if (!specularOn)
				pointLight3.turnSpecularOff();

			pointLight4.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight4.turnOff();
			if (!ambientOn)
				pointLight4.turnAmbientOff();
			if (!diffuseOn)
				pointLight4.turnDiffuseOff();
			if (!specularOn)
				pointLight4.turnSpecularOff();

			pointLight5.setUpPointLight(lightingShaderWithTexture);
			if (!pointLightOn)
				pointLight5.turnOff();
			if (!ambientOn)
				pointLight5.turnAmbientOff();
			if (!diffuseOn)
				pointLight5.turnDiffuseOff();
			if (!specularOn)
				pointLight5.turnSpecularOff();
		}


		//Setting up Spot Light
		spotLight.setUpLight(lightingShaderWithTexture);
		spotLight2.setUpLight(lightingShaderWithTexture);
		spotLight3.setUpLight(lightingShaderWithTexture);
		if (!spotLightOn) {
			spotLight.turnOff();
			spotLight2.turnOff();
			spotLight3.turnOff();
		}

		if (!ambientOn) {
			spotLight.turnAmbientOff();
			spotLight2.turnAmbientOff();
			spotLight3.turnAmbientOff();
		}

		if (!diffuseOn) {
			spotLight.turnDiffuseOff();
			spotLight2.turnDiffuseOff();
			spotLight3.turnDiffuseOff();
		}

		if (!specularOn) {
			spotLight.turnSpecularOff();
			spotLight2.turnSpecularOff();
			spotLight3.turnSpecularOff();
		}


		//Setting up Camera and Others
		lightingShaderWithTexture.setVec3("viewPos", camera.Position);
		lightingShaderWithTexture.setBool("lightingOn", lightingOn);
		lightingShaderWithTexture.setFloat("ambientOn", ambientOn);
		lightingShaderWithTexture.setFloat("diffuseOn", diffuseOn);
		lightingShaderWithTexture.setFloat("specularOn", specularOn);
		lightingShaderWithTexture.setFloat("pointLightOn", pointLightOn);
		lightingShaderWithTexture.setFloat("directionalLightOn", directionalLightOn);
		lightingShaderWithTexture.setFloat("spotLightOn", spotLightOn);
		lightingShaderWithTexture.setBool("dark", dark);

		////For axis
		//ourShader.use();
		//glm::mat4 identity = glm::mat4(1.0f); // identity matrix
		//ourShader.setMat4("model", identity);
		//glBindVertexArray(axisVAO);
		//glDrawArrays(GL_LINES, 0, 6);


		// Starting
		glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 translateMatrix, model, rotation, scale, translate;
		glm::vec4 color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


		//float dx = 0.5;
		//for (int i = 0; i < 6; i++) {

		//	//tree curve here
		//	lightingShader.use();
		//	CurveObj tree;
		//	tree.ambient = glm::vec4(0.0, 1.0, 0.0, 1.0);
		//	tree.diffuse = glm::vec4(0.6, 0.21, 0.05, 1.0);
		//	tree.specular = glm::vec4(0.10, 0.21, 0.05, 1.0);
		//	tree.translation = glm::vec3(10.5f + dx, 0.1f, 0.8f);
		//	tree.scale = glm::vec3(0.3f, 0.56f, 0.3f);
		//	tree.hollowBezier(treeCuve, (sizeof(treeCuve) / sizeof(treeCuve[0])) / 3 - 1, lightingShader);

		//	//Picher
		//	CurveObj tree_leaf1;
		//	tree_leaf1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf1.translation = glm::vec3(10.5f + dx, 1.0f, 0.9f);
		//	tree_leaf1.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf1.rotateX = glm::radians(-30.0f);
		//	tree_leaf1.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//samner
		//	CurveObj tree_leaf2;
		//	tree_leaf2.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf2.translation = glm::vec3(10.5f + dx, 1.0f, 0.7f);
		//	tree_leaf2.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf2.rotateX = glm::radians(30.0f);
		//	tree_leaf2.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//bamer
		//	CurveObj tree_leaf3;
		//	tree_leaf3.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf3.translation = glm::vec3(10.6f + dx, 1.0f, 0.7f);
		//	tree_leaf3.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf3.rotateZ = glm::radians(30.0f);
		//	tree_leaf3.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//daner
		//	CurveObj tree_leaf4;
		//	tree_leaf4.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf4.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf4.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf4.translation = glm::vec3(10.3f + dx, 1.0f, 0.7f);
		//	tree_leaf4.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf4.rotateZ = glm::radians(-30.0f);
		//	tree_leaf4.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	dx += 0.5;
		//}
		//dx = 0.5;
		//for (int i = 0; i < 6; i++) {

		//	//tree curve here
		//	lightingShader.use();
		//	CurveObj tree;
		//	tree.ambient = glm::vec4(0.0, 1.0, 0.0, 1.0);
		//	tree.diffuse = glm::vec4(0.6, 0.21, 0.05, 1.0);
		//	tree.specular = glm::vec4(0.10, 0.21, 0.05, 1.0);
		//	tree.translation = glm::vec3(10.5f + dx, 0.1f, 0.8f + 0.5f);
		//	tree.scale = glm::vec3(0.3f, 0.56f, 0.3f);
		//	tree.hollowBezier(treeCuve, (sizeof(treeCuve) / sizeof(treeCuve[0])) / 3 - 1, lightingShader);

		//	//Picher
		//	CurveObj tree_leaf1;
		//	tree_leaf1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf1.translation = glm::vec3(10.5f + dx, 1.0f, 0.9f + 0.5f);
		//	tree_leaf1.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf1.rotateX = glm::radians(-30.0f);
		//	tree_leaf1.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//samner
		//	CurveObj tree_leaf2;
		//	tree_leaf2.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf2.translation = glm::vec3(10.5f + dx, 1.0f, 0.7f + 0.5f);
		//	tree_leaf2.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf2.rotateX = glm::radians(30.0f);
		//	tree_leaf2.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//bamer
		//	CurveObj tree_leaf3;
		//	tree_leaf3.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf3.translation = glm::vec3(10.6f + dx, 1.0f, 0.7f + 0.5f);
		//	tree_leaf3.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf3.rotateZ = glm::radians(30.0f);
		//	tree_leaf3.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//daner
		//	CurveObj tree_leaf4;
		//	tree_leaf4.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf4.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf4.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf4.translation = glm::vec3(10.3f + dx, 1.0f, 0.7f + 0.5f);
		//	tree_leaf4.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf4.rotateZ = glm::radians(-30.0f);
		//	tree_leaf4.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	dx += 0.5;
		//}
		//dx = 0.5;
		//for (int i = 0; i < 6; i++) {

		//	//tree curve here
		//	lightingShader.use();
		//	CurveObj tree;
		//	tree.ambient = glm::vec4(0.0, 1.0, 0.0, 1.0);
		//	tree.diffuse = glm::vec4(0.6, 0.21, 0.05, 1.0);
		//	tree.specular = glm::vec4(0.10, 0.21, 0.05, 1.0);
		//	tree.translation = glm::vec3(10.5f + dx, 0.1f, 0.8f + 1.0f);
		//	tree.scale = glm::vec3(0.3f, 0.56f, 0.3f);
		//	tree.hollowBezier(treeCuve, (sizeof(treeCuve) / sizeof(treeCuve[0])) / 3 - 1, lightingShader);

		//	//Picher
		//	CurveObj tree_leaf1;
		//	tree_leaf1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf1.translation = glm::vec3(10.5f + dx, 1.0f, 0.9f + 1.0f);
		//	tree_leaf1.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf1.rotateX = glm::radians(-30.0f);
		//	tree_leaf1.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//samner
		//	CurveObj tree_leaf2;
		//	tree_leaf2.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf2.translation = glm::vec3(10.5f + dx, 1.0f, 0.7f + 1.0f);
		//	tree_leaf2.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf2.rotateX = glm::radians(30.0f);
		//	tree_leaf2.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//bamer
		//	CurveObj tree_leaf3;
		//	tree_leaf3.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf3.translation = glm::vec3(10.6f + dx, 1.0f, 0.7f + 1.0f);
		//	tree_leaf3.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf3.rotateZ = glm::radians(30.0f);
		//	tree_leaf3.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//daner
		//	CurveObj tree_leaf4;
		//	tree_leaf4.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf4.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf4.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf4.translation = glm::vec3(10.3f + dx, 1.0f, 0.7f + 1.0f);
		//	tree_leaf4.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf4.rotateZ = glm::radians(-30.0f);
		//	tree_leaf4.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	dx += 0.5;
		//}
		//dx = 0.5;
		//for (int i = 0; i < 6; i++) {

		//	//tree curve here
		//	lightingShader.use();
		//	CurveObj tree;
		//	tree.ambient = glm::vec4(0.0, 1.0, 0.0, 1.0);
		//	tree.diffuse = glm::vec4(0.6, 0.21, 0.05, 1.0);
		//	tree.specular = glm::vec4(0.10, 0.21, 0.05, 1.0);
		//	tree.translation = glm::vec3(10.5f + dx, 0.1f, 0.8f + 1.5f);
		//	tree.scale = glm::vec3(0.3f, 0.56f, 0.3f);
		//	tree.hollowBezier(treeCuve, (sizeof(treeCuve) / sizeof(treeCuve[0])) / 3 - 1, lightingShader);

		//	//Picher
		//	CurveObj tree_leaf1;
		//	tree_leaf1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf1.translation = glm::vec3(10.5f + dx, 1.0f, 0.9f + 1.5f);
		//	tree_leaf1.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf1.rotateX = glm::radians(-30.0f);
		//	tree_leaf1.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//samner
		//	CurveObj tree_leaf2;
		//	tree_leaf2.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf2.translation = glm::vec3(10.5f + dx, 1.0f, 0.7f + 1.5f);
		//	tree_leaf2.scale = glm::vec3(0.4f, 0.8f, 0.05f);
		//	tree_leaf2.rotateX = glm::radians(30.0f);
		//	tree_leaf2.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//bamer
		//	CurveObj tree_leaf3;
		//	tree_leaf3.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf3.translation = glm::vec3(10.6f + dx, 1.0f, 0.7f + 1.5f);
		//	tree_leaf3.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf3.rotateZ = glm::radians(30.0f);
		//	tree_leaf3.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	//daner
		//	CurveObj tree_leaf4;
		//	tree_leaf4.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		//	tree_leaf4.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		//	tree_leaf4.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		//	tree_leaf4.translation = glm::vec3(10.3f + dx, 1.0f, 0.7f + 1.5f);
		//	tree_leaf4.scale = glm::vec3(0.05f, 0.8f, 0.4f);
		//	tree_leaf4.rotateZ = glm::radians(-30.0f);
		//	tree_leaf4.hollowBezier(bodyCurve, (sizeof(bodyCurve) / sizeof(bodyCurve[0])) / 3 - 1, lightingShader);

		//	dx += 0.5;
		//}


//eikhane tree

		

		//fountain 
		lightingShader.use();
		CurveObj fountain_lomba;
		fountain_lomba.ambient = glm::vec4(0.0, 1.0, 0.0, 1.0);
		fountain_lomba.diffuse = glm::vec4(0.6, 0.21, 0.05, 1.0);
		fountain_lomba.specular = glm::vec4(0.10, 0.21, 0.05, 1.0);
		fountain_lomba.translation = glm::vec3(8.5f, -1.49f, 5.0f);
		fountain_lomba.scale = glm::vec3(0.15f, 1.1f, 0.15f);
		fountain_lomba.hollowBezier(leafCurve, (sizeof(leafCurve) / sizeof(leafCurve[0])) / 3 - 1, lightingShader);

		//fountain gol
		lightingShader.use();
		CurveObj golla;
		golla.ambient = glm::vec4(0.6, 0.2, 0.6, 1.0);
		golla.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		golla.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		golla.translation = glm::vec3(8.5f, 0.38f, 5.0f);
		golla.scale = glm::vec3(0.7f, 1.5f, 0.7f);
		golla.hollowBezier(points, (sizeof(points) / sizeof(points[0])) / 3 - 1, lightingShader);


		//fountain 2nd lomba
		lightingShader.use();
		CurveObj choto_lomba;
		choto_lomba.ambient = glm::vec4(0.1, 0.0, 0.0, 1.0);
		choto_lomba.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		choto_lomba.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		choto_lomba.translation = glm::vec3(8.5f, 1.3f, 5.0f);
		choto_lomba.scale = glm::vec3(0.1f, 0.25f, 0.1f);
		choto_lomba.hollowBezier(treeCuve, (sizeof(treeCuve) / sizeof(treeCuve[0])) / 3 - 1, lightingShader);

		//fountain gol
		lightingShader.use();
		CurveObj golla2;
		golla2.ambient = glm::vec4(0.02, 0.5, 0.5, 1.0);
		golla2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		golla2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		golla2.translation = glm::vec3(8.5f, 1.4f, 5.0f);
		golla2.scale = glm::vec3(0.2f, 0.7f, 0.2f);
		golla2.hollowBezier(points, (sizeof(points) / sizeof(points[0])) / 3 - 1, lightingShader);

		//fountain 2nd lomba
		lightingShader.use();
		CurveObj choto_lomba2;
		choto_lomba2.ambient = glm::vec4(0.1, 0.0, 0.0, 1.0);
		choto_lomba2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		choto_lomba2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		choto_lomba2.translation = glm::vec3(8.5f, 1.8f, 5.0f);
		choto_lomba2.scale = glm::vec3(0.1f, 0.15f, 0.1f);
		choto_lomba2.hollowBezier(treeCuve, (sizeof(treeCuve) / sizeof(treeCuve[0])) / 3 - 1, lightingShader);
		

		//first traffice light
		lightingShader.use();
		CurveObj bulb_box1;
		bulb_box1.ambient = glm::vec4(0.0, 0.0, 0.0, 1.0);
		bulb_box1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		bulb_box1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		bulb_box1.translation = glm::vec3(0.1f, 3.46f, 13.5f);
		bulb_box1.scale = glm::vec3(0.2f, .2f, 0.2f);
		bulb_box1.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);


		CurveObj lamp1;
		lamp1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		lamp1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		lamp1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		lamp1.translation = glm::vec3(0.1f, 3.2f, 13.5f);
		lamp1.scale = glm::vec3(0.1f, 0.3f, 0.1f);
		lamp1.hollowBezier(lampPoints, (sizeof(lampPoints) / sizeof(lampPoints[0])) / 3 - 1, lightingShader);


		lightingShader.use();
		//second traffice light
		CurveObj bulb_box2;
		bulb_box2.ambient = glm::vec4(0.0, 0.0, 0.0, 1.0);
		bulb_box2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		bulb_box2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		bulb_box2.translation = glm::vec3(11.0f, 3.46f, 13.5f);
		bulb_box2.scale = glm::vec3(0.2f, .2f, 0.2f);
		bulb_box2.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);


		CurveObj lamp2;
		lamp2.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		lamp2.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		lamp2.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		lamp2.translation = glm::vec3(11.0f, 3.2f, 13.5f);
		lamp2.scale = glm::vec3(0.1f, 0.3f, 0.1f);
		lamp2.hollowBezier(lampPoints, (sizeof(lampPoints) / sizeof(lampPoints[0])) / 3 - 1, lightingShader);


		lightingShader.use();
		//third traffice light
		CurveObj bulb_box3;
		bulb_box3.ambient = glm::vec4(0.0, 0.0, 0.0, 1.0);
		bulb_box3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		bulb_box3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		bulb_box3.translation = glm::vec3(23.0f, 3.46f, 13.5f);
		bulb_box3.scale = glm::vec3(0.2f, .2f, 0.2f);
		bulb_box3.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);


		CurveObj lamp3;
		lamp3.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		lamp3.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		lamp3.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		lamp3.translation = glm::vec3(23.0f, 3.2f, 13.5f);
		lamp3.scale = glm::vec3(0.1f, 0.3f, 0.1f);
		lamp3.hollowBezier(lampPoints, (sizeof(lampPoints) / sizeof(lampPoints[0])) / 3 - 1, lightingShader);


		//plate for table one
		lightingShader.use();
		CurveObj plate1;
		plate1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		plate1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		plate1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		plate1.translation = glm::vec3(2.0, 0.49, 3.2);
		plate1.scale = glm::vec3(0.25f, 0.3f, 0.25f);
		plate1.hollowBezier(points, (sizeof(points) / sizeof(points[0])) / 3 - 1, lightingShader);

		//wine glass for table one
		lightingShader.use();
		CurveObj wine_glass1;
		wine_glass1.ambient = glm::vec4(0.32, 0.5, 0.8, 1.0);
		wine_glass1.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
		wine_glass1.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
		wine_glass1.translation = glm::vec3(2.5, 0.32, 3.2);
		wine_glass1.scale = glm::vec3(0.25f, 0.3f, 0.25f);
		wine_glass1.hollowBezier(wine_glass, (sizeof(wine_glass) / sizeof(wine_glass[0])) / 3 - 1, lightingShader);

		// niche namteche
		float dy = 0.0; 
		float poredx = 0.0;
		float poredx2 = 0.0;
		float poredy = 0.01; 
		float middleDx = 0.02;
		for (int i = 0; i < 100; i++) {
			if (i <= 6) {

				if (i <= 2) {
					translateMatrix = glm::translate(identityMatrix, glm::vec3(8.5 + poredx - 0.03, 2.10 - dy + globalDownDotStep + poredy - 0.001, 5.0));
					color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
					dotdot(lightingShader, translateMatrix, color1, all_cubes);

				}
				else if (i == 3) {
					translateMatrix = glm::translate(identityMatrix, glm::vec3(8.5 + poredx2, 2.19 - dy + globalDotStep + poredy - 0.002 - 0.1, 5.0));
					color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
					dotdot(lightingShader, translateMatrix, color1, all_cubes);

				}

				poredx += 0.03;
				poredx2 += 0.02;
				poredy += 0.02;

			}
			else if (i <= 25)
			{
				translateMatrix = glm::translate(identityMatrix, glm::vec3(8.55, 2.12 - dy + globalDotStep - 0.001, 5.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				dotdot(lightingShader, translateMatrix, color1, all_cubes);

			}
			else if (i >= 26 && i <= 39) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(8.301 + middleDx, 1.945, 5.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				dotdot(lightingShader, translateMatrix, color1, all_cubes);

			}
			else if (i == 40) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(8.725, 1.93, 5.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				dotdot(lightingShader, translateMatrix, color1, all_cubes);

			}
			else {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(8.725, 2.3 - dy + globalDotStep, 5.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				dotdot(lightingShader, translateMatrix, color1, all_cubes);
			}
			
			/*if (i <= 50) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 + 0.75 - 0.03, 1.19 - dy + globalDownDotStep, 6.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				dotdot(lightingShader, translateMatrix, color1, all_cubes);
				
				
			}*/
			
				
			dy += 0.01;
			middleDx += 0.01;
		}
	 

		lightingShaderWithTexture.use();

		// Grass
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Grasses(lightingShaderWithTexture, translateMatrix, color1, all_cubes);


		//Tent
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		float dxx = 0.0f;
		for (int i = 0; i < 2; i++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f + dxx, 0.0f, 0.5f));
			Tent(lightingShaderWithTexture, translateMatrix, translateMatrix, color1, all_cubes, false);
			dxx += 18.5f;
		}
	

		//swimming_pool
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		SwimmingPool(lightingShaderWithTexture, translateMatrix, color1, all_cubes);


		//street
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		Street(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		//traffic_light
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		TrafficLight(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		//mati
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		Mati(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

		////ulta tent
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 0.0f, 10.9f));
		TentY(lightingShaderWithTexture, translateMatrix, 180.0f, all_cubes);

		////right ulta tent
		color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		translateMatrix = glm::translate(identityMatrix, glm::vec3(23.5f, 0.0f, 10.9f));
		TentY(lightingShaderWithTexture, translateMatrix, 180.0f, all_cubes);

		//table for ulta right tent
		translateMatrix = glm::translate(identityMatrix, glm::vec3(20.9f, 0.61f, 8.8f));
		Table(lightingShaderWithTexture, translateMatrix, 0.0f, false, all_cubes);


		//chair for ulta right tent
		translateMatrix = glm::translate(identityMatrix, glm::vec3(21.3f, 0.61f, 9.5f));
		Chair(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);

		//rasta
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		Boro_Raste(lightingShaderWithTexture, translateMatrix, color1, all_cubes);
		 

		if (isglobalDotOn) {

			globalDotStep -= 0.0006;
			globalDownDotStep += 0.0006;

			if (globalDotStep < -0.001 * 25)
			{
				globalDotStep = 0.01;
			}
			if (globalDownDotStep >  0.001 * 25)
			{
				globalDownDotStep = 0.01;
			}


		}


		/*	for (int i = 0; i < 3; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f * i, 0.0f, 0.0f));
				Tent(ourShader, translateMatrix, color1);

			}*/

			//Floor

			/*translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Floor(lightingShaderWithTexture, translateMatrix, color1, all_cubes);*/


			/*float dy = 5.0 - 1.5;
			float dz = -7.3f;
			translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 3.6, 0.0f + dz));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			SecondFloorShamne(lightingShaderWithTexture, translateMatrix, color1, all_cubes);*/


			//Pillars
			//translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
			//color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			//Pillars(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

			////Choto red bricks blocks
			//translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 3.5f + 1.5, -0.2 + 0.05f));
			//color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			//ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);
			////Choto red bricks blocks 2 
			//translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5 + 0.5, 3.5f + 1.5, -0.2 + 0.05f));
			//color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			//ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

			//int dx = 1.8;
			//for (int i = 0; i < 4; i++) {
			//	//Choto red bricks blocks 2 
			//	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 + 0.5 * i + dx, 3.5f + 1.5, -0.2 + 0.05f));
			//	color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			//	ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);
			//	dx += 3.0;

			//}


			//Choto red bricks blocks
		/*	translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.0, 3.5f + 1.5, -0.2 + 0.05f));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);*/

			//Choto red bricks blocks 2 
			/*translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.85 - 3.0, 3.5f + 1.5, -0.2 + 0.05f));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChotoBlocks(lightingShaderWithTexture, translateMatrix, color1, all_cubes);*/

			// Corner tables
		/*	float translate_table = 0.0;
			for (int i = 0; i < 4; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 + translate_table, 1.0, -6.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Table(lightingShaderWithTexture, translateMatrix, 0.0f, false, all_cubes);
				translate_table += 1.6;


			}
			float translate_chair = -0.2;
			for (int i = 0; i < 10; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 + translate_chair, 1.0, -6.0 + 0.7));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Chair(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);
				translate_chair += 0.6;
			}

			translate_chair = -0.2;
			for (int i = 0; i < 10; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 + 0.6 + translate_chair, 1.0, -6.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
				translate_chair += 0.6;
			}



			translate_table = 0.0;
			for (int i = 0; i < 3; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 - translate_table, 1.0, -10.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Table(lightingShaderWithTexture, translateMatrix, 90.0f, true, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4 - .5, 1.0, -10.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Chair(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 0.7 - .5, 1.0, -10.0));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Chair(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4, 1.0, -10.0 - 1.5));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 0.7, 1.0, -10.0 - 1.5));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4 - 1.5, 1.0, -10.0 - 1.5 + .65));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0f - translate_table + 1.4 - 1.5 + 1.60f, 1.0, -10.0 - 1.5 + 1.1));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

				translate_table += 5.0;
			}




			translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0, 1.0, -5.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 90.0f, true, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 + 4, 1.0, -5.0 - 0.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 0.8 + 4, 1.0, -5.0 - 0.5 - 1.2));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4 + 4, 1.0, -5.0 - 0.5 - 1.2));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 1.0 - 0.6 + 4, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4 - 0.6, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);


			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0, 1.0, -5.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Table(lightingShaderWithTexture, translateMatrix, 90.0f, true, all_cubes);


			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6, 1.0, -5.0 - 0.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 0.8, 1.0, -5.0 - 0.5 - 1.2));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4, 1.0, -5.0 - 0.5 - 1.2));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180.0, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.6 - 1.0 - 0.6, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);
			translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 1.4 - 0.6, 1.0, -5.0 - 0.5 - 1.2 + 1.5));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);

			translate_table = 0.0;
			for (int i = 0; i < 2; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0, 1.0, -16.0 + translate_table));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Table(lightingShaderWithTexture, translateMatrix, 90.0f, false, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + 1.0, 1.0, -16.0 + translate_table));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 - 0.5, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 - 0.3, 1.0, -16.0 + translate_table - 0.6 - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);


				translate_table += 1.5;



			}
			translate_table = 0;
			for (int i = 0; i < 2; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0, 1.0, -16.0 + translate_table));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Table(lightingShaderWithTexture, translateMatrix, 0.0f, false, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 + 1.0, 1.0, -16.0 + translate_table));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 - 0.5, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(16.0 - 0.3, 1.0, -16.0 + translate_table - 0.6 - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);


				translate_table += 1.5;



			}

			translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0, 0.0, 0.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			CafeFoodCounter(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			CafeShop(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(9.6, 1.0, -18.7f));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			RotateChairY(lightingShaderWithTexture, translateMatrix, 180, all_cubes);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 + 0.60, 0.0, -2));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			CoffeMachine(lightingShaderWithTexture, translateMatrix, color1, all_cubes);

			translate_table = 0;
			for (int i = 0; i < 2; i++) {
				translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0, 1.0, -16.0 + translate_table));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				Table(lightingShaderWithTexture, translateMatrix, 90.0f, false, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 + 1.0, 1.0, -16.0 + translate_table));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 + 1.0, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, 90.0, all_cubes);

				translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 - 0.5, 1.0, -16.0 + translate_table - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(12.0 - 0.3, 1.0, -16.0 + translate_table - 0.6 - 0.6));
				color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				RotateChairY(lightingShaderWithTexture, translateMatrix, -90.0, all_cubes);


				translate_table += 1.5;



			}


			if (isglobalBallonOn) {

				if (globalBallonRotation <= 15 && testBallon != 0.0) {
					globalBallonRotation += 0.4f;
					if (globalBallonRotation >= 15) {
						testBallon = 0.0;
					}
				}
				else {
					globalBallonRotation -= 0.4f;
					if (globalBallonRotation < -15) {
						testBallon = 1.0;
					}
				}



			}


			if (isglobalDotOn) {

				globalDotStep += 0.003;

				if (globalDotStep > 0.01 * 5 )
				{
					globalDotStep = 0.0;
				}


			}

			float translate_ballon = 0.0;
			for (int i = 0; i < 4; i++) {
				CurveObj co;
				co.ambient = glm::vec4(0.6f, 0.9f, 0.6f, 1.0);

				co.hollowBezier(blank, (sizeof(blank) / sizeof(blank[0])) / 3 - 1, lightingShader);
				glm::vec3 ambient1 = glm::vec3(0.0f, 0.9f, 0.0f);
				glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f + translate_ballon, 2.5, -10));
				Baloon(lightingShaderWithTexture, lightingShader, translateMatrix, rotationAxis, ambient1, color1, globalBallonRotation, all_cubes);
				translate_ballon += 7.0;
			}

			lightingShader.use();
			translate_ballon = 0.0;
			for (int i = 0; i < 4; i++) {
				CurveObj co;
				co.ambient = glm::vec4(0.4f, 0.6f, 0.9f, 1.0);

				co.hollowBezier(blank, (sizeof(blank) / sizeof(blank[0])) / 3 - 1, lightingShader);
				glm::vec3 ambient1 = glm::vec3(0.0f, 0.9f, 0.0f); 			glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f + translate_ballon, 2.5, -13));
				Baloon(lightingShaderWithTexture, lightingShader, translateMatrix, rotationAxis, ambient1, color1, globalBallonRotation, all_cubes);
				translate_ballon += 7.0;
			}
			translate_ballon = 0.0;
			for (int i = 0; i < 4; i++) {
				CurveObj co;
				co.ambient = glm::vec4(0.8f, 0.4f, 0.1f, 1.0);

				co.hollowBezier(blank, (sizeof(blank) / sizeof(blank[0])) / 3 - 1, lightingShader);
				glm::vec3 ambient1 = glm::vec3(0.0f, 0.9f, 0.0f);
				glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
				translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f + translate_ballon, 2.5, -16));
				Baloon(lightingShaderWithTexture, lightingShader, translateMatrix, rotationAxis, ambient1, color1, globalBallonRotation, all_cubes);
				translate_ballon += 7.0;
			}




			translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0 + 5, 3 - 1, -20 + 0.3));
			TubeLight(lightingShaderWithTexture, translateMatrix, color1, all_cubes);*/

			// point lights 

			  // make sure to initialize matrix to identity matrix first
			/*lightPositions[0] = glm::vec3(7.0 + 5, 3.01 - 1, -20 + 0.36);
			glm::mat4 model;
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPositions[0]);
			model = glm::scale(model, glm::vec3(2, 0.01, 0.01));
			lightingShader.setMat4("model", model);
			lightingShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
			all_cubes[1].drawCubeWithTexture(lightingShaderWithTexture, model);



			float spotLightDz = 0.0;
			for (int i = 0; i < 3; i++) {

				translateMatrix = glm::translate(identityMatrix, glm::vec3(4.2f, 2.5, -5.0 - spotLightDz));
				SpotLightWithCurve(lightingShaderWithTexture, lightingShader, translateMatrix, color1, all_cubes, reverseCurve);

				CurveObj lightCurve;
				lightCurve.ambient = glm::vec4(0.06, 0.05, 0.08, 1.0);
				lightCurve.diffuse = glm::vec4(0.32, 0.21, 0.05, 1.0);
				lightCurve.specular = glm::vec4(0.0, 0.21, 0.05, 1.0);
				lightCurve.translation = glm::vec3(4.2f, 2.5, -5.0f - spotLightDz);
				lightCurve.scale = glm::vec3(0.2f, .2f, 0.2f);
				lightCurve.hollowBezier(reverseCurve, (sizeof(reverseCurve) / sizeof(reverseCurve[0])) / 3 - 1, lightingShader);

				spotLightDz += 2.0;
			}

			translateMatrix = glm::translate(identityMatrix, glm::vec3(23.0,.40, 1.5f));
			shiri(lightingShaderWithTexture, translateMatrix, color1, all_cubes, 20 );


			translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0,1.0,10.0));
			color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Chair(lightingShaderWithTexture, translateMatrix, 0.0, all_cubes);*/



			//    glDrawArrays(GL_TRIANGLES, 0, 36);
			//}

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &cubeEBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}


void Tent(Shader ourShader, glm::mat4 moveMatrix, glm::mat4 forTableChair, glm::vec4 color, Cube all_cubes[], bool isRotate)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateMatrix;



	// tent roof(it will be curve) 
 // Roof Part 1
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 2.5f, 0.0f)); // Centered and above the tent
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.18f, 9.0f)); // Match tent's width, half depth
	rotateMatrix = glm::rotate(identityMatrix, glm::radians(-1.5f), glm::vec3(1.0f, 0.0f, 0.0f)); // Tilt the roof
	model = moveMatrix * translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, model); // Assuming index 9 for the first part of the roof

	// Roof Part 2
	//translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 2.5f, 2.0f)); // Same position as Part 1
	//scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.2f, 4.0f)); // Same scale as Part 1
	//rotateMatrix = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Opposite tilt
	//model = moveMatrix * translateMatrix * rotateMatrix * scaleMatrix;
	//all_cubes[10].drawCubeWithTexture(ourShader, model); // Assuming index 10 for the second part of the roof

	// tent floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.0f, 0.2f, 8.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//chair
	translateMatrix = isRotate ? glm::translate(identityMatrix, glm::vec3(3.6, 0.6, 9.2)) : glm::translate(identityMatrix, glm::vec3(1.8, 0.6, 3.5)) * forTableChair;
	Chair(ourShader, translateMatrix, 0.0, all_cubes);


	//table
	translateMatrix = isRotate ? glm::translate(identityMatrix, glm::vec3(3.0, 0.6, 8.5)) : glm::translate(identityMatrix, glm::vec3(1.5, 0.6, 2.8)) * forTableChair;
	//color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Table(ourShader, translateMatrix, 0.0f, false, all_cubes);


	// Bed Frame
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.2f, 2.0f)); // Adjust these values as needed
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.5f, 3.0f)); // Adjust the size of the bed frame
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Mattress
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.45f, 2.0f)); // Adjust for the height of the bed frame
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, 3.0f)); // Adjust the thickness of the mattress
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Bed Head
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.5f, 2.0f)); // Adjust position for bed head
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, 0.2f)); // Adjust size for bed head
	model = translateMatrix * scaleMatrix;
	all_cubes[6].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Pillow
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.35f, 0.46f, 2.1f)); // Adjust position for pillow on mattress
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.2f, 0.45f)); // Adjust size for pillow
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);


	// tent pichoner wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.0f, 5.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	// tent left wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 5.0f, 8.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);


	// tent right wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 5.0f, 8.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//samer first wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.5f, 5.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//samner second wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.95f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.5f, 5.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//samner choto cube
	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 1.5f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja first part
	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.65f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 3.0f, 0.4f));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = translateMatrix * scaleMatrix * rotationMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja second part
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.3f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 3.0f, 0.4f));
	//glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//Window 1st
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.8f, 4.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.8f, 0.1f));
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix * model);

	//Window 2nd
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.4f, 0.8f, 4.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.8f, 0.1f));
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix* model);

}


void Boro_Raste(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateMatrix;

	// Pichoner wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, -0.17f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(48.0f, 6.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//left wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.17f, 0.0, -0.17f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 6.0f, 22.6f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//right wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(23.9f, 0.0, -0.17f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 6.0f, 22.6f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//front first wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.17f, 0.0, 11.1f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.0f, 6.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//front second wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(14.85f, 0.0, 11.1f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(18.5f, 6.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//uporer wall first
	translateMatrix = glm::translate(identityMatrix, glm::vec3(9.5f, 3.0, 11.1f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 4.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//uporer wall second
	translateMatrix = glm::translate(identityMatrix, glm::vec3(14.86f, 3.0, 11.1f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 4.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//uporer wall second
	translateMatrix = glm::translate(identityMatrix, glm::vec3(9.5f, 4.5, 11.1f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(11.0f, 2.5f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

}


void Tent1(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateMatrix;



	// tent roof(it will be curve) 
 // Roof Part 1
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 2.5f, 0.0f)); // Centered and above the tent
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.18f, 9.0f)); // Match tent's width, half depth
	rotateMatrix = glm::rotate(identityMatrix, glm::radians(-1.5f), glm::vec3(1.0f, 0.0f, 0.0f)); // Tilt the roof
	model = moveMatrix * translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, model); // Assuming index 9 for the first part of the roof

	// Roof Part 2
	//translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 2.5f, 2.0f)); // Same position as Part 1
	//scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.2f, 4.0f)); // Same scale as Part 1
	//rotateMatrix = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Opposite tilt
	//model = moveMatrix * translateMatrix * rotateMatrix * scaleMatrix;
	//all_cubes[10].drawCubeWithTexture(ourShader, model); // Assuming index 10 for the second part of the roof

	// tent floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.0f, 0.2f, 8.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);

	//chair
	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.8, 0.6, 3.5));
	Chair(ourShader, translateMatrix, 0.0, all_cubes);


	//table
	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5, 0.6, 2.8));
	//color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Table(ourShader, translateMatrix, 0.0f, false, all_cubes);


	// Bed Frame
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.2f, 2.0f)); // Adjust these values as needed
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.5f, 3.0f)); // Adjust the size of the bed frame
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Mattress
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.45f, 2.0f)); // Adjust for the height of the bed frame
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, 3.0f)); // Adjust the thickness of the mattress
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Bed Head
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.5f, 2.0f)); // Adjust position for bed head
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, 0.2f)); // Adjust size for bed head
	model = translateMatrix * scaleMatrix;
	all_cubes[6].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Pillow
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.35f, 0.46f, 2.1f)); // Adjust position for pillow on mattress
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.2f, 0.45f)); // Adjust size for pillow
	model = translateMatrix * scaleMatrix;
	all_cubes[5].drawCubeWithTexture(ourShader, moveMatrix * model);


	// tent pichoner wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.0f, 5.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	// tent left wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 5.0f, 8.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);


	// tent right wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 5.0f, 8.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//samer first wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.5f, 5.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//samner second wall
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.95f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.5f, 5.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//samner choto cube
	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 1.5f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja first part
	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.65f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 3.0f, 0.4f));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = translateMatrix * scaleMatrix * rotationMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja second part
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.3f, 0.0f, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 3.0f, 0.4f));
	//glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//Window 1st
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.8f, 4.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.8f, 0.1f));
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix * model);

	//Window 2nd
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.4f, 0.8f, 4.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.8f, 0.1f));
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix * model);

}


void SwimmingPool(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateMatrix;

	//water
	translateMatrix = glm::translate(identityMatrix, glm::vec3(11.0f, 0.0, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 1.0f, 7.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[8].drawCubeWithTexture(ourShader, moveMatrix * model);

	//left border
	translateMatrix = glm::translate(identityMatrix, glm::vec3(10.8f, 0.0, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 1.2f, 7.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//right bordera
	translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5f, 0.0, 4.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 1.2f, 7.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//top border
	translateMatrix = glm::translate(identityMatrix, glm::vec3(10.8f, 0.0, 3.89f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.69f, 1.2f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	//bottom border
	translateMatrix = glm::translate(identityMatrix, glm::vec3(10.8f, 0.0, 7.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.69f, 1.2f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);


	//first pool chair
	// Base of the chair
	translateMatrix = glm::translate(identityMatrix, glm::vec3(14.5f, 0.25, 5.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 0.1f, 3.0f)); // Scale to make it flat and wide
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Backrest of the chair
	translateMatrix = glm::translate(identityMatrix, glm::vec3(14.5f, 0.25f, 6.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 1.0f, 0.1f)); // Scale to make it tall and thin
	rotateMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1, 0, 0)); // Tilt backrest for curve effect
	model = translateMatrix * rotateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);


	// Front Left Leg
	translateMatrix = glm::translate(identityMatrix, glm::vec3(14.5f, 0.0f, 6.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f)); // Small, thin cube
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Front Right Leg
	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.10f, 0.0f, 6.5f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Back Left Leg
	translateMatrix = glm::translate(identityMatrix, glm::vec3(14.5f, 0.0f, 5.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Back Right Leg
	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.10f, 0.0f, 5.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[10].drawCubeWithTexture(ourShader, moveMatrix * model);
}


void Street(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	//First road
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, 11.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(48.0f, 0.1f, 7.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);
}

void TrafficLight(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	//First light
	//lomba rod
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, 14.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 8.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//uporer rod
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 3.85, 14.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.3f, -2.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	
	//Second Light 
	//lomba rod
	translateMatrix = glm::translate(identityMatrix, glm::vec3(11.0f, 0.0, 14.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 8.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//uporer rod
	translateMatrix = glm::translate(identityMatrix, glm::vec3(11.0f, 3.85, 14.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.3f, -2.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	//Third Light 
	//lomba rod
	translateMatrix = glm::translate(identityMatrix, glm::vec3(23.0f, 0.0, 14.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 8.0f, 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//uporer rod
	translateMatrix = glm::translate(identityMatrix, glm::vec3(23.0f, 3.85, 14.5f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.3f, -2.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);
}


void dotdot(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateXMatrix, translateToPivot, translateFromPivot;

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.06, 0.06, .06));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);
}

void shiri(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[], int steps = 5) {
	// shamner block er shirir 1 
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateXMatrix, translateToPivot, translateFromPivot;


	float dy = 0.0;
	float dz = 0.5;
	for (int i = 0; i < steps; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 - 7.5, 0.0 + dy, 0.0f - dz)); // (0,0,0) ekahnei
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.5f, 1.0f));
		model = translateMatrix * scaleMatrix;
		all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

		// shamner block er shirir 2

		translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 - 7.5, 0.165f + dy, 0.0f - dz)); // (0,0,0) ekahnei , 7.5 hocche 30*0.5 = 15 jeta shirir er X, er half 
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.5f, 0.4f));
		model = translateMatrix * scaleMatrix;
		all_cubes[6].drawCubeWithTexture(ourShader, moveMatrix * model);
		dy += 0.165;
		dz += 0.5;
	}
}
void Baloon(Shader ourShader, Shader sphereShader, glm::mat4 moveMatrix, glm::vec3 rotationAxis, glm::vec3 ambient, glm::vec4 color, float rotation, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateXMatrix, translateToPivot, translateFromPivot;

	glm::vec3 pivot1 = glm::vec3(0.0f, 1.00, 0.0f);

	// ring
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.0f - 0.05 / 2, -0.01));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 0.05, .05));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	// String
	translateToPivot = glm::translate(identityMatrix, -pivot1);
	translateFromPivot = glm::translate(identityMatrix, pivot1);

	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotation), glm::vec3(rotationAxis));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, -0.01f, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02, 2.0f, .02));
	model = translateFromPivot * rotateXMatrix * translateToPivot * translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	Sphere s1 = Sphere();
	sphereShader.use();
	s1.ambient = ambient;
	s1.diffuse = ambient;
	s1.specular = glm::vec3(.1f, .1f, .1f);
	s1.scale = glm::vec3(.1f, 0.1f, 0.1f);
	s1.drawSphere(sphereShader, moveMatrix, pivot1, translateMatrix,
		translateToPivot, translateFromPivot, rotateXMatrix);


	//ourShader.use();

}

//define_koro
void Mati(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	//mati
	translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, 0.1f, 0.6f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.0f, 0.01f, 5.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[11].drawCubeWithTexture(ourShader, moveMatrix * model);
}


void RotateChairY(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[])
{
	// Create a rotation matrix around the y-axis
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

	// Combine the rotation matrix with the existing transformation matrix
	moveMatrix = moveMatrix * rotationMatrix;

	// Call the Chair function with the updated moveMatrix to draw the chair
	Chair(ourShader, moveMatrix, 0.0, all_cubes);
}

void TentY(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[])
{
	// Create a rotation matrix around the y-axis
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

	// Combine the rotation matrix with the existing transformation matrix
	glm::mat4 forTableChair = moveMatrix;
	moveMatrix = moveMatrix * rotationMatrix;
	bool isRotate = true;

	// Call the Chair function with the updated moveMatrix to draw the chair
	Tent(ourShader, moveMatrix, forTableChair ,glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) , all_cubes, isRotate);
}

void TentX(Shader ourShader, glm::mat4& moveMatrix, float angleDegrees, Cube all_cubes[]) {

	// Create a rotation matrix around the y-axis
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

	// Combine the rotation matrix with the existing transformation matrix
	glm::mat4 forTableChair = moveMatrix;
	moveMatrix = moveMatrix * rotationMatrix;
	bool isRotate = false;

	// Call the Chair function with the updated moveMatrix to draw the chair
	Tent(ourShader, moveMatrix, forTableChair, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), all_cubes, isRotate);
}


void Grasses(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[])
{

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	//Grass
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(48.0f, 0.1f, 22.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[0].drawCubeWithTexture(ourShader, moveMatrix * model);


}

void CoffeMachine(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	// left 
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1 + 0.05, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 1.0f, 1));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//main part
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1 + 0.05 + 0.75 / 2 / 2, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6, 0.75, 1));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	// nozzle 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + 0.15, 1.0f + 0.2, -17.59f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.2, 0.01));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//right thin
	translateMatrix = glm::translate(identityMatrix, glm::vec3(.3f - 0.01 / 2 / 2, 1 + 0.05, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 1.0f, 1));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);
}

void CafeShop(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0, 0.5, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 1.0f, 4.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 + 2.0, 0.5, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 1.0f, 4.0 - 0.3f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	glm::mat4 rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 - 2.5 / 2 + 1.9, 0.5, -18.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 1.0f, 3.0f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);



	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0 - 2.5 / 2 + 1.9, 0.5 + 0.5, -18.0 + 0.02f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7, 0.05f, 3.0f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);
}
void CafeFoodCounter(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	// pillars 
	float translate_pillar = 0.0;
	for (int i = 0; i < 3; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1 + 0.05, -20.0f + translate_pillar)); // grass 20 e sesh hoiche
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 5.8f, 0.8f));
		model = translateMatrix * scaleMatrix;
		all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);
		translate_pillar += 8.3;
	}


	//food 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 1.0f, 34.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1, -20.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2, 0.1f, 34.0f));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

}
void SecondFloorShamne(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube cube_tiles[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	float dy = 5.0 - 1.5;
	float dz = -10.3f;

	//dorja er left pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f - 4.5, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.5f, 5.8 + 7, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er left pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.75f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8 + 7, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja
	glm::mat4 rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.86f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.2f, 5.1 + 8, .2f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	cube_tiles[7].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.5, 1.8 + 8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er right pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f - 0.1, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8 + 8, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er right pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8 + 8, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f + 0.75f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(43.5, 1.8 + 8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);


	float dx = 8.25f;
	float dx_window = 7.5 + 0.75f;
	//dorja er right pillar 2 
	for (int i = 0; i < 4; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx - 0.5, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8 + 8, 1.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);



		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 1.875, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5, 7.5 + 8, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[4].drawCubeWithTexture(ourShader, moveMatrix * model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.75, 2 + 8, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 2.5, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5 + 8, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25, 1, -3.0f + 0.05 + 0.5));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25 + window_translate, 1, -3.0f + 0.1 + 0.5));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);

		if (i != 3) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 0.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 1 + 8, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 2.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5 + 8, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, moveMatrix * model);


			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 1, -3.0f + 0.05));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);

			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11 + window_translate, 1, -3.0f + 0.1));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, moveMatrix * model);


		}


		dx += 6.0;
		dx_window += 4.0;

	}
}
void SpotLightWithCurve(Shader ourShader, Shader lightingShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[], GLfloat reverseCurve[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;



	// ring
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.5f + 0.05 / 2, -0.01));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 0.05, .05));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.25f, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.02, 2.0f, .03));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);





}
void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube cube_tiles[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//shamner block
	//glBindTexture(GL_TEXTURE_2D, tilesTex);
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0, -20.0f)); // grass 20 e sesh hoiche
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(63.0f, 1.0f, 40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[6].drawCubeWithTexture(ourShader, model);



	// shamner block er shirir 1 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 - 7.5, 0.0, 0.0f)); // (0,0,0) ekahnei
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.33f, 1.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[6].drawCubeWithTexture(ourShader, model);

	// shamner block er shirir 2

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 - 7.5, 0.165f, 0.0f)); // (0,0,0) ekahnei , 7.5 hocche 30*0.5 = 15 jeta shirir er X, er half 
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.33f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[3].drawCubeWithTexture(ourShader, model);



	//Back
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 0.0, -20.0 - 0.2f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 23.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//shamner 1st floor er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5, -0.2f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 3.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//shamner 2nd floor er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 9.0 - 1.5, -0.2f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 3.0f, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//shamner 2nd floor er block er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 9.0 - 1.5, -0.2f - 10.1f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 3.0f, 20.2f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//shamner 2nd floor er block er block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(30.0f - 0.5f, 9.0 - 1.5, -0.2f - 10.1f)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 3.0f, 20.2f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);


	//ceiling 1st floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(61.0f, 1.0f, -40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//left close
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5 - 3, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 20.0, -40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//up 1st floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5 + 7.5, -0.2f - 1.25));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 1.0f, -40.0f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);



	//shamner wall 1st floor
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 7.5, 0.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	//dorja er left pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//dorja er left pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.75f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//dorja
	glm::mat4 rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(dorja1_rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.86f, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.2f, 5.1, .2f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	cube_tiles[7].drawCubeWithTexture(ourShader, model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.5, 1.8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//dorja er right pillar strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f - 0.1, 0.35f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 5.8, .4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[9].drawCubeWithTexture(ourShader, model);

	//dorja er right pillar
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f, 0.0, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8, 1.4f));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);

	//dorja er uporer strip
	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5f + 0.75f, 2.75f, -3.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(43.5, 1.8, .4));
	model = translateMatrix * scaleMatrix;
	cube_tiles[4].drawCubeWithTexture(ourShader, model);


	float dx = 8.25f;
	float dx_window = 7.5 + 0.75f;
	//dorja er right pillar 2 
	for (int i = 0; i < 4; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx - 0.5, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 5.8, 1.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, model);



		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 1.875, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5, 7.5, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[4].drawCubeWithTexture(ourShader, model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 0.0, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.75, 2, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx, 2.5, -3.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5, 0.4f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[9].drawCubeWithTexture(ourShader, model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25, 1, -3.0f + 0.05));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, model);

		//window 
		translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + .25 + window_translate, 1, -3.0f + 0.1));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
		model = translateMatrix * scaleMatrix;
		cube_tiles[1].drawCubeWithTexture(ourShader, model);

		if (i != 3) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 0.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 1, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, model);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 2.5, -3.0f));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.79, 0.5, 0.4f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[9].drawCubeWithTexture(ourShader, model);


			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11, 1, -3.0f + 0.05));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, model);

			//window 
			translateMatrix = glm::translate(identityMatrix, glm::vec3(dx + 4.11 + window_translate, 1, -3.0f + 0.1));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25 / 2, 3, 0.05f));
			model = translateMatrix * scaleMatrix;
			cube_tiles[1].drawCubeWithTexture(ourShader, model);


		}


		dx += 6.0;
		dx_window += 4.0;

	}







	////shamner wall  2nd floor 
	//translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, 5.0 - 1.5, -10.3f));
	//scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 18.0f, 0.4f));
	//model = translateMatrix * scaleMatrix;
	//cube_tiles[4].drawCubeWithTexture(ourShader, model);





}
void ChotoBlocks(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;
	//shamner 1st floor er choto choto block
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.6f, 1.5f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	//shamner 1st floor er choto choto block - left 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-.1, 0.0, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);


	//shamner 1st floor er choto choto block - right 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(2.8, 0.0, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);


	//shamner 1st floor er choto choto block - up 
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-.1, 0.74, 0.0)); // -0.2 cz z axis e 0.2  
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, .2f, 0.2f));
	model = translateMatrix * scaleMatrix;
	all_cubes[4].drawCubeWithTexture(ourShader, moveMatrix * model);

}
void SquareBati(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//back 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.06, 1.0));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 0.125 / 2, 0.0, 0.5));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 0.1, 0.06));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 0.125 / 2, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 0.1, 0.06));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);



}
void TubeLight(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//back 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 0.06, 0.01));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.06, 0.1));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0, 0.0, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.06, 0.1));
	model = translateMatrix * scaleMatrix;
	all_cubes[3].drawCubeWithTexture(ourShader, moveMatrix * model);


}

void Pillars(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color, Cube all_cubes[]) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;


	//Left Side shamner Pillar Shirir

	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 - 0.3, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 - 0.3, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, model);




	//right Side shamner Pillar Shirir

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 + 7.5, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0 + 7.5, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	//right Side shamner Pillar 1 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.75, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	translateMatrix = glm::translate(identityMatrix, glm::vec3(30 - 3.75, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	//Left Side shamner Pillar 1 

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.75, 0.0, -0.2f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 20.0f, 0.8f));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.75, 10.0, 0.0 + 0.2));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.6f, -20.6));
	model = translateMatrix * scaleMatrix;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model);

}

void Table(Shader ourShader, glm::mat4 moveMatrix, float rotation, bool square, Cube all_cubes[])
{

	float tableY = 0.05f;
	float squareZ = 1.5f;
	if (square == true) {
		squareZ = 3.0f;
	}
	// Top
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.06f, squareZ));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	all_cubes[6].drawCubeWithTexture(ourShader, moveMatrix * model);


	// Leg 1
	glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.0, -0.5, 0.05));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
	model1 = rotateYMatrix * translateMatrix1 * scaleMatrix1;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model1);


	// Leg 2
	glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(.01f, -0.5, squareZ / 2 - 0.1));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
	model2 = rotateYMatrix * translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);


	// Leg 3
	//glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(1.5 - 0.05, -0.5, 0.05));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
	model1 = rotateYMatrix * translateMatrix1 * scaleMatrix1;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model1);;


	// Leg 4
	//glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.5 - .05f, -0.5, squareZ / 2 - 0.1));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
	model2 = rotateYMatrix * translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);
}

void Chair(Shader ourShader, glm::mat4 moveMatrix, float rotation, Cube all_cubes[])
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model;

	float fixLeg = 0.7f;
	float fixY = 0.1f;
	float fixYWhole = -0.17f;

	// Top
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.11f, 0.0f - fixY + fixYWhole, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.07f, 0.7f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	// Leg 1
	glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.13f, -0.32f + fixYWhole, 0.01f));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model1 = translateMatrix1 * scaleMatrix1;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model1);


	// Leg 2
	glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.13f, -0.32f + fixYWhole, 0.28f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model2);


	//// Leg 3
	//glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
	translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.43f, -0.32f + fixYWhole, 0.01f));
	scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model1 = translateMatrix1 * scaleMatrix1;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model1);


	// Leg 4
	//glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.43f, -0.32f + fixYWhole, 0.28f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model2);


	//Left up 
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.17f, 0.01f - fixY + fixYWhole, 0.29f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f + 0.28, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);


	//Right up
	translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.39f, 0.01f - fixY + fixYWhole, 0.29f));
	scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f + 0.28, 0.07f));
	model2 = translateMatrix2 * scaleMatrix2;
	all_cubes[9].drawCubeWithTexture(ourShader, moveMatrix * model2);

	//Back support
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f + 0.0150, 0.09f - fixY + fixYWhole + 0.1, 0.28f + 0.0135));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.1f, 0.03f));
	model = translateMatrix * scaleMatrix;
	all_cubes[2].drawCubeWithTexture(ourShader, moveMatrix * model);

	//Back support
	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f + 0.0150, 0.09f - fixY + fixYWhole, 0.28f + 0.0135));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.08f, 0.03f));
	model = translateMatrix * scaleMatrix;
	all_cubes[7].drawCubeWithTexture(ourShader, moveMatrix * model);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {                 //Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {                 //Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {                 //Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {                 //Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //Down
	{
		/*if (rotateAxis_X) rotateAngle_X -= 0.1;
		else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
		else rotateAngle_Z -= 0.1;*/

		camera.ProcessKeyboard(DOWN, deltaTime);


	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)                   //Pitch positive
	{
		/*rotateAngle_X += 1;
		rotateAxis_X = 1.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(0.0f, 3.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)                   //Pitch negative
	{
		/*rotateAngle_X += 1;
		rotateAxis_X = 1.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(0.0f, -3.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)                   //Yaw positive
	{
		/*rotateAngle_Y += 1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 1.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(3.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)                   //Yaw negative
	{
		/*rotateAngle_Y += 1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 1.0;
		rotateAxis_Z = 0.0;*/
		camera.ProcessYPR(-3.0f, 0.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)                   //Roll positive
	{
		/*rotateAngle_Z += 0.1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 1.0;*/
		camera.ProcessYPR(0.0f, 0.0f, 0.5f);

	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Roll negative
	{
		/*rotateAngle_Z += 0.1;
		rotateAxis_X = 0.0;
		rotateAxis_Y = 0.0;
		rotateAxis_Z = 1.0;*/
		camera.ProcessYPR(0.0f, 0.0f, -0.5f);

	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		eyeX += 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)                   //Rotate camera around a look at point
	{                                                                   //Right
		/*eyeX -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
		camera.RotateAroundLookAt(2.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)                   //Rotate camera around a look at point
	{                                                                   //Left
		/*eyeX -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
		camera.RotateAroundLookAt(-2.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		eyeZ += 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)                   //Rotate Fan
	{
		/*eyeZ -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
		isRotating ^= true;
		cout << isRotating << endl;

		Sleep(100);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		eyeY += 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
	{
		eyeY -= 2.5 * deltaTime;
		basic_camera.changeEye(eyeX, eyeY, eyeZ);

		camera.ProcessKeyboard(UP, deltaTime);

	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)                   //Up
	{
		while (dorja1_rotationY <= 100)
		{
			dorja1_rotationY += 24.0f;
			Sleep(100);
		}

		Sleep(100);

	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)                   //Up
	{
		while (dorja1_rotationY >= 24)
		{
			dorja1_rotationY -= 24.0f;
			Sleep(100);
		}



	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)                   //Up
	{
		if (window_translate < 0)
			window_translate = 0.8125f;
		else
			window_translate = -0.8125f;

		Sleep(100);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)                   //Up
	{
		isglobalBallonOn ^= true;



		Sleep(100);
	}

	if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)                   //Up
	{
		isglobalDotOn ^= true;



		Sleep(100);
	}



	//***************Lighting***************

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)                   //Lighting On-Off
	{
		lightingOn ^= true;
		cout << lightingOn << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)                   //Ambient On
	{
		ambientOn = 1.0;
		pointLight1.turnAmbientOn();
		pointLight2.turnAmbientOn();
		pointLight3.turnAmbientOn();
		pointLight4.turnAmbientOn();
		pointLight5.turnAmbientOn();
		spotLight.turnAmbientOn();
		spotLight2.turnAmbientOn();
		spotLight3.turnAmbientOn();
		directionalLight.turnAmbientOn();
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)                   //Ambient Off
	{
		ambientOn = 0.0;
		pointLight1.turnAmbientOff();
		pointLight2.turnAmbientOff();
		pointLight3.turnAmbientOff();
		pointLight4.turnAmbientOff();
		pointLight5.turnAmbientOff();
		spotLight.turnAmbientOff();
		spotLight2.turnAmbientOff();
		spotLight3.turnAmbientOff();
		directionalLight.turnAmbientOff();
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)                   //Diffuse On
	{
		diffuseOn = 1.0;
		pointLight1.turnDiffuseOn();
		pointLight2.turnDiffuseOn();
		pointLight3.turnDiffuseOn();
		pointLight4.turnDiffuseOn();
		pointLight5.turnDiffuseOn();
		spotLight.turnDiffuseOn();
		spotLight2.turnDiffuseOn();
		spotLight3.turnDiffuseOn();
		directionalLight.turnDiffuseOn();

	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)                   //Diffuse Off
	{
		diffuseOn = 0.0;
		pointLight1.turnDiffuseOff();
		pointLight2.turnDiffuseOff();
		pointLight3.turnDiffuseOff();
		pointLight4.turnDiffuseOff();
		pointLight5.turnDiffuseOff();
		spotLight.turnDiffuseOff();
		spotLight2.turnDiffuseOff();
		spotLight3.turnDiffuseOff();
		directionalLight.turnDiffuseOff();
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)                   //Specular On
	{
		specularOn = 1.0;
		pointLight1.turnSpecularOn();
		pointLight2.turnSpecularOn();
		pointLight3.turnSpecularOn();
		pointLight4.turnSpecularOn();
		pointLight5.turnSpecularOn();
		spotLight.turnSpecularOn();
		spotLight2.turnSpecularOn();
		spotLight3.turnSpecularOn();
		directionalLight.turnSpecularOn();
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)                   //Specular Off
	{
		specularOn = 0.0;
		pointLight1.turnSpecularOff();
		pointLight2.turnSpecularOff();
		pointLight3.turnSpecularOff();
		pointLight4.turnSpecularOff();
		pointLight5.turnSpecularOff();
		spotLight.turnSpecularOff();
		spotLight2.turnSpecularOff();
		spotLight3.turnSpecularOff();
		directionalLight.turnSpecularOff();
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)                   //Point Light On
	{
		pointLightOn = 1.0;
		pointLight1.turnOn();
		pointLight2.turnOn();
		pointLight3.turnOn();
		pointLight4.turnOn();
		pointLight5.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)                   //Point Light Off
	{
		pointLightOn = 0.0;
		pointLight1.turnOff();
		pointLight2.turnOff();
		pointLight3.turnOff();
		pointLight4.turnOff();
		pointLight5.turnOff();
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)                   //Directional Light On
	{
		directionalLightOn = 1.0;
		directionalLight.turnOn();
		directionalLight2.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)                   //Directional Light Off
	{
		directionalLightOn = 0.0;
		directionalLight.turnOff();
		directionalLight2.turnOff();
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)                   //Spot Light On
	{
		spotLightOn = 1.0;
		spotLight.turnOn();
		spotLight2.turnOn();
		spotLight3.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)                   //Spot Light Off
	{
		spotLightOn = 0.0;

		spotLight.turnOff();
		spotLight2.turnOn();
		spotLight3.turnOn();
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)                   //Dark On-Off
	{
		dark ^= true;
		cout << dark << endl;
	}




	//if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)               //Basic Camera rotate around lookat
	//{
	//    //lookAtX += 2.5 * deltaTime;
	//    //basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	//    float change = -0.3f;
	//    float x, y, z;
	//    x = eyeX * cos(glm::radians(change)) + eyeZ * sin(glm::radians(change));
	//    y = eyeY;
	//    z = - eyeX * sin(glm::radians(change)) + eyeZ * cos(glm::radians(change));

	//    eyeX = x, eyeY = y, eyeZ = z;
	//    basic_camera.changeEye(eyeX, eyeY, eyeZ);
	//}
	//if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	//{
	//    //lookAtX -= 2.5 * deltaTime;
	//    //basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);

	//    float change = 0.3f;
	//    float x, y, z;
	//    x = eyeX * cos(glm::radians(change)) + eyeZ * sin(glm::radians(change));
	//    y = eyeY;
	//    z = -eyeX * sin(glm::radians(change)) + eyeZ * cos(glm::radians(change));

	//    eyeX = x, eyeY = y, eyeZ = z;
	//    basic_camera.changeEye(eyeX, eyeY, eyeZ);
	//}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		lookAtY += 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		lookAtY -= 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		lookAtZ += 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		lookAtZ -= 2.5 * deltaTime;
		basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


//Texture Loading



unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

//OBJECTS

void drawCube(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), float spec = 1.0f, float shininess = 32.0f)
{
	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngleTest_Y), glm::vec3(0.0f, 1.0f, 0.0f));

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
	model = translateMatrix * rotateYMatrix * scaleMatrix;
	ourShader.setMat4("model", moveMatrix * model);

	ourShader.setVec4("material.ambient", color);
	ourShader.setVec4("material.diffuse", color);
	ourShader.setVec4("material.specular", color * spec);
	ourShader.setFloat("material.shininess", shininess);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

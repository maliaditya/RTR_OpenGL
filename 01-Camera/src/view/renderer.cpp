#include "renderer.h"
#include <GL/glew.h>
#include <GL/gl.h>




int Renderer::initialize() {



	if(deviceSetup()){
		return deviceSetup();
	}

	// create shader
	Shader shader;
	shader.initialize();
 	shaderProgramObject= shader.getObject();

		
	// initialize mesh
	s.init();

	// initiallize objects of mesh
	RenderableEntity sun(shaderProgramObject,s.VAO, s.VBO_Position, s.EBO, s.gNumElements );
	RenderableEntity earth(shaderProgramObject,s.VAO, s.VBO_Position, s.EBO, s.gNumElements );
	RenderableEntity moon(shaderProgramObject,s.VAO, s.VBO_Position, s.EBO, s.gNumElements );

	// add the created object to the map
	entityMap["sun"] = sun;
	entityMap["earth"] = earth;
	entityMap["moon"] = moon;

	defaultSettings();

	return(0);
}


void Renderer::render() {

    RenderableEntity& sun = entityMap["sun"];
	RenderableEntity& earth = entityMap["earth"];
	RenderableEntity& moon = entityMap["moon"];
	
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sun.setViewMatrix(camera.getMatrix());
	sun.translate(vec3(0.0f, 0.0f, 0.0f));
	stack.pushMatrix(sun.getModelMatrix());
	sun.setProjectionMatrix(perspectiveProjectionMatrix);
	sun.setColor(1.0f, 1.0f, 0.0f);
	sun.setPolygonMode(GL_FILL);
	sun.render();

	
	earth.setModelMatrix(stack.popMatrix()); 
	earth.rotate((GLfloat)year, 0.0f, 1.0f, 0.0f);
	earth.translate(vec3(-1.0f, 0.0f, 0.0f));
	earth.scale(0.2f);
	earth.setProjectionMatrix(perspectiveProjectionMatrix);
	earth.setColor( 0.4f, 0.9f, 1.0f);
	earth.setPolygonMode(GL_LINE);
	earth.rotate((GLfloat)year, 0.0f, 1.0f, 0.0f);
	earth.render();
	stack.pushMatrix(earth.getModelMatrix());

	stack.pushMatrix(moon.setModelMatrix(stack.popMatrix())); // pop the matrix -> set the matrix of earth -> push the new matrix
	moon.rotate((GLfloat)moonx, 0.0f, 1.0f, 0.0f);
	moon.translate(vec3(-1.0f, 0.0f, 0.0f));
	moon.scale(0.2f);
	moon.setProjectionMatrix(perspectiveProjectionMatrix);
	moon.setColor(1.0f, 1.0f, 1.0f);
	moon.setPolygonMode(GL_FILL);
	moon.rotate((GLfloat)moonx, 0.0f, 1.0f, 0.0f);
	moon.render();


	stack.popMatrix();
	
	SwapBuffers(ghdc);
}




int Renderer::deviceSetup(void){
// Variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	// Code
	// Initialization of PIXELFORMATDESCRIPTOR structure
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;   // 24 can also be done

	// Get DC
	ghdc = GetDC(ghwnd);

	// Choose pixel format
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
		return(-1);

	// set the choosen pixel format
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
		return(-2);

	// create opengl rendering context
	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
		return(-3);

	//make the rendering context as the current context
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
		return(-4);

	// Here starts OpenGlCode

	// GLEW Initialization
	if (glewInit() != GLEW_OK)
	{
		return -5;
	}

	return 0;

}


void Renderer::update() {


}

void Renderer::defaultSettings() {

	// Depth & ClearColor related Changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Optional
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// clear the screen using blue color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
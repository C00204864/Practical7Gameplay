#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube") {}

Game::~Game() {}

float vertices[] = { 1.0f, 1.0f, -20.0f, -1.0f, 1.0f, -20.0f, -1.0f, -1.0f, -20.0f , 1.0f, -1.0f, -20.0f, 1.0f, 1.0f, -22.0f, -1.0f, 1.0f, -22.0f, -1.0f, -1.0f, -22.0f, 1.0f, -1.0f, -22.0f};
float colors[] = { 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
unsigned int vertex_index1[] = {1, 2, 3};
unsigned int vertex_index2[] = {1, 3, 0};
unsigned int vertex_index3[] = {0, 7, 4};
unsigned int vertex_index4[] = {0, 3, 7};
unsigned int vertex_index5[] = {4, 6, 5};
unsigned int vertex_index6[] = {4, 7, 6};
unsigned int vertex_index7[] = {5, 2, 1};
unsigned int vertex_index8[] = {5, 6, 2};
unsigned int vertex_index9[] = {5, 1, 0};
unsigned int vertex_index10[] = {5, 0, 4};
unsigned int vertex_index11[] = {7, 2, 6};
unsigned int vertex_index12[] = {7, 3, 2};
unsigned int * vertex_index_array[] = { vertex_index1, vertex_index2, vertex_index3, vertex_index4 , vertex_index5, vertex_index6, vertex_index7, vertex_index8, vertex_index9,vertex_index10, vertex_index11,vertex_index12 };

bool scaleAndTranslate = true;
int counter = 0;

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	/*glTranslatef(0.0f, 0.0f, -21.0f);
	glRotatef(0.1f, 1.0f, 0.0f, 0.0f);
	glRotatef(0.1f, 0.0f, 1.0f, 0.0f);
	if (scale)
	{
		glScalef(1.0f / 1.001f, 1.0f / 1.001f, 1.0f / 1.001f);
		counter++;
		if (counter > 1000)
		{
			scale = false;
			counter = 0;
		}
	}
	else
	{
		glScalef(1.001f, 1.001f, 1.001f);
		counter++;
		if (counter > 1000)
		{
			scale = true;
			counter = 0;
		}
	}
	glTranslatef(0.0f, 0.0f, 21.0f);*/
	Matrix3 mCaller = Matrix3();
	for (int i = 0; i < 24; i += 3)
	{
		MyVector3 tempVector(vertices[i], vertices[i + 1], vertices[i + 2] + 21);
		tempVector = mCaller.RotateAboutX(tempVector, 0.1);
		tempVector = mCaller.RotateAboutY(tempVector, 0.1);
		if (scaleAndTranslate)
		{
			tempVector = tempVector.Scale(1.001);
			mCaller.Translate(0.005f, 0.005f, tempVector);
			counter++;
		}
		else
		{
			tempVector = tempVector.Scale(1 / 1.001);
			mCaller.Translate(-0.005f, -0.005f, tempVector);
			counter++;
		}
		vertices[i] = tempVector.GetX();
		vertices[i + 1] = tempVector.GetY();
		vertices[i + 2] = (tempVector.GetZ() - 21);
	}
	counter++;
	if (counter > 10000)
	{
		if (scaleAndTranslate)
		{
			scaleAndTranslate = false;
		}
		else 
		{
			scaleAndTranslate = true;
		}
		counter = 0;
	}

	glCullFace(GL_BACK);
	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 12; i++)
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, vertex_index_array[i]);
	}

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}


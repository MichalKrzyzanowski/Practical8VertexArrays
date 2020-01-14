#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}


// Vertices for one Triangle
float vertices[24] = 
			{ -1.0f, -1.0f, 1.0f ,
			   1.0f, -1.0f, 1.0f,
		  	  1.0f, 1.0f, 1.0f,
			   -1.0f, 1.0f, 1.0f,

			  -1.0f, -1.0f, -1.0f,
			   1.0f, -1.0f, -1.0f,
			  1.0f, 1.0f, -1.0f,
			   -1.0f, 1.0f, -1.0f };

Vector3 m_points[] = { { vertices[0], vertices[1] , vertices[2] },
						{ vertices[3], vertices[4] , vertices[5] },
						{ vertices[6], vertices[7] , vertices[8] },
						{ vertices[9], vertices[10] , vertices[11] },
						{ vertices[12], vertices[13] , vertices[14] },
						{ vertices[15], vertices[16] , vertices[17] },
						{ vertices[18], vertices[19] , vertices[20] },
						{ vertices[21], vertices[22] , vertices[23] } };

// Colors for those vertices
float colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

// Index to be drawn
unsigned int vertex_index[] = { 0,1,2,
								2,3,0,
								2,6,3,
								6,7,3,
								7,6,5,
								5,4,7,
								5,0,4,
								5,1,0,
								1,5,6,
								6,2,1,
								4,0,3,
								3,7,4 };

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		std::cout << "Game running..." << std::endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::controlCube()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationX(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationX(-rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationY(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationY(-rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationZ(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationZ(-rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Translate(0, -1) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Translate(0, 1) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Translate(-1, 0) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Translate(1, 0) * m_points[i];
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Scale3D(101.0) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Scale3D(99.0) * m_points[i];
		}
	}

	for (int i = 0, j = 0; i < 8, j < 24; i++)
	{
		vertices[j] = m_points[i].X;
		j++;
		vertices[j] = m_points[i].Y;
		j++;
		vertices[j] = m_points[i].Z;
		j++;
	}
}

void Game::initialize()
{
	isRunning = true;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -8.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	controlCube();

	std::cout << "Update up" << std::endl;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::cout << "Drawing" << std::endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;
}


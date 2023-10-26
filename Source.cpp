#include"Header.h";



void SetParticles(vector<Particle>& particles, bool randomColors, Vector2f spawnPosition, Vector2f sizeRange, Vector2f velocityRange, Vector2f deathRange)
{
	for (int i = 0; i < particles.size(); i++)
	{
		//get a random size
		float sizeRandom = (float)rand() / (float)(RAND_MAX);
		float size = sizeRandom * (sizeRange.y - sizeRange.x + 1) + sizeRange.x;

		//get a random velocity
		float velocityRandom = (float)rand() / (float)(RAND_MAX);
		float velocity = velocityRandom * (velocityRange.y - velocityRange.x + 1) + velocityRange.x;

		//get a random angle for velocity
		float randomAngle = (rand() % 360) * 3.1415/180;
		Vector2f randomDirection(cos(randomAngle), sin(randomAngle));

		//get a random death time
		float deathRandom = (float)rand() / (float)(RAND_MAX);
		float deathTime = deathRandom * (deathRange.y - deathRange.x) + deathRange.x;

		Color particleColor = randomColors ? GetRandomColor() : Color::White;
		
		particles[i].SetNewParameters(spawnPosition, particleColor, size, randomDirection * velocity, deathTime);

		/*
		particles[i].pixelPosition = spawnPosition;
		particles[i].shapeColor = Color::White;
		particles[i].shapeRadius = size;
		particles[i].pixelVelocity = randomDirection * velocity;
		particles[i].deathTime = deathTime;
		*/


	}
}


/* THINGS TO DO
* - allow particles to die over time
* - read canvas asignment
* - watch recording to see what phil does
*/



int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Particle Adventure!");
	//Particle firstParticle = Particle(Color::Red, 50, Vector2f(0, 0), Vector2f(50, 50));

	//create delta time variables
	Clock deltaSrc;
	float previousTime = deltaSrc.getElapsedTime().asSeconds();

	//create clicked variables
	bool alreadyClicked = false;

	//create particle system
	vector<Particle> particles(64);
	SetParticles(particles, false, Vector2f(0,0), particleSizeRange, particleVelocityRange, Vector2f(-1, -1));



	while (window.isOpen())
	{
		//mouse pressed
		bool mousePressed = Mouse::isButtonPressed(Mouse::Left);
		Vector2f currentMousePos = Vector2f(Mouse::getPosition(window));

		//find delta time
		Time start = deltaSrc.getElapsedTime();
		float currentTime = start.asSeconds();
		float deltaTime = currentTime - previousTime;

		//window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (mousePressed && !alreadyClicked)
		{
			alreadyClicked = true;
			RandomizeParticles(particles, currentMousePos);
		}
		else if (!mousePressed && alreadyClicked)
		{
			alreadyClicked = false;
		}


		//draw particles
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i].Tick(deltaTime);

			if (particles[i].isAlive)
			{
				//if (i == 0) cout << "delta time: " << deltaTime << ", deathtime: " << particles[i].deathTime << endl;
				window.draw(particles[i].GetShape());
			}
		}


		window.display();


		previousTime = currentTime; //set time for next frame
	}
	return 0;
}


void RandomizeParticles(vector<Particle>& particles, Vector2f spawnPosition)
{
	SetParticles(particles, true, spawnPosition, particleSizeRange, particleVelocityRange, particleDeathRange);
}

Color GetRandomColor()
{
	//Colors are a global variable defined in header
	

	int randomColorAddress = rand() % colors.size();

	return colors[randomColorAddress];
}

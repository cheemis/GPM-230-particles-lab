#include"Header.h";



void SetParticles(vector<Particle>& particles, Vector2i sizeRange, Vector2i velocityRange)
{
	for (int i = 0; i < particles.size(); i++)
	{
		float size = rand() % (sizeRange.y - sizeRange.x + 1) + sizeRange.x;

		float velocity = rand() % (velocityRange.y - velocityRange.x + 1) + velocityRange.x;
		float randomAngle = (rand() % 360) * 3.1415 /180;
		Vector2f randomDirection(cos(randomAngle), sin(randomAngle));


		

		particles[i].shapeColor = Color::White;
		particles[i].shapeRadius = size;
		particles[i].pixelVelocity = randomDirection * velocity;


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

	

	
	Clock deltaSrc;
	float previousTime = deltaSrc.getElapsedTime().asSeconds();



	vector<Particle> particles(64);
	SetParticles(particles, Vector2i(5,20), Vector2i(1,30));



	while (window.isOpen())
	{
		bool mousePressed = Mouse::isButtonPressed(Mouse::Left);
		Vector2f currentMousePos = Vector2f(Mouse::getPosition(window));

		//find delta time
		Time start = deltaSrc.getElapsedTime();
		float currentTime = start.asSeconds();
		float deltaTime = currentTime - previousTime;
		



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(firstParticle.GetShape());

		for (int i = 0; i < particles.size(); i++)
		{
			particles[i].Tick(deltaTime);
			window.draw(particles[i].GetShape());
		}


		window.display();


		previousTime = currentTime; //set time for next frame
	}
	return 0;
}

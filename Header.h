#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>

using namespace std;
using namespace sf;

//global variables
Vector2f particleSizeRange(1, 30);
Vector2f particleVelocityRange(10, 500);
Vector2f particleDeathRange(0.1, 3);
vector<Color> colors = { Color::Red, Color::Blue, Color::Green, Color::Yellow, Color::Cyan, Color::Magenta, Color::White };


class Particle
{
	public:
		Vector2f pixelPosition;
		Vector2f pixelVelocity;

		Color shapeColor;
		float shapeRadius;

		float deathTime;
		bool isAlive;

		Particle(Color color, float radius, Vector2f position, Vector2f velocity, float death)
		{
			pixelPosition = position;
			pixelVelocity = velocity;

			shapeColor = color;
			shapeRadius = radius;

			deathTime = death;
			isAlive = true;
			
		}

		Particle() : Particle(Color::White, 32, Vector2f(512/2, 512/2), Vector2f(0,0), 10) {}

		CircleShape GetShape()
		{
			auto shape = CircleShape(32);
			shape.setPosition(pixelPosition);

			shape.setFillColor(shapeColor);
			shape.setRadius(shapeRadius);

			return shape;
		}

		void SetNewParameters(Vector2f spawnPosition, sf::Color newColor, float newRadius, Vector2f newVelocity, float newDeathTime)
		{
			pixelPosition = spawnPosition;
			shapeColor = newColor;
			shapeRadius = newRadius;
			pixelVelocity = newVelocity;
			deathTime = newDeathTime;
			isAlive = true;
		}


		void Tick(float deltaTime)
		{
			if (isAlive)
			{
				MoveParticle(deltaTime);
				KillParticle(deltaTime);
			}
		}


		void MoveParticle(float deltaTime)
		{
			pixelPosition += pixelVelocity * deltaTime;
		}

		void KillParticle(float deltaTime)
		{
			deathTime -= deltaTime;
			if (deathTime <= 0)
			{
				isAlive = false;
			}
		}

};

void SetParticles(vector<Particle>&, bool, Vector2f, Vector2f, Vector2f, Vector2f);
void RandomizeParticles(vector<Particle>&, Vector2f);
Color GetRandomColor();

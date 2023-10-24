#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace std;
using namespace sf;


float particleSizeRange[] = { 10, 50 };


class Particle
{
	public:
		Vector2f pixelPosition;
		Vector2f pixelVelocity;

		Color shapeColor;
		float shapeRadius;

		Particle(Color color, float radius, Vector2f position, Vector2f velocity)
		{
			pixelPosition = position;
			pixelVelocity = velocity;

			shapeColor = color;
			shapeRadius = radius;
			
		}

		Particle() : Particle(Color::White, 32, Vector2f(512/2, 512/2), Vector2f(0,0))
		{
			/*
			pixelPosition = Vector2f(0, 0);
			pixelVelocity = Vector2f(0, 0);

			shapeColor = Color::White;
			shapeRadius = 32;
			*/
		}

		CircleShape GetShape()
		{
			auto shape = CircleShape(32);
			shape.setPosition(pixelPosition);

			shape.setFillColor(shapeColor);
			shape.setRadius(shapeRadius);

			return shape;
		}


		void Tick(float deltaTime)
		{
			MoveParticle(deltaTime);
		}


		void MoveParticle(float deltaTime)
		{
			pixelPosition += pixelVelocity * deltaTime;
		}

		

};


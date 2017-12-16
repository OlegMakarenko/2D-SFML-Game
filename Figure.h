#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Player.h"
using namespace sf;

namespace My
{
	class Figure
	{
	public:
		Figure();
		virtual void Update(RenderWindow &window, float time){};
		void setPlayer(Player &player);
		void SpeedUp();
	protected:
		float X;
		float Y;
		int StartY;
		int A;
		int SpeedX;
		int SpeedY;
		int CR;
		int CG;
		int CB;
		int MaxSpeed;
		void setStartValues();
		//virtual bool Collision(){};
		Player *player;
	};

	class Square :
		public Figure
	{
	public:
		Square();
		virtual void Update(RenderWindow &window, float time);
	protected:
		sf::RectangleShape rectangle;
	};

	class Rectangle :
		public Square
	{
	public:
		Rectangle();
		int B;
		void Update(RenderWindow &window, float time);
	};

	class Circle :
		public Figure
	{
	public:
		Circle();
		void Update(RenderWindow &window, float time);
	protected:
		sf::CircleShape circle;

	};

	class Triangle :
		public Circle
	{
	public:
		Triangle();
	};
}

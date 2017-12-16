#include "stdafx.h"
#include "Figure.h"

using namespace My;
Figure::Figure()
{
	StartY = -400;
	MaxSpeed = 5;
	setStartValues();
}

void Figure::setStartValues()
{
	if (StartY<-100)StartY++;
	X = rand() % 900-50;
	Y = -300;
	A = rand() % 80+10;
	SpeedX = rand() % 10;
	SpeedY = rand() % MaxSpeed + 3;
	CR = rand() % 255;
	CG = rand() % 255;
	CB = rand() % 255;
}


void Figure::setPlayer(Player &player)
{
	this->player = &player;
}

void Figure::SpeedUp()
{
	MaxSpeed++;
}

Square::Square()
{
	rectangle.setSize(sf::Vector2f(A, A));
	rectangle.setFillColor(sf::Color(CR, CG, CB));
}


void Square::Update(RenderWindow &window, float time)
{
	X += SpeedX * time;
	Y += SpeedY * time;
	if ((X+A >= player->GetX()) &&
		(X <= player->GetX() + player->GetWidth()) &&
		(Y+A >= player->GetY()) &&
		(Y <= player->GetY() + player->GetHeight()))
		player->Die();
	else
		rectangle.setPosition(X, Y);
	if (Y >= 600) setStartValues();
	window.draw(rectangle);
}

Rectangle::Rectangle()
{
	B = rand() % 80+10;
	rectangle.setSize(sf::Vector2f(A, B));
	rectangle.setFillColor(sf::Color(CR, CG, CB));
}


void Rectangle::Update(RenderWindow &window, float time)
{
	X += SpeedX * time;
	Y += SpeedY * time;
	if ((X + A >= player->GetX()) &&
		(X <= player->GetX() + player->GetWidth()) &&
		(Y + B >= player->GetY()) &&
		(Y <= player->GetY() + player->GetHeight()))
		player->Die();
	else
		rectangle.setPosition(X, Y);
	if (Y >= 600) setStartValues();
	window.draw(rectangle);
}

Circle::Circle()
{
	circle.setRadius(A/2);
	circle.setFillColor(sf::Color(CR, CG, CB));
}


void Circle::Update(RenderWindow &window, float time)
{
	X += SpeedX * time;
	Y += SpeedY * time;
	if ((X + A >= player->GetX()) &&
		(X <= player->GetX() + player->GetWidth()) &&
		(Y + A >= player->GetY()) &&
		(Y <= player->GetY() + player->GetHeight()))
		player->Die();
	else
		circle.setPosition(X, Y);
	if (Y >= 600) setStartValues();
	window.draw(circle);
}

Triangle::Triangle()
{
	circle.setRadius(A / 2);
	circle.setPointCount(3);
	circle.setFillColor(sf::Color(CR, CG, CB));
}


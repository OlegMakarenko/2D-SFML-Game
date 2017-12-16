#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include "Player.h"
#include "figure.h"
#include <msclr\marshal_cppstd.h>
using namespace System;
using namespace sf;


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	RenderWindow window(VideoMode(800, 600), "Oleg Makarenko - Task 2");
	
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 5000.f);  
    glEnable(GL_TEXTURE_2D);
	Texture TextureBackGround;
	Texture TextureBackGround2;
	Texture TextureMountains;
	Texture TextureGrass;
	Texture TextureGameOver;
	Texture TextureTarget;
	TextureBackGround.loadFromFile("Images\\BackGround.png");
	TextureBackGround2.loadFromFile("Images\\BackGround 2.png");
	TextureMountains.loadFromFile("Images\\Mountains.png");
	TextureGrass.loadFromFile("Images\\Grass.png");
	TextureGameOver.loadFromFile("Images\\GameOver.png");
	TextureTarget.loadFromFile("Images\\Iphone.png");
	Sprite SpriteBackGround;
	Sprite SpriteBackGround2;
	Sprite SpriteMountains;
	Sprite SpriteGrass;
	Sprite SpriteGameOver;
	Sprite SpriteTarget;
	SpriteBackGround.setTexture(TextureBackGround);
	SpriteBackGround2.setTexture(TextureBackGround2);
	SpriteMountains.setTexture(TextureMountains);
	SpriteGrass.setTexture(TextureGrass);
	SpriteGameOver.setTexture(TextureGameOver);
	SpriteTarget.setTexture(TextureTarget);
	SpriteBackGround.setPosition(0, 0);
	SpriteBackGround2.setPosition(0, 0);
	SpriteMountains.setPosition(-84, 0);
	SpriteGrass.setPosition(-166, 0);
	SpriteGameOver.setPosition(0, 0);
	SpriteTarget.setPosition(60, 470);
	Clock clock;
	My::Figure** figure;
	figure = new My::Figure*[20];
	Player player;
	My::Square square[5];
	My::Rectangle rectangle[5];
	My::Circle circle[5];
	My::Triangle triangle[5];
	sf::Font font;
	font.loadFromFile("arialbd.ttf");
	sf::Text text;
	text.setFont(font);
	text.setColor(sf::Color::Green);
	text.rotate(9);
	text.setCharacterSize(20);
	text.setPosition(550, 20);
	text.setStyle(sf::Text::Bold);
	text.setString("Iphones collected: 0");
	sf::Music music0;
	music0.openFromFile("music0.ogg");
	music0.setLoop(1);
	music0.play();
	sf::Music music1;
	music1.openFromFile("music1.ogg");
	music1.setLoop(1);
	// set the color
	text.setColor(sf::Color::Red);
	int j = 0;
	int Scores = 0;
	int DrawCount = 1;
	bool SideTarged = 0,
		MusicChanged=0;

	for (int i = 0; i < 5; i++)
	{
		figure[j] = &square[i];
		figure[j]->setPlayer(player);
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		figure[j] = &rectangle[i];
		figure[j]->setPlayer(player);
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		figure[j] = &circle[i];
		figure[j]->setPlayer(player);
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		figure[j] = &triangle[i];
		figure[j]->setPlayer(player);
		j++;
	}
	
	while (window.isOpen())
    {
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time/50;
		if (time>3) time=3;


        Event event;
        while (window.pollEvent(event))
        {
			if (event.type == Event::Closed)
				window.close();

            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
                window.close();
        }
	

		if ((player.GetX()<80) && (!SideTarged))
		{
			Scores++;
			SideTarged = 1;
			SpriteTarget.setPosition(740, 470);
			text.setString("Iphones collected: " + msclr::interop::marshal_as<std::string>(Scores.ToString()));
			for (int i = 0; i < 20; i++)
				figure[i]->SpeedUp();
			player.SpeedUp();
		}
		if ((player.GetX()>720) && (SideTarged))
		{
			Scores++;
			SideTarged = 0;
			SpriteTarget.setPosition(60, 470);
			text.setString("Iphones collected: " + msclr::interop::marshal_as<std::string>(Scores.ToString()));
			for (int i = 0; i < 20; i++)
				figure[i]->SpeedUp();
			player.SpeedUp();
		}
		if (Scores < 20)
			DrawCount=Scores+1;

		if ((!MusicChanged) && (Scores == 10))
		{
			music0.stop();
			music1.play();
			MusicChanged = 1;
		}

	SpriteMountains.setPosition(player.GetX() * 0.12 - 100, 0);
	SpriteGrass.setPosition(player.GetX() * 0.4742 - 360, 0);
		//Drawing
	glClear(GL_DEPTH_BUFFER_BIT);    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	window.pushGLStates();
	if (Scores<10)
		window.draw(SpriteBackGround);
	else
		window.draw(SpriteBackGround2);
	window.draw(SpriteTarget);
	window.draw(SpriteMountains);
	player.Update(window, time);
	for (int i = 0; i < DrawCount; i++)
		figure[i]->Update(window, time);
	window.draw(SpriteGrass);
	if (player.Died)
	{
		window.draw(SpriteGameOver);
		music0.stop();
		music1.stop();
	}
	window.draw(text);
	window.popGLStates();
	window.display();
    }

    return 0;
}

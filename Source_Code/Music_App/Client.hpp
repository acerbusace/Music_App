#pragma once

#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>

#include "List.hpp"
#include "Player.hpp"
#include "Button.hpp"

class Client {
public:
	Client();
	~Client();

	void loop();
	void inputs();
	void update(sf::Time);
	void render();
private:
	sf::RenderWindow window;
	sf::Image icon;

	float winw, winh;

	sf::Clock clock;

	sf::Time volumeTime;
	float volumeTimeRate;

	sf::Time playTime;
	float playTimeRate;
	bool prevSongReleased, nextSongReleased;

	bool playButtonState;

	List list;

	Player musicPlayer;

	enum State
	{
		REGULAR,
		SHUFFLE
	};

	State playState;

	Button playButton;
	Button pauseButton;

	sf::RectangleShape songCompletion;
	sf::RectangleShape songCompletionOutLine;

	sf::Vector2i mousePos;

	bool plause, prevSong, nextSong, shuffle, sort, repeat, upVolume, downVolume, songOffSetHover, updateSongOffSet;

	bool mouseLeftButtonPressed;

	//std::vector<std::string> songs;

	//int songIndex;
};
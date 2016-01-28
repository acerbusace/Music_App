#include <SFML/System.hpp>

#include "Client.hpp"

Client::Client() {
	winw = 600;
	winh = 400;

	volumeTimeRate = 35;

	playTimeRate = 100;
	playTime = sf::Time(sf::milliseconds(playTimeRate));

	//boost::filesystem::path p = "C:/Users/Acerbusace/Music/test";

	std::vector<boost::filesystem::path> songs;
	list.Search(songs);

	musicPlayer.init(songs);

	playState = REGULAR;

	plause = false;
	prevSong = false;
	prevSongReleased = false;
	nextSong = false;
	nextSongReleased = false;
	shuffle = false;
	repeat = false;
	repeat = false;
	upVolume = false;
	downVolume = false;
	songOffSetHover = false;
	updateSongOffSet = false;

	mouseLeftButtonPressed = false;

	playButton.init("textures/playButton.png", "textures/playButtonHover.png", sf::Vector2f(winw / 2, winh / 2), sf::Vector2f(winw / 5, winh / 5));
	pauseButton.init("textures/pauseButton.png", "textures/pauseButtonHover.png", sf::Vector2f(winw / 2, winh / 2), sf::Vector2f(winw / 5, winh / 5));

	playButtonState = false;

	songCompletionOutLine.setOutlineThickness(5);
	songCompletionOutLine.setSize(sf::Vector2f(winw - songCompletionOutLine.getOutlineThickness() * 2, winh / 10 - songCompletionOutLine.getOutlineThickness()));
	songCompletionOutLine.setFillColor(sf::Color::Transparent);
	songCompletionOutLine.setOutlineColor(sf::Color::White);
	songCompletionOutLine.setPosition(sf::Vector2f(songCompletionOutLine.getOutlineThickness(), winh - songCompletionOutLine.getSize().y - songCompletionOutLine.getOutlineThickness()));

	songCompletion.setSize(sf::Vector2f(winw, winh / 10));
	songCompletion.setFillColor(sf::Color::Blue);
	songCompletion.setPosition(sf::Vector2f(0, winh - songCompletion.getSize().y));

	//creating and setting window and icon
	icon.loadFromFile("favicon.png");

	window.create(sf::VideoMode(winw, winh), "Music Player");
	window.setFramerateLimit(60);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

Client::~Client() {

}

void Client::loop() {
	while (window.isOpen()) {
		inputs();

		sf::Time timeElapsed = clock.getElapsedTime();
		clock.restart();
		update(timeElapsed);
		render();
	}
}

void Client::inputs() {
	sf::Event event;

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Space:
				//plause = true;
				break;

			case sf::Keyboard::Left:
				prevSong = true;
				break;

			case sf::Keyboard::Right:
				nextSong = true;
				break;

			case sf::Keyboard::S:
				shuffle = true;
				break;

			case sf::Keyboard::N:
				sort = true;
				break;

			case sf::Keyboard::R:
				repeat = true;
				break;

			case sf::Keyboard::Equal:
				upVolume = true;
				break;

			case sf::Keyboard::Dash:
				downVolume = true;
				break;
			}
			break;

		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Space:
				plause = true;
				break;

			case sf::Keyboard::Left:
				prevSongReleased = true;
				break;

			case sf::Keyboard::Right:
				nextSongReleased = true;
				break;

			case sf::Keyboard::Equal:
				upVolume = false;
				break;

			case sf::Keyboard::Dash:
				downVolume = false;
				break;
			}
			break;
		}
	}

	mousePos = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		mouseLeftButtonPressed = true;
	}
	else {
		if (mouseLeftButtonPressed) {
			if (playButton.collision(mousePos)) {
				plause = true;
			}
		}
		mouseLeftButtonPressed = false;
	}

	if (mousePos.x > songCompletion.getPosition().x - songCompletionOutLine.getOutlineThickness() && mousePos.x < songCompletionOutLine.getPosition().x + songCompletionOutLine.getSize().x + songCompletionOutLine.getOutlineThickness() && mousePos.y > songCompletion.getPosition().y && mousePos.y < songCompletion.getPosition().y + songCompletion.getSize().y) {
		songOffSetHover = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			updateSongOffSet = true;
		}
	}
	else {
		songOffSetHover = false;
	}
}

void Client::update(sf::Time timeElapsed) {
	if (plause) {
		if (playButtonState) {
			playButtonState = false;
		}
		else {
			playButtonState = true;
		}

		musicPlayer.Plause();

		plause = false;
	}

	if (nextSong || prevSong) {
		playTime += timeElapsed;

		if (playTime.asMilliseconds() > playTimeRate) {
			if (nextSong) {
				std::cout << "Index: " << musicPlayer.nextSong() << std::endl;
			}
			if (prevSong) {
				std::cout << "Index: " << musicPlayer.prevSong() << std::endl;
			}
			playTime = sf::Time::Zero;
		}

		if (!prevSong) {
			if (nextSongReleased) {
				musicPlayer.playSong();
				nextSong = false;
				nextSongReleased = false;
				playTime = sf::Time(sf::milliseconds(playTimeRate));
			}
		}
		else if (!nextSong) {
			if (prevSongReleased) {
				musicPlayer.playSong();
				prevSong = false;
				prevSongReleased = false;
				playTime = sf::Time(sf::milliseconds(playTimeRate));
			}
		}
		else {
			if (prevSongReleased) {
				prevSong = false;
				prevSongReleased = false;
			}

			if (nextSongReleased) {
				nextSong = false;
				nextSongReleased = false;
			}

			if (prevSongReleased && nextSongReleased) {
				musicPlayer.playSong();
				prevSong = false;
				nextSong = false;
				prevSongReleased = false;
				nextSongReleased = false;
				playTime = sf::Time(sf::milliseconds(playTimeRate));
			}
		}
	}

	if (shuffle) {
		musicPlayer.shuffle();
		musicPlayer.playNext();

		shuffle = false;
	}

	if (sort) {
		musicPlayer.sort();
		musicPlayer.playNext();

		sort = false;
	}

	if (repeat) {
		musicPlayer.repeat();

		repeat = false;
	}

	if (upVolume || downVolume) {
		volumeTime += timeElapsed;

		if (volumeTime.asMilliseconds() > volumeTimeRate) {
			if (upVolume) {
				musicPlayer.volumeUp();
			}

			if (downVolume) {
				musicPlayer.volumeDown();
			}
			volumeTime = sf::Time::Zero;
		}
	}

	if (songOffSetHover) {
		songCompletionOutLine.setOutlineColor(sf::Color::Cyan);
	}
	else {
		songCompletionOutLine.setOutlineColor(sf::Color::White);
	}

	if (updateSongOffSet) {
		std::cout << "x " << mousePos.x << "w " << winw << std::endl;
		std::cout << "ratio " << mousePos.x / winw << std::endl;
		musicPlayer.setMusicOffSet(mousePos.x / winw);

		updateSongOffSet = false;
	}


	if (playState == REGULAR) {
		if (musicPlayer.musicDone()) {
			musicPlayer.playNext();
		}
	}

	playButton.collision(mousePos);
	pauseButton.collision(mousePos);
	songCompletion.setSize(sf::Vector2f(musicPlayer.getMusicCompleteRatio()*winw, winh / 10));
}

void Client::render() {
	window.clear();

	//draw
	if (playButtonState) {
		window.draw(playButton.getButton());
	}
	else {
		window.draw(pauseButton.getButton());
	}
	window.draw(songCompletion);
	window.draw(songCompletionOutLine);

	window.display();
}
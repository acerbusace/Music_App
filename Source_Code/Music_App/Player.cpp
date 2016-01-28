#include <iostream>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "Player.hpp"

Player::Player() {
	std::srand(std::time(0));

	index = -1;
	playingSongIndex = index;
	volume = 50;
	volumeRate = 1;
}

Player::~Player() {

}

void Player::init(std::vector<boost::filesystem::path> songs) {
	this->songAd = songs;

	playNext();
}

void Player::Plause() {
	std::cout << "Plause" << std::endl;

	if (music.getStatus() == sf::Music::Playing) {
		//std::cout << "Music Playing" << std::endl;

		music.pause();
	}
	else {
		music.play();
	}
}

int Player::nextSong() {
	index + 1 >= songAd.size() ? index = 0 : index++;
	return index;
}

int Player::prevSong() {
	index - 1 < 0 ? index = songAd.size() - 1 : index--;
	return index;
}

int Player::getIndex() {
	return index;
}

void Player::playSong() {
	if (playingSongIndex != index) {
		if (loadMusic()) {
			playMusic();
		}
	}
}

void Player::playNext() {
	nextSong();
	playSong();
}

void Player::playPrev() {
	prevSong();
	playSong();
}


bool Player::loadMusic() {
	if (songAd.size() == 0) {
		std::cout << "Found no soungs on the list" << std::endl;
		return false;
	}

	if (!music.openFromFile(songAd[index].string())) {
		std::cout << "ERROR: Failed to load music from file -> " << songAd[index] << std::endl;
		return false;
	}
	return true;
}

void Player::playMusic() {
	std::cout << "index: " << index << ", numOfSongs: " << songAd.size() << ", " << songAd[index].string() << std::endl;

	playingSongIndex = index;
	music.play();
}

bool Player::musicDone() {
	if (music.getStatus() == sf::Music::Stopped) {
		return true;
	}
	return false;
}

void Player::volumeUp() {
	if (music.getVolume() + volumeRate > 100) {
		music.setVolume(100);
	}
	else {
		music.setVolume(music.getVolume() + volumeRate);
	}
	std::cout << "Volume: " << music.getVolume() << std::endl;
}

void Player::volumeDown() {
	if (music.getVolume() - volumeRate < 0) {
		music.setVolume(0);
	}
	else {
		music.setVolume(music.getVolume() - volumeRate);
	}
	std::cout << "Volume: " << music.getVolume() << std::endl;
}

float Player::getMusicCompleteRatio() {
	return music.getPlayingOffset() / music.getDuration();
}

sf::Time Player::getMusicDuration() {
	return music.getDuration();
}

void Player::setMusicOffSet(float ratio) {
	std::cout << "time " << ratio*music.getDuration().asSeconds() << std::endl;
	music.setPlayingOffset(sf::seconds(ratio*music.getDuration().asSeconds()));
}

int Player::random(int i) {
	return std::rand() % i;
}

void Player::shuffle() {
	std::random_shuffle(songAd.begin(), songAd.end());

	index = -1;
}

void Player::sort() {
	std::sort(songAd.begin(), songAd.end());

	index = -1;
}

void Player::repeat() {
	if (music.getLoop()) {
		music.setLoop(false);
	}
	else {
		music.setLoop(true);
	}
}
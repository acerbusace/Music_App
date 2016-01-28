#pragma once

#include <vector>
#include <SFML/Audio.hpp>

class Player {
public:
	Player();
	~Player();

	void init(std::vector<boost::filesystem::path>);
	int nextSong();
	int prevSong();
	int getIndex();
	void playSong();
	void playNext();
	void playPrev();
	void Plause();
	bool musicDone();
	void volumeUp();
	void volumeDown();
	float getMusicCompleteRatio();
	sf::Time getMusicDuration();
	void setMusicOffSet(float ratio);
	int random(int i);
	void shuffle();
	void sort();
	void repeat();
private:
	std::vector<boost::filesystem::path> songAd;

	sf::Music music;

	int index;
	int playingSongIndex;
	int volume;
	float volumeRate;

	bool loadMusic();
	void playMusic();
};
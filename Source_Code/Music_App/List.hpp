#pragma once

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

class List{
public:
	List();
	~List();

	std::string getMusicFolderPath();
	void Search(std::vector<boost::filesystem::path>&);
	void Search(boost::filesystem::path, std::vector<boost::filesystem::path>&);
private:
	std::vector<std::string> ext;
};
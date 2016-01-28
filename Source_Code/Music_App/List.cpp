#include <vector>
#include "List.hpp"

List::List() {
	ext.push_back(".ogg");
	ext.push_back(".wav");
	ext.push_back(".flac");
	ext.push_back(".aiff");
	ext.push_back(".raw");
	ext.push_back(".paf");
	ext.push_back(".svx");
	ext.push_back(".nist");
	ext.push_back(".voc");
	ext.push_back(".ircam");
	ext.push_back(".w64");
	ext.push_back(".mat4");
	ext.push_back(".mat5 ");
	ext.push_back(".pvf");
	ext.push_back(".htk");
	ext.push_back(".sds");
	ext.push_back(".avr");
	ext.push_back(".sd2");
	ext.push_back(".caf");
	ext.push_back(".wve");
	ext.push_back(".mpc2k");
	ext.push_back(".rf64");
}

List::~List() {

}

std::string List::getMusicFolderPath() {
	std::string user = "Users";
	std::string appData = "AppData";
	std::string userName = boost::filesystem::temp_directory_path().string().substr(boost::filesystem::temp_directory_path().string().find(user) + user.length() + 1, boost::filesystem::temp_directory_path().string().find(appData) - boost::filesystem::temp_directory_path().string().find(user) - user.length() - 2);

	std::string musicPath = "C:/users/" + userName + "/Music";
	return musicPath;
}

void List::Search(std::vector<boost::filesystem::path> &list) {
	boost::filesystem::path p = getMusicFolderPath();

	if (boost::filesystem::is_directory(p)) {
		for (auto i = boost::filesystem::directory_iterator(p); i != boost::filesystem::directory_iterator(); i++) {
			//std::string::size_type status = i->path().filename().string().find(".wav");
			if (boost::filesystem::is_regular_file(i->path())) {
				for (int j = 0; j < ext.size(); j++) {
					if (i->path().filename().string().find(ext[j]) != std::string::npos) {
						list.push_back(i->path());
						break;
					}
				}
			}

			if (boost::filesystem::is_directory(i->path())) {
				Search(i->path(), list);
			}
		}
	}
}

void List::Search(boost::filesystem::path p, std::vector<boost::filesystem::path> &list) {
	if (boost::filesystem::is_directory(p)) {
		for (auto i = boost::filesystem::directory_iterator(p); i != boost::filesystem::directory_iterator(); i++) {
			//std::string::size_type status = i->path().filename().string().find(".wav");
			if (boost::filesystem::is_regular_file(i->path())) {
				for (int j = 0; j < ext.size(); j++) {
					if (i->path().filename().string().find(ext[j]) != std::string::npos) {
						list.push_back(i->path());
						break;
					}
				}
			}

			if (boost::filesystem::is_directory(i->path())) {
				Search(i->path(), list);
			}
		}
	}
}
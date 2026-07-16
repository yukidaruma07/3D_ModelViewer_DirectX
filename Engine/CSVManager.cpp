#include "CSVManager.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include "LoggerManager.h"

CSVManager::CSVManager(const std::string& path)
{
	path_ = path;
	data_.clear();
}

CSVManager::~CSVManager()
{
}

void CSVManager::Init() {
	if (!path_.ends_with(".csv")) {
		MessageBox(NULL, "CSVファイル以外を読むことはできません。", NULL, MB_OK);
		return;
	}

	std::ifstream file(path_);
	if (!file.is_open()) {
		MessageBox(NULL, "ファイルを開くことができませんでした。", NULL, MB_OK);
		return;
	}

	std::string line = "";
	while (std::getline(file, line)) {
		std::vector<std::string> yVec;
		std::string oneText = "";
		for (int i = 0; i < line.length(); i++) {
			const char text = line.at(i);
			if (text == ',') {
				yVec.push_back(oneText);
				oneText = "";
			}
			else {
				oneText += text;
			}
		}
		data_.push_back(yVec);
	}

	LoggerManager::InfoDebug("x:" + std::to_string(data_.at(0).size()) + "y:" + std::to_string(data_.size()));
}

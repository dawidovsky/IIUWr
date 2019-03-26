#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <shared_mutex>
#include <thread>
#include <random>

std::shared_timed_mutex writeReadFile;

int randomNumber(int max) {
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(10, max);

	return distr(eng);
}

class Reader{
public:
	int id;

	Reader(int i) {
		id = i;
	}

	std::string lastLine() {
		std::fstream file;
		file.open("data.txt");
		int length = 0;
		std::string data;
		while (getline(file, data)) length++;
		file.close();
		file.open("data.txt");
		for (int i = 0; i < length; i++)getline(file, data);
		return data;
	}

	void readData() {
		std::string data;
		data = lastLine();
		if(data != "")
			std::cout << id << ": " << std::fixed <<  data.substr(3) << "\n";
	}
};

class Writer {
public:
	int id;

	Writer(int i) {
		id = i;
	}

	void writeData() {
		std::fstream file;
		std::string data;
		file.open("data.txt", std::ios_base::app);
		file << id << ": " << std::fixed << randomNumber(1000000) << "\n";
		file.close();
	}
};

class Arbitrator {
public:

	Arbitrator() {}

	void write(Writer w) {
		std::lock_guard<std::shared_timed_mutex> writerLock(writeReadFile);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		w.writeData();
	}

	void read(Reader r) {
		std::shared_lock<std::shared_timed_mutex> readerLock(writeReadFile);
		r.readData();
	}
};;

void pickRandomReader() {
	int chance = randomNumber(100);
	Reader r(chance);
	std::thread read(&Arbitrator::read, Arbitrator(), r);
	read.join();
};

void pickRandomWriter() {
	int chance = randomNumber(100);
	Writer w(chance);
	std::thread write(&Arbitrator::write, Arbitrator(), w);
	write.join();
}

int main(){
	int readerChance = 101;
	for (int i = 0; i < 10; i++) {
		int chance = randomNumber(readerChance);
		if (chance < 50) {
			readerChance = (int)(readerChance * 0.75);
			pickRandomReader();
		}
		else pickRandomWriter();
	}

}

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>

using std::string;
using std::vector;

class Player
{
	string name;
	int age;
	int duration_contract;
	int salary;
	string player_position;
	int played_game;
	int missed_game;
	string health_status;

public:
	Player(string name, int age, int duration_contract, int salary, string player_position,
		int played_game, int missed_game, string health_status)
		:
		name(name),
		age(age),
		duration_contract(duration_contract),
		salary(salary),
		player_position(player_position),
		played_game(played_game),
		missed_game(missed_game),
		health_status(health_status)
	{ }

	string getName() { return name; }
	int getAge() { return age; }
	int getDurationContract() { return duration_contract; }
	int getSalary() { return salary; }
	string getPlayerPosition() { return player_position; }
	int getPlayedGame() { return played_game; }
	int getMissedGame() { return missed_game; }
	string getHealthStatus() { return health_status; }
};

class Report
{
	string header;
	string body;
	string footer;

	string name_team;
	vector<Player> players;
	bool insert_name_player;
	bool insert_age;
	bool insert_duration_contract;
	bool insert_salary;
	bool insert_played_game;
	bool insert_missed_game;
	bool insert_health_status;
	bool insert_player_position;

public:

	Report(string name_team, vector<Player> players, bool insert_name_player, bool insert_age, bool insert_duration_contract,
		bool insert_player_position, bool insert_salary, bool insert_played_game,
		bool insert_health_status, bool insert_missed_game) :
		name_team(name_team),
		players(players),
		insert_name_player(insert_name_player),
		insert_age(insert_age),
		insert_duration_contract(insert_duration_contract),
		insert_salary(insert_salary),
		insert_played_game(insert_played_game),
		insert_missed_game(insert_missed_game),
		insert_health_status(insert_health_status),
		insert_player_position(insert_player_position)
	{
		buildHeader();
		buildBody();
		buildFooter();
	}

	void buildHeader()
	{
		std::chrono::zoned_time now{ std::chrono::current_zone(), std::chrono::system_clock::now() };
		header = "TEAM: " + name_team + "\nPLAYERS REPORT " + "ON DATE: " + std::format("{}", now);
		header += "\n============================================================";
		header += "============================================================";
	}

	void buildBody()
	{
		body += "\n";
		for (auto& el : players)
		{
			if (insert_name_player)
				body += "Player Name: " + el.getName() + "\t\t";
			if (insert_age)
				body += std::format("Age: {}\t\t", el.getAge());
			if (insert_duration_contract)
				body += std::format("Age: {}\t\t", el.getDurationContract());
			if (insert_salary)
				body += std::format("Salary: {}\t\t", el.getSalary());
			if (insert_played_game)
				body += std::format("Played game: {}\t\t", el.getPlayedGame());
			if (insert_missed_game)
				body += std::format("Missed game: {}\t\t", el.getMissedGame());
			if (insert_health_status)
				body += "Health status: " + el.getHealthStatus() + "\t\t";
			if (insert_player_position)
				body += "Player position: " + el.getPlayerPosition() + "\t\t";

			body += "\n";
		}
	}

	void buildFooter()
	{
		footer += "\n============================================================";
		footer += "============================================================\n";

		double sum = 0;
		for (auto& el : players)
			sum += el.getSalary();

		footer += ("\nTOTAL PLAYERS: " + std::format("{}", players.size()) +
			"\n" + "TOTAL SALARY: " + std::format("{}", sum) + " usd\n");
	}

	friend std::ostream& operator<< (std::ostream& out, const Report& rep)
	{
		out << "\n" << rep.header << "\n" << rep.body << "\n" << rep.footer;
		return out;
	}
};
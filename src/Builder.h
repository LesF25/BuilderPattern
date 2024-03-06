#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>

using std::string;
using std::vector;

class Report
{
public:
	string header;
	string body;
	string footer;

	friend std::ostream& operator<< (std::ostream& out, const Report& rep)
	{
		out << "\n" << rep.header << "\n" << rep.body << "\n" << rep.footer;
		return out;
	}
};

class ReportPlayer
{
public:
	string reportPlayer;
};

class IBuilder
{
public:
	virtual Report getReport() = 0;

	virtual void addHeader() = 0;

	virtual void addBody() = 0;

	virtual void addFooter() = 0;

	virtual void addNameBody() = 0;

	virtual void addAgeBody() = 0;

	virtual void addDurationContractBody() = 0;

	virtual void addSalaryBody() = 0;

	virtual void addPlayerPositionBody() = 0;

	virtual void addPlayedGameBody() = 0;

	virtual void addMissedGameBody() = 0;

	virtual void addHealthStatusBody() = 0;

	virtual ~IBuilder() = default;
};

class Director
{
	IBuilder* builder;
public:
	Director(IBuilder& builder) :
		builder(&builder)
	{
		generationBody();
	}

	void build()										// метод, в котором происходит построение отчёта
	{
		builder->addHeader();
		builder->addBody();
		builder->addFooter();
	}

private:
	void generationBody()								// метод, в котором директор может задавать определенные требования к отчёту (какая информация об игроках требуется)
	{
		builder->addNameBody();
		builder->addAgeBody();
		builder->addDurationContractBody();
		builder->addHealthStatusBody();
	}
};

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

class PlayerReportBuilder : public IBuilder
{
	Report report;
	string name_team;
	vector<Player> players;
	vector<ReportPlayer> playersReport;

public:
	PlayerReportBuilder(std::pair<string, vector<Player>> players) :
		name_team(players.first), players(players.second), playersReport(players.second.size())
	{ }

	~PlayerReportBuilder() = default;

	Report getReport() override { return report; }

	void addHeader() override
	{
		std::chrono::zoned_time now{ std::chrono::current_zone(), std::chrono::system_clock::now() };
		report.header = "TEAM: " + name_team + "\nPLAYERS REPORT " + "ON DATE: " + std::format("{}", now);
		report.header += "\n============================================================";
		report.header += "============================================================";
	}

	void addFooter() override
	{
		report.footer += "\n============================================================";
		report.footer += "============================================================\n";

		double sum = 0;
		for (auto& el : players)
			sum += el.getSalary();

		report.footer += ("TOTAL PLAYERS: " + std::format("{}", players.size()) +
			"\n" + "TOTAL SALARY: " + std::format("{}", sum) + " usd");
	}

	void addBody() override
	{
		for (auto& el : playersReport)
			report.body += el.reportPlayer + "\n";
	}

	void addNameBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += "Player Name: " + players[it].getName() + "\t\t";
	}

	void addAgeBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += std::format("Age: {}\t\t", players[it].getAge());
	}

	void addDurationContractBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += std::format("Duration contract: {}\t\t", players[it].getDurationContract());
	}

	void addSalaryBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += std::format("Salary: {}\t\t", players[it].getSalary());
	}

	void addPlayerPositionBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += "Player position: " + players[it].getPlayerPosition() + "\t\t";
	}

	void addPlayedGameBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += std::format("Played games: {}\t\t", players[it].getPlayedGame());
	}

	void addMissedGameBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += std::format("Missed games: {}\t\t", players[it].getMissedGame());
	}

	void addHealthStatusBody() override
	{
		for (int it = 0; it < players.size(); it++)
			playersReport[it].reportPlayer += "Health status: " + players[it].getHealthStatus() + "\t\t";
	}
};
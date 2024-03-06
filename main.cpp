// #include "NoBuilder.h"
#include "Builder.h"

int main()
{
	std::pair<string, vector<Player>> GOLDEN_STATE_WARRIORS = std::make_pair<string, vector<Player>>(
		"GOLDEN STATE WARRIORS",
		{
			Player("Stephen Curry   ", 35, 5, 10000, "Point guard", 55, 0, "Healthy"),
			Player("Klay Thompson   ", 33, 2, 6000, "Shooting guard", 50, 5, "Healthy"),
			Player("Draymond Green  ", 33, 3, 7000, "Power forward", 30, 25, "Healthy"),
			Player("Andrew Wiggins  ", 29, 2, 5500, "Small forward", 20, 35, "Healthy"),
			Player("Jonathan Kuminga", 22, 2, 1500, "Power forward", 55, 0, "Healthy"),
			Player("Kevon Looney    ", 28, 3, 5000, "Center", 55, 0, "Injury"),
			Player("Moses Moody     ", 22, 2, 1500, "Small forward", 40, 15, "Healthy"),
			Player("Chris Paul      ", 38, 2, 5000, "Point guard", 15, 30, "Injury"),
			Player("Gary Payton     ", 31, 3, 3500, "Shooting guard", 10, 35, "Injury"),
			Player("Dario Sarich    ", 30, 2, 2500, "Center", 33, 22, "Injury")
		}
	);

	PlayerReportBuilder builder_GSW(GOLDEN_STATE_WARRIORS);

	Director director_GSW(builder_GSW);
	director_GSW.build();

	Report report_GSW = builder_GSW.getReport();

	std::cout << report_GSW << "\n";

	return 0;
}
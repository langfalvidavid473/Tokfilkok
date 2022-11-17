#include "pch.h"
#include "../../Source_code/utilities.h"

TEST(PlayerTest, PlayerStatsPositive) {
	Player player1(1500, 300, 50, 0, 0);
	EXPECT_GT(player1.health, 0);
	EXPECT_GT(player1.damage, 0);
	EXPECT_GT(player1.armor, 0);
	EXPECT_GE(player1.gold, 0);
	EXPECT_GE(player1.keys, 0);
}

// Teszt: Szörnyeket tároló vektor tartalmaz elemeket

TEST(BossTest, BossVectorNotEmpty) {
	const string path = "../../Enemies";
	vector<Bosses> allBosses = generateBoss(path);
	const int countBosses = countEnemies(path);
	const int bossCount = allBosses.size();
	EXPECT_EQ(bossCount, countBosses);
}

// Teszt: Szörnyeket tároló vektor objektumai megfelelõ értékekkel vannak-e ellátva

TEST(BossTest, BossStatsPositive) {
	const string path = "../../Enemies";
	vector<Bosses> allBosses = generateBoss(path);
	for (int i = 0; i < allBosses.size(); i++) {
		EXPECT_GT(allBosses[i].damage, 0);
		EXPECT_GT(allBosses[i].health, 0);
		EXPECT_TRUE(allBosses[i].name.length() > 0);
	}
}

// Teszt: Árukat tároló vektor tartalmaz-e elemeket

TEST(ShopTest, ShopVectorNotEmpty) {
	const string path = "../../txtFiles/shop.txt";
	vector<ShopItems> shopGoods = shopSystem(path);
	EXPECT_GT(shopGoods.size(), 0);
}
// Teszt: Árukat tároló vektor objektumai megfelelõ értékkel vannak-e ellátva
TEST(ShopTest, ShopObjectsHaveValues) {
	const string path = "../../txtFiles/shop.txt";
	vector<ShopItems> shopGoods = shopSystem(path);
	for (int i = 0; i < shopGoods.size(); i++) {
		EXPECT_TRUE(shopGoods[i].buff == true or shopGoods[i].buff == false);
		EXPECT_TRUE(shopGoods[i].name.length() > 0);
		EXPECT_TRUE(shopGoods[i].price > 0);
		EXPECT_TRUE(shopGoods[i].type > 0 and shopGoods[i].type < 10);
		EXPECT_TRUE(shopGoods[i].value > 0);
	}
}

// Teszt: Debuffokat tároló vektor tartalmaz-e elemeket

TEST(DebuffsTest, DebuffsVectorNotEmpty) {
	const string path = "../../txtFiles/debuffs.txt";
	vector<Debuffs> debuffs = debuffSystem(path);
	EXPECT_GT(debuffs.size(), 0);
}

// Teszt: Debuffokat tároló vektor objektumai megfelelõ értékkel vannak-e ellátva

TEST(ShopTest, DebuffsObjectsHaveValues) {
	const string path = "../../txtFiles/debuffs.txt";
	vector<Debuffs> debuffs = debuffSystem(path);
	for (int i = 0; i < debuffs.size(); i++) {
		EXPECT_TRUE(debuffs[i].name.length() > 0);
		EXPECT_TRUE(debuffs[i].type > 0 and debuffs[i].type < 7);
		EXPECT_TRUE(debuffs[i].value > 0);
	}
}
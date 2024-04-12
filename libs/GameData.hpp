#pragma once
#include <vector>
#include <fstream>
#include "GameManager.hpp"

class GameData
{
public:
  static void saveGame(const GameManager &manager, const std::string &filename);
  static GameManager loadGame(const std::string &filename);

private:
  // Helper functions for serialization/deserialization
  static void serializePlayer(std::ofstream &file, const PlayerController *player);
  static PlayerController *deserializePlayer(std::ifstream &file);
  static void serializeEnemy(std::ofstream &file, const EnemyController *enemy);
  static EnemyController *deserializeEnemy(std::ifstream &file);
};

#include "GameData.hpp"

void GameData::saveGame(const GameManager &manager, const std::string &filename)
{
  std::ofstream file(filename, std::ios::binary);
  if (!file)
  {
    std::cerr << "Error: Unable to open file for writing.\n";
    return;
  }

  // Serialize game manager data
  file.write(reinterpret_cast<const char *>(&manager), sizeof(manager));

  file.close();
}

GameManager GameData::loadGame(const std::string &filename)
{
  std::ifstream file(filename, std::ios::binary);
  if (!file)
  {
    std::cerr << "Error: Unable to open file for reading.\n";
    // You might want to handle this error in your game
    exit(1);
  }

  // Read game manager data
  GameManager manager;
  file.read(reinterpret_cast<char *>(&manager), sizeof(manager));

  file.close();

  return manager;
}

void GameData::serializePlayer(std::ofstream &file, const PlayerController *player)
{
  // Serialize player data
}

PlayerController *GameData::deserializePlayer(std::ifstream &file)
{
  // Deserialize player data
  return nullptr;
}

void GameData::serializeEnemy(std::ofstream &file, const EnemyController *enemy)
{
  // Serialize enemy data
}

EnemyController *GameData::deserializeEnemy(std::ifstream &file)
{
  // Deserialize enemy data
  return nullptr;
}
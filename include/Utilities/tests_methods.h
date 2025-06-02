#ifndef TESTS_METHODS_H
#define TESTS_METHODS_H

/**
 * @file test_methods.h 
 * @brief Additional functions needed to make tests more convenient and easy to check. 
*/

#include "Players/Player.h"
#include "Players/Bot.h"

#include <memory> 

/**
 * @brief Function that creates Bot with given parameters.
 * @param name Name of Bot. 
 * @param health Health of Bot. 
 * @param respect Respect of Bot. 
 * @param difficulty Difficulty of Bot. 
 * @return Unique pointer on Bot class object which represents the needed Bot.
*/
std::unique_ptr<Bot> createTestBot(const std::string& name, int health, int respect, Difficulty difficulty);

/**
 * @brief Function that creates Player with given parameters.
 * @param name Name of Player. 
 * @param health Health of Player. 
 * @param respect Respect of Player. 
 * @return Unique pointer on Player class object which represents the needed Bot.
*/
std::unique_ptr<Player> createTestPlayer(const std::string& name, int health, int respect);

#endif
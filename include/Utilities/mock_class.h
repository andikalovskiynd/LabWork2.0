#ifndef MOCK_CLASS_H
#define MOCK_CLASS_H

/**
 * @file mock_class.h 
 * @brief GameManager mock class and Deck class stub.
*/

#include "gmock/gmock.h"

#include "Game/GameManager/GameManager.h"
#include "Deck/Deck.h"

/**
 * @brief Deck stub. 
 * @details Needed only to initialize GameManager mock.
*/
class StubDeck : public Deck 
{
    public:
        /**
         * @brief StubDeck constructor. 
         * @details Initializes empty deck. 
        */
        StubDeck() : Deck() {}
};

/**
 * @brief Mock of GameManager class. 
*/
class MockGameManager : public GameManager
{
    private:
        StubDeck stubDeck_; //< StubDeck. 

    public: 
        /**
         * @brief MockGameManager constructor. 
         * @param stubDeck_ Deck stub. 
        */
        MockGameManager() : GameManager(stubDeck_), stubDeck_() {}

        /**
         * @brief shouldAmplify() method mock. 
        */
        MOCK_METHOD(bool, shouldAmplify, (), (const, override));

        /**
         * @brief getPlayers() method mock. 
        */
        MOCK_METHOD(const std::vector<std::unique_ptr<Character>>&, getPlayers, (), (const, override));

        /**
         * @brief updateMagicPool() method mock. 
        */
        MOCK_METHOD(void, updateMagicPool, (int amount), (override));

        /**
         * @brief getCurrentPlayer() method mock.
        */
        MOCK_METHOD(Character*, getCurrentPlayer, (), (override));

        /**
         * @brief setCurrentPlayer() method mock.
        */
        MOCK_METHOD(void, setCurrentPlayer, (Character* player), (override));

        /**
         * @brief resetMagicPool() method mock.
        */
        MOCK_METHOD(void, resetMagicPool, (), (override));

        /**
         * @brief addSpirit() method mock.
        */
        MOCK_METHOD(void, addSpirit, (std::unique_ptr<Spirit> spirit), (override));

        /**
         * @brief addPlayer() method mock.
        */
        MOCK_METHOD(void, addPlayer, (std::unique_ptr<Character> player), (override));

        /**
         * @brief getMagicPool() method mock.
        */
        MOCK_METHOD(int, getMagicPool, (), (const, override));
};

#endif
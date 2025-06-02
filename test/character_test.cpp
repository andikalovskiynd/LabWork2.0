/**
 * @defgroup CharacterTest Test of class Character and inherits
 * @file character_test.cpp 
 * @brief Test for Character class.
 * @{
*/

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Utilities/mock_class.h"

#include "Players/Character.h"
#include "Players/Player.h" // Character is an abstract class so we can't make object of it
#include "Players/Bot.h" // opponent is neccesery

#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"

#include <string>
#include <memory> 
#include <vector>

// Using Player as inherit of Character and its representative
// A lot of AAA comments for my personal covinience and logic separation of code

// Character tests
// Constructor test
/**
 * @brief Test of Character class constructor.
*/
TEST(CharacterTestConstructor, Constructor_Initializes_Correctly)
{
    // Arrange 
    Player testChar("Test char", 10, 15);

    // Act EMPTY

    // Assert
    ASSERT_EQ("Test char", testChar.getName());
    ASSERT_EQ(10, testChar.getHealth());
    ASSERT_EQ(15, testChar.getRespect());
}

// Basic Getters (name, health, respect) test
/**
 * @brief Test of basic getters from class Character. 
 * @details 2 series of checks, at first initialize check, then change and check again. 
*/
TEST(CharacterTestGetters, BasicGetters_Return_CorrectValues)
{
    // Arrange 
    Player testChar("Test char", 10, 15);
    
    // Act EMPTY

    // Assert 
    ASSERT_EQ("Test char", testChar.getName());
    ASSERT_EQ(10, testChar.getHealth());
    ASSERT_EQ(15, testChar.getRespect());


    // NEW Arrange NOT NEEDED


    // NEW Act 
    testChar.changeHealth(10);
    testChar.changeRespect(10);


    // NEW Assert 
    ASSERT_EQ(20, testChar.getHealth());
    ASSERT_EQ(25, testChar.getRespect());
}

// changeHealth() tests
// Test for healing
/**
 * @brief First test of Character changeHealth() method. 
 * @details Checking Increasing of health. 
*/
TEST(CharacterTestChanges, ChangeHealth_Increases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialHealth = 20;
    int healing = 10;


    // Act
    testChar.changeHealth(healing);


    // Assert
    ASSERT_EQ(initialHealth + healing, testChar.getHealth());
}

// Damage test
/**
 * @brief Second test of Character changeHealth() method. 
 * @details Checking decreasing of health. 
*/
TEST(CharacterTest, ChangeHealth_Decreases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialHealth = 20;
    int damage = -10;


    // Act
    testChar.changeHealth(damage);


    // Assert
    ASSERT_EQ(initialHealth + damage, testChar.getHealth());
}

// Zero changes test
/**
 * @brief Third test of Character changeHealth() method. 
 * @details Checking what happens if change will be zero. 
*/
TEST(CharacterTestChanges, ChangeHealth_ZeroDamage_NothingChanges)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialHealth = 20;
    int damage = 0;


    // Act
    testChar.changeHealth(damage);


    // Assert
    ASSERT_EQ(initialHealth, testChar.getHealth());
}

// changeRespect() tests 
// Test for increasing respect
/**
 * @brief First test of Character changeRespect() method. 
 * @details Checking Increasing of respect. 
*/
TEST(CharacterTestChanges, ChangeRespect_Increases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialRespect = 20;
    int change = 10;


    // Act
    testChar.changeRespect(change);


    // Assert
    ASSERT_EQ(initialRespect + change, testChar.getRespect());
}

// Decrease test
/**
 * @brief Second test of Character changeRespect() method. 
 * @details Checking Decreasing of respect. 
*/
TEST(CharacterTestChanges, ChangeRespect_Decreases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialRespect = 20;
    int change = -10;


    // Act
    testChar.changeRespect(change);


    // Assert
    ASSERT_EQ(initialRespect + change, testChar.getRespect());
}

/**
 * @brief Third test of Character changeRespect() method. 
 * @details Checking respect change with zero value. 
*/
TEST(CharacterTestChanges, ChangeRespect_ZeroChange_NothingChanges)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialRespect = 20;
    int change = 0;


    // Act
    testChar.changeRespect(change);


    // Assert
    ASSERT_EQ(initialRespect, testChar.getRespect());
}

// IsAlive() tests
// Positive test
/**
 * @brief First test of Character isAlive() method.
 * @details Two players are alive, expected to return true. 
*/
TEST(CharacterTestIsAlive, IsAlive_ReturnsWhenPositiveHealth_True)
{
    // Arrange 
    Player testChar1("Test char 1", 20, 20);
    Player testChar2("Test char 2", 20, 20);

    // Act EMPTY

    // Assert
    ASSERT_TRUE(testChar1.IsAlive());
    ASSERT_TRUE(testChar2.IsAlive());
}

/**
 * @brief Second test of Character isAlive() method.
 * @details One player is alive other is zero health, expected to return false in both ways.
*/
TEST(CharacterTestIsAlive, IsAlive_ReturnsWhenZeroOrNegative_False)
{
    // Arrange 
    Player testChar1("Test char 1", 0, 20);
    Player testChar2("Test char 2", -10, 20);

    // Act EMPTY

    // Assert
    ASSERT_FALSE(testChar1.IsAlive());
    ASSERT_FALSE(testChar2.IsAlive());
}

// ApplyCardEffect() tests using mock and stub 
// Attack card not amplified
/**
 * @brief Not amplified Attack card ApplyCardEffect() method test.
*/
TEST(CharacterTestAttack, ApplyCardEffect_AttackCardNotAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    AttackCard stubAttackCard("Test Attack", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubAttackCard.getHealthEffect();
    int magicEffect = stubAttackCard.getMagicEffect();

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubAttackCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth - healthEffect, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock checks everything else 
}

// Attack card amplified
/**
 * @brief Amplified Attack card ApplyCardEffect() method test.
*/
TEST(CharacterTestAttack, ApplyCardEffect_AttackCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    AttackCard stubAttackCard("Test Attack", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubAttackCard.getHealthEffect();
    int magicEffect = stubAttackCard.getMagicEffect();

    int ampHealth = healthEffect * 2;
    int ampMagic = magicEffect * 2;

    // mock: shouldAmplify() must return true
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reseting mp

    // Act
    testCharPtr->ApplyCardEffect(stubAttackCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth - ampHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock checks everything else 
}

// Heal card not amplified 
/**
 * @brief Not amplified Heal card ApplyCardEffect() method test.
*/
TEST(CharacterTestHeal, ApplyCardEffect_HealCardNotAmplifed_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    HealCard stubCard("Test Heal", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubCard.getHealthEffect();
    int magicEffect = stubCard.getMagicEffect();

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth + healthEffect, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Heal card amplified 
/**
 * @brief Amplified Heal card ApplyCardEffect() method test.
*/
TEST(CharacterTestHeal, ApplyCardEffect_HealCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    HealCard stubCard("Test Heal", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubCard.getHealthEffect();
    int magicEffect = stubCard.getMagicEffect();

    int ampHealth = healthEffect * 2;
    int ampMagic = magicEffect * 2;

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reseting mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth + ampHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}


// Respect card not amplified
/**
 * @brief Not amplified Respect card ApplyCardEffect() method test.
*/
TEST(CharacterTestRespect, ApplyCardEffect_RespectCardNotAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    RespectCard stubCard("Test Respect", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int respectEffect = stubCard.getRespectEffect();
    int magicEffect = stubCard.getMagicEffect();

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act 
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect + respectEffect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Respect card amplified
/**
 * @brief Amplified Respect card ApplyCardEffect() method test.
*/
TEST(CharacterTestRespect, ApplyCardEffect_RespectCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    RespectCard stubCard("Test Heal", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int respectEffect = stubCard.getRespectEffect();
    int magicEffect = stubCard.getMagicEffect();

    int ampRespect = respectEffect * 2;
    int ampMagic = magicEffect * 2;

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reseting mp

    // Act 
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect + ampRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Magic card not amplified
/**
 * @brief Not amplified Magic card ApplyCardEffect() method test.
*/
TEST(CharacterTestMagic, ApplyCardEffect_MagicCardNotAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    MagicCard stubCard("Test Magic", 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int magicEffect = stubCard.getMagicEffect();

    // mock:
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Magic Card amplified 
/**
 * @brief Amplified Magic card ApplyCardEffect() method test.
*/
TEST(CharacterTestMagic, ApplyCardEffect_MagicCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    MagicCard stubCard("Test Magic", 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int magicEffect = stubCard.getMagicEffect();

    int ampMagic = magicEffect * 2;

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Zero changes card
/**
 * @brief Zero changes card ApplyCardEffect() test.
*/
TEST(CharacterTestZero, ApplyCardEffect_ZeroChangeCard_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    Card stubCard("Test", 0, 0, 0, Card::Type::ATTACK);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int magicEffect = stubCard.getMagicEffect();

    // mock: shouldAmplify() may be called 0 or 1 time 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so do not reset mp


    // Act 
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

/**
 * @}
*/
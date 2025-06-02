/**
 * @file card_test.cpp 
 * @brief Tests for class Card and it's inherits.
*/

#include "gtest/gtest.h"

#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"

// Basic Card class tests
// Constrcutor and getters
/**
 * @brief Test of constructor and getters of basic Card class.
 * @details It is expected to make a correct Basic Card object of class Card which is being cheked after. 
*/
TEST(BasicCardTest, ConstructorAndGetters)
{
    // Arrange
    Card testCard("Basic card", 10, 5, 3, Card::Type::ATTACK);

    // Assert
    ASSERT_EQ("Basic card", testCard.getName());
    ASSERT_EQ(10, testCard.getHealthEffect());
    ASSERT_EQ(5, testCard.getRespectEffect());
    ASSERT_EQ(3, testCard.getMagicEffect());
    ASSERT_EQ(Card::Type::ATTACK, testCard.getType());

    EXPECT_EQ("Basic card", testCard.getName());
    EXPECT_EQ(10, testCard.getHealthEffect());
    EXPECT_EQ(5, testCard.getRespectEffect());
    EXPECT_EQ(3, testCard.getMagicEffect());
    EXPECT_EQ(Card::Type::ATTACK, testCard.getType());
}

// '==' test
/**
 * @brief Test of operator '==' overloading from Card class. 
 * @details It is expected to return correct value when card names are similar and when not.
*/
TEST(BasicCardTest, EqualityOperator)
{
    Card card1("Name", 0, 0, 0, Card::Type::ATTACK);
    Card card2("Name", 1, 1, 1, Card::Type::HEAL);
    Card card3("Not name", 0, 0, 0, Card::Type::ATTACK);

    ASSERT_TRUE(card1 == card2);
    ASSERT_FALSE(card1 == card3);
    ASSERT_FALSE(card2 == card3);
}

// Inherits tests
// Attack card
/**
 * @brief Test of constructor and getters of Attack Card class.
 * @details It is expected to make a correct Attack Card object which is being cheked after. 
*/
TEST(AttackCardTest, ConstructorGettersEffects)
{
    AttackCard attackCard("Fireball", 8, 5);

    ASSERT_EQ("Fireball", attackCard.getName());
    ASSERT_EQ(Card::Type::ATTACK, attackCard.getType());

    ASSERT_EQ(8, attackCard.getHealthEffect());
    ASSERT_EQ(5, attackCard.getMagicEffect());
    ASSERT_EQ(0, attackCard.getRespectEffect());
}

// Heal card
/**
 * @brief Test of constructor and getters of Heal Card class.
 * @details It is expected to make a correct Heal Card object which is being cheked after. 
*/
TEST(HealCardTest, ConstructorGettersEffects)
{
    HealCard healCard("Minor healing", 6, 2);

    ASSERT_EQ("Minor healing", healCard.getName());
    ASSERT_EQ(Card::Type::HEAL, healCard.getType());

    ASSERT_EQ(6, healCard.getHealthEffect());
    ASSERT_EQ(2, healCard.getMagicEffect());
    ASSERT_EQ(0, healCard.getRespectEffect());
}

/**
 * @brief Test of constructor and getters of Magic Card class.
 * @details It is expected to make a correct Magic Card object which is being cheked after. 
*/
TEST(MagicCardTest, ConstructorGettersEffects)
{
    MagicCard magicCard("Mana burst", 7);

    ASSERT_EQ("Mana burst", magicCard.getName());
    ASSERT_EQ(Card::Type::MAGIC, magicCard.getType());

    ASSERT_EQ(0, magicCard.getHealthEffect());
    ASSERT_EQ(7, magicCard.getMagicEffect());
    ASSERT_EQ(0, magicCard.getRespectEffect());
}

/**
 * @brief Test of constructor and getters of Respect Card class.
 * @details It is expected to make a correct Respect Card object which is being cheked after. 
*/
TEST(RespectCardTest, ConstructorGettersEffects)
{
    RespectCard respectCard("Bow", 4, 1);

    ASSERT_EQ("Bow", respectCard.getName());
    ASSERT_EQ(Card::Type::RESPECT, respectCard.getType());

    ASSERT_EQ(0, respectCard.getHealthEffect());
    ASSERT_EQ(1, respectCard.getMagicEffect());
    ASSERT_EQ(4, respectCard.getRespectEffect());
}
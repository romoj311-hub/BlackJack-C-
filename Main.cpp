// ============================================================================
// BlackJack.cpp - SFML 3.x Graphical Version
// Title: Blackjack Game
// Description: A playable blackjack game with SFML 3.x graphics
// Author: Juan, Anthony
// Date: 5/10/26
// ============================================================================

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Player.h"
#include "Dealer.h"
#include "CardDeck.h"
#include "Cards.h"
using namespace std;

// ============================================================================
// Constants
// ============================================================================
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;
const float CARD_WIDTH = 120.f;
const float CARD_HEIGHT = 174.f;
const float CARD_SPACING = 135.f;

// ============================================================================
// GameState
// ============================================================================
enum class GameState {
    WaitingToDeal,   // Showing DEAL button, no cards yet
    Dealing,         // Animating the initial 4-card deal
    PlayerTurn,      // HIT / STAND available
    DealerTurn,      // Dealer auto-plays
    ShowResult       // Win/loss screen
};

// ============================================================================
// getCardKey()
// ============================================================================
string getCardKey(int value, int index) {
    vector<string> suits = { "clubs", "diamonds", "hearts", "spades" };
    string suit = suits[index % 4];
    if (value == 11) return "ace_of_" + suit;
    if (value == 10) {
        vector<string> tens = { "10", "jack", "queen", "king" };
        return tens[index % 4] + "_of_" + suit;
    }
    return to_string(value) + "_of_" + suit;
}

// ============================================================================
// loadCardTextures()
// ============================================================================
void loadCardTextures(map<string, sf::Texture>& textures) {
    vector<string> ranks = { "ace","2","3","4","5","6","7","8","9","10","jack","queen","king" };
    vector<string> suits = { "clubs","diamonds","hearts","spades" };

    for (auto& rank : ranks) {
        for (auto& suit : suits) {
            string key = rank + "_of_" + suit;
            string path = "cards/" + key + ".png";
            sf::Texture tex;
            if (tex.loadFromFile(path))
                textures[key] = std::move(tex);
            else
                cout << "Warning: Could not load " << path << endl;
        }
    }

    sf::Texture backTex;
    if (backTex.loadFromFile("cards/download.png"))
        textures["back"] = std::move(backTex);
    else
        cout << "Warning: Could not load cards/download.png" << endl;
}

// ============================================================================
// makeCardSprite()
// ============================================================================
sf::Sprite makeCardSprite(const string& key, map<string, sf::Texture>& textures,
    float x, float y) {
    sf::Sprite sprite(textures.count(key) ? textures[key] : textures["back"]);
    sf::Vector2u texSize = sprite.getTexture().getSize();
    sprite.setScale({ CARD_WIDTH / (float)texSize.x, CARD_HEIGHT / (float)texSize.y });
    sprite.setPosition({ x, y });
    return sprite;
}

// ============================================================================
// centerText()
// ============================================================================
void centerText(sf::Text& text, float windowWidth, float y) {
    sf::FloatRect b = text.getLocalBounds();
    text.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    text.setPosition({ windowWidth / 2.f, y });
}

// ============================================================================
// main()
// ============================================================================
int main() {
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Blackjack");
    window.setFramerateLimit(60);

    // Font
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Could not load font!" << endl;
        return -1;
    }

    // Textures
    map<string, sf::Texture> cardTextures;
    loadCardTextures(cardTextures);

    // ========== BACKGROUND ==========
    sf::RectangleShape table({ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
    table.setFillColor(sf::Color(34, 100, 34));

    sf::CircleShape felt(380.f, 60);
    felt.setFillColor(sf::Color(27, 85, 27));
    felt.setOrigin({ 380.f, 380.f });
    felt.setPosition({ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f });

    // ========== UI TEXT ==========
    sf::Text titleText(font, "BLACKJACK", 42);
    titleText.setFillColor(sf::Color(255, 215, 0));
    titleText.setStyle(sf::Text::Bold);
    centerText(titleText, WINDOW_WIDTH, 30.f);

    sf::Text dealerLabel(font, "Dealer", 22);
    dealerLabel.setFillColor(sf::Color::White);
    dealerLabel.setPosition({ 40.f, 100.f });

    sf::Text playerLabel(font, "Player", 22);
    playerLabel.setFillColor(sf::Color::White);
    playerLabel.setPosition({ 40.f, 490.f });

    sf::Text dealerValueText(font, "", 20);
    dealerValueText.setFillColor(sf::Color::Yellow);
    dealerValueText.setPosition({ 40.f, 128.f });

    sf::Text playerValueText(font, "", 20);
    playerValueText.setFillColor(sf::Color::Yellow);
    playerValueText.setPosition({ 40.f, 518.f });

    sf::Text scoreText(font, "", 22);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);

    sf::Text resultText(font, "", 52);
    resultText.setStyle(sf::Text::Bold);

    sf::Text messageText(font, "", 22);
    messageText.setFillColor(sf::Color::White);

    sf::Text dealPrompt(font, "Click DEAL to play again", 20);
    dealPrompt.setFillColor(sf::Color(200, 200, 200));

    // Result backdrop
    sf::RectangleShape resultBox({ 440.f, 140.f });
    resultBox.setFillColor(sf::Color(0, 0, 0, 190));
    resultBox.setOutlineColor(sf::Color(255, 215, 0));
    resultBox.setOutlineThickness(3.f);
    resultBox.setPosition({ WINDOW_WIDTH / 2.f - 220.f, WINDOW_HEIGHT / 2.f - 80.f });

    // ========== BUTTONS ==========
    // HIT
    sf::RectangleShape hitShape({ 130.f, 52.f });
    hitShape.setFillColor(sf::Color(40, 130, 40));
    hitShape.setOutlineColor(sf::Color::White);
    hitShape.setOutlineThickness(2.f);
    hitShape.setPosition({ 360.f, 675.f });
    sf::Text hitLabel(font, "HIT", 24);
    hitLabel.setFillColor(sf::Color::White);
    hitLabel.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = hitLabel.getLocalBounds();
        hitLabel.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
        hitLabel.setPosition({ 360.f + 65.f, 675.f + 26.f });
    }

    // STAND
    sf::RectangleShape standShape({ 130.f, 52.f });
    standShape.setFillColor(sf::Color(160, 40, 40));
    standShape.setOutlineColor(sf::Color::White);
    standShape.setOutlineThickness(2.f);
    standShape.setPosition({ 510.f, 675.f });
    sf::Text standLabel(font, "STAND", 24);
    standLabel.setFillColor(sf::Color::White);
    standLabel.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = standLabel.getLocalBounds();
        standLabel.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
        standLabel.setPosition({ 510.f + 65.f, 675.f + 26.f });
    }

    // DEAL
    sf::RectangleShape dealShape({ 160.f, 52.f });
    dealShape.setFillColor(sf::Color(40, 80, 180));
    dealShape.setOutlineColor(sf::Color::White);
    dealShape.setOutlineThickness(2.f);
    dealShape.setPosition({ 432.f, 675.f });
    sf::Text dealLabel(font, "DEAL", 24);
    dealLabel.setFillColor(sf::Color::White);
    dealLabel.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = dealLabel.getLocalBounds();
        dealLabel.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
        dealLabel.setPosition({ 432.f + 80.f, 675.f + 26.f });
    }

    // ========== GAME VARIABLES ==========
    CardDeck deck;
    Player* player = new Player("Player");
    Dealer* dealer = new Dealer();

    int playerWins = 0;
    int dealerWins = 0;
    bool hideDealer = true;
    GameState state = GameState::WaitingToDeal;

    // Dealing sequence: 0=p1, 1=d1, 2=p2, 3=d2(hidden)
    int dealStep = 0;

    vector<sf::Sprite> playerSprites;
    vector<sf::Sprite> dealerSprites;

    // ========== HELPERS ==========
    auto rebuildSprites = [&]() {
        playerSprites.clear();
        dealerSprites.clear();

        const vector<int>& pH = player->getHand();
        const vector<int>& dH = dealer->getHand();

        float pStart = WINDOW_WIDTH / 2.f - (pH.size() * CARD_SPACING) / 2.f;
        float dStart = WINDOW_WIDTH / 2.f - (dH.size() * CARD_SPACING) / 2.f;

        for (int i = 0; i < (int)pH.size(); i++)
            playerSprites.push_back(makeCardSprite(getCardKey(pH[i], i), cardTextures,
                pStart + i * CARD_SPACING, 510.f));

        for (int i = 0; i < (int)dH.size(); i++) {
            // Dealer's second card (index 1) stays hidden until player stands
            string key = (hideDealer && i == 1) ? "back" : getCardKey(dH[i], i);
            dealerSprites.push_back(makeCardSprite(key, cardTextures,
                dStart + i * CARD_SPACING, 140.f));
        }
        };

    auto showResult = [&](const string& result, const string& msg, sf::Color color) {
        resultText.setString(result);
        resultText.setFillColor(color);
        messageText.setString(msg);
        centerText(resultText, WINDOW_WIDTH, WINDOW_HEIGHT / 2.f - 30.f);
        centerText(messageText, WINDOW_WIDTH, WINDOW_HEIGHT / 2.f + 20.f);
        centerText(dealPrompt, WINDOW_WIDTH, WINDOW_HEIGHT / 2.f + 55.f);
        state = GameState::ShowResult;
        };

    auto resetRound = [&]() {
        delete player;
        delete dealer;
        player = new Player("Player");
        dealer = new Dealer();
        deck.reset();
        hideDealer = true;
        dealStep = 0;
        resultText.setString("");
        messageText.setString("");
        playerSprites.clear();
        dealerSprites.clear();
        state = GameState::WaitingToDeal;
        };

    // ========== MAIN LOOP ==========
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (click->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mPos = { (float)click->position.x, (float)click->position.y };

                    // ===== DEAL button (start of round OR between rounds) =====
                    if ((state == GameState::WaitingToDeal || state == GameState::ShowResult)
                        && dealShape.getGlobalBounds().contains(mPos)) {

                        if (state == GameState::ShowResult) resetRound();

                        // Deal alternating: player, dealer, player, dealer(hidden)
                        // Step 0: player card 1
                        player->addCard(deck.dealCard().getValue());
                        rebuildSprites();
                        dealStep = 1;
                        state = GameState::Dealing;
                    }

                    // ===== DEAL button during Dealing phase (advance deal steps) =====
                    else if (state == GameState::Dealing
                        && dealShape.getGlobalBounds().contains(mPos)) {

                        if (dealStep == 1) {
                            // Dealer card 1
                            dealer->addCard(deck.dealCard().getValue());
                            rebuildSprites();
                            dealStep = 2;
                        }
                        else if (dealStep == 2) {
                            // Player card 2
                            player->addCard(deck.dealCard().getValue());
                            rebuildSprites();
                            dealStep = 3;
                        }
                        else if (dealStep == 3) {
                            // Dealer card 2 — face down
                            dealer->addCard(deck.dealCard().getValue());
                            hideDealer = true;
                            rebuildSprites();
                            dealStep = 4;
                            state = GameState::PlayerTurn;
                        }
                    }

                    // ===== HIT =====
                    else if (state == GameState::PlayerTurn
                        && hitShape.getGlobalBounds().contains(mPos)) {
                        player->addCard(deck.dealCard().getValue());
                        rebuildSprites();

                        if (player->getHandValue() > 21) {
                            hideDealer = false;
                            rebuildSprites();
                            dealerWins++;
                            showResult("BUST!", "You went over 21. Dealer wins!", sf::Color::Red);
                        }
                    }

                    // ===== STAND =====
                    else if (state == GameState::PlayerTurn
                        && standShape.getGlobalBounds().contains(mPos)) {
                        hideDealer = false;
                        rebuildSprites();
                        state = GameState::DealerTurn;
                    }
                }
            }
        }

        // ===== DEALER AUTO PLAY =====
        if (state == GameState::DealerTurn) {
            if (dealer->getHandValue() < 17) {
                dealer->addCard(deck.dealCard().getValue());
                rebuildSprites();
            }
            else {
                int pVal = player->getHandValue();
                int dVal = dealer->getHandValue();

                if (dVal > 21) { playerWins++; showResult("YOU WIN!", "Dealer busted!", sf::Color(50, 220, 50)); }
                else if (pVal > dVal) { playerWins++; showResult("YOU WIN!", "Your hand beats the dealer!", sf::Color(50, 220, 50)); }
                else if (pVal < dVal) { dealerWins++; showResult("DEALER WINS", "Better luck next time!", sf::Color::Red); }
                else { showResult("PUSH!", "It's a tie!", sf::Color::Yellow); }
            }
        }

        // Check blackjack after full deal
        if (state == GameState::PlayerTurn && player->getHandValue() == 21) {
            hideDealer = false;
            rebuildSprites();
            playerWins++;
            showResult("BLACKJACK!", "You hit 21!", sf::Color(255, 215, 0));
        }

        // ===== UPDATE UI =====
        scoreText.setString("Player: " + to_string(playerWins) +
            "     Dealer: " + to_string(dealerWins));
        centerText(scoreText, WINDOW_WIDTH, 68.f);

        playerValueText.setString(player->getHand().empty() ? "" :
            "Hand: " + to_string(player->getHandValue()));
        dealerValueText.setString(dealer->getHand().empty() ? "" :
            hideDealer ? "Hand: ?" :
            "Hand: " + to_string(dealer->getHandValue()));

        // Button hover
        sf::Vector2f mPosF = { (float)sf::Mouse::getPosition(window).x,
                               (float)sf::Mouse::getPosition(window).y };

        if (state == GameState::PlayerTurn) {
            hitShape.setFillColor(hitShape.getGlobalBounds().contains(mPosF)
                ? sf::Color(60, 160, 60) : sf::Color(40, 130, 40));
            standShape.setFillColor(standShape.getGlobalBounds().contains(mPosF)
                ? sf::Color(200, 60, 60) : sf::Color(160, 40, 40));
        }
        if (state == GameState::WaitingToDeal || state == GameState::Dealing ||
            state == GameState::ShowResult) {
            dealShape.setFillColor(dealShape.getGlobalBounds().contains(mPosF)
                ? sf::Color(60, 100, 220) : sf::Color(40, 80, 180));
        }

        // ===== DRAW =====
        window.clear();
        window.draw(table);
        window.draw(felt);
        window.draw(titleText);
        window.draw(scoreText);
        window.draw(dealerLabel);
        window.draw(dealerValueText);
        window.draw(playerLabel);
        window.draw(playerValueText);

        for (auto& s : dealerSprites) window.draw(s);
        for (auto& s : playerSprites) window.draw(s);

        // Show DEAL button when waiting, dealing, or showing result
        if (state == GameState::WaitingToDeal || state == GameState::Dealing ||
            state == GameState::ShowResult) {
            window.draw(dealShape);
            window.draw(dealLabel);
        }

        // Show HIT/STAND during player turn
        if (state == GameState::PlayerTurn) {
            window.draw(hitShape);
            window.draw(hitLabel);
            window.draw(standShape);
            window.draw(standLabel);
        }

        // Show result overlay
        if (state == GameState::ShowResult) {
            window.draw(resultBox);
            window.draw(resultText);
            window.draw(messageText);
            window.draw(dealPrompt);
        }

        window.display();
    }

    delete player;
    delete dealer;
    return 0;
}
#include "Board.h"
#include<sstream>
#include <iostream>
#include <iomanip>
#include <chrono> 

Board::Board(int _NOC)
{
    //-------background image
    if (!tempBg.loadFromFile("bg5.png"))
    {
        throw("Unable to load img");
    }
    bg.setTexture(tempBg);
    bg.scale(1, 1);
    bg.setPosition(0, 0);

    //--------Load Font
    ScoreFont.loadFromFile("ScoreFont.ttf");
    sf::Color gold(204, 191, 63);
    _Score.setFont(ScoreFont);
    _Score.setCharacterSize(50);
    _Score.setOutlineColor(sf::Color::Black);
    _Score.setOutlineThickness(5);
    _Score.setFillColor(gold);
    _Score.setPosition(50, 610);

    _Move.setFont(ScoreFont);
    _Move.setCharacterSize(50);
    _Move.setOutlineColor(sf::Color::Black);
    _Move.setOutlineThickness(5);
    _Move.setFillColor(gold);
    _Move.setPosition(250, 610);

    Timetxt.setFont(ScoreFont);
    Timetxt.setCharacterSize(50);
    Timetxt.setOutlineColor(sf::Color::Black);
    Timetxt.setOutlineThickness(5);
    Timetxt.setFillColor(gold);
    Timetxt.setPosition(500, 610);

    //-------Undo image
    if (!texUndo.loadFromFile("undo.png"))
    {
        throw("Unable to load img");
    }
    Undo.setTexture(texUndo);
    Undo.scale(0.2, 0.2);
    Undo.setPosition(1150, 600);

    //-------Redo image
    if (!texRedo.loadFromFile("redo.png"))
    {
        throw("Unable to load img");
    }
    Redo.setTexture(texRedo);
    Redo.scale(0.2, 0.2);
    Redo.setPosition(1250, 600);

    //---------initialize variables
    this->NOC = _NOC;
    this->pileNo = -1;
    this->DcPileNo = -1;
    this->cardNo = -1;
    this->DeckCardSelected = false;
    this->score = 0;
    this->moves = 0;
    this->sri = -1;
    this->sci = -1;
    this->dri = -1;
    this->dci = -1;
    this->isAutoMove = false;
   
    //-------Create and shuffle deck
    deck = new Deck();
    deck->shuffle();

    //------Create Piles
    Ps = new Pile * [7];
    int ri = 200, ci = 160;

    for (int i = 0; i < 7; i++)
    {
        Ps[i] = new Pile(i + 1, deck, ri, ci + (155 * i));
    }
    /*int ri = 220, ci = 0;

    for (int i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            ci = 30;
        }
        else if (i == 1)
        {
            ci = 210;
        }
        else
        {
            ci += 200;
        }
        Ps[i] = new Pile(i + 1, deck, ri, ci);
    }*/

    //------create Queue Deck
    QD = new QueueDeck(NOC, deck);

    //---------creating free cells
    Cs = new FreeCell * [4];
    for (int suit = HEARTS,i=0; suit <= SPADES; suit++,i++)
    {
        Cs[i] = new FreeCell(Suit(suit), 20, 640 + (150 * i));
    }
}
Board::Board(const Board& _B)
{
    this->NOC = _B.NOC;
    this->score = _B.score;
    this->moves = _B.moves;
    this->ScoreFont = _B.ScoreFont;
    this->_Score = _B._Score;
    this->_Move = _B._Move;
    this->Timetxt = _B.Timetxt;
    this->time = _B.time;
    this->sri = _B.sri;
    this->sci = _B.sci;
    this->dri = _B.dri;
    this->dci = _B.dci;
    deck = new Deck(*_B.deck);
    bg = sf::Sprite(_B.bg);
    Undo = sf::Sprite(_B.Undo);
    Redo = sf::Sprite(_B.Redo);
    
    Ps = new Pile * [7];
    for (int i = 0; i < 7; i++)
    {
        Ps[i] = new Pile(*_B.Ps[i]);
    }
    QD = new QueueDeck(*_B.QD);
    this->pileNo = _B.pileNo;
    this->DcPileNo = _B.DcPileNo;
    this->cardNo = _B.cardNo;
    this->DeckCardSelected = _B.DeckCardSelected;
    this->Cs = new FreeCell * [4];
    for (int i = 0; i < 4; i++)
    {
        this->Cs[i] = new FreeCell(*_B.Cs[i]);
    }
}

void Board::drawPiles(sf::RenderWindow& window)
{
    for (int i = 0; i < 7; i++)
    {
        Ps[i]->draw(window, Ps, bg,this);
    }
}

void Board::drawDeck(sf::RenderWindow& window)
{
    QD->draw(window);
}

void Board::drawFreeCells(sf::RenderWindow& window)
{
    for (int i = 0; i < 4; i++)
    {
        Cs[i]->draw(window);
    }
}

void Board::drawSelectedCards(sf::RenderWindow& window)
{
    for (int i = 0; i < SelectedCards.size(); i++)
    {
        SelectedCards[i]->Draw(window);
    }
}

void Board::draw(sf::RenderWindow& window)
{
    window.draw(bg);
    drawUndoRedo(window);
    drawScore(window);
    drawMoves(window);
    displayTime(window);
    drawFreeCells(window);
    QD->draw(window);
    drawPiles(window);
    drawSelectedCards(window);
}

void Board::isValidSc(int r, int c, bool& isSelected)
{
    bool isClickedPile = false;
    bool isClickedFreeCell = false;
    bool isDeckCard = false;
    if(!QD->isDClicked(r,c))
    {
        if (QD->isCardSelected(r, c))
        {
            isSelected = true;
            DeckCardSelected = true;
            SelectedCards.push_back(QD->removeCard());
            sri = r, sci = c;
            pileNo = 12;
            return;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if(Cs[i]->isClicked(r,c) && Cs[i]->isEmpty()==false)
        {
            isClickedFreeCell = true;
            isSelected = true;
            pileNo = 7 + i;
            SelectedCards = Cs[i]->split();
            sri = r, sci = c;
            break;
        }
    }
    if(!isClickedFreeCell)
    {
        for (int i = 0; i < 7; i++)
        {
            if (Ps[i]->isCardSelected(r, c))
            {
                pileNo = i;
                isClickedPile = true;
                sri = r, sci = c;
                break;
            }
        }
    }
    if (isClickedPile)
    {
        for (int i = Ps[pileNo]->getSize()-1; i >= 0; i--)
        {
            if (Ps[pileNo]->getCardAt(i)->isClicked(r, c) && Ps[pileNo]->getCardAt(i)->isFaceUp() == true)
            {
                Ps[pileNo]->selectTopCard(i);
                cardNo = i;
                isSelected = true;
                SelectedCards = Ps[pileNo]->split(i);
                sri = r, sci = c;
                break;
            }
        }
    }
}

void Board::move(int r, int c)
{
    for (int i = 0; i < SelectedCards.size(); i++)
    {
        SelectedCards[i]->setPosition(r - 80 + (40 * i), c - 50);
    }
}

bool Board::isValidDes(int r, int c)
{
    bool isClickedPile = false;
    bool isClickedFreeCell = false;
    if (r == sri && c == sci)
    {
        isAutoMove = true;
        return true;
    }
    for (int i = 0; i < 4; i++)
    {
        if (Cs[i]->isClicked(r, c))
        {
            isClickedFreeCell = true;
            DcPileNo = 7+i;
            break;
        }
    }
    if (isClickedFreeCell)
    {
        if(SelectedCards.size()==1)
        {
            if (Cs[DcPileNo - 7]->canAppend(SelectedCards.back()))
                return true;
        }
    }
    if (!isClickedFreeCell)
    {
        for (int i = 0; i < 7; i++)
        {
            if (Ps[i]->isCardSelected(r, c) && i != pileNo)
            {
                DcPileNo = i;
                isClickedPile = true;
                break;
            }
        }

        if (isClickedPile)
        {
            if (Ps[DcPileNo]->canAppend(SelectedCards))
                return true;
        }
    }
    return false;
}

void Board::emptyStack()
{
    while (!SelectedCards.empty())
    {
        SelectedCards.pop_back();
    }
    DeckCardSelected = false;
    DcPileNo = -1;
    pileNo = -1;
    cardNo = -1;
    sri = -1;
    sci = -1;
    dri = -1;
    dci = -1;
}

void Board::MovetoDc(sf::RenderWindow& window)
{
    bool isMoved = false;
    bool pileApn = false;
    if (isAutoMove)
    {
        if (SelectedCards.size() == 1)
        {
            for (int i = 0; i < 4; i++)
            {
                if (i != pileNo - 7)
                {
                    if (Cs[i]->canAppend(SelectedCards.back()))
                    {
                        Cs[i]->append(SelectedCards.back());
                        DcPileNo = 7 + i;
                        CardWinAnimation(window);
                        score += 15;
                        moves += 1;
                        isMoved = true;
                        break;
                    }
                }
            }
        }
        
        if (!isMoved)
        {
            for (int i = 0; i < 7; i++)
            {
                if (i != pileNo)
                {
                    if (Ps[i]->canAppend(SelectedCards))
                    {
                        Ps[i]->append(SelectedCards);
                        score += 5;
                        moves += 1;
                        isMoved = true;
                        break;
                    }
                }
            }
            if (!isMoved)
                MovetoSc();
        }

    }
    else
    {
        if (DcPileNo > 6)
        {
            Cs[DcPileNo - 7]->append(SelectedCards.back());
            CardWinAnimation(window);
            score += 15;
            moves += 1;
            isMoved = true;
        }
        else
        {
            Ps[DcPileNo]->append(SelectedCards);
            pileApn = true;
            moves += 1;
            isMoved = true;
        }
    }
    if(isMoved)
    {
        if (pileNo < 7 && pileNo >= 0)
        {
            if (Ps[pileNo]->getSize() != 0 && Ps[pileNo]->getRevealCards() == 0)
            {
                if (pileApn)
                    moves += 5;
                Ps[pileNo]->revealNext();
            }
        }
        if (QD->IsCard())
        {
            QD->showNextTop(score);
        }
    }
    emptyStack();
}

void Board::MovetoSc()
{
    if (DeckCardSelected)
    {
        QD->append(SelectedCards.back());
    }
    else if (pileNo > 6)
    {
        Cs[pileNo - 7]->append(SelectedCards.back());
    }
    else
    {
        Ps[pileNo]->append(SelectedCards);
    }
    emptyStack();
}
bool Board::isDeckClicked(int r, int c)
{
    if (QD->isDClicked(r, c))
    {
        moves += 1;
        return true;
    }
    return false;
}
void Board::RevealDeck()
{
    QD->showNext(score);
}

void Board::CardWinAnimation(sf::RenderWindow& window)
{
    int j = 0;
    sf::Texture texture;
    texture.loadFromFile("stars.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(Cs[DcPileNo - 7]->getPostion().y-35, Cs[DcPileNo - 7]->getPostion().x-50);
    sprite.setScale(0.55, 0.55);

    sf::Color spriteColor = sprite.getColor();
    sf::Clock clock;
    float elapsed = 0.0f;

    for (int i = 0; i < 300; i++)
    {
        window.clear();

        // Calculate elapsed time in seconds.
        elapsed = clock.getElapsedTime().asSeconds();

        // Gradually decrease opacity over 5 seconds.
        if (elapsed <= 2.0f)
        {
            int newAlpha = static_cast<int>(255 - (255 * (elapsed / 1.0f)));
            sprite.setColor(sf::Color(spriteColor.r, spriteColor.g, spriteColor.b, newAlpha));
            sprite.setScale(sprite.getScale().x + 0.0001, sprite.getScale().y + 0.0001);
            sprite.setPosition(sprite.getPosition().x - 0.014, sprite.getPosition().y - 0.014);
        }
        j++;
        if (j == 350)
            time++;
        window.clear();
        window.draw(bg);
        drawUndoRedo(window);
        drawScore(window);
        drawMoves(window);
        displayTime(window);
        window.draw(sprite);
        drawFreeCells(window);
        QD->draw(window);
        drawPiles(window);
        drawSelectedCards(window);
        window.display();
    }
}

void Board::drawUndoRedo(sf::RenderWindow& window)
{
    window.draw(Undo);
    window.draw(Redo);
}

void Board::drawScore(sf::RenderWindow& window)
{
    _Score.setString("Score   " + std::to_string(score));
    window.draw(_Score);
}

void Board::drawMoves(sf::RenderWindow& window)
{
    _Move.setString("Moves   " + std::to_string(moves));
    window.draw(_Move);
}

bool Board::isUndoClicked(int r, int c)
{
    if (Undo.getGlobalBounds().contains(r, c))
        return true;
    return false;
}

bool Board::isRedoClicked(int r, int c)
{
    if (Redo.getGlobalBounds().contains(r, c))
        return true;
    return false;
}

bool Board::isWin()
{
    for (int i = 0; i < 4; i++)
    {
        if (!Cs[i]->isComplete())
            return false;
    }
    return true;
}

void Board::displayTime(sf::RenderWindow& window)
{
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;
    int seconds = time % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;

    Timetxt.setString(ss.str());
    window.draw(Timetxt);
}

void Board::setTime(int t)
{
    time = t;
}
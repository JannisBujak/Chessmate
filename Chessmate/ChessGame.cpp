//
// Created by jannis on 29.08.23.
//

#include "ChessGame.h"


ChessGame::ChessGame(QObject* parent)
        : QObject(parent)
        , m_bGameOver(false)
{
    init();
}

ChessGame::ChessGame(const ChessGame& other)
        : m_playingColor(other.m_playingColor)
        , m_bGameOver(false)
{
    for (auto w : other.white)
        white.push_back(std::shared_ptr< Pieces::Piece>(w->clone()));

    for (auto b : other.black)
        black.push_back(std::shared_ptr<Pieces::Piece>(b->clone()));
}

Pieces::Color ChessGame::playingColor()
{
    return m_playingColor;
}

void ChessGame::togglePlayingColor()
{
    using namespace Pieces;
    setPlayingColor(oppositeColor(playingColor()));
}

void ChessGame::setPlayingColor(Pieces::Color a_playingColor)
{
    m_playingColor = a_playingColor;
    emit playingColorChanged(m_playingColor);
}

void ChessGame::fillBackrow(Pieces::Color a_color, int a_col)
{
    addPiece	<Pieces::Rook>(a_color, 0, a_col);
    addPiece	<Pieces::Knight>(a_color, 1, a_col);
    addPiece	<Pieces::Bishop>(a_color, 2, a_col);
    addPiece	<Pieces::Queen>(a_color, 3, a_col);
    addPiece	<Pieces::King>(a_color, 4, a_col);
    addPiece	<Pieces::Bishop>(a_color, 5, a_col);
    addPiece	<Pieces::Knight>(a_color, 6, a_col);
    addPiece	<Pieces::Rook>(a_color, 7, a_col);
}

void ChessGame::removeAllPieces()
{
    if (!white.empty())
        white.clear();
    if (!black.empty())
        black.clear();
}

bool ChessGame::isMoveable(std::shared_ptr<Pieces::Piece> a_piece)
{
    auto pc = a_piece->getColor();
    return playingColor() == pc;
}

std::shared_ptr<Pieces::Piece> ChessGame::pieceAt(int x, int y)
{
    for (std::shared_ptr<Pieces::Piece> w : white)
    {
        if (w->same_pos(x, y))
        {
            return w;
        }
    }

    for (std::shared_ptr<Pieces::Piece> b : black)
    {
        if (b->same_pos(x, y))
        {
            return b;
        }
    }
    return std::shared_ptr<Pieces::Piece>();
}

const std::shared_ptr<Pieces::Piece> ChessGame::pieceAt(int x, int y) const
{
    for (std::shared_ptr<Pieces::Piece> w : white)
    {
        if (w->same_pos(x, y))
        {
            return w;
        }
    }

    for (std::shared_ptr<Pieces::Piece> b : black)
    {
        if (b->same_pos(x, y))
        {
            return b;
        }
    }
    return std::shared_ptr<Pieces::Piece>();
}

Pieces::King* ChessGame::getKingFromList(std::vector < std::shared_ptr<Pieces::Piece>> a_ColoredPieces)
{
    Pieces::King* king;
    for (auto e : a_ColoredPieces)
        if (king = dynamic_cast<Pieces::King*>(e.get()))
            return king;

    return nullptr;
}

Pieces::King* ChessGame::getKingFromList(Pieces::Color a_color)
{
    using namespace Pieces;
    return getKingFromList((a_color == Color::Black) ? black : white);
}

std::vector<std::shared_ptr<Pieces::Piece>>& ChessGame::getListOfColor(Pieces::Color a_color)
{
    using namespace Pieces;
    return (a_color == Color::Black) ? black : white;
}

const std::vector<std::shared_ptr<Pieces::Piece>>& ChessGame::getListOfColor(Pieces::Color a_color) const
{
    using namespace Pieces;
    return (a_color == Color::Black) ? black : white;
}

std::vector<std::shared_ptr<Pieces::Piece>> ChessGame::getListOfPieces()
{
    std::vector<std::shared_ptr<Pieces::Piece>> all_pieces = black;
    all_pieces.insert(all_pieces.end(), white.begin(), white.end());

    return all_pieces;
}

void ChessGame::checkForWin()
{
    using namespace Pieces;
    // First get the two kings
    Pieces::King* bk = getKingFromList(black)
        , * wk = getKingFromList(white);
    Q_ASSERT(bk || wk);
    if (!bk)
    {
        qDebug() << "No black King";
        endGame(Color::White);
    }
    else if (!wk)
    {
        qDebug() << "No white King";
        endGame(Color::Black);
    }
    else
    {
        // TODO: Check or stalemate

        Pieces::King* checked_king = getKingFromList(m_playingColor);
        std::vector<std::shared_ptr<Pieces::Piece>> opposing_pieces = getListOfColor(oppositeColor(m_playingColor));
        // Check if players king is under Attack
        if(checked_king->isAttacked(*this)) {
            qDebug() << ((m_playingColor == Color::White) ? QString("White") : QString("Black")) << "King checked";
        }
    }
}

void ChessGame::endGame(Pieces::Color a_WinningColor)
{
    m_bGameOver = true;
    emit  playerWon(a_WinningColor);
}

bool ChessGame::gameOver() const {
    return m_bGameOver;
}

void ChessGame::confirmMove()
{
    // Toggles playing color
    togglePlayingColor();

    // Check if player is under attack and can defend
    checkForWin();
}

void ChessGame::cleanPiece(std::shared_ptr<Pieces::Piece> a_piece)
{
    using namespace Pieces;
    if (a_piece->getColor() == Color::White)
    {
        deleteElementFromList(a_piece, white);
    }
    else
    {
        deleteElementFromList(a_piece, black);
    }
}

void ChessGame::init()
{
    using namespace Pieces;
    removeAllPieces();
    setPlayingColor(Color::White);
    m_bGameOver = false;

    for (int x = 0; x < BOARD_WIDTH; ++x)
    {
        addPiece <Pieces::Pawn> (Color::White, x, 6);
        addPiece <Pieces::Pawn> (Color::Black, x, 1);
    }

    fillBackrow(Color::Black, 0);
    fillBackrow(Color::White, 7);
}



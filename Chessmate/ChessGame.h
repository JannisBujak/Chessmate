//
// Created by jannis on 29.08.23.
//
#include <QObject>
#include "Pieces.h"

#pragma  once

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8


class ChessGame : public QObject
{
    Q_OBJECT
private:
    Pieces::Color m_playingColor;
    std::vector<std::shared_ptr<Pieces::Piece>> white, black;

public:
    ChessGame(QObject* parent = nullptr);
    ChessGame(const ChessGame&);

    template <typename T>
    void addPiece(Pieces::Color a_color, int a_col, int a_row);

    template <typename T>
    static void deleteElementFromList(std::shared_ptr<T> element, std::vector<std::shared_ptr<T>>& list);

    Pieces::Color playingColor();
    void togglePlayingColor();
    void setPlayingColor(Pieces::Color a_playingColor);

    void fillBackrow(Pieces::Color a_color, int a_col);
    void removeAllPieces();
    std::shared_ptr<Pieces::Piece> pieceAt(int x, int y) const;

    bool isMoveable(std::shared_ptr<Pieces::Piece> a_piece);

    static Pieces::King* getKingFromList(std::vector < std::shared_ptr<Pieces::Piece>> a_ColoredPieces);
    Pieces::King* getKingFromList(Pieces::Color a_color);

    const std::vector<std::shared_ptr<Pieces::Piece>> getListOfColor(Pieces::Color a_color) const;
    std::vector<std::shared_ptr<Pieces::Piece>> getListOfColor(Pieces::Color a_color);
    std::vector<std::shared_ptr<Pieces::Piece>> getListOfPieces();

    void checkForWin();
    void confirmMove();

    void cleanPiece(std::shared_ptr<Pieces::Piece> a_piece);

public slots:
    void init();
signals:
    void playingColorChanged(Pieces::Color);
    void playerWon(Pieces::Color);

};


template<typename T>
inline void ChessGame::addPiece(Pieces::Color a_color, int a_col, int a_row)
{
    std::shared_ptr<T> piece = std::make_shared<T>(a_col, a_row, a_color);
    ((a_color == Pieces::Color::White) ? white : black).push_back(piece);
}

template<typename T>
inline void ChessGame::deleteElementFromList(std::shared_ptr<T> element, std::vector<std::shared_ptr<T>>& list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        if (it->get() == element.get())
        {
            list.erase(it);
            break;
        }
    }
}



#pragma once

#include <memory>

class IBoard
{
public:
	virtual ~IBoard() = default;
};

class ChessBoard : public IBoard
{
};

class ScrabbleBoard : public IBoard
{
};

class IGameFactory
{
public:
    virtual ~IGameFactory() = default;
    virtual std::shared_ptr<IBoard> createBoard() = 0;
};

class ChessFactory : public IGameFactory
{
public:
    std::shared_ptr<IBoard> createBoard() override final
    {
        return std::make_shared<ChessBoard>();
    }
};

class ScrabbleFactory : public IGameFactory
{
public:
    std::shared_ptr<IBoard> createBoard() override final
    {
        return std::make_shared<ScrabbleBoard>();
    }
};

class Game
{
public:
    enum class EGameType
    {
        EGame_Chess,
        EGame_Scrabble,
    };

    void initializeGame(const EGameType type)
    {
        switch (type)
        {
            case EGameType::EGame_Chess:        m_iGameFactory = std::make_shared<ChessFactory>();      break;
            case EGameType::EGame_Scrabble:     m_iGameFactory = std::make_shared<ScrabbleFactory>();   break;
        }

        auto board = m_iGameFactory->createBoard();
        board;
    }

private:
    std::shared_ptr<IGameFactory> m_iGameFactory{nullptr};
};
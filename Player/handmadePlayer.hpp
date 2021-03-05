#ifndef CHOTOTSUPLAYER2
#define CHOTOTSUPLAYER2
#include <string>
#include <random>
#include "random.hpp"
#include "player.hpp"

class handmadePlayer : public Player
{
    cpprefjp::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> choiceRandom;

public:
    handmadePlayer() : mt(rd())
    {
    }

    virtual std::string decideRed()
    {
        return std::string("EFGH");
    }

    uint64_t get_rand_range(uint64_t min_val, uint64_t max_val)
    {
        // 乱数生成器
        static std::mt19937_64 mt64(0);

        // [min_val, max_val] の一様分布整数 (int) の分布生成器
        std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

        // 乱数を生成
        return get_rand_uni_int(mt64);
    }

    //現在何手目かの変数
    int present = 0;

    virtual std::string decideHand(std::string res)
    {
        present++;
        game.setState(res);
        const std::array<Unit, 16> &units = game.allUnit();
        std::vector<Hand> legalMoves = game.getLegalMove1st();
        std::uniform_int_distribution<int> serector1(0, legalMoves.size() - 1);

        // ゴール
        for (const Unit &u : units)
        {
            if (u.color() == UnitColor::Blue)
            {
                if (u.x() == 0 && u.y() == 0)
                {
                    Hand action = Hand({u, Direction::West});
                    for (int i = 0; i < legalMoves.size(); i++)
                        if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                            return action;
                }
                if (u.x() == 5 && u.y() == 0)
                {
                    Hand action = Hand({u, Direction::East});
                    for (int i = 0; i < legalMoves.size(); i++)
                        if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                            return action;
                }
            }
        }

        //取得した赤コマと青コマの数
        int takeRed = 0;
        int takeBlue = 0;
        for (int u = 8; u < 16; ++u)
        {
            const Unit &unit = units[u];
            if (unit.x() == 9 && unit.y() == 9)
            {
                if (unit.color() == UnitColor::Red)
                    takeRed++;
                if (unit.color() == UnitColor::Blue)
                    takeBlue++;
            }
        }

        //初期のコマの動き方
        if (present == 1)
        {
            Hand action = Hand({units[4], Direction::West});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }
        else if (present == 2)
        {
            Hand action = Hand({units[7], Direction::East});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }
        else if (present == 3)
        {
            Hand action = Hand({units[5], Direction::West});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }
        else if (present == 4)
        {
            Hand action = Hand({units[6], Direction::East});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }

        //相手の赤コマが近づいた場合
        for (int u = 8; u < 16; ++u)
        {
            //取った赤コマが既に3の場合
            if (takeRed == 3 && takeBlue < 3)
                break;
            const Unit &unit = units[u];
            if (unit.x() == units[4].x() + 1 && unit.y() == units[4].y() && units[4].y() > 3 && units[4].y() < 6)
            {
                Hand action = Hand({units[4], Direction::East});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[4].x() - 1 && unit.y() == units[4].y() && units[4].y() > 3 && units[4].y() < 6)
            {
                Hand action = Hand({units[4], Direction::West});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[4].x() && unit.y() == units[4].y() + 1 && units[4].y() > 3 && units[4].y() < 6)
            {
                Hand action = Hand({units[4], Direction::South});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[4].x() && unit.y() == units[4].y() - 1 && units[4].y() > 3 && units[4].y() < 6)
            {
                Hand action = Hand({units[4], Direction::North});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }

            if (unit.x() == units[7].x() + 1 && unit.y() == units[7].y() && units[7].y() > 3 && units[7].y() < 6)
            {
                Hand action = Hand({units[7], Direction::East});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[7].x() - 1 && unit.y() == units[7].y() && units[7].y() > 3 && units[7].y() < 6)
            {
                Hand action = Hand({units[7], Direction::West});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[7].x() && unit.y() == units[7].y() + 1 && units[7].y() > 3 && units[7].y() < 6)
            {
                Hand action = Hand({units[7], Direction::South});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[7].x() && unit.y() == units[7].y() - 1 && units[7].y() > 3 && units[7].y() < 6)
            {
                Hand action = Hand({units[7], Direction::North});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }

            // if(units[0].y()>2&&units[0].y()<6){
            if (unit.x() == units[5].x() + 1 && unit.y() == units[5].y())
            {
                Hand action = Hand({units[5], Direction::East});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[5].x() - 1 && unit.y() == units[5].y())
            {
                Hand action = Hand({units[5], Direction::West});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[5].x() && unit.y() == units[5].y() + 1)
            {
                Hand action = Hand({units[5], Direction::South});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[5].x() && unit.y() == units[5].y() - 1)
            {
                Hand action = Hand({units[5], Direction::North});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            // }else Hand action = Hand({units[0],Direction::South});for (int i = 0; i < legalMoves.size(); i++)
            // if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
            // return action;

            // if(units[3].y()>2&&units[3].y()<6){
            if (unit.x() == units[6].x() + 1 && unit.y() == units[6].y())
            {
                Hand action = Hand({units[6], Direction::East});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[6].x() - 1 && unit.y() == units[6].y())
            {
                Hand action = Hand({units[6], Direction::West});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[6].x() && unit.y() == units[6].y() + 1)
            {
                Hand action = Hand({units[6], Direction::South});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[6].x() && unit.y() == units[6].y() - 1)
            {
                Hand action = Hand({units[6], Direction::North});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            // }else Hand action = Hand({units[3],Direction::South});
            // for (int i = 0; i < legalMoves.size(); i++)
            // if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
            // return action;

            // if(units[5].y()>2&&units[5].y()<6){
            if (unit.x() == units[5].x() + 1 && unit.y() == units[5].y())
            {
                Hand action = Hand({units[5], Direction::East});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[5].x() - 1 && unit.y() == units[5].y())
            {
                Hand action = Hand({units[5], Direction::West});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[5].x() && unit.y() == units[5].y() + 1)
            {
                Hand action = Hand({units[5], Direction::South});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[5].x() && unit.y() == units[5].y() - 1)
            {
                Hand action = Hand({units[5], Direction::North});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            // }else Hand action = Hand({units[5],Direction::South});

            // if(units[6].y()>2&&units[6].y()<6){
            if (unit.x() == units[6].x() + 1 && unit.y() == units[6].y())
            {
                Hand action = Hand({units[6], Direction::East});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[6].x() - 1 && unit.y() == units[6].y())
            {
                Hand action = Hand({units[6], Direction::West});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[6].x() && unit.y() == units[6].y() + 1)
            {
                Hand action = Hand({units[6], Direction::South});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
            else if (unit.x() == units[6].x() && unit.y() == units[6].y() - 1)
            {
                Hand action = Hand({units[6], Direction::North});
                for (int i = 0; i < legalMoves.size(); i++)
                    if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                        return action;
            }
        }

        int mostFrontPos = units[0].y();
        int mostFrontIndex = 0;
        for (int u = 1; u < 8; ++u)
        {
            const Unit &unit = units[u];
            if (unit.color() == UnitColor::Blue && unit.y() <= mostFrontPos && unit.y() > 0)
            {
                if (unit.y() < mostFrontPos || choiceRandom(mt))
                {
                    mostFrontIndex = u;
                    mostFrontPos = unit.y();
                }
            }
        }
        if (units[mostFrontIndex].x() == 0 || units[mostFrontIndex].x() == 5)
        {
            auto action = Hand({units[mostFrontIndex], Direction::North});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }
        else if (units[mostFrontIndex].y() == 4 || units[mostFrontIndex].y() == 5)
        {
            auto action = Hand({units[mostFrontIndex], Direction::North});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }
        else if ((units[mostFrontIndex].x() == 1 || units[mostFrontIndex].x() == 2) && units[mostFrontIndex].y() <= 3 && units[mostFrontIndex].y() >= 0)
        {
            auto action = Hand({units[mostFrontIndex], Direction::West});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }
        else if ((units[mostFrontIndex].x() == 3 || units[mostFrontIndex].x() == 4) && units[mostFrontIndex].y() <= 3 && units[mostFrontIndex].y() >= 0)
        {
            auto action = Hand({units[mostFrontIndex], Direction::East});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action.unit.id() == legalMoves[i].unit.id() && action.direct == legalMoves[i].direct)
                    return action;
        }

        //上記のプログラムの中で合法手がなかった場合
        int number = get_rand_range(0, legalMoves.size());
        return Hand({units[legalMoves[number].unit.id()], legalMoves[number].direct});
    }
};

#endif
#ifndef CHOTOTSUPLAYER2
#define CHOTOTSUPLAYER2
#include <string>
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
        return std::string("ADFG");
    }

    int present = 0;

    virtual std::string decideHand(std::string res)
    {
        present++;
        game.setState(res);
        const std::array<Unit, 16> &units = game.allUnit();
        auto legalMoves = candidateHand();

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
        // ゴール
        for (const Unit &u : units)
        {
            if (u.color() == UnitColor::Blue)
            {
                if (u.x() == 0 && u.y() == 0)
                {
                    return Hand({u, Direction::West});
                }
                if (u.x() == 5 && u.y() == 0)
                {
                    return Hand({u, Direction::East});
                }
            }
        }

        //初期のコマの動き方
        if (present == 1)
        {
            Hand action = Hand({units[4], Direction::West});
            return action;
        }
        else if (present == 2)
        {
            return Hand({units[7], Direction::East});
        }
        else if (present == 3)
        {
            return Hand({units[5], Direction::West});
        }
        else if (present == 4)
        {
            return Hand({units[6], Direction::East});
        }

        for (int u = 8; u < 16; ++u)
        {
            if (takeRed == 3)
                break;
            const Unit &unit = units[u];
            if (unit.x() == units[4].x() + 1 && unit.y() == units[4].y() && units[4].y() > 3 && units[4].y() < 6)
            {
                return Hand({units[4], Direction::East});
            }
            else if (unit.x() == units[4].x() - 1 && unit.y() == units[4].y() && units[4].y() > 3 && units[4].y() < 6)
            {
                return Hand({units[4], Direction::West});
            }
            else if (unit.x() == units[4].x() && unit.y() == units[4].y() + 1 && units[4].y() > 3 && units[4].y() < 6)
            {
                return Hand({units[4], Direction::South});
            }
            else if (unit.x() == units[4].x() && unit.y() == units[4].y() - 1 && units[4].y() > 3 && units[4].y() < 6)
            {
                return Hand({units[4], Direction::North});
            }

            if (unit.x() == units[7].x() + 1 && unit.y() == units[7].y() && units[7].y() > 3 && units[7].y() < 6)
            {
                return Hand({units[7], Direction::East});
            }
            else if (unit.x() == units[7].x() - 1 && unit.y() == units[7].y() && units[7].y() > 3 && units[7].y() < 6)
            {
                return Hand({units[7], Direction::West});
            }
            else if (unit.x() == units[7].x() && unit.y() == units[7].y() + 1 && units[7].y() > 3 && units[7].y() < 6)
            {
                return Hand({units[7], Direction::South});
            }
            else if (unit.x() == units[7].x() && unit.y() == units[7].y() - 1 && units[7].y() > 3 && units[7].y() < 6)
            {
                return Hand({units[7], Direction::North});
            }

            // if(units[0].y()>2&&units[0].y()<6){
            if (unit.x() == units[0].x() + 1 && unit.y() == units[0].y())
            {
                return Hand({units[0], Direction::East});
            }
            else if (unit.x() == units[0].x() - 1 && unit.y() == units[0].y())
            {
                return Hand({units[0], Direction::West});
            }
            else if (unit.x() == units[0].x() && unit.y() == units[0].y() + 1)
            {
                return Hand({units[0], Direction::South});
            }
            else if (unit.x() == units[0].x() && unit.y() == units[0].y() - 1)
            {
                return Hand({units[0], Direction::North});
            }
            // }else return Hand({units[0],Direction::South});

            // if(units[3].y()>2&&units[3].y()<6){
            if (unit.x() == units[3].x() + 1 && unit.y() == units[3].y())
            {
                return Hand({units[3], Direction::East});
            }
            else if (unit.x() == units[3].x() - 1 && unit.y() == units[3].y())
            {
                return Hand({units[3], Direction::West});
            }
            else if (unit.x() == units[3].x() && unit.y() == units[3].y() + 1)
            {
                return Hand({units[3], Direction::South});
            }
            else if (unit.x() == units[3].x() && unit.y() == units[3].y() - 1)
            {
                return Hand({units[3], Direction::North});
            }
            // }else return Hand({units[3],Direction::South});

            // if(units[5].y()>2&&units[5].y()<6){
            if (unit.x() == units[5].x() + 1 && unit.y() == units[5].y())
            {
                return Hand({units[5], Direction::East});
            }
            else if (unit.x() == units[5].x() - 1 && unit.y() == units[5].y())
            {
                return Hand({units[5], Direction::West});
            }
            else if (unit.x() == units[5].x() && unit.y() == units[5].y() + 1)
            {
                return Hand({units[5], Direction::South});
            }
            else if (unit.x() == units[5].x() && unit.y() == units[5].y() - 1)
            {
                return Hand({units[5], Direction::North});
            }
            // }else return Hand({units[5],Direction::South});

            // if(units[6].y()>2&&units[6].y()<6){
            if (unit.x() == units[6].x() + 1 && unit.y() == units[6].y())
            {
                return Hand({units[6], Direction::East});
            }
            else if (unit.x() == units[6].x() - 1 && unit.y() == units[6].y())
            {
                return Hand({units[6], Direction::West});
            }
            else if (unit.x() == units[6].x() && unit.y() == units[6].y() + 1)
            {
                return Hand({units[6], Direction::South});
            }
            else if (unit.x() == units[6].x() && unit.y() == units[6].y() - 1)
            {
                return Hand({units[6], Direction::North});
            }
            // }else return Hand({units[6],Direction::South});

            // if(unit.color() == UnitColor::unknown && units[4].x()==0 && units[4].y()==5){
            //     if(unit.x() == 0 && unit.y() == 4){
            //         return Hand({units[4],Direction::North});
            //     }else if(unit.x() == 1 && unit.y() == 5){
            //         return Hand({units[4],Direction::East});
            //     }
            // }
            // if(unit.color() == UnitColor::unknown && units[0].x()==1 && units[0].y()==4){
            //     if(unit.x() == 0 && unit.y() == 4){
            //         return Hand({units[0],Direction::West});
            //     }else if(unit.x() == 1 && unit.y() == 3){
            //         return Hand({units[0],Direction::North});
            //     }else if(unit.x() == 2 && unit.y() == 4){
            //         return Hand({units[0],Direction::East});
            //     }else if(unit.x() == 1 && unit.y() == 5){
            //         return Hand({units[0],Direction::South});
            //     }
            // }
            // if(unit.color() == UnitColor::unknown && units[5].x()==1 && units[5].y()==5){
            //     if(unit.x() == 0 && unit.y() == 5){
            //         return Hand({units[5],Direction::West});
            //     }else if(unit.x() == 1 && unit.y() == 4){
            //         return Hand({units[5],Direction::North});
            //     }else if(unit.x() == 2 && unit.y() == 5){
            //         return Hand({units[5],Direction::East});
            //     }
            // }
            // if(unit.color() == UnitColor::unknown && units[7].x()==5 && units[7].y()==5){
            //     if(unit.x() == 5 && unit.y() == 4){
            //         return Hand({units[7],Direction::North});
            //     }else if(unit.x() == 4 && unit.y() == 5){
            //         return Hand({units[7],Direction::East});
            //     }
            // }
            // if(unit.color() == UnitColor::unknown && units[3].x()==4 && units[3].y()==4){
            //     if(unit.x() == 3 && unit.y() == 4){
            //         return Hand({units[3],Direction::West});
            //     }else if(unit.x() == 4 && unit.y() == 3){
            //         return Hand({units[3],Direction::North});
            //     }else if(unit.x() == 5 && unit.y() == 4){
            //         return Hand({units[3],Direction::East});
            //     }else if(unit.x() == 4 && unit.y() == 5){
            //         return Hand({units[3],Direction::South});
            //     }
            // }
            // if(unit.color() == UnitColor::unknown && units[6].x()==4 && units[6].y()==5){
            //     if(unit.x() == 3 && unit.y() == 5){
            //         return Hand({units[6],Direction::West});
            //     }else if(unit.x() == 4 && unit.y() == 4){
            //         return Hand({units[6],Direction::North});
            //     }else if(unit.x() == 5 && unit.y() == 5){
            //         return Hand({units[6],Direction::East});
            //     }
            // }
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
            Hand action = Hand({units[mostFrontIndex], Direction::North});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action == legalMoves[i])
                    return action;
        }
        else if (units[mostFrontIndex].y() == 4 || units[mostFrontIndex].y() == 5)
        {
            Hand action = Hand({units[mostFrontIndex], Direction::North});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action == legalMoves[i])
                    return action;
        }
        else if ((units[mostFrontIndex].x() == 1 || units[mostFrontIndex].x() == 2) && units[mostFrontIndex].y() <= 3 && units[mostFrontIndex].y() >= 0)
        {
            Hand action = Hand({units[mostFrontIndex], Direction::West});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action == legalMoves[i])
                    return action;
        }
        else if ((units[mostFrontIndex].x() == 3 || units[mostFrontIndex].x() == 4) && units[mostFrontIndex].y() <= 3 && units[mostFrontIndex].y() >= 0)
        {
            Hand action = Hand({units[mostFrontIndex], Direction::East});
            for (int i = 0; i < legalMoves.size(); i++)
                if (action == legalMoves[i])
                    return action;
        }
    }
};

#endif
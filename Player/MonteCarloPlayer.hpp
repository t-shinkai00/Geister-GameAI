#include "player.hpp"
#include "random.hpp"
#include "simulator.hpp"
#include <vector>
#include <iostream>

#ifndef PLAYOUT_COUNT
#define PLAYOUT_COUNT 100
#endif


class MonteCarloPlayer: public Player{
    uint32_t playoutCount = PLAYOUT_COUNT;
    cpprefjp::random_device rd;
    std::mt19937 mt;
public:
    MonteCarloPlayer(): mt(rd()){
    }

    virtual std::string decideRed(){
        std::uniform_int_distribution<int> serector(0, pattern.size() - 1);
        return pattern[serector(mt)];
    }

    virtual std::string decideHand(std::string res){
        game = Geister(res);
        // 合法手の列挙と着手の初期化
        std::vector<Hand> legalMoves = game.getLegalMove1st();
        Hand action = legalMoves[0];
        // 勝率記録用配列
        std::vector<double> rewards(legalMoves.size(), 0.0);

        // 合法手の数だけ子局面を生成する
        std::vector<Simulator> children;
        for(int i=0;i<legalMoves.size();i++){
            Geister next(game);
            next.move(legalMoves[i]);
            Simulator sim(next);
            children.push_back(sim);
        }
        // 規定回数のプレイアウトを実行
        for(int i=0;i<legalMoves.size();i++){
            rewards[i]=children[i].run(100);
        }

        // 報酬が最大の手を探す
        std::vector<double>::iterator result=std::max_element(rewards.begin(),rewards.end());
        std::size_t dist=std::distance(rewards.begin(),result);

        action=legalMoves[dist];

        return action;
    }
};
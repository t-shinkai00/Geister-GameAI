#include "Geister.hpp"
#include "unit.hpp"
#include "Simulator.hpp"
#include <array>
#include <algorithm>
#include <map>

cpprefjp::random_device Simulator::rd;
std::mt19937 Simulator::mt(rd());

Simulator::Simulator(): geister()
{
    depth = 0;
    setColorRandom();
    geister.countTaken();
}

Simulator::Simulator(const Geister& g): geister(g)
{
    depth = 0;
    setColorRandom();
    geister.countTaken();
}

Simulator::Simulator(const Geister& g, std::string ptn): geister(g), depth(0)
{
    for(int u = 8; u < 16; ++u){
        if(ptn.find(std::toupper(geister.allUnit()[u].name)) != std::string::npos)
            geister.allUnit()[u].color = UnitColor::red;
        else
            geister.allUnit()[u].color = UnitColor::blue;
    }
    if(ptn.size() < 4){
        setColorRandom();
    }
    geister.countTaken();
}

void Simulator::init(const Geister& g){
    geister = g;
    depth = 0;
    setColorRandom();
    geister.countTaken();
}

void Simulator::init(const Geister& g, std::string ptn){
    geister = g;
    depth = 0;
    for(int u = 0; u < 8; ++u){
        if(ptn.find(std::toupper(geister.allUnit()[u+8].name)) != std::string::npos)
            geister.allUnit()[u+8].color = UnitColor::red;
        else
            geister.allUnit()[u+8].color = UnitColor::blue;
    }
    if(ptn.size() < 4){
        setColorRandom();
    }

    geister.countTaken();
}
    
// 未判明の相手駒色を適当に仮定
void Simulator::setColorRandom(){
    std::uniform_int_distribution<int> BorR(0,1);
    int assumeTakeBlue = 4;
    int assumeTakeRed = 4;
    for(int i = 8; i < 16; ++i){
        auto color = geister.allUnit()[i].color;
        if(color == UnitColor::blue)
            assumeTakeBlue -= 1;
        if(color == UnitColor::red)
            assumeTakeRed -= 1;
    }
    for(int i = 8; i < 16; ++i){
        if(geister.allUnit()[i].color == UnitColor::unknown){
            if(assumeTakeRed == 0){
                geister.allUnit()[i].color = UnitColor::blue;
                assumeTakeBlue -= 1;
            }
            else if(assumeTakeBlue == 0){
                geister.allUnit()[i].color = UnitColor::red;
                assumeTakeRed -= 1;
            }
            else{
                if(BorR(mt)){
                    geister.allUnit()[i].color = UnitColor::blue;
                    assumeTakeBlue -= 1;
                }
                else{
                    geister.allUnit()[i].color = UnitColor::red;
                    assumeTakeRed -= 1;
                }
            }
        }
    }
}
    
double Simulator::playout(){
    while(true){
        if(geister.checkResult() != 0)
            break;
        // 相手の手番
        auto lm = geister.getLegalMove2nd();
        std::uniform_int_distribution<int> selector1(0, lm.size() - 1);
        auto m = lm[selector1(mt)];
        geister.move(m);
        if(geister.checkResult() != 0)
            break;
        // 自分の手番
        lm = geister.getLegalMove1st();
        std::uniform_int_distribution<int> selector2(0, lm.size() - 1);
        m = lm[selector2(mt)];
        geister.move(m);
    }
    return evaluate();
}

double Simulator::run(){
    Geister root = geister;
    double result = playout();
    geister = root;
    return result;
}

double Simulator::run(int count){
    Geister root = geister;
    double result = 0.0;
    for(int i = 0; i < count; ++i){
        result += playout();
        geister = root;
    }
    return result;
}
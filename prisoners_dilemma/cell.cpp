#include "cell.h"

#include <stdlib.h> // random numbers
#include <time.h> // time()

Cell::Cell()
{
    // random integer in the range 0 to 100
    //thre_ = rand() % 101;
    // test
    thre_ = 0;

    score_ = 0;

    table_.resize(2);
    for(unsigned int i=0;i<table_.size();i++) table_[i].resize(2);

    // this cell first
    table_[0][0] = 3;
    table_[0][1] = 6;
    table_[1][0] = 0;
    table_[1][1] = 5;
}

int Cell::score() const
{
    return score_;
}

int Cell::thre() const
{
    return thre_;
}

void Cell::set_thre(const int thre)
{
    thre_ = thre;
}

void Cell::interact(Cell *c)
{
    score_ += table_[decide()][c->decide()];
}

bool Cell::decide()
{
    bool decision = 0;

    int rnd; // random integer in the range 0 to 99
    rnd = rand() % 100;

    if(rnd < thre_) decision = 1;

    return decision;
}

void Cell::evolve()
{
    int scores [] = {score_, north->score(), south->score(), east->score(), west->score()};
    int thres [] = {thre_, north->thre(), south->thre(), east->thre(), west->thre()};

    // if its score is too low, the cell dies and is replaced by a new one
    double mean_score = 0;
    for(int i=1;i<5;i++) mean_score += scores[i];
    mean_score /= 4;

    double lowest_score = 0.8*mean_score;
    if(score_ < lowest_score) respawn();

    // else hybridisation of the thresholds
    else
    {
        int max_score = 0;
        int max_thre = 0;        
        for(int i=0;i<5;i++) if(scores[i] > max_score) max_score = scores[i];
        int idx_max = 0;
        while(scores[idx_max] != max_score) idx_max++;
        max_thre = thres[idx_max];

        new_thre_ = (score_*thre_ + max_score*max_thre)/(score_ + max_score);
        new_score_ = 0;
    }
}

void Cell::update()
{
    thre_ = new_thre_;
    score_ = new_score_;
}

void Cell::respawn()
{
    srand(time(NULL));

    new_thre_ = rand() % 101;
    new_score_ = 0;
}

void Cell::life_cycle(int ni)
{
    for(int n=0;n<ni;n++)
    {
        interact(north);
        interact(south);
        interact(east);
        interact(west);
    }
}

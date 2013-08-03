#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell
{
private:

    // level of cooperation of the cell (100: always cooperative, 0: never cooperative)
    int thre_;
    int new_thre_;

    // score of the cell (the highest, the best!)
    int score_;
    int new_score_;

    // score table
    std::vector< std::vector <int> > table_;

public:
    Cell();

    // getters
    int score() const;
    int thre() const;

    // interact with cell c, modify the score subsequently
    void interact(Cell * c);

    // return the result of a decision (0: defection, 1: cooperation)
    bool decide();

    // do the cell evolution after all interactions are done
    void evolve();

    // update private variables after evolution
    void update();

    // oh no! this cell just died
    void respawn();

    // one life cycle of the cell. ni: number of interactions with each neighbour during the life cycle
    void life_cycle(int ni);

    // pointers on neighbouring cell
    Cell * east;
    Cell * west;
    Cell * north;
    Cell * south;
};

#endif // CELL_H

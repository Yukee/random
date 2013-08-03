#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#include "cell.h"
#include "containers/Array/Array.h"
#include "containers/Vector.h"

using namespace std;

typedef unsigned int INT;

void write(fstream & data, const ij::Array<Cell> & a)
{
    ij::Vector<INT> d = a.get_dim();
    ij::Vector< ij::Vector<INT> > b = d.get_base_vectors(0, 1);

    for(INT i=0;i<d[0];i++)
    {
        for(INT j=0;j<d[1];j++)
        {
            data << a[i*b[0]+j*b[1]].thre() << "\t";
        }
        data << endl;
    }
}

void write(string filename, const ij::Array<Cell> & a)
{
    fstream data;
    string path = "results/" + filename + ".tsv";
    data.open(path.c_str(), ios::out);

    write(data, a);

    data.close();
}

// link each cell to its neighbours
void link(ij::Array<Cell> & w)
{
    ij::Vector<INT> d = w.get_dim();
    ij::Vector< ij::Vector<INT> > b = d.get_base_vectors(0, 1);

    int ip; int im; int jp; int jm;
    for(INT i=0;i<d[0];i++)
    {
        for(INT j=0;j<d[1];j++)
        {
            ip = i+1;
            im = i-1;
            jp = j+1;
            jm = j-1;
            if(i == 0) im += d[0];
            if(i == d[0]-1) ip = 0;
            if(j == 0) jm += d[1];
            if(j == d[1]-1) jp = 0;
            w.at(i*b[0]+j*b[1]).west = &(w.at(im*b[0]+j*b[1]));
            w.at(i*b[0]+j*b[1]).east = &(w.at(ip*b[0]+j*b[1]));
            w.at(i*b[0]+j*b[1]).south = &(w.at(i*b[0]+jm*b[1]));
            w.at(i*b[0]+j*b[1]).north = &(w.at(i*b[0]+jp*b[1]));
        }
    }
}

int main()
{
    // number of cell along
    // number of interactions per generation
    int ni = 10;
    // number of generations
    int gen = 500;

    // initialization of the cell array
    srand(time(NULL));
    INT n = 150;
    ij::Vector<INT> d (2, n);
    ij::Vector< ij::Vector <INT> > b = d.get_base_vectors(0,1);
    ij::Array<Cell> w (d);
    for(INT i=0;i<d[0];i++) for(INT j=0;j<d[1];j++)
    {
        w[i*b[0] + j*b[1]] = Cell();
    }


    // linkage: the cells can now interact with their neighbourhood!
    link(w);

    write("initial", w);

    // evolution
    for(int n=0;n<gen;++n)
    {
        INT s = w.get_size();
        for(INT it=0;it<s;++it) w[it].life_cycle(ni);
        for(INT it=0;it<s;++it) w[it].evolve();
        for(INT it=0;it<s;++it) w[it].update();
    }

    write("final", w);

    return 0;
}


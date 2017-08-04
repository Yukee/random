# coding: utf8
"""
Written by Quentin Fortier 
http://quentinfortier.fr/
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation
import random

class UnionFind(object):
    """Union-find data structure.

    Each unionFind instance X maintains a family of disjoint sets of
    hashable objects, supporting the following two methods:

    - X[item] returns a name for the set containing the given item.
      Each set is named by an arbitrarily-chosen one of its members; as
      long as the set remains unchanged it will keep the same name. If
      the item is not yet part of a set in X, a new singleton set is
      created for it.

    - X.union(item1, item2, ...) merges the sets containing each item
      into a single larger set.  If any item is not yet part of a set
      in X, it is added to X as one of the members of the merged set.
    """

    def __init__(self):
        """Create a new empty union-find structure."""
        self.weights = {}
        self.parents = {}

    def __getitem__(self, object):
        """Find and return the name of the set containing the object."""

        # check for previously unknown object
        if object not in self.parents:
            self.parents[object] = object
            self.weights[object] = 1
            return object

        # find path of objects leading to the root
        path = [object]
        root = self.parents[object]
        while root != path[-1]:
            path.append(root)
            root = self.parents[root]

        # compress the path and return
        for ancestor in path:
            self.parents[ancestor] = root
        return root
        
    def __iter__(self):
        """Iterate through all items ever found or unioned by this structure."""
        return iter(self.parents)

    def union(self, *objects):
        """Find the sets containing the objects and merge them all."""
        roots = [self[x] for x in objects]
        heaviest = max([(self.weights[r],r) for r in roots])[1]
        for r in roots:
            if r != heaviest:
                self.weights[heaviest] += self.weights[r]
                self.parents[r] = heaviest
    
    def max_sz(self):
        """Return the maximum size of a set and the corresponding representative."""
        return max([(self.weights[r], r) for r in self.parents])

sz = 50 
uf = UnionFind()
for i in range(sz):
    for j in range(sz):
        uf[(i, j)]  
edges = [ [i, i+1, j, j] for i in range(sz-1) for j in range(sz)] + [ [i, i, j, j+1] for i in range(sz) for j in range(sz-1)]
random.shuffle(edges)
n = len(edges)
p = [] # taille relative de la plus grande comp. connexe
step = 7 # nb d'arÃªtes ajoutÃ©es Ã  chaque itÃ©ration

def vertex(e): # extrÃ©mitÃ©s de e
    return (e[0], e[2]), (e[1], e[3])
    
def animer(j):
    for i in range(step*j, step*j+step):
        e = edges[i]
        uf.union(*vertex(e))
        sz_r, r = uf.max_sz()
        p.append(sz_r/sz**2)
        plot_edges[i].set_data(e[:2], e[2:])
        plot_sz.set_data(list(range(i)), p[:i])
    sz_r, r = uf.max_sz()
    for k in range(step*j+step):
        if uf[vertex(edges[k])[0]] == r:
            plot_edges[k].set_color("red")
        else:
            plot_edges[k].set_color("black")
    return tuple(plot_edges) + (plot_sz,)
    
fig = plt.figure(1)

plt.subplot(211, adjustable='box', aspect='equal')
plt.axis([0, sz, 0, sz])
plot_edges = []
for i in range(len(edges)):
    plot_edges.append(plt.plot([], [], color='black')[0])

plt.subplot(212)
plt.axis([0, n, 0, 1])
plot_sz, = plt.plot([], [])

anim = animation.FuncAnimation(fig,animer,frames=n//step,interval=0.1,blit=True)
anim.save('percolation.gif', dpi=50, writer='imagemagick')
plt.show()

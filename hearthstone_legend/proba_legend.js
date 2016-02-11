// A program that computes the probability to go Legend on Hearthstone, using Markov chains. Credit goes to Reddit user /u/jimbohs

// There are 80 stars to rank 5, and another 25 stars to legend.
// There are 80 * 3 different states before rank 5 corresponding to each
// rank and 0, 1, or 2 previous wins, and 25 states between rank 5 and legend,
// and 1 legend state.
// But for simplicity of implementation, we also include 'streak' states
// between legend and 0, and simply modify the transition matrix so that
// they are unreachable.

// States are laid out from lower rank to higher rank in one bloc, then
// again for 1 win and 2 wins. For example:
// idx 0 : rank 25 0 stars, no previous wins
// idx 81 : rank 5 1 star, no previous wins
// idx 104 : rank 1 5 stars, no previous wins
// idx 105 : rank 25 0 stars, 1 previous win
// ...
// idx 209 : rank 1 5 stars, 1 previous win
// ...
// idx 314 : rank 1 5 stars, 2 previous wins
// idx 315 : legend
numeric.largeArray = 2000;
numeric.precision = 3;


var ranks = 80 + 25;
var ps = [.48, .49, 0.5, 0.51, 0.52, 0.53, 0.55, 0.6, 0.65, 0.7];

for (var i = 0; i < ps.length; i++) {
    var p = ps[i];
    var T = numeric.diag(numeric.linspace(0, 0, ranks * 3 + 1));

    for (var curr_rank = 0; curr_rank < ranks; curr_rank++) {
        for (var curr_streak = 0; curr_streak < 3; curr_streak++) {
            var rank_if_win = curr_rank + ((curr_streak == 2 && curr_rank < 80) ? 3 : 1); // 2 bonus stars if already have 2 wins
            var streak_if_win = rank_if_win >= 80 ? 0 : Math.min(curr_streak + 1, 2);
            var rank_if_lose = Math.max(0, curr_rank - 1);

            var curr_idx = curr_rank + curr_streak * ranks;
            var idx_if_win = rank_if_win >= ranks ? 315 : rank_if_win + streak_if_win * ranks;
            var idx_if_lose = rank_if_lose;

            T[curr_idx][idx_if_win] = p;
            T[curr_idx][idx_if_lose] = 1 - p;
        }
    }
    T[315][315] = 1; // Absorbing state: legend stays at legend

    var x = numeric.linspace(0, 0, ranks * 3 + 1);
    x[81] = 1; // Start at rank 5 1 star, no streak

    var pct_5 = 0;
    var pct_25 = 0;
    var pct_50 = 0;
    var pct_75 = 0;
    var pct_95 = 0;

    for (var t = 1; t <= 15000; t++) {
        x = numeric.dot(x, T);
        var cum_prob = x[315];
        if (cum_prob > 0.05 && pct_5 == 0) {
            pct_5 = t;
        }
        if (cum_prob > 0.25 && pct_25 == 0) {
            pct_25 = t;
        }    
        if (cum_prob > 0.5 && pct_50 == 0) {
            pct_50 = t;
        }
        if (cum_prob > 0.75 && pct_75 == 0) {
            pct_75 = t;
        }    
        if (cum_prob > 0.95 && pct_95 == 0) {
            pct_95 = t;
        }
    }
    // Format this for pasting into reddit
    var line = [Math.round(p * 100) + "%", pct_5, pct_25, pct_50, pct_75, pct_95];
    var sep = "  |  ";
    console.log((sep + line.join(sep) + sep).trim());
}

% Nodes are simply assigned indices
% Each node has at most one in and one out edge
1 { cycle(X, Y) : edge(X, Y) } 1 :- node(X).
1 { cycle(X, Y) : edge(X, Y) } 1 :- node(Y).

% Nodes are reached
reached(Y) :- cycle(1, Y).
reached(Y) :- cycle(X, Y), reached(X).

:- node(Y), not reached(Y).

total_cost(Z) :- Z = #sum{ C : cost(X, Y, C), cycle(X, Y) }.

#show cycle/2.
#show total_cost/1.
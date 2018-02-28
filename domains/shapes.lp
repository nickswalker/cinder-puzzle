on_grid(1..n, 1..m).

% TODO: Not really a square,
corner(X, Y) :- square(X, Y, W, H).
corner(A, B) :- square(X, Y, W, H), A=X+0, B=Y+0.
corner(A, B) :- square(X, Y, W, H), A=X+W, B=Y+0.
corner(A, B) :- square(X, Y, W, H), A=X+W, B=Y+H.
corner(A, B) :- square(X, Y, W, H), A=X+0, B=Y+H.

% Sides, clockwise from left
line(X, Y, A, Y), line(X, Y, X, B), line(A, B, A, Y), line(A, B, X, B)   :- square(X, Y, W, H) A=X+W, B=Y+H.
line(X, Y, Q, R) :- endpoint(X, Y), endpoint(Q, R).

line(X, Y, Q, R) :- line(Q, R, X, Y).

%{ shape(X, Y) }
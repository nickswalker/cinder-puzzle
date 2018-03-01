grid_point(1..n, 1..m).

shape_type((rect; triangle)).

% A rectangle implies corners
corner(X, Y) :- rect(X, Y, W, H).
corner(A, B) :- rect(X, Y, W, H), A=X+0, B=Y+0.
corner(A, B) :- rect(X, Y, W, H), A=X+W, B=Y+0.
corner(A, B) :- rect(X, Y, W, H), A=X+W, B=Y+H.
corner(A, B) :- rect(X, Y, W, H), A=X+0, B=Y+H.

% A triangle implies corners
corner(X, Y), corner(Q, R), corner(A, B) :- triangle(X, Y, Q, R, A, B).

% A rectangle covers its interior and borders
inside_shape(A, B) :- rect(X, Y, W, H), A=X..X+W, B=Y..Y+H.

% A version not including edges
inside_shape(A, B) :- rect(X, Y, W, H), A=X+1..X+W-1, B=Y+1..Y+H-1.

% Sides, clockwise from left
line(X, Y, A, Y), line(X, Y, X, B), line(A, B, A, Y), line(A, B, X, B) :- rect(X, Y, W, H), A=X+W, B=Y+H.
line(X, Y, Q, R) :- endpoint(X, Y), endpoint(Q, R).


% Order of endpoints doesn't matter
line(X, Y, Q, R) :- line(Q, R, X, Y).

% Make all concrete shapes imply their abstraction
shape(X, Y, rect) :- rect(X, Y, W, H).
shape(X, Y, triangle) :- triangle(X, Y, Q, R, A, B).

covered(X, Y) :- inside_shape(X, Y).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% There's one shape placed on some grid point.
{ shape(X, Y, S): grid_point(X, Y), shape_type(S) } = 1.

% Generate n (1) shapes
{ rect(X, Y, W, H): W=1..n, H=1..m } = 1 :- shape(X, Y, rect).

% Cover the grid
:- not covered(N, M), grid_point(N, M), N=1..n, M=1..m.

% How do we deal with intersection


%#show corner/2.
%#show rect/4.
%#show triangle/6.
%#show line/4.

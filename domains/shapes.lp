grid_point(1..n, 1..m).

shape_type((rect)).

%%LINE%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
line(X, Y, Q, R) :- endpoint(X, Y), endpoint(Q, R).

% Order of endpoints doesn't matter
line(X, Y, Q, R) :- line(Q, R, X, Y).

%%RECT%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% A rectangle implies corners
corner(X, Y) :- rect(X, Y, W, H, _).
corner(A, B) :- rect(X, Y, W, H, _), A=X+0, B=Y+0.
corner(A, B) :- rect(X, Y, W, H, _), A=X+W, B=Y+0.
corner(A, B) :- rect(X, Y, W, H, _), A=X+W, B=Y+H.
corner(A, B) :- rect(X, Y, W, H, _), A=X+0, B=Y+H.

% A rectangle implies lines (clockwise from left)
%line(X, Y, A, Y), line(X, Y, X, B), line(A, B, A, Y), line(A, B, X, B) :- rect(X, Y, W, H, _), A=X+W, B=Y+H.

% A rectangle covers its interior and borders
inside_shape(A, B, I) :- rect(X, Y, W, H, shape(I, S)), A=X..X+W, B=Y..Y+H.

% Alternative: a rectangle covers its interior
%inside_shape(A, B, I) :- rect(X, Y, W, H, shape(I, rect)), A=X+1..X+W-1, B=Y+1..Y+H-1.

%%TRIANGLE%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% A triangle implies corners
corner(X, Y), corner(Q, R), corner(A, B) :- triangle(X, Y, Q, R, A, B).



%%COVERING%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
covered(X, Y) :- inside_shape(X, Y, _).


%%GENERATION%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% There's s shapes placed on some grid point.
%{ shape(X, Y, S): grid_point(X, Y), shape_type(S) } = s.

% There are s shapes, each has some chosen type
{ shape(I, S): shape_type(S) } = 1 :- I=1..s.

% Decide any abstract rectangles' dimensions. Choose an instantiation for each
{ rect(X, Y, W, H, shape(I, rect)): W=1..n, H=1..m, grid_point(X, Y) } = 1 :- shape(I, rect), I=1..s.

% Break symmetry: must have lower numbered shapes up and toward the left of the higher numbered shapes
:- not XA + YA > XB + YB, rect(XA, YA, _, _, shape(I, rect)), rect(XB, YB, _, _, shape(I + 1, rect)).

% Cover the grid
:- not covered(N, M), grid_point(N, M).

% No double covering
:- inside_shape(N, M, A), inside_shape(N, M, B), A!=B, grid_point(N, M).


%#show corner/2.
%#show rect/4.
%#show triangle/6.
%#show line/4.

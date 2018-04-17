% The canvas is made of N x M pixels
pix(1..n, 1..m).

% Vertically and horizontally adjacent pixels are neighbors.
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A+1, D=B+0.
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A+0, D=B+1.
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A-1, D=B-0.
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A-0, D=B-1.

% Diagonally adjacent pixels are neighbors
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A+1, D=B+1.
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A-1, D=B-1.

neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A-1, D=B+1.
neighbor(A, B, C, D) :- pix(A,B), pix(C, D), C=A+1, D=B-1.

% Allow one cpix/3 for a given pix/2
1 {cpix(C, A, B): col(C) } 1 :- pix(A, B).

%#show neighbor/4.
#show cpix/3.

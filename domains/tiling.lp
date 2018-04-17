#include <incmode>.

cell(1..n, 1..m).

#program step(t).
    1{
        f_shape(X, Y, t): cell(X, Y);
        i_shape(X, Y, t): cell(X, Y);
        i_shape_r1(X, Y, t): cell(X, Y);
        l_shape(X, Y, t) : cell(X, Y) ;
        %l_shape_y_flip(X, Y, t): cell(X, Y);
        %q_shape(X, Y, t): cell(X, Y);
        %q_shape_y_flip(X, Y, t): cell(X, Y);
        t_shape(X, Y, t) : cell(X, Y);
        %t_shape_x_flip(X, Y, t) : cell(X, Y);
        p_shape(X, Y, t) : cell(X, Y);
        %p_shape_y_flip(X, Y, t) : cell(X, Y);
        %u_shape(X, Y, t): cell(X, Y);
        %u_shape_x_flip(X, Y, t): cell(X, Y);
        %w_shape(X, Y, t) : cell(X, Y);
        w_shape_r2(X, Y, t): cell(X, Y);
        x_shape(X, Y, t) : cell(X, Y)
    }1.

    covered(X, Y+1, t), covered(X, Y..Y+2, t), covered(X+2, Y, t) :- f_shape(X, Y, t).
    covered(X, Y..Y+4, t) :- i_shape(X, Y, t).
    covered(X..X+4, Y, t) :- i_shape_r1(X, Y, t).
    covered(X, Y..Y+2, t), covered(X+1..X+2, Y+2, t) :- l_shape(X, Y, t).
    covered(X..X+2, Y+2, t), covered(X+2, Y..Y+1, t) :- l_shape_y_flip(X, Y, t).

    covered(X..X+1, Y..Y+1, t), covered(X+1, Y+2, t) :- p_shape(X, Y, t).
    covered(X..X+2, Y, t), covered(X+1, Y+1..Y+2, t) :- t_shape(X, Y, t).


    covered(X, Y, t), covered(X, Y+1, t), covered(X+1, Y+1,t ), covered(X+1, Y+2,t ), covered(X+2, Y+2,t ) :- w_shape(X, Y, t).


#program check(t).
    :- query(t), not covered(X, Y, _), cell(X, Y).
    :- covered(X, Y, A), covered(X, Y, B), A != B.


%#show covered/3.
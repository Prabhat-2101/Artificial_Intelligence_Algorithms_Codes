% Adding in front: add(X, Y, Z) – add X in front of Y and result into Z
push_front(X,Y,[X|Y]).

% Adding in front: add(X, Y, Z) – add X in back of Y and result into Z
push_back(X,[],[X]).
push_back(X,[H|T],[H|T2]):- push_back(X,T,T2).

% Poping first element from list
pop_front([H|T],H).

% Poping last element from list
pop_back([X],X).
pop_back([H|T],T2):- pop_back(T,T2).

% Deletion: del(X, Y, Z) – delete X from Y and store result in Z
del(X,[X|T],T).
del(X,[H|T],[H|T2]):-del(X,T,T2).

% Membership: member(X,Y) - Check if X is member of Y.
member(X,[X|_]).
member(X,[_|T]):-member(X,T).

% Length of the list: list_len(X,N)
list_len([],0).
list_len([_|T],N):- list_len(T,N1),N is N1+1.

% Concatenate List X & Y and store in Z: concatenate(X,Y,Z).
concatenate([],L,L).
concatenate([H|T],Y,[H|Z]):-concatenate(T,Y,Z).

% Sum of elements of List X: list_sum(X,S).
list_sum([X],X).
list_sum([H|T],S1):-list_sum(T,S2), S1 is S2+H.

% Sublist: sublist(S, L) – check whether S is sublist of L
sublist(S, L) :- concatenate(_, L2, L), concatenate(S, _, L2).
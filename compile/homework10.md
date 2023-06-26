| Grammar rule   | semantic rules                                               |
| -------------- | ------------------------------------------------------------ |
| E->TE'         | E.tree=E'.tree; E'.left=T.tree                               |
| E'~1~->+TE'~2~ | E'.tree=E'~2~.tree; E’~2~.left=mkOpNode(+,E’~1~.left,T.tree) |
| E'->ε          | E’.tree=E’.left                                              |
| T->FT'         | T.tree=T’.tree T’.left=F.tree                                |
| T'~1~->*FT'~2~ | T’~1~.tree=T’~2~.tree<br/>T’~2~.left=mkOpNode(*,T’~1~.left,F.tree) |
| T'->ε          | T’.tree=T’.left                                              |
| F->(E)         | F.tree=E.tree                                                |
| F->i           | F.tree=mkNumNode(i.lexval)                                   |





| Grammar rule | semantic rules         |
| ------------ | ---------------------- |
| L->E         | print(E.val)           |
| E->E~1~+T    | E.val = E~1~.val+T.val |
| E->T         | E.val=T.val            |
| T->T~1~*F    | T.val=T~1~.val*F.val   |
| T->F         | T.val=F.val            |
| F->(E)       | F.val=E.val            |
| F->i         | F.val=i.lexval         |
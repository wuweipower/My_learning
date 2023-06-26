/*
For each particle
____Initialize particle
END
Do
____For each particle
________Calculate fitness value
________If the fitness value is better than the best fitness value (pBest) in history
____________set current value as the new pBest
____End
____Choose the particle with the best fitness value of all the particles as the gBest
____For each particle
________Calculate particle velocity according equation (a)
________Update particle position according equation (b)
____End
While maximum iterations or minimum error criteria is not attained


*/
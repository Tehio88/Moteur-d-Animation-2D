# TP 1 - INTRO A L'IMAGE

## Théo BRYANT

### COMPILATION

Pour compiler les différents programmes du TP, il suffit d'utiliser dans le terminal la commande make suivi du programme souhaité 

make exoN

(avec N allant de 1 à 5)
Et ensuite éxectuer le programme avec la commande:

./exoN

### DOCUMENTATION

Pour la plupart des exercices, une barre s'affiche sur les côtés nous permmettant de changer entre le mode bounce ou cross des particules ou bien la barre permettant de gérer la poursuite du snake avec la souris.

### DIFFICULTEES

La principale difficultée de ce TP a été le chaînage des particules pour assembler le snake ainsi que la gestion des obstacles. En effet, mes premières versions du snake (exo4) affichaient un snake qui n'était pas relié à la tête et se balader librement et pouvaient même se faire manger par la tête et ainsi afficher un nouveau snake. De ce fait, j'ai ajouté un champ de type boolean qui permet de dissocier les particules mangées par le snake des autres particules. L'autre difficultée réside dans la gestion des obstacles avec les divers calculs et vecteurs à créer pour obtenir un résultat fluide (cf exo5). Malheureusement, le snake n'arrive pas à contourner comme demandé les obstacles de la fenêtre. D'autres part, les particules ont toute la même vitesse et je n'ai de ce fait pas pu changer la couleur de ces dernières. Une autre difficulté du TP a été de maintenir une bonne modularisation de mes fichiers sources et en-têtes. Ainsi, je me suis aidé du cours sur la modularistion à de nombreuses reprises pour y remédier.
# piscine-minimax-algorithm
implementing the minimax algorithm in C++ creating the game of "the cat and the mouse"

# Steps:
- Lo primero que hice fue estudiar sobre el algoritmo minimax, y la mejor forma fue haciendo un ta-te-ti donde me explicaban de forma sencilla lo que hace este algoritmo.

- Lo segundo que hice fue hacerlo en python primeramente ya que no tengo conocimientos en C++ pero si podia hacer la logica en python ya migrar a otro lenguaje no seria tan complicado.

- Ahora si, los pasos que tenia en mi cabeza:
lo primero que necesitaba era crear un tablero en el cual iban a estar mi raton y mi gato. Una vez hecho el tablero pense en que tanto el gato como el raton deben iniciar obligatoriamente en las diferentes puntas del tablero, en este caso el gato inicia en lo que vendria a ser la meta para el raton y el raton inicia en las ultimas casillas del tablero.

- Una vez definido el inicio de cada jugador me dedique a poder hacer lo mas sencillo que fue controlar al raton, para ello necesitaba hacer que al dar una accion especifica pueda mover hacia una direccion concreta siempre y cuando este permitido (casilla libre evitando saltos de columnas) y que se actualice el tablero a medida que el raton se va moviendo. Una vez que el raton llegue a cualquiera de las casillas de meta es coronado ganador.

- Deje el gato que era lo mas complicado para el final, asi como el raton tiene que empezar de forma obligatoria en la meta, una vez que elija su posicion que calcule la distncia que existe entre ellos. Para que sea efectivo el movimiento del gato era fundamental crear la funcion del algoritmo minimax, que en sintesis hace lo siguiente:
    analiza todas las posibilidades posibles y segun su prediccion elige un camino.
    
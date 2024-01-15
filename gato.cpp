#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
using namespace std;

// VARIABLES
const string raton = "R"; // "<:3 )~";
const string gato = "G"; //"^._.^";

// TABLERO
map<int, string> tablero = {
    {1, " "}, {2, " "}, {3, " "}, {4, " "}, {5, " "},
    {6, " "}, {7, " "}, {8, " "}, {9, " "}, {10, " "},
    {11, " "}, {12, " "}, {13, " "}, {14, " "}, {15, " "},
    {16, " "}, {17, " "}, {18, " "}, {19, " "}, {20, " "},
    {21, " "}, {22, " "}, {23, " "}, {24, " "}, {25, " "}
};

// FUNCIONES

// funcion que imprime el tablero
void imprimir_tablero(map<int, string> tablero){
    cout << "\n";
    cout << "- - - - - - - - - - - - - - - -\n";
    cout << "|  " << tablero[1] << "  |  " << tablero[2] << "  |  " << tablero[3] << "  |  " << tablero[4] << "  |  " << tablero[5] << "  |\n";
    cout << "- - - - - - - - - - - - - - - -\n";
    cout << "|  " << tablero[6] << "  |  " << tablero[7] << "  |  " << tablero[8] << "  |  " << tablero[9] << "  |  " << tablero[10] << "  |\n";
    cout << "- - - - - - - - - - - - - - - -\n";
    cout << "|  " << tablero[11] << "  |  " << tablero[12] << "  |  " << tablero[13] << "  |  " << tablero[14] << "  |  " << tablero[15] << "  |\n";
    cout << "- - - - - - - - - - - - - - - -\n";
    cout << "|  " << tablero[16] << "  |  " << tablero[17] << "  |  " << tablero[18] << "  |  " << tablero[19] << "  |  " << tablero[20] << "  |\n";
    cout << "- - - - - - - - - - - - - - - -\n";
    cout << "|  " << tablero[21] << "  |  " << tablero[22] << "  |  " << tablero[23] << "  |  " << tablero[24] << "  |  " << tablero[25] << "  | INICIO\n";
    cout << "- - - - - - - - - - - - - - - -\n";
    cout << "\n";
}

// funcion que verifica si una casilla esta libre
bool espacio_libre(int posicion){
    return tablero[posicion] == " ";
}

// funcion para colocar al gato o al raton en la casilla
void colocar_gato_raton(int posicion, string jugador){
    if(espacio_libre(posicion)){
        tablero[posicion] = jugador;
    }
}

// funcion para la primera posicion del jugador
int movimiento_inicial_jugador(){
    imprimir_tablero(tablero);
    int posicion;
    cout << "Elija una casilla del 21 al 25\nRespuesta: ";
    cin >> posicion;

    while (!(posicion >= 21 && posicion <= 25)){
        cout << "Opción no válida, elija una casilla del 21 al 25\nRespuesta: ";
        cin >> posicion;
    }

    colocar_gato_raton(posicion, raton);
    return posicion;
}

// funcion que calcula segun tu posicion previa tu nueva ubicacion y que no te saltes columnas
int obtener_nueva_posicion(int posicion, int direccion){
    if(direccion == 1){ 
        return posicion - 5;
    } else if(direccion == 2){ 
        return posicion + 5;
    } else if(direccion == 3){ 
        if(posicion % 5 == 1){ 
            return posicion; 
        }
        return posicion - 1;
    } else if(direccion == 4){ 
        if(posicion % 5 == 0){ 
            return posicion; 
        }
        return posicion + 1;
    } else{
        cout << "Opción no válida";
        return posicion; 
    }
}

// funcion para calcular las distancias de los jugadores
int calcular_distancia(int posicion_gato, int posicion_raton){
    int fila_gato = (posicion_gato - 1) / 5;
    int columna_gato = (posicion_gato - 1) % 5;

    int fila_raton = (posicion_raton - 1) / 5;
    int columna_raton = (posicion_raton - 1) % 5;

    int diferencia_filas = abs(fila_gato - fila_raton);
    int diferencia_columnas = abs(columna_gato - columna_raton);

    return diferencia_filas + diferencia_columnas;
}

// funcion que verifica si el movimiento se puede realizar.
bool es_movimiento_valido(int posicion){
    return posicion >= 1 && posicion <= 25 && (espacio_libre(posicion) || tablero[posicion] == raton);
}

// funcion que analiza si gano el raton
bool gano_raton(int posicion_raton){
    if(posicion_raton == 1 || posicion_raton == 2 || posicion_raton == 3 || posicion_raton == 4 || posicion_raton == 5){
        return true;
    }
    return false;
}

// funcion que determina la mejor posicion incial para el gato.
int posicion_inicial_gato(){
    // se inicializa con infinito para poder minimizar despues la evaluacion y con -1 para asegurar que cualquier posicion valida en el tablero va a ser mejor que el valor inicial
    float mejor_evaluacion = INFINITY;
    int mejor_posicion = -1;
    // recorre las cinco casillas donde puede empezar.
    for(int posicion = 1; posicion <= 5; posicion++){
        float maximizar = -INFINITY;
        // recorre en todas las direcciones
        for(int direccion = 1; direccion <= 4; direccion++){
            // clacula la nueva direccion
            int nueva_posicion = obtener_nueva_posicion(posicion, direccion);
            if(es_movimiento_valido(nueva_posicion)){
                // si la condicion es verdadera,calcula la distancia entre el gato y el raton.
                float evaluacion = static_cast<float>(calcular_distancia(posicion, nueva_posicion));
                maximizar = max(maximizar, evaluacion);
            }
        }


        if(maximizar < mejor_evaluacion){
            // actualiza la mejor evaluacion y su mejor posicion.
            mejor_evaluacion = maximizar;
            mejor_posicion = posicion;
        }
    }
    return mejor_posicion;
}

// funcion que determina la posicion del jugador cada vez que realiza un movimiento.
int determinar_posicion(int posicion){
    cout << "Te encuentras en la posición " << posicion << ". ¿En qué dirección quieres ir?\n";
    cout << "Seleccione una de las siguientes opciones:\n - 1 si desea ir arriba\n - 2 si desea ir abajo\n - 3 si desea ir izquierda\n - 4 si desea ir derecha\n Respuesta: ";

    int mover;
    cin >> mover;

    if(mover >= 1 && mover <= 4){
        int nueva_posicion = obtener_nueva_posicion(posicion, mover);
        if(es_movimiento_valido(nueva_posicion)){
            tablero[posicion] = ' ';
            tablero[nueva_posicion] = raton;

            if(gano_raton(nueva_posicion)){
                imprimir_tablero(tablero);
                cout << "¡Felicidades! ¡Has ganado!";
                exit(0);  // Terminar el juego
            }

            return nueva_posicion;
        }
    } else{
        cout << "Movimiento no válido. Intenta de nuevo.";
    }

    return determinar_posicion(posicion);
}

// funcion minimax que minimiza la perdida maxima posible.
float minimax(int posicion_gato, int posicion_raton, int profundidad, float alfa, float beta, bool es_maximizador){
    // analiza todo el arbol de posibilidades (profundidad) y segun la prediccion eligira un camino
    if(profundidad == 0 || gano_raton(posicion_raton)){
        return calcular_distancia(posicion_gato, posicion_raton);
    }

    // cuando sea el turno del jugador.
    if(es_maximizador){
        // se asegura que todo valor encontrado sea mayor
        float maximizar = -INFINITY;
        // recorre el tablero para identificar los movimientos que puede hacer el raton.
        for(int direccion = 1; direccion <= 4; direccion++){
            // calcula la nueva posicion del raton
            int nueva_posicion = obtener_nueva_posicion(posicion_raton, direccion);
            // verifica el movimiento
            if(es_movimiento_valido(nueva_posicion)){
                // hace la evaluacion del movimiento con minimax()
                float evaluacion = minimax(posicion_gato, nueva_posicion, profundidad - 1, alfa, beta, false);
                // se actualiza el valor de maximizar siempre y cuando el resultado de la evaluacion sea mejor, para eso se usa la funcion max(), devuelve el valor maximo de dos valores dados
                maximizar = max(maximizar, evaluacion);
                // se actualiza alfa, que es el mejor valor que el maximizador encontro hasta ahora.
                alfa = max(alfa, evaluacion);
                // si beta es menor a alfa, paramos e ignoramos todas las ramas innecesarias!.
                if(beta <= alfa){
                    break;
                }
            }
        }
        // se devuelve el valor maximo encontrado.
        return maximizar;

        // turno del gato
    } else{
        // inicializa el valor minimo a infinito
        float minimizar = INFINITY;
        // recorre el tablero probando posiciones
        for(int direccion = 1; direccion <= 4; direccion++){
            int nueva_posicion = obtener_nueva_posicion(posicion_gato, direccion);
            // si el movimiento es valido realiza la evaluacion
            if(es_movimiento_valido(nueva_posicion)){
                float evaluacion = minimax(nueva_posicion, posicion_raton, profundidad - 1, alfa, beta, true);
                // actualiza el valor minimizar siempre y cuando el resultado de la evaluacion sea mejor
                minimizar = min(minimizar, evaluacion);
                // se actualiza beta, que es el emjor valor que el minimizador encontro.
                beta = min(beta, evaluacion);
                if(beta <= alfa){
                    break;
                }
            }
        }
        return minimizar;
    }
}

// funcion que determina la mejor opcion de movimiento que puede realizar la computadora
int movimiento_gato(int posicion_gato, int posicion_raton){
    float mejor_evaluacion = INFINITY;
    int mejor_movimiento = -1;
    for(int direccion = 1; direccion <= 4; direccion++){
        int nueva_posicion = obtener_nueva_posicion(posicion_gato, direccion);
        if(es_movimiento_valido(nueva_posicion)){
            float evaluacion = minimax(nueva_posicion, posicion_raton, 5, -INFINITY, INFINITY, true);
            if(evaluacion < mejor_evaluacion){
                mejor_evaluacion = evaluacion;
                mejor_movimiento = direccion;
            }
        }
    }
    return mejor_movimiento;
}

// funcion que usaria cuando se ejecute el juego para que la pc pueda jugar, tambien analiza si se le atrapo al jugador.
int turno_gato(int posicion_gato, int &posicion_raton){
    int direccion = movimiento_gato(posicion_gato, posicion_raton);
    int nueva_posicion = obtener_nueva_posicion(posicion_gato, direccion);
    
    if(es_movimiento_valido(nueva_posicion)){
        if(nueva_posicion == posicion_raton){
            cout << "¡El gato ha atrapado al ratón!\n Haz perdido :'(";
            exit(0);
        } else{
            tablero[posicion_gato] = ' ';
            tablero[nueva_posicion] = gato;
            return nueva_posicion;
        }
    } else{
        cout << "Movimiento no válido. El gato se queda en su posición.";
        return posicion_gato;
    }
    
    return posicion_gato;
}

int main(){
    int posicion_gato = posicion_inicial_gato();
    colocar_gato_raton(posicion_gato, gato);
    imprimir_tablero(tablero);
    int posicion_raton = movimiento_inicial_jugador();
    imprimir_tablero(tablero);

// El juego
    while (true){
        posicion_gato = turno_gato(posicion_gato, posicion_raton);
        imprimir_tablero(tablero);

        posicion_raton = determinar_posicion(posicion_raton);
        imprimir_tablero(tablero);

        if(gano_raton(posicion_raton)){
            imprimir_tablero(tablero);
            cout << "¡Felicidades! ¡Has ganado!";
            break;
        }
    }

    return 0;
}

#include <iostream>
#include <string>


#include <conio.h>
#include <windows.h>

using namespace std;


char Tablero[3][3] = { 
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' } 
};

char TurnoJugador = 'X';
string playerX, playerO;


bool EsNumeroValido(string str) {
    int digito;
    if (str.empty() && str.length() < 2) {
        return false;
    }

    for (char c : str) {

        if (!isdigit(c)) {
            return false;
        }
        digito = c - '0' ;
        if (digito < 1 || digito >3)
        {
            return false;
        }
    }
    // Evitar que no este entre 1 y 3
    return true;
}

// Función para imprimir el tablero
void ImprimirTablero() {
    for (int i = 0; i < 3; i++) {
        cout << "-------------" << endl;
        for (int j = 0; j < 3; j++)
        {
            cout << "| " << Tablero[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "-------------" << endl;
}


// Función para verificar si alguien ha ganado, usa la fuerza bruta para verificar todas las opciones de victoria posibles. 
bool Victoria() {
    // Implementa las reglas para verificar si un jugador ha ganado
    // (filas, columnas, diagonales)

    // Comprueba filas y columnas
    for (int i = 0; i < 3; i++) {
        if (Tablero[i][0] == TurnoJugador && Tablero[i][1] == TurnoJugador && Tablero[i][2] == TurnoJugador)
            return true;
        if (Tablero[0][i] == TurnoJugador && Tablero[1][i] == TurnoJugador && Tablero[2][i] == TurnoJugador)
            return true;
    }

    // Comprueba diagonales
    if (Tablero[0][0] == TurnoJugador && Tablero[1][1] == TurnoJugador && Tablero[2][2] == TurnoJugador)
        return true;
    if (Tablero[0][2] == TurnoJugador && Tablero[1][1] == TurnoJugador && Tablero[2][0] == TurnoJugador)
        return true;

    return false;
}

void LimpiarPantalla() {
    system("pause");
    system("cls");
}

void menuInicio(char &JugadorInicial) {
    bool inputValid = false;
    int teclado;

    // Entrada de nombres de jugadores
    cout << "Ingrese el nombre del jugador X: ";
    cin >> playerX;
    cout << "Ingrese el nombre del jugador O: ";
    cin >> playerO;

    // Selección del jugador que comienza
    cout << "Seleccione quién comenzará (X o O): ";

    while (!inputValid)
    {
        teclado = _getch();

        if (teclado == 88 || teclado == 120) {
            JugadorInicial = 'X';
            inputValid = true;
        }
        else if (teclado == 79 || teclado == 111) {
            JugadorInicial = 'O';
            inputValid = true;
        }
        else {
            cout << "\n\tEntrada inválida. Debes seleccionar 'X' o 'O'." << endl;
        }
        cout << endl;
    }
}
void EjectutarTicTacToe()
{
    system("COLOR 5F");
    int Fila, Columna, EntradaInt;
    int Movimientos = 0;
    string entrada, invalida;
    char JugadorInicial;
    
    
    menuInicio(JugadorInicial);

                 //     Preambulo incio juegos 
    if (JugadorInicial == 'X' || JugadorInicial == 'x') {
        TurnoJugador = 'X';
    }
    else {
        TurnoJugador = 'O';
    }

    LimpiarPantalla();

    //Juego
    while (true) {
        cout << "Turno de " << ((TurnoJugador == 'X') ? playerX : playerO) << endl;
        ImprimirTablero();

        // Entrada de filas y columnas del jugador
        cout << "Ingresa la fila y columna (1-3): ";
        cin >> entrada;

        if (!EsNumeroValido(entrada))
        {
            cout << "Entrada inválida. Solo dos numeros entre 3 y 1." << endl;
            LimpiarPantalla();
            continue;
        }
        //Se convierte la entrada ASCII en su contraparte numerica
        Fila = entrada[0] - '0' - 1;
        Columna = entrada[1] - '0' - 1;

        if (Tablero[Fila][Columna] != ' ')
        {
            cout << "Movimiento inválido, YA HAY una marca. Inténtalo de nuevo." << endl;
            LimpiarPantalla();
            continue;
        }
        // Actualización del tablero
        Tablero[Fila][Columna] = TurnoJugador;
        Movimientos++;

        // Verificación del resultado del juego
        if (Victoria()) {
            system("cls");
            ImprimirTablero();
            cout << "¡" << ((TurnoJugador == 'X') ? playerX : playerO) << " ha ganado!" << endl;
            break;
        }

        // Verificación de empate
        if (Movimientos == 9) {
            ImprimirTablero();
            cout << "¡Empate!" << endl;
            break;
        }
        system("cls");
        // Cambio de jugador
        TurnoJugador = (TurnoJugador == 'X') ? 'O' : 'X';
    }

   

}
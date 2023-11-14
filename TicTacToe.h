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



bool EsNumeroValido(string str, int maxChar) {
    int digito;
    if (str.empty() || str.length() > maxChar) {
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

void Gotoxy(int x, int y) {
    HANDLE manejadorConsola ;
    COORD coordenada;
    coordenada.X = x;
    coordenada.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenada);
}
void NombreJugadores() {
    int y = 8;
    Gotoxy(10, y++);cout << char(218);      for (int i = 0; i < 21; i++) { cout << char(196); }      cout << char(191) << endl;
    Gotoxy(10, y++);cout << char(179) << "    Jugadores:       ";
    Gotoxy(10, y++);cout << char(179) << "                     ";
    Gotoxy(10, y++);cout << char(179) << "   " << playerX << " => X";
    Gotoxy(10, y++);cout << char(179) << "   " << playerO << " => O";
    Gotoxy(10, y++);cout << char(179) << "                     ";
    Gotoxy(10, y++);cout << char(192);      for (int i = 0; i < 21; i++) { cout << char(196); }      cout << char(217) << endl;

    Gotoxy(0, 0);
}


// Función para imprimir el tablero
void ImprimirTablero() {
    int margenX = 50;
    Gotoxy(margenX, 7); cout << "00";
    for (int i = 0; i < 3; i++) {
        Gotoxy(margenX, 8 + (i * 2)); cout << "  -------------" << endl; Gotoxy(margenX, 9 + (i * 2));cout << "  ";
        
        for (int j = 0; j < 3; j++)
        {
            cout << "| " << Tablero[i][j] << " ";
        }
        cout << "|" ;
    }
    Gotoxy(margenX, 14);cout << "  -------------" << endl;
    Gotoxy(0, 0);
    NombreJugadores();
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



void menuInicio(char &JugadorInicial) {
    bool inputValid = false;
    string teclado;
    int y = 0;

    Gotoxy(40,y++);cout << char(218);      for (int i = 0; i < 21; i++) { cout << char(196); }      cout << char(191) << endl;
    Gotoxy(40,y++);cout << char(179) << "                     " << char(179) << endl;
    Gotoxy(40,y++);cout << char(179) << "                     " << char(179) << endl;
    Gotoxy(40,y++);cout << char(179) << "     Tic Tac Toe     " << char(179) << endl;
    Gotoxy(40,y++);cout << char(179) << "      BruteForce     " << char(179) << endl;
    Gotoxy(40,y++);cout << char(179) << "                     " << char(179) << endl;
    Gotoxy(40,y++);cout << char(192);      for (int i = 0; i < 21; i++) { cout << char(196); }      cout << char(217) << endl;
  
    

    // Entrada de nombres de jugadores
    cout << "\t\tMENU INICIO\n";
    cout << "Ingrese el nombre del jugador X: ";
    cin >> playerX;
    cout << "Ingrese el nombre del jugador O: ";
    cin >> playerO;

    

    while (!inputValid)
    {
        // Selección del jugador que comienza
        cout << "Seleccione quién comenzará (" << playerX << "[X] o "<<playerO<<"[O] ): ";
        cin >> teclado;

        if (teclado == "X" || teclado == "x") {
            JugadorInicial = 'X';
            inputValid = true;
        }
        else if (teclado == "O" || teclado == "o") {
            JugadorInicial = 'O';
            inputValid = true;
        }
        else if(!EsNumeroValido(teclado, 1)){
            cout << "\n\tEntrada inválida. Debes seleccionar 'X' o 'O'." << endl;
        }
        cout << endl;
    }
}

void LimpiarPantalla() {
    system("pause");
    system("cls");
}

void EjectutarTicTacToe()
{
    system("COLOR 5F");
    int Fila, Columna, EntradaInt;
    int Movimientos = 0;
    string entrada, invalida;
    char JugadorInicial;
    
    
    //     Preambulo incio juegos 
    menuInicio(JugadorInicial);
    LimpiarPantalla();

    if (JugadorInicial == 'X' || JugadorInicial == 'x') {
        TurnoJugador = 'X';
    }
    else {
        TurnoJugador = 'O';
    }
  
    //Juego
    while (true) {
        ImprimirTablero();
        Gotoxy(50, 5);
        cout << "Turno de " << ((TurnoJugador == 'X') ? playerX : playerO) << endl;
        Gotoxy(0, 0);
        // Entrada de filas y columnas del jugador
        cout << "Ingresa la fila y columna (1-3): ";
        cin >> entrada;

        if (!EsNumeroValido(entrada,2))
        {
            Gotoxy(30,25);
            cout << "Entrada inválida. Solo dos numeros entre 3 y 1." << endl;
            LimpiarPantalla();
            continue;
        }
        //Se convierte la entrada ASCII en su contraparte numerica
        Fila = entrada[0] - '0' - 1;
        Columna = entrada[1] - '0' - 1;

        if (Tablero[Fila][Columna] != ' ')
        {
            Gotoxy(30, 25);
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
            Gotoxy(30, 25);
            cout << "¡" << ((TurnoJugador == 'X') ? playerX : playerO) << " ha ganado!" << endl;
            break;
        }

        // Verificación de empate
        if (Movimientos == 9) {
            ImprimirTablero();
            Gotoxy(30, 25);
            cout << "¡Empate!" << endl;
            break;
        }
        system("cls");
        // Cambio de jugador
        TurnoJugador = (TurnoJugador == 'X') ? 'O' : 'X';
    }

   

}
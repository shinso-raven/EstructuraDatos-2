/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Realizar un programa C++ que un juego de Tic Tac Toe usando el paradigma de Fuerza Bruta (Brute Force).
 *  Autores (ID - Nombre):
 *  1107555 - Angel Soriano
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114290 - Angel Antonio Orona Pimentel
 *  1116252 - Radhames Ventura
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  14/11/2023
 */



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
string playerX, playerO, nombrePlayer;
string maquinaNombre = "maquina";


bool EsNumeroValido(string str, int maxChar) {
    int digito;
    if (str.empty() || str.length() != maxChar) {
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
#pragma region Pintura




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



char ValidarXoO(string teclado) {
    bool inputValid = false;
    char JugadorInicial = ' ';

    if (teclado == "X" || teclado == "x") {
        JugadorInicial = 'X';
        inputValid = true;
    }
    else if (teclado == "O" || teclado == "o") {
        JugadorInicial = 'O';
        inputValid = true;
    }
    else if (!EsNumeroValido(teclado, 1)) {
        cout << "\n\tEntrada inválida. Debes seleccionar 'X' o 'O'." << endl;
    }
    cout << endl;

    if (inputValid) {
        return JugadorInicial;

    }
    else {
        return '-';
    }
}

void menuInicio(char& JugadorInicial) {
    bool inputValid = false;
    string teclado;
    int y = 0;
    JugadorInicial = '-';
    Gotoxy(40, y++); cout << char(218);      for (int i = 0; i < 21; i++) { cout << char(196); }      cout << char(191) << endl;
    Gotoxy(40, y++); cout << char(179) << "                     " << char(179) << endl;
    Gotoxy(40, y++); cout << char(179) << "                     " << char(179) << endl;
    Gotoxy(40, y++); cout << char(179) << "     Tic Tac Toe     " << char(179) << endl;
    Gotoxy(40, y++); cout << char(179) << "      BruteForce     " << char(179) << endl;
    Gotoxy(40, y++); cout << char(179) << "                     " << char(179) << endl;
    Gotoxy(40, y++); cout << char(192);      for (int i = 0; i < 21; i++) { cout << char(196); }      cout << char(217) << endl;

            //Hacer que el jugador seleccione X o O, ese player tiene nombre, el otro se llama "maquina"

    // Entrada de nombres de jugadores
    cout << "\t\tMENU INICIO\n";

    cout << "Ingrese el nombre del jugador: ";
    cin >> nombrePlayer;

    cout << "Ingrese su letra [X] o [O]";


    cout << "Ingrese el nombre del jugador X: ";
    cin >> playerX;
    cout << "Ingrese el nombre del jugador O: ";
    cin >> playerO;



    while (JugadorInicial == '-')
    {
        // Selección del jugador que comienza
        cout << "Seleccione quién comenzará (" << playerX << "[X] o " << playerO << "[O] ): ";
        cin >> teclado;


        JugadorInicial =  ValidarXoO(teclado);

        if (teclado == "X" || teclado == "x") {
            JugadorInicial = 'X';
            inputValid = true;
        }
        else if (teclado == "O" || teclado == "o") {
            JugadorInicial = 'O';
            inputValid = true;
        }
        else if (!EsNumeroValido(teclado, 1)) {
            cout << "\n\tEntrada inválida. Debes seleccionar 'X' o 'O'." << endl;
        }
        cout << endl;
    }
}

void LimpiarPantalla() {
    system("pause");
    system("cls");
}

#pragma endregion

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





void EjectutarTicTacToe()
{
    int Fila, Columna, EntradaInt;
    int Movimientos = 0;
    string entrada, invalida;
    char JugadorInicial;


    system("COLOR 8F");
    //     Preambulo incio juegos 
    menuInicio(JugadorInicial);
    LimpiarPantalla();

    //Ya la selección fue validada
    if (JugadorInicial == 'X') {
        TurnoJugador = 'X';
    }
    else {
        TurnoJugador = 'O';
    }

  
    //Juego
    while (true) {
        ImprimirTablero();
        Gotoxy(50, 5); //Imprime justo arriba del tablero
        cout << "Turno de " << ((TurnoJugador == 'X') ? playerX : playerO) << endl;
        Gotoxy(0, 0);




        // Entrada de filas y columnas del jugador HUMANO
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
            cout << "Movimiento inválido, Ya HAY una marca. Inténtalo de nuevo." << endl;
            LimpiarPantalla();
            continue;
        }

        // Actualización del tablero, con movimiento valido
        Tablero[Fila][Columna] = TurnoJugador;
        Movimientos++;

        // Verificación del resultado del juego
        if (Victoria()) {
            system("cls");
            ImprimirTablero();
            Gotoxy(30, 25);     //mensaje victoria
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
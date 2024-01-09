/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Realizar un programa C++ que un juego de Tic Tac Toe player vs maquina.
 *  Autores (ID - Nombre):
 *  1107555 - Angel Soriano
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114290 - Angel Antonio Orona Pimentel
 *  1116252 - Radhames Ventura
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  8/1/2024
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
    char entradaJugador = '-';
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


    while (entradaJugador == '-')
    {
        cout << "Ingrese su letra [X] o [O]: ";
        cin >> teclado;

        entradaJugador = ValidarXoO(teclado);
        cout << endl;
    }
    
    if (entradaJugador == 'X')
    {
        playerX = nombrePlayer;
        playerO = maquinaNombre;
    }
    else {
        playerO = nombrePlayer;
        playerX = maquinaNombre;
    }



    while (JugadorInicial == '-')
    {
        // Selección del jugador que comienza
        cout << "Seleccione quién comenzará (" << playerX << "[X] o " << playerO << "[O] ): ";
        cin >> teclado;


        JugadorInicial =  ValidarXoO(teclado);

       
        cout << endl;
    }
}

void LimpiarPantalla() {
    system("pause");
    system("cls");
}

#pragma endregion

// Función para verificar si alguien ha ganado, usa la fuerza bruta para verificar todas las opciones de victoria posibles. 
char Victoria(const char tableroTemp[3][3], char jugadorActual) {
    // Implementa las reglas para verificar si un jugador ha ganado
    // (filas, columnas, diagonales)
    bool victoria = false;
    // Comprueba filas y columnas
    for (int i = 0; i < 3; i++) {
        if (Tablero[i][0] == jugadorActual && Tablero[i][1] == jugadorActual && Tablero[i][2] == jugadorActual)
            victoria =  true;
        if (Tablero[0][i] == jugadorActual && Tablero[1][i] == jugadorActual && Tablero[2][i] == jugadorActual)
            victoria = true;
    }

    // Comprueba diagonales
    if (Tablero[0][0] == jugadorActual && Tablero[1][1] == jugadorActual && Tablero[2][2] == jugadorActual)
        victoria = true;
    if (Tablero[0][2] == jugadorActual && Tablero[1][1] == jugadorActual && Tablero[2][0] == jugadorActual)
        victoria = true;


    if (victoria)
    {
        return jugadorActual;
    }
    else
    {
        return '-';

    }
}

int minimoMaximo(char tempTablero[3][3], bool maximizar) {

    char letraJugador, letraMaquina, ganador;
    int puntuacion = 0, limitePuntuacion, resultado;
    if (playerO == maquinaNombre)
    {
        letraJugador= 'X';
        letraMaquina = 'O';
    }
    else
    {
        letraJugador = 'O';
        letraMaquina = 'X';
    }

    ganador = Victoria(tempTablero, letraMaquina);
    if (ganador ==letraMaquina)
    {
        return 1;
    }
    ganador = Victoria(tempTablero, letraJugador);
    if (ganador == letraJugador)
    {
        return -1;
    }
    

    //Posibles soluciones
    if (maximizar)
    {
        limitePuntuacion = -INT_MAX;
        for (int filas = 0; filas < 3; filas++)
        {
            for (int columnas = 0; columnas < 3; columnas++)
            {
                if (tempTablero[filas][columnas] == ' ')
                {
                    tempTablero[filas][columnas] = letraMaquina;

                    //evaluar posibilidad
                    puntuacion = minimoMaximo(tempTablero, false);

                    tempTablero[filas][columnas] = ' ';

                    if (puntuacion > limitePuntuacion)
                    {
                        limitePuntuacion = puntuacion;

                    }
                }

            }
        }
        return limitePuntuacion;
    }
    else
    {
        limitePuntuacion = INT_MAX;
        for (int filas = 0; filas < 3; filas++)
        {
            for (int columnas = 0; columnas < 3; columnas++)
            {
                if (tempTablero[filas][columnas] == ' ')
                {
                    tempTablero[filas][columnas] = letraJugador;

                    //evaluar posibilidad
                    puntuacion = minimoMaximo(tempTablero, true);

                    tempTablero[filas][columnas] = ' ';

                    if (puntuacion < limitePuntuacion)
                    {
                        limitePuntuacion = puntuacion;

                    }
                }

            }
        }
        return limitePuntuacion;
    }



}

string JugarMaquina(char tableroTemp[3][3]) {
    char letraMaquina;
    int mejorPuntuacion = -2, puntuacion = 0;

    string fila, columna, movimiento;

    if (playerX == maquinaNombre )
    {
        letraMaquina = 'X';
    }
    else
    {
        letraMaquina = 'O';
    }


    for (int filas = 0; filas < 3; filas++)
    {
        for (int columnas = 0; columnas < 3; columnas++)
        {
            //posiciones vacias
            if (tableroTemp[filas][columnas] == ' ')
            {
                tableroTemp[filas][columnas] = letraMaquina;
                //minimo maximo
                puntuacion = minimoMaximo(tableroTemp, false);

                tableroTemp[filas][columnas] = ' ';


                if (puntuacion > mejorPuntuacion)
                {
                    mejorPuntuacion = puntuacion;
                    fila = to_string(filas+1);
                    columna = to_string(columnas+1);
                    movimiento = fila + columna;

                }
            }
        }
    }



    return movimiento;

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

        string jugadorActual = ((TurnoJugador == 'X') ? playerX : playerO);

        if (jugadorActual == maquinaNombre)
        {
            //turno de la maquina
           entrada = JugarMaquina(Tablero);
        }
        else
        {
            // Entrada de filas y columnas del jugador HUMANO
            cout << "Ingresa la fila y columna (1-3): ";
            cin >> entrada;

            if (!EsNumeroValido(entrada, 2))
            {
                Gotoxy(30, 25);
                cout << "Entrada inválida. Solo dos numeros entre 3 y 1." << endl;
                LimpiarPantalla();
                continue;
            }
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
        if (Victoria(Tablero, TurnoJugador) != '-') {
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
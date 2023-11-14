/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Realizar un programa C++ que realice una conversion de numero a texto usando un algoritmo de Divide y Venceras.

 *  Autores (ID - Nombre):
 *  1113891 - Alan Arturo Sosa Del Villar
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114290 - Angel Antonio Orona Pimentel
 *  1116252 - Radhames Ventura
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  06/11/2023
 */

using namespace std;

#include <iostream>
#include <string>

bool EsNumero(string numeroStr) {

	try {
		double numero = stod(numeroStr);
		// Verificar si el número está dentro del rango deseado
		if (numero >= 0 && numero <= 9) {
			return true; // Si la conversión fue exitosa y está en el rango, es válido.
		}
		else {
			return false; // Si el número no está en el rango, no es válido.
		}
	}
	catch (const invalid_argument& e) {
		return false; // Si la conversión falla, no es un número decimal válido.
	}
}

string entradaValidaADouble(string entrada) {
	string entradaNumerica = "", caracter;
	int NumerosFormato = 0, max = 2, puntos = 0, coma = 0;

	for (int i = 0; i < entrada.length(); i++)
	{
		if (puntos > 1)
			return "";
		if (entrada[i] != ',')
		{
			if (entrada[i] == '.')
			{
				NumerosFormato = 0;
				puntos++;
			}
			if (NumerosFormato > max)
			{
				return "";
			}
			else
			{
				entradaNumerica += entrada[i];
				NumerosFormato++;
				caracter = entrada[i];
				if (!EsNumero(caracter) && caracter != ".")
					return "";
			}
		}
		else {
			if ((coma > 0 && NumerosFormato < 3) || puntos == 1)
				return "";

			coma++;
			NumerosFormato = 0;
		}
	}

	cout << entradaNumerica << endl;
	return entradaNumerica;
}


string DecenasUnidadesEnTexto(int numero) {
	string unidades[] = { "", "Un", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve" };
	string especiales[] = { "Diez", "Once", "Doce", "Trece", "Catorce", "Quince", "Dieciséis", "Diecisiete", "Dieciocho", "Diecinueve" };
	string decenas[] = { "", "", "Veinti", "Treinta", "Cuarenta", "Cincuenta", "Sesenta", "Setenta", "Ochenta", "Noventa" };

	string texto;

	if (numero == 0) {
		texto = "";
	}
	else if (numero < 10) {
		texto = unidades[numero];
	}
	else if (numero < 20) {
		texto = especiales[numero - 10];
	}
	else {
		int decena = numero / 10;
		int unidad = numero % 10;
		if (decena == 2) {
			// Caso especial para "Veinti"
			if (unidad == 0) {
				texto = "Veinte";
			}
			else {
				texto = decenas[decena] + unidades[unidad];
			}
		}
		else if (unidad == 0) {
			texto = decenas[decena];
		}
		else {
			texto = decenas[decena] + " y " + unidades[unidad];
		}
	}
	return texto;
}


string numeroATextoRecursivo(int entradaNumero) {

	size_t Auxiliar, cien = 100, mil = 1000, millon = 1000000;
	string textoGlobal = "";

	string unidades[] = { "", "Ciento", "Doscientos", "Trescientos", "Cuatrocientos", "Quinientos", "Seiscientos", "Setecientos", "Ochocientos", "Novecientos" };

	if (entradaNumero < cien)
	{
		textoGlobal += DecenasUnidadesEnTexto(entradaNumero);
	}
	else if (entradaNumero < mil)
	{
		Auxiliar = entradaNumero / 100;
		if (entradaNumero == 100)
			textoGlobal += "Cien ";
		else
			textoGlobal += unidades[Auxiliar] + " ";

		textoGlobal += numeroATextoRecursivo(entradaNumero % 100);
	}
	else if (entradaNumero < millon)
	{
		Auxiliar = entradaNumero / 1000;
		if (Auxiliar == 1)
			textoGlobal += "Mil ";
		else
			textoGlobal += numeroATextoRecursivo(Auxiliar) + " Mil ";

		textoGlobal += numeroATextoRecursivo(entradaNumero % 1000);
	}
	else
	{
		Auxiliar = entradaNumero / millon;
		if (Auxiliar == 1)
			textoGlobal += "Un Millon ";
		else
			textoGlobal += numeroATextoRecursivo(Auxiliar) + " Millones ";

		textoGlobal += numeroATextoRecursivo(entradaNumero % 1000000);
	}
	return textoGlobal;
}

int EjecutarNumeroALetra() {

	bool continuar = true;
	double numero;
	string entrada, entradaNumerica;
	string texto;
	while (continuar)
	{
		cout << "Ingresa un numero valido (o -1 para salir): ";
		cin >> entrada;
		if (entrada == "-1") {
			continuar = false;
			continue;
		}

		entradaNumerica = entradaValidaADouble(entrada);

		if (entradaNumerica == "")
		{
			cout << "\n------Formato invalido------\n";
			continue;
		}
		else {
			numero = stod(entradaNumerica);

			//No mayor a 999,999,999.99 CONVERSION
			if (numero > 999999999.99) {
				cout << "\n------Numero muy grande------\n";
				continue;
			}

			int parte_entera = static_cast<int>(numero);
			int parte_decimal_entera = round((numero - parte_entera) * 100);

			if (parte_entera == 0)
			{
				texto = "Cero";
			}
			else
			{
				texto = numeroATextoRecursivo(parte_entera);
			}
			texto += " Pesos dominicanos con ";

			//Agregar centimos:
			if (parte_decimal_entera == 0)
			{
				texto += "Cero centavos";
			}
			else
			{
				texto += numeroATextoRecursivo(parte_decimal_entera) + " Centavos";
			}

			cout << endl << texto << endl;
		}
	}
	return 0;
}


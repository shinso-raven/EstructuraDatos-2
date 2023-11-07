using namespace std;

#include <iostream>
#include <string>


string entradaValidaADouble(string entrada) {
	string entradaNumerica = "";
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
			if (NumerosFormato >max)
			{
				return "";
			}
			else
			{
				entradaNumerica += entrada[i];
				NumerosFormato++;
			}	
		}
		else {
			if ((coma > 0 && NumerosFormato < 3)|| puntos ==1)
				return "";
			
			coma++;
			NumerosFormato = 0;
		}
	}

	cout << entradaNumerica << endl;


	return entradaNumerica;
}


string DecenasUnidadesEnTexto(int numero) {
	string unidades[] = { "", "Uno", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve" };
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
		if (entradaNumero ==100)
		{
			textoGlobal += "Cien ";
		}
		else
		{
			textoGlobal += unidades[Auxiliar] + " ";
		}
			
		textoGlobal += numeroATextoRecursivo(entradaNumero % 100);
	}
	else if( entradaNumero < millon)
	{
		Auxiliar = entradaNumero / 1000;
		if (Auxiliar == 1)
		{
			textoGlobal += "Mil ";
		}
		else
		{
			textoGlobal += numeroATextoRecursivo(Auxiliar) + " Mil ";
		}
		
		textoGlobal += numeroATextoRecursivo(entradaNumero % 1000);
	}
	else
	{
		Auxiliar = entradaNumero / millon;
		if(Auxiliar == 1)
			textoGlobal += "Un Millon ";
		else
			textoGlobal += numeroATextoRecursivo(Auxiliar) + " Millones ";

		textoGlobal += numeroATextoRecursivo(entradaNumero % 1000000);
	}
	return textoGlobal;
}

int main() {

	bool continuar = true;
	int numero;
	string entrada, entradaNumerica;
	string texto;
	while (continuar)
	{
		cout << "Indica un numero: ";
		cin >> entrada;
		//TransformarNumero();

		entradaNumerica = entradaValidaADouble(entrada);

		if (entradaNumerica =="")
		{
			cout << "\nFormato invalido";
			continue;
		}
		else {
			numero = stod(entradaNumerica);

			//No mayor a 999,999,999.99 CONVERSION
			if (numero == 0)
			{
				texto = "Cero";
			}
			else
			{
				texto = numeroATextoRecursivo(numero) + " Pesos dominicanos con ";

			}
			//Agregar centimos:
			/*
			* int parte_entera = static_cast<int>(num);

				double parte_decimal = num - parte_entera;
			*/

			cout << endl << texto << endl;
		}
	}
	return 0;
}


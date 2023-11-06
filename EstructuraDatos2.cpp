using namespace std;

#include <iostream>
#include <string>


bool EsNumeroValido(string str) {
	if (str.empty()) {
		return false;
	}

	try {
		double numero = stod(str);
		return true; // Si la conversi�n fue exitosa, es un n�mero decimal v�lido.
	}
	catch (const invalid_argument& e)
	{
		return false; // Si la conversi�n falla, no es un n�mero decimal v�lido.
	}
}
int* obtenerprimerasubdivision(double num) {
	int* arreglo = new int[7]; // Asigna din�micamente un arreglo de 7 enteros

	// Obtener la parte entera del n�mero
	int parte_entera = static_cast<int>(num);

	// Obtener la parte decimal del n�mero
	double parte_decimal = num - parte_entera;

	// Calcular la subdivisi�n
	arreglo[0] = (parte_entera / 100000000); // Centenas de millones
	arreglo[1] = (parte_entera % 100000000) / 1000000; // Decenas y unidades de mill�n
	arreglo[2] = ((parte_entera % 1000000) / 100000); // Centenas de miles
	arreglo[3] = (parte_entera % 100000) / 1000; // Decenas y unidades de miles
	arreglo[4] = (parte_entera / 100) % 10; // Centenas
	arreglo[5] = parte_entera % 100; // Decenas y unidades
	arreglo[6] = parte_decimal * 100; // Decimales
	return arreglo;
}

string CentenasEnTexto(int centena)
{
	string unidades[] = { "Cero", "Cien", "Doscientos", "Trescientos", "Cuatrocientos", "Quinientos", "Seiscientos", "Setecientos", "Ochocientos", "Novecientos" };

	return unidades[centena];
}

string DecenasUnidadesEnTexto(int numero) {
	string unidades[] = { "Cero", "Uno", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve" };
	string especiales[] = { "Diez", "Once", "Doce", "Trece", "Catorce", "Quince", "Diecis�is", "Diecisiete", "Dieciocho", "Diecinueve" };
	string decenas[] = { "", "", "Veinti", "Treinta", "Cuarenta", "Cincuenta", "Sesenta", "Setenta", "Ochenta", "Noventa" };

	string texto;

	if (numero == 0) {
		texto = "Cero";
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

void finality(int* arr)
{
	string texto;
	string nomenclatura[] = { " Millones ", " mil "," Pesos dominicanos con ", " Centimos " };

	for (size_t i = 0; i < 7; i++)
	{
		if (arr[i] == 0 && i != 6)
		{
			continue;
		}

		if (i % 2 == 0 && i < 6)
		{
			texto += CentenasEnTexto(arr[i]);
			if (arr[i] == 1 && arr[i + 1] != 0)
			{
				texto += "to";
			}

		}
		else
		{
			texto += DecenasUnidadesEnTexto(arr[i]);
		}

		if (i == 1)
		{
			texto += nomenclatura[0];
		}
		else if (i == 3)
		{
			texto += nomenclatura[1];

		}
		else if (i == 5)
		{
			texto += nomenclatura[2];
		}

		else if (i == 6)
		{
			texto += nomenclatura[3] + " ";

		}
		else
		{
			texto += " ";

		}



	}

	cout << texto;
	cout << endl;

}


string numeroATextoRecursivo(size_t entradaNumero) {

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
		if (Auxiliar ==100)
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

void TransformarNumero() {
	double numero;
	string entrada;
	bool invalido = true;

	while (invalido) {
		cout << "Ingresa un n�mero v�lido: ";
		cin >> entrada;

		if (EsNumeroValido(entrada)) {
			numero = stod(entrada);
			break;
		}
		else {
			cout << "No has ingresado un n�mero v�lido. Int�ntalo de nuevo." << endl;
		}
	}


	int* resultado = obtenerprimerasubdivision(numero);


	for (size_t i = 0; i < 7; i++)
	{
		cout << resultado[i] << " ";
	}

	cout << endl;

	finality(resultado);

	delete[] resultado;
}

int main() {

	bool continuar = true;
	size_t numero;
	string texto;
	while (continuar)
	{
		cout << "Indica un numero: ";
		cin >> numero;
		//TransformarNumero();
		
		//No mayor a 999,999,999.99
		if (numero ==0)
		{
			texto = "Cero";
		}
		else
		{
			texto = numeroATextoRecursivo(numero) + " Pesos dominicanos con ";

		}
		//Agregar centimos:


		cout << endl << texto<< endl;
	}
	return 0;
}


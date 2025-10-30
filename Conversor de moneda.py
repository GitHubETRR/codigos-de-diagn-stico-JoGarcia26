def obtener_tasa(codigo_moneda):
    """
    esto retorna cuántos pesos argentinos (ARS) vale 1 unidad de la moneda indicada.
    Actualizadas a octubre 2025.
    """
    tasas = {
        "USD": 1490.0,   # Dólar USA
        "EUR": 1732.0,   # Euro
        "GBP": 1987.0,   # Libra esterlina
        "JPY": 9.8       # Yen 
    }
    return tasas.get(codigo_moneda.upper(), None)

def convertir_a_pesos(importe, moneda):
    """
    convierte el importe indicado en la moneda extranjera seleccionada a pesos argentinos.
    """
    tasa = obtener_tasa(moneda)
    if tasa is None:
        print(f"No conozco la tasa de cambio para {moneda}.")
        return None
    return importe * tasa

def main():
    print(" Conversor a Pesos Argentinos ")
    print("Monedas disponibles: USD, EUR, GBP, JPY")
    
    moneda = input("Que moneda tiene (USD, EUR, GBP, JPY): ").upper()
    importe = float(input(f"Ingrese la cantidad en {moneda}: "))
    
    resultado = convertir_a_pesos(importe, moneda)
    if resultado is not None:
        print(f"\n {importe:.2f} {moneda} equivalen a {resultado:,.2f} pesos argentinos (ARS).")

if __name__ == "__main__":
    main()

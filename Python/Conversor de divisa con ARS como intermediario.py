def obtener_tasa(codigo_moneda):
    """
    esto retorna la tasa de cambio de 1 unidad de la moneda dada a ARS.
    Las tasas están en ARS por unidad de moneda extranjera.
    """
    tasas = {
        "USD": 1490.0,   # Dólar USA
        "EUR": 1732.0,   # Euro
        "GBP": 1987.0,   # Libra esterlina
        "JPY": 9.8       # Yen
    }
    return tasas.get(codigo_moneda.upper(), None)

def convertir(importe, desde, hacia):
    """
    convierte un importe de una moneda 'desde' a otra moneda 'hacia',
    usando ARS como moneda intermedia.
    """
    desde = desde.upper()
    hacia = hacia.upper()
    tasa_desde = obtener_tasa(desde)
    tasa_hacia = obtener_tasa(hacia)

    if tasa_desde is None or tasa_hacia is None:
        print(f"No conozco la tasa para alguna de las monedas: {desde} o {hacia}")
        return None

    importe_ars = importe * tasa_desde
    resultado = importe_ars / tasa_hacia
    return resultado

def main():
    print("Conversor de monedas con base en ARS 🇦🇷")
    importe = float(input("Ingrese el importe a convertir: "))
    desde = input("Moneda origen (USD, EUR, GBP, JPY): ")
    hacia = input("Moneda destino (USD, EUR, GBP, JPY): ")
    resultado = convertir(importe, desde, hacia)
    if resultado is not None:
        print(f"{importe:.2f} {desde.upper()} equivalen a {resultado:.2f} {hacia.upper()}")

if __name__ == "__main__":
    main()

import secrets
import string

def generar_contraseña(longitud=12, usar_mayus=True, usar_minus=True,
                       usar_digitos=True, usar_simbolos=True,
                       evitar_ambiguos=True):
    if longitud < 4:
        raise ValueError("La longitud mínima recomendada es 4 caracteres.")
    
    mayus = string.ascii_uppercase
    minus = string.ascii_lowercase
    digitos = string.digits
    simbolos = string.punctuation
    ambiguos = "Il1O0`'\".,;:/\\|"
    
    pool = ""
    if usar_mayus: pool += mayus
    if usar_minus: pool += minus
    if usar_digitos: pool += digitos
    if usar_simbolos: pool += simbolos
    
    if evitar_ambiguos:
        pool = ''.join(ch for ch in pool if ch not in ambiguos)
        mayus = ''.join(ch for ch in mayus if ch not in ambiguos)
        minus = ''.join(ch for ch in minus if ch not in ambiguos)
        digitos = ''.join(ch for ch in digitos if ch not in ambiguos)
        simbolos = ''.join(ch for ch in simbolos if ch not in ambiguos)
    
    if not pool:
        raise ValueError("No hay caracteres disponibles para generar la contraseña.")
    
    contraseña = []
    tipos = []
    if usar_mayus: tipos.append(mayus)
    if usar_minus: tipos.append(minus)
    if usar_digitos: tipos.append(digitos)
    if usar_simbolos: tipos.append(simbolos)
    
    for grupo in tipos:
        if len(contraseña) < longitud:
            contraseña.append(secrets.choice(grupo))
    
    while len(contraseña) < longitud:
        contraseña.append(secrets.choice(pool))
    
    secrets.SystemRandom().shuffle(contraseña)
    return ''.join(contraseña)

def generar_varias(n=5, **kwargs):
    return [generar_contraseña(**kwargs) for _ in range(n)]

if __name__ == "__main__":
    print("Generador de contraseñas seguras")
    
    while True:
        entrada = input("Longitud deseada (ej: 12): ").strip()
        if entrada.isdigit() and int(entrada) >= 4:
            longitud = int(entrada)
            break
        print("Por favor ingresa un número entero mayor o igual a 4.")
    
    while True:
        entrada = input("¿Cuántas contraseñas generar? (ej: 5): ").strip()
        if entrada.isdigit() and int(entrada) > 0:
            n = int(entrada)
            break
        print("Por favor ingresa un número entero mayor que 0.")
    
    evitar_ambiguos = input("Evitar caracteres ambiguos? (s/n) [s]: ").strip().lower() != 'n'
    usar_simbolos = input("Incluir símbolos/puntuación? (s/n) [s]: ").strip().lower() != 'n'
    
    contraseñas = generar_varias(n, longitud=longitud, evitar_ambiguos=evitar_ambiguos, usar_simbolos=usar_simbolos)
    
    print("\nContraseñas generadas:")
    for i, pwd in enumerate(contraseñas, 1):
        print(f"{i}. {pwd}")
    
    try:
        import pyperclip
        pyperclip.copy(contraseñas[0])
        print("\nLa primera contraseña fue copiada al portapapeles (pyperclip).")
    except Exception:
        pass

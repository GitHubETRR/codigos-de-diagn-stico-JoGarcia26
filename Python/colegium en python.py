alumnos = {}

def cargar_datos_txt():
    global alumnos
    alumnos = {}
    try:
        with open("alumnos.txt", "r") as f:
            lineas = f.readlines()
    except FileNotFoundError:
        print("No existe archivo alumnos.txt, iniciando vacío.\n")
        return

    alumno_actual = None
    for linea in lineas:
        linea = linea.strip()
        if linea == "":
            alumno_actual = None
            continue
        if linea == "# Alumno":
            continue
        if alumno_actual is None:
            alumno_actual = linea
            alumnos[alumno_actual] = {"materias": {}}
            continue
        if ":" in linea:
            materia, notas = linea.split(":", 1)
            materia = materia.strip()
            notas = notas.strip().split()
            notas_f = []
            for n in notas:
                try:
                    notas_f.append(float(n))
                except ValueError:
                    pass
            alumnos[alumno_actual]["materias"][materia] = notas_f
        else:
            # Línea inesperada: la ignoramos (por seguridad)
            continue

    print("Datos cargados desde alumnos.txt\n")

def guardar_datos_txt():
    with open("alumnos.txt", "w") as f:
        for alumno, datos in alumnos.items():
            f.write("# Alumno\n")
            f.write(alumno + "\n")

            for materia, notas in datos["materias"].items():
                notas_str = " ".join(map(str, notas))
                f.write(f"{materia}: {notas_str}\n")

            f.write("\n")
    print("Datos guardados en alumnos.txt\n")
    
def agregar_alumno():
    nombre = input("Nombre del alumno: ").capitalize().strip()
    if nombre == "":
        print("Nombre vacío. Operación cancelada.\n")
        return
    if nombre in alumnos:
        print("El alumno ya está registrado.\n")
        return
    alumnos[nombre] = {
        "materias": {}
    }
    print(f"Alumno {nombre} agregado.\n")

def agregar_materia():
    nombre = input("Nombre del alumno: ").capitalize().strip()
    if nombre not in alumnos:
        print("El alumno no está registrado.\n")
        return

    materia = input("Nombre de la materia: ").capitalize().strip()
    if materia == "":
        print("Nombre de materia vacío.\n")
        return

    if materia in alumnos[nombre]["materias"]:
        print("La materia ya existe para este alumno.\n")
    else:
        alumnos[nombre]["materias"][materia] = []
        print(f"Materia {materia} agregada a {nombre}.\n")

def agregar_nota():
    nombre = input("Nombre del alumno: ").capitalize().strip()
    if nombre not in alumnos:
        print("El alumno no está registrado.\n")
        return

    materia = input("Materia: ").capitalize().strip()

    if materia not in alumnos[nombre]["materias"]:
        print("La materia no existe para este alumno.\n")
        return

    entrada = input("Ingrese la nota: ").strip()
    try:
        nota = float(entrada)
    except ValueError:
        print("Valor inválido. La nota debe ser un número.\n")
        return

    alumnos[nombre]["materias"][materia].append(nota)
    print(f"Nota {nota} agregada a {materia} de {nombre}.\n")

def mostrar_promedio():
    nombre = input("Nombre del alumno: ").capitalize().strip()
    if nombre not in alumnos:
        print("El alumno no está registrado.\n")
        return

    materia = input("Materia: ").capitalize().strip()
    if materia not in alumnos[nombre]["materias"]:
        print("El alumno no tiene esa materia.\n")
        return

    notas = alumnos[nombre]["materias"][materia]
    if not notas:
        print("No hay notas cargadas.\n")
        return
    promedio = sum(notas) / len(notas)
    print(f"Promedio de {nombre} en {materia}: {promedio:.2f}\n")

def listar_alumnos():
    if not alumnos:
        print("No hay alumnos registrados.\n")
        return
    for nombre, datos in alumnos.items():
        print(f"Alumno: {nombre}")
        for materia, notas in datos["materias"].items():
            print(f"  {materia}: {notas}")
    print()

if __name__ == "__main__":
    cargar_datos_txt() 
    try:
        while True:
            print("///Colegium///")
            print("1. Agregar alumno")
            print("2. Agregar materia")
            print("3. Agregar nota")
            print("4. Mostrar promedio por materia")
            print("5. Listar alumnos")
            print("6. Guardar datos en alumnos.txt")
            print("7. Salir (guarda automáticamente)")

            opcion = input("Elija opcion: ").strip()
            
            if opcion == "1":
                agregar_alumno()
            elif opcion == "2":
                agregar_materia()
            elif opcion == "3":
                agregar_nota()
            elif opcion == "4":
                mostrar_promedio()
            elif opcion == "5":
                listar_alumnos()
            elif opcion == "6":
                guardar_datos_txt()
            elif opcion == "7":
                guardar_datos_txt()
                print("Saliendo...")
                break
            else:
                print("Opción inválida.\n")
    except KeyboardInterrupt:
        print("\nInterrumpido por usuario. Guardando datos...")
        guardar_datos_txt()
        print("Guardado")

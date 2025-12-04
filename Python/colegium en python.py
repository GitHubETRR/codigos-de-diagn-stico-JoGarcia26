alumnos={}

def agregar_alumno():
    nombre = input("Nombre del alumno: ").capitalize().strip()
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

    nota = float(input("Ingrese la nota: "))
    alumnos[nombre]["materias"][materia].append(nota)
    print(f"Nota {nota} agregada a {materia} de {nombre}.\n")

def mostrar_promedio():
    nombre = input("Nombre del alumno: ")
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
    
while True:
    print("///Colegium///")
    print("1. Agregar alumno")
    print("2. Agregar materia")
    print("3. Agregar nota")
    print("4. Mostrar promedio por materia")
    print("5. Listar alumnos")
    print("6. Salir")

    opcion = input("Elija opción: ")

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
        break
    else:
        print("Opción inválida.\n")

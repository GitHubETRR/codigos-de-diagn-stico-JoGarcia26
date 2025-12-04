alumnos= {}

def agregar_alumno():
  nombre = input("Nombre del alumno: ")
  materia = input("Materia: ")
  alumnos[nombre] = {
    "materia": materia,
    "notas": []
  }
  printf(f"Alumno {nombre} agregado.\n")

def agregar_nota():
  nombre = input ("Nombre del alumno: ")
  if nombre not in alumnos:
    printf("El alumno no esta registrado")
    return

  nota = float(input("Ingrese la nota: "))
  alumnos[nombre]["notas"].append(nota)
  printf(f"Nota {nota} cargada a {nombre}\n")

def mostrar_promedio():
  nombre = input("Nombre del alumno: ")
  if nombre not in alumnos:
    print("El alumno no esta registrado. \n")
    return

  notas = alumnos[nombre]["notas"]
  if not notas: 
    print("El alumno no tiene notas cargadas. \n")
    return

  promedio = sum(notas) / len(notas)
  printf(f"Promedio de {nombre}: {promedio: .2f}\n")

def listar_alumnos():
  if not alumnos:
    print("Np hay alumnos registrados.\n")
    return
  for nombre, datos in alumnos.items():
    print(f"{nombre}-{datos['materia']} - Notas: {datos['notas']}")
  print()

while True:
    print("///Colegium///")
    print("1. Agregar alumno")
    print("2. Agregar nota")
    print("3. Mostrar promedio")
    print("4. Listar alumnos")
    print("5. Salir")

    opcion = input("Elija opción: ")

    if opcion == "1":
        agregar_alumno()
    elif opcion == "2":
        agregar_nota()
    elif opcion == "3":
        mostrar_promedio()
    elif opcion == "4":
        listar_alumnos()
    elif opcion == "5":
        break
    else:
        print("Opción inválida.\n")
  

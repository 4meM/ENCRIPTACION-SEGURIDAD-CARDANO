# -*- coding: cp1252 -*-

import os

def atbash_descifrar(texto: str) -> str:
    resultado = []
    for ch in texto:
        if 'a' <= ch <= 'z':
            resultado.append(chr(ord('z') - (ord(ch) - ord('a'))))
        elif 'A' <= ch <= 'Z':
            resultado.append(chr(ord('Z') - (ord(ch) - ord('A'))))
        else:
            resultado.append(ch)
    return ''.join(resultado)

if __name__ == "__main__":
    input_file = "ENTRADA_ATBASH.txt"
    output_file = "SALIDA_ATBASH.txt"

    print("Seleccione modo:")
    print("1. Ingresar texto por consola")
    print("2. Leer desde archivo ENTRADA_ATBASH.txt")
    opcion = input("Opcion (1/2): ").strip()

    if opcion == "1":
        texto = input("Ingrese texto cifrado: ")
        with open(input_file, "w", encoding="utf-8") as f:
            f.write(texto)

    elif opcion == "2":
        if not os.path.exists(input_file):
            print(f"No existe {input_file}. Cree el archivo o use la opcion 1.")
            exit(1)
        with open(input_file, "r", encoding="utf-8") as f:
            texto = f.read().strip()
    
    else:
        print("Opcion invalida.")
        exit(1)

    descifrado = atbash_descifrar(texto)

    with open(output_file, "w", encoding="utf-8") as f:
        f.write(descifrado)

    print(f"Texto original       : {texto}")
    print(f"Texto descifrado     : {descifrado}")
    print(f"Resultado guardado en {output_file}")

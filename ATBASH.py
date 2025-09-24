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
    ejemplo = input("Ingrese texto cifrado: ")

    descifrado = atbash_descifrar(ejemplo)
    print("Texto original:", ejemplo)
    print("Texto descifrado:", descifrado)


# MazeECE

Petit projet C pour générer/faire fonctionner un labyrinthe (projet étudiant).

## Description

Ce dépôt contient une implémentation minimale en C d'un programme lié à un labyrinthe. Le point d'entrée est `main.c` et la compilation est gérée avec CMake.

## Prérequis

- CMake (>= 3.15 recommandé)
- Un compilateur C (GCC, Clang ou MSVC)
- Ninja (recommandé) ou tout générateur supporté par CMake

Sur Windows, utilisez PowerShell (les exemples ci-dessous sont pour PowerShell).

## Construire le projet (PowerShell)

1. Créez un dossier de build puis configurez avec CMake (générateur Ninja dans cet exemple) :

```powershell
cmake -S . -B build -G "Ninja"
```

2. Construisez :

```powershell
cmake --build build
```

3. L'exécutable `main` (ou `main.exe` sous Windows) sera généré dans le dossier `build` ou selon la configuration de CMake.

## Exécuter

Depuis PowerShell (depuis la racine du projet) :

```powershell
# si l'exécutable est dans build/Debug ou build/
Set-Location build
.\main.exe
```

ou directement :

```powershell
build\main.exe
```

Remplacez le chemin et le nom d'exécutable selon la configuration de build utilisée.

## Structure du dépôt

- `CMakeLists.txt` - configuration de build CMake
- `main.c` - point d'entrée du programme
- `cmake-build-debug/` - dossier généré par un environnement (e.g. CLion) contenant les fichiers de build

## Tests et développement

Ce petit projet n'inclut pas encore de suite de tests automatisés. Pour du développement local, construire avec CMake comme indiqué et exécuter `main`.

## Contribution

Si vous souhaitez améliorer le projet :

1. Ouvrez une issue décrivant votre proposition.
2. Faites une branche, implémentez les changements, exécutez les tests locaux (si ajoutés) et soumettez une pull request.

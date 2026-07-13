# Simple Remote

Une télécommande physique minimaliste pour piloter un **Player Freebox Pop** via le réseau local.

Le projet est développé en **C++17** dans le but d'être porté par la suite sur un **ESP32**. Le développement commence par une application en ligne de commande afin de valider les échanges avec la Freebox avant de passer à la partie matérielle.

---

## Fonctionnalités prévues

- Authentification à l'API Freebox
- Découverte automatique du Player
- Changement de chaîne
- Contrôle du volume
- Navigation (OK, Haut, Bas, Gauche, Droite, Retour, Home...)
- Portage sur ESP32

---

## Prérequis

### Windows

Installer les outils suivants :

- MSYS2 (UCRT64)
- GCC
- CMake
- Ninja
- Git
- Visual Studio Code (optionnel mais recommandé)

Vérifier que les commandes suivantes fonctionnent :

```bash
g++ --version
cmake --version
ninja --version
git --version
```

---

## Cloner le projet

```bash
git clone git@github.com:Catoire-dev/SimpleRemote.git
cd SimpleRemote
```

---

## Compilation

### Générer le projet

```bash
cmake --preset default
```

### Compiler

```bash
cmake --build --preset default
```

---

## Exécution

Sous Windows :

```bash
./build/SimpleRemote.exe
```

---

## Structure du projet

```text
SimpleRemote/
│
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── src/
│   └── main.cpp
└── build/
```

---

## Nettoyer le projet

Supprimer le dossier `build`.

Sous PowerShell :

```powershell
Remove-Item -Recurse -Force build
```

---

## Roadmap

- [x] Initialisation du projet
- [ ] Communication HTTP
- [ ] Authentification Freebox
- [ ] Découverte automatique du Player
- [ ] Contrôle du Player
- [ ] Changement de chaîne
- [ ] Gestion du volume
- [ ] Portage ESP32

---
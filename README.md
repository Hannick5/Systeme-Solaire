# Système Solaire

![image1](https://github.com/Hannick5/Systeme-Solaire/assets/61098254/9a44c9a3-d0cb-4292-a2ec-c5067ffbebbf)


## Introduction

Ce fichier README explique comment compiler et exécuter l'application sur le système d'exploitation Linux.

## Prérequis
Assurez-vous d'avoir les éléments suivants installés sur votre système avant de procéder à la compilation et à l'exécution de l'application :

- **Compilateur C++ :** Assurez-vous d'avoir un compilateur C++ compatible avec le standard C++11 ou supérieur. G++ est recommandé.
- **Bibliothèques :** Assurez-vous d'avoir installé les bibliothèques nécessaires. Vous pouvez les installer avec les commandes suivantes :
    ```bash
    sudo apt-get update
    sudo apt-get install libglfw3-dev libglm-dev libglew-dev
    ```

## Compilation
Suivez ces étapes pour compiler l'application sur Linux :

1. Ouvrez un terminal dans le répertoire de votre application.
2. Exécutez la commande suivante pour compiler l'application :
    ```bash
    g++ -std=c++11 -o nom_de_sortie main.cpp -lglfw -lGL -lGLEW
    ```
    Remplacez `nom_de_sortie` par le nom souhaité pour le fichier exécutable et `main.cpp` par le nom de votre fichier source.

## Exécution
Après la compilation, suivez ces étapes pour exécuter l'application :

1. Exécutez la commande suivante dans le terminal :
    ```bash
    ./nom_de_sortie
    ```
    Remplacez `nom_de_sortie` par le nom que vous avez choisi pour le fichier exécutable.

## Remarques
- Assurez-vous d'ajuster les options de compilation en fonction des besoins de votre application.
- Vous pouvez également ajouter des instructions supplémentaires ici si votre application nécessite des configurations spécifiques.


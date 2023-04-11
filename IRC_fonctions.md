# irssi

 - port 6697 avec TLS
 - port 6667 sans chiffrement


# Commandes a utiliser

/connect OFTC

/join #debian

/say <mon message>

/bye

/quit



---



# des infos sur des fonctions et cie

## recv
La fonction recv en C++ est utilisée pour recevoir des données d'un socket. Dans le cas d'un serveur IRC, elle serait utilisée pour recevoir des messages envoyés par les clients connectés au serveur.

Lorsqu'elle est appelée, la fonction recv attend jusqu'à ce qu'elle reçoive des données sur le socket. Les données reçues sont stockées dans un tampon spécifié, et la fonction renvoie le nombre d'octets de données reçus.

Dans le contexte d'un serveur IRC, la fonction recv serait appelée sur le socket qui a été créé pour écouter les connexions des clients. Lorsqu'un client se connecte, le serveur crée un nouveau socket pour gérer la communication avec ce client. La fonction recv serait alors appelée sur ce nouveau socket pour recevoir les messages envoyés par le client. Le serveur peut ensuite traiter ces messages et envoyer des réponses appropriées au client.

Voici le prototype de la fonction recv en C++ :

c++
```
#include <sys/socket.h>

ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```
Les paramètres de la fonction sont les suivants :

    sockfd : le descripteur de fichier du socket à partir duquel recevoir des données.
    buf : le tampon dans lequel stocker les données reçues.
    len : la taille maximale des données à recevoir.
    flags : des indicateurs de contrôle supplémentaires, tels que MSG_WAITALL pour attendre que toutes les données demandées soient disponibles avant de les renvoyer.

La fonction renvoie le nombre d'octets de données reçus, qui peut être inférieur à la taille maximale spécifiée dans len. Si elle renvoie une valeur de 0, cela indique que la connexion a été fermée par le côté distant. Si elle renvoie -1, cela indique qu'une erreur s'est produite et la raison de l'erreur peut être récupérée en appelant la fonction errno.

# quelle soit les toutes premieres donnee qu'envoie un client lors de la connection

Lorsqu'un client se connecte à un serveur IRC, il envoie une série de messages au serveur pour établir la connexion et s'identifier auprès du serveur. Voici les premiers messages envoyés par un client lorsqu'il se connecte à un serveur IRC :

    Le client envoie un message PASS (mot de passe) s'il est nécessaire de fournir un mot de passe pour se connecter au serveur. Le message a la forme suivante :



PASS <mot_de_passe>

Le client envoie un message NICK (pseudo) pour indiquer le pseudo qu'il souhaite utiliser sur le serveur. Le message a la forme suivante :



NICK <pseudo>

Le client envoie un message USER pour fournir des informations d'identification supplémentaires. Le message a la forme suivante :



    USER <identifiant> <hôte> <serveur> <nom réel>

        <identifiant> : un identifiant unique pour le client, souvent le même que le pseudo.
        <hôte> : le nom d'hôte ou l'adresse IP du client.
        <serveur> : le nom d'hôte ou l'adresse IP du serveur IRC.
        <nom réel> : le nom réel du client.

Une fois que ces messages ont été envoyés avec succès, le serveur répondra avec un message 001 pour confirmer la connexion et donner la bienvenue au client sur le serveur.


#std::istringstream
std::istringstream est une classe de la bibliothèque standard C++ qui permet de traiter une chaîne de caractères comme un flux d'entrée, de la même manière que std::cin peut être utilisé pour traiter l'entrée à partir de la console.

La classe std::istringstream est définie dans l'en-tête <sstream> et hérite de la classe std::basic_istringstream, qui est un tampon d'entrée basé sur une chaîne de caractères (std::basic_string).

Pour utiliser std::istringstream, vous pouvez créer une instance de la classe en passant une chaîne de caractères dans le constructeur. Vous pouvez ensuite extraire des valeurs à partir de cette instance en utilisant l'opérateur >> de flux d'entrée, tout comme vous le feriez avec std::cin.

Voici un exemple de code qui utilise std::istringstream pour extraire un entier à partir d'une chaîne de caractères :

c++

#include <sstream>
#include <iostream>
#include <string>

int main() {
    std::string inputStr = "42";
    std::istringstream iss(inputStr);
    int value;
    iss >> value;
    std::cout << "La valeur extraite est : " << value << std::endl;
    return 0;
}

L'exemple ci-dessus crée un objet std::istringstream à partir de la chaîne "42", extrait l'entier 42 à partir de l'objet et l'affiche à la console.

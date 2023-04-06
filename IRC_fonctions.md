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



## des infos sur des fonctions

# recv
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

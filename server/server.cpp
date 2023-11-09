//
// Created by jojo on 09/11/23.
//

#include "server.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

bool handleNewConnection(int clientSocket) {
    // Met en œuvre le traitement pour la nouvelle connexion
    std::cout << "Nouvelle connexion établie !" << std::endl;

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));  // Assure que le tampon est initialisé

    // Boucle de lecture des données de la socket cliente
    ssize_t bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        std::string t = "";
        // Affiche les données reçues
        for(int i = 0; i< 1024; i++){
            if( (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z' ) ){
                std::cout << buffer[i] << std::endl;
                t.push_back(buffer[i]);
            }

        }
        if(t == "shutdown"){
            close(clientSocket);
            return true;
        }
        std::cout << "Message reçu du client : " << std::endl;
        //printf("%s", tamere.c_str());

        // Tu peux traiter les données ici selon tes besoins

        // Nettoie le tampon pour la prochaine lecture
        memset(buffer, 0, sizeof(buffer));
    }

    if (bytesRead == 0) {
        std::cout << "La connexion a été fermée par le client." << std::endl;
    } else {
        std::cerr << "Erreur lors de la réception des données." << std::endl;
    }
    return false;
}

int tamerelapute() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Erreur lors de la création de la socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddress;
    int port = 12345;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la liaison de la socket à l'adresse" << std::endl;
        close(serverSocket);
        return -1;
    }

    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Erreur lors de l'attente de connexions" << std::endl;
        close(serverSocket);
        return -1;
    }

    //printf("Attente de connexions sur le port %d...",port);
    std::cout << "Attente de connexions sur le port " << port << std::endl;
    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            std::cerr << "Erreur lors de l'acceptation de la connexion" << std::endl;
            continue;  // Passe à la prochaine itération de la boucle
        }

        // Nouvelle connexion acceptée, lance la fonction de traitement
        if(handleNewConnection(clientSocket)){
            break;
        }
    }
    close(serverSocket);

    // N'arrivera jamais ici, mais c'est une bonne pratique de fermer les sockets

    return 0;
}
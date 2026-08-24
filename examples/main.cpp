/*
** EPITECH PROJECT, 2026
** Blackbox
** File description:
** main
*/

#include "blackbox/Logger.hpp"

#include <chrono>
#include <thread>

int main()
{
    blackbox::Logger::instance().init("app.log", blackbox::LogLevel::TRACE);

    LOG_INFO("Programme principal lance");
    LOG_TRACE("Trace de debug : valeur x = " << 42);
    LOG_DEBUG("Connexion active sur le port " << 8080);
    LOG_WARN("Attention : charge CPU a " << 87.5 << "%");
    LOG_ERROR("Erreur detectee : " << "Fichier introuvable");
    LOG_FATAL("Arret critique du module");

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return 0;
}
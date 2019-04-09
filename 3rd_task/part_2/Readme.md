# Первая часть: сборка телеграм-бота.
---
### Сборка
  - Необходимо скачать и разархивировать данный проект.
  - Добавить права для запуска build-execute.sh: chmod +x build-execute.sh
  - Запустить build-execute.sh.
---
### Проблемы, возникшие при выполнении задания:
  - Установка различных библиотек: 
    1. Boost - sudo apt-get install libboost-system-dev
    2. OpenSSL - sudo apt-get install libssl-dev
    3. CURL - libcurl4-openssl-dev) 
    4. Sendmail - sudo apt-get install sendmail*
    5. GnuTLS - sudo apt-get install gnutls*
 - Изменение файла Decorator/cpp-source/vmime_project-prefix/src/vmime_project/CMakeLists.txt (добавление FORCE в SendMail) для избежания ошибки.
 - Замена протокола smtp на smtps в EmailNotifier.cpp.
 - Использование VPN.
---
### Почта: tpsendmail@gmail.com, password = test_password_TP
---
### Tg bot: TP_zabot, chanel = TP_myzabot, token = 822905900:AAFlWZSVozmwefSJmquWe738QHpY3vJ-hIs, chat_id = -1001180066368
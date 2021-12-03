web_server
---
*42 project, recoding our own web server in C++. A program capable of running an HTTP server, handling requests, and parsing configuration files.*

Team : [sgath](https://github.com/yukovalski), [ctragula](https://github.com/web-sonic), [msamual](https://github.com/msamual)

`Subject:`

[RU](https://github.com/yukovalski/web_serv/blob/main/.doc/ru.subject.md)

[EN](https://github.com/yukovalski/web_serv/blob/main/.doc/en.subject.pdf)

[`Checklist`](https://github.com/yukovalski/web_serv/blob/main/.doc/webserver_check_list.pdf)

---

## Физический уровень.

Основные способы подключения к интернету и их стандарты(протоколы):
- `IEEE 802.3` - стандарт Ethernet
- `IEEE 802.11` - стандарт Wi-Fi
- `GSM` - стандарт сотовой связи
  
## Канальный уровень.
Основные протоколы:
- `ARP` - протокол построение таблицы соответствия mac-адресов и ip-адресов. Необходим для привязки ip-адреса к компьютеру(к сетевой карте компьютера). Используется в многоточечных соединениях.
- `PPP` - Используется в соединениях точка-точка. Определяет структуру кадра и способ контроля его целостности. Также определяет правила установки соединения и проверки состояния сети.
  
 `IP` - internetworking protocol(межсетевой протокол)
  
 `октет` - байт, состоящий из 8 битов.
 
 `network gateway` - сетевой шлюз, компьютер который является пропускным пунктом в сети.
  
 `Сокет` - это объект, созданный по рецепту, который по своей сути является шаблоном на основе которого формируются пакеты данных.
  
 `Сокеты` - это де-факто стандарт интерфейсов для транспортной подсистемы
 

<details>
<summary>
`Summary`
</summary>

[`Интерфейс сокетов | Курс "Компьютерные сети". Созыкин`](https://www.youtube.com/watch?v=_vAjHdh92YU)

[`Web сокеты | Компьютерные сети. Продвинутые темы. Созыкин`](https://www.youtube.com/watch?v=TxVriqBkqbM)

[`Изучение С++. Часть 1. Уроки С++`](https://www.youtube.com/watch?v=A4y97MTqO6c)

[`Изучение С++. Часть 2. Уроки С++`](https://www.youtube.com/watch?v=zsyXZLJQ_Dg)

[`C++ Web Server from Scratch | Part 1: Creating a Socket Object`](https://www.youtube.com/watch?v=YwHErWJIh6Y)

---

[` SSL Programming Tutorial`](https://support.hpe.com/hpesc/public/docDisplay?docId=emr_na-c04622320) .................................59

[`HTTP учебник`](https://developer.mozilla.org/ru/docs/Web/HTTP )

[`select / poll / epoll: практическая разница`](https://habr.com/ru/company/infopulse/blog/415259/)

[`Mongoose - easy to use web server`](https://code.google.com/archive/p/mongoose/)

[`Веб-сервер на C++ и сокетах`](https://code-live.ru/post/cpp-http-server-over-sockets/)

[`WebServer как тестовое задание`](https://habr.com/ru/post/152345/)

[`+ forum`](http://rsdn.org/forum/job/4795893.flat)

[`HTTP Server: Everything you need to know to Build a simple HTTP server from scratch`](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)

[`Hypertext Transfer Protocol -- HTTP/1.1`](https://www.ietf.org/rfc/rfc2616.txt)


RFC:
[7230](https://efim360.ru/rfc-7230-protokol-peredachi-giperteksta-http-1-1-sintaksis-soobshheniya-i-marshrutizacziya/)	
[7231]()	
[7232]()
[7233]()
[7234]()
[7235]()

---

https://adrienblanc.com/projects/42/webserv

http://dwise1.net/pgm/sockets/blocking.html




 </details>

<details>
<summary>
`Todolist`
</summary>
[ ] Создать сокет

[ ] Привязать сокет к сетевому интерфейсу

[ ] Прослушивать сокет, привязанный к определенному сетевому интерфейсу

[ ] Принимать входящие соединения

[ ] Реагировать на события происходящие на сокетах
  



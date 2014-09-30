Hartje met website
==================

Een hartje, samengesteld uit rgbleds, waar bij via een website de kleuren, de beweging en de snelheid bestuurd worden.

In de uitleg wordt ingegaan op neoPixels en de arduino Yun in clientmode (via polling om de 15 seconden een nieuw commando gaan ophalen).
Er komt geen uitleg over wat Arduino en dergelijke is, je hebt best al een paar eenvoudige projectjes met de Arduino Uno achter de rug.
Alles wat nieuw is voor de Yun, wordt uitgelegd.

# neoPixels
- [neoPixels](http://www.adafruit.com/category/168) zijn rgb-leds die individueel adresseerbaar zijn, wat wil zeggen dat je ze eenvoudig in één kring kan verbinden, maar toch individueel een kleur kan geven of aan/uit zetten.
- Om ze in een Arduino project te gebruiken, download je de [neoPixel library](https://github.com/adafruit/Adafruit_NeoPixel) [(directe link naar de zip)](https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip). Hier [een uitleg over hoe je libraries toevoegt aan je Arduino IDE](http://arduino.cc/en/Guide/Libraries).
- Een neoPixel heeft vier soldeerpunten
![neoPixel layout](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/neopixelv2.png)
- Je maakt van de neoPixels een ketting door alle Vcc-punten met elkaar te verbinden, alle Gnd-punten met elkaar te verbinden en vervolgens iedere keer van de Signaal uit met de Signaal in van de volgende neoPixel te verbinden. Op het einde zorg je dat de Signaal in van eerste pixel kan verbonden worden met je Arduino.
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/solderen-stap01.jpg)
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/solderen-stap02.jpg)
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/solderen-stap03.jpg)
- neoPixels detecteren automatisch het hoeveelste ledje ze in de ketting zijn, wat het zeer handig maakt om ze te besutren.

# Verbinden met de Arduino
- Je kan de neoPixels rechtstreeks op een breakout board solderen, maar het is handiger als je ze los kan koppelen om ze eenvoudig aan en uit te doen. Aangezien er drie signalen van de Arduino naar de neoPixels moeten gaan (Vcc, Gnd en Signaal in), is een stereo mini-jack handig.
- Op zich maakt het niet uit welke draad je met welke pin verbindt, zolang je maar weet welke je met welke verbindt. Dit heb je straks nodig om de vrouwelijke kant van de mini-jack te solderen.
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/solderen-stap04.png)
- De vrouwelijke kant van je mini-jack verbind je in functie van hoe je de draadjes aan de mannelijke kant gesoldeerd hebt. Vin verbindt je met 3.3V, Gnd met gnd en de Signaal in via een 470Ohm weerstand (of een weerstand tussen 300 en 500 Ohm) met poort 10 op je arduino. Deze weerstand is niet nodig om het te laten werken, maar zorgt wel dat je neoPixels minder snel kapot geraken.
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/howto/schema.png)
- je kan de neoPixels testen met de strandtest die in de arduino library zit. In de Arduino IDE kies je 'file' > 'examples' > 'Adafruit_NeoPixel' > 'strandtest'. Zet de poort in de code van 6 naar 10 en test het.
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/aangesloten.jpg)

- Voor de finale versie is het proper om dit op een stukje soldeerplaat te solderen en met de juiste afmetingen maak je je eigen Arduino shield.
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/shield-bovenkant.jpg)
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/shield-onderkant.jpg)
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/shield-arduino-links.jpg)
![neoPixels solderen](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/shield-arduino-rechts.jpg)

# Wifi instellen op de arduino Yun
- Als de Arduino Yun nog niet geconfigureerd is, maakt hij zelf een wifi-netwerk met de naam 'Arduino Yun-XXXXXXXXXXXX'. Connecteer met dit wifi-netwerk.
- Open de webpagina http://arduino.local. Je krijgt nu een pagina in arduino stijl met een formulier om in te loggen.
![stap 1](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap01.png)
- Het standaard wachtwoord is 'arduino'.
- geef je Arduino een naam (bv koffiezet) en stel een admin wachtwoord in
![stap 2](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap02.png)
- Kies het wifi netwerk waarmee je wil verbinden, vul het wifi-wachtwoord in
![stap 3](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap03.png)
- Onder de knop 'configure & restart' staat nog een optie die belangrijk is voor dit project: Rest api access, zet deze op 'open'. Info over de Web services op de Arduino Yun: http://arduino.cc/en/Guide/ArduinoYun#toc5
![stap 4](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap04.png)
- Kies nu 'Configure & restart'. De Arduino herstart en connecteert terug met je eigen wifi.

# Arduino code
- Je hebt de Arduino IDE 1.5 nodig (momenteel misschien nog in beta, maar is geen probleem). Kies het juiste board uit de lijst via 'tools' > 'board'
- Yun moet stroom hebben via usb kabel, hoeft niet via kabel met je computer verbonden te zijn (wel op hetzelfde wifi netwerk). Kies de juiste poort via 'tools' > 'port'
- laad de code op: https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/hartje_met_website.ino

# Communicatie tussen Arduino en website
- Om de 15 seconden gaat de arduino connecteren met een bepaald webadres. Het resutlaat hiervan is een string met data in van het formaat: rodekleur|groenekleur|blauwekleur|beweging|snelheid|.
- Als je bv naar http://www.nerdland.be/api/arduino/hartje/random surft, zal je zien dat iedere keer je deze pagina laadt er een nieuwe willekeurige string klaar staat.
- Op http://www.nerdland.be/hartje is er een wachtrij systeem rond gebouwd, maar je kan zelf een eenvoudige applicatie maken die op een bepaalde url een string klaarzet. Pas de code voor je Arduino zo aan dat de Arduino op dit adres deze code gaat ophalen.

# Afwerking
- Mocht je in een fablab passeren of een lasercutter hebben, dan kan je met volgend ontwerp een doosje snijden voor je arduino: https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/arduinodoosje.svg. Dit doosje is gemaakt met de geweldige plugin voor inkscape: [Tabbed Box Maker](http://www.keppel.demon.co.uk/111000/111000.html)
- Combineer met een batterij, bv een [mobile power bank](http://www.dx.com/p/bp-5s-ultra-thin-6000mah-mobile-power-source-bank-for-iphone-5s-samsung-htc-black-grey-309071#.VCrH2CmSxYU). Voordeel hiervan is dat die 5v geeft en een hoge mAh heeft.
- resultaat:
![resultaat](https://raw.githubusercontent.com/nerdlandbe/hartje_met_website/master/footage/afgewerkt.jpg)

# referenties:
- http://www.homautomation.org/2013/10/01/playing-with-arduino-yun/
- http://arduino.cc/en/Main/ArduinoBoardYun
- http://arduino.cc/en/Guide/ArduinoYun
- http://www.adafruit.com/category/168
- http://www.djresource.eu/images/topics/tricks/cable_schema.jpg
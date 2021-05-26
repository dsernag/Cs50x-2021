-- Keep a log of any SQL queries you execute as you solve the mystery.
--1) "Chamberlin Street" fué el robo (id 296)
SELECT * FROM crime_scene_reports 
WHERE month = 7 AND day = 28;

--2) El robo ocurrió a las 10:15 am del 28 de julio.
    --Al revisar los registros de entrada al palacio de justica:

SELECT * FROM courthouse_security_logs 
WHERE month = 7 AND day = 28
AND hour = 10; 
--Entre las 10:16 y las 10:20 salieron dos placas:
    --5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7

--3) Revisamos las entrevistas:
SELECT * FROM interviews
WHERE month = 7 AND day = 28;
--Ruth:Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--Raymond:As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

--De las entrevistas sabemos dos cosas, las placas, el dinero sacado y la llamada
--Las placas ya están en el numeral 2
--El retiro de dinero en la fifer street puede ser de:
--28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156,26013199

--4) Miremos de quién son esas cuentas:
SELECT * FROM bank_accounts
WHERE account_number
IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156,26013199);

--4.1) También puedo mirar los nombres de esas ID
--28500762= 467400 /2014 = Danielle	(389) 555-5198	8496433585	4328GD8
--28296815= 395717 /2014 = Bobby (826) 555-1652	9878712108	30G67EN
--76054385= 449774 /2015 = Madison (286) 555-6063	1988161715	1106N58
--49610011= 686048 /2010 = Ernest	(367) 555-5533	5773159633	94KL13X
--16153065= 458378 /2012 = Roy	(122) 555-4581	4408372428	QX4YZN3
--25506511= 396669 /2014 = Elizabeth (829) 555-5269	7049073643	L93JTIZ
--81061156= 438727 /2018 = Victoria (338) 555-6650	9586786673	8X428L0
--26013199= 514354 /2012 = Russell	(770) 555-1861	3592750733	322W7JE

--5) De este query se observa que el Único que coincide con el dinero y la placa es Ernest
SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs 
WHERE month = 7 AND day = 28
AND hour = 10 AND minute IN (16,18,19,20));

--Ernest es el culpable. Ahora, ¿Con quién?
--Según Raymond la llamada fué corta, así que:

--6) Vamos a ver las llamadas el día 28 de Ernest:
SELECT phone_number FROM people WHERE name = "Ernest";
--La llamada de 45 segundos fué con (375) 555-8161
SELECT * FROM people WHERE phone_number = "(375) 555-8161"

--Su complice es Berthold id = 864400 license_plate = 4V16VO0

--Ahora bien, ¿a dónde escaparon?

--7) Del pasaporte de Ernest 5773159633 puedo saber el vuelo:
--Y de ahí podemos saber el destino y qué aeropuerto es:
SELECT * FROM airports WHERE id =
(SELECT destination_airport_id FROM flights 
WHERE id = (SELECT flight_id FROM  passengers WHERE passport_number = 5773159633));

--Finalmente van para Londres!!!!!
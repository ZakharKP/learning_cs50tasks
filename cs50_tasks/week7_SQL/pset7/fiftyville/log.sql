-- Keep a log of any SQL queries you execute as you solve the mystery.

-- See infomacion from crime_scene_reports about CS50
SELECT * FROM crime_scene_reports WHERE description LIKE "%CS50%";

-- get: date 28-07-2020 and there was intervie and time 10:15am

-- read intervie from 28-7-2020
SELECT * FROM interviews WHERE day = 28 AND year = 2020 AND month = 7;

/*
158 | Jose | It is a little souvenir from the King of Bohemia
in return for my assistance in the case of the Irene Adler papers.”
159 | Eugene | when Mr. Windibank came back from France
he was very annoyed at your having gone to the ball.”
160 | Barbara | “You had my note?” --deep harsh voice and a strongly marked German accent.
“I told you that I would call.” --which to address.
161 | Ruth | Sometime within ten minutes of the theft, == 10.25 !!!!!!!!!!!
I saw the thief get into a car in the courthouse parking lot and drive away.
If you have security footage from the courthouse parking lot,
you might want to look for cars that left the parking lot in that time frame.
162 | Eugene | Earlier this morning, house, -- ATM on Fifer Street !!!!!!!
and saw the thief there withdrawing some money.
163 | Raymond  | As the thief was leaving the courthouse,
I heard the thief say -- to take the earliest *!!! flight out of Fiftyville tomorrow. == 29.07.2020 !!!!!!!!
The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- find whall activity from 10.15 to 10.35 in courthouse_security_logs

SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7
AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 35;

/*
260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55
"5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55"
*/

-- find whall withdraw transaction on fifer street at 28.07.2020
SELECT * FROM atm_transactions
WHERE transaction_type = "withdraw" AND year = 2020 AND day = 28 AND month = 7
AND atm_location = "Fifer Street";

/*
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35
28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199
*/

--Find persons who withdraw money and get out from campus
SELECT * FROM people WHERE license_plate IN(
"5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55") AND id IN(
SELECT person_id FROM bank_accounts WHERE account_number IN(
28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199));
 /*
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
passport_number IN (7049073643, 8496433585, 3592750733, 5773159633)
 */

 -- Find Flights 29.07.2020 where passengers was
 ----whith that passport_number IN (7049073643, 8496433585, 3592750733, 5773159633)
SELECT id FROM flights WHERE id IN(
SELECT flight_id FROM passengers
WHERE passport_number IN (7049073643, 8496433585, 3592750733, 5773159633))
AND day = 29 AND month = 7 AND year = 2020;

/*flight_id IN(18, 36)
*/

-- find passport of passenger from list of passport whith we find before  and fly id
SELECT passport_number FROM passengers
WHERE passport_number IN(7049073643, 8496433585, 3592750733, 5773159633)
AND flight_id IN(18, 36);

/*
passport_number IN(3592750733, 5773159633, 8496433585)
*/

--take phones info about that peoples
SELECT phone_number FROM people WHERE passport_number IN(3592750733, 5773159633, 8496433585);

/*
phone number IN("(389) 555-5198", "(770) 555-1861", "(367) 555-5533")
*/

-- find calls from that numbers at 28.07.2020
SELECT * FROM phone_calls
WHERE day = 28 AND year = 2020 AND month = 7
AND caller IN("(389) 555-5198", "(770) 555-1861", "(367) 555-5533");
/*
id | caller | receiver | year | month | day | duration
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
236 | (367) 555-5533 | (344) 555-9601 | 2020 | 7 | 28 | 120
245 | (367) 555-5533 | (022) 555-4052 | 2020 | 7 | 28 | 241
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
285 | (367) 555-5533 | (704) 555-5790 | 2020 | 7 | 28 | 75

phone number IN("(770) 555-1861", "(367) 555-5533")
*/
-- find passports of that person
sqlite> SELECT passport_number FROM people WHERE phone_number IN("(770) 555-1861", "(367) 555-5533");
/*
passport_number IN(3592750733, 5773159633)
*/
-- take flight where that two peson was
SELECT * FROM flights WHERE id IN(
SELECT flight_id FROM passengers WHERE passport_number IN (3592750733, 5773159633))
AND day = 29 AND month = 7 AND year = 2020;
/*
id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
earliest is at 8.00 whith id 36 we cath him we need to khow passport, phone number and destination
*/
SELECT passport_number FROM passengers WHERE passport_number IN (3592750733, 5773159633)
AND flight_id = 36;
/* passport_number = 5773159633 */

SELECT * FROM airports WHERE id = 4;
/*.  4 | LHR | Heathrow Airport | London  */

SELECT * FROM people WHERE passport_number = 5773159633;
/*id | name | phone_number | passport_number | license_plate
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
*/

-- find to who ernest call
SELECT receiver FROM phone_calls
WHERE day = 28 AND year = 2020 AND month = 7
AND caller IN("(367) 555-5533");

/*
receiver
(375) 555-8161
(344) 555-9601
(022) 555-4052
(704) 555-5790
("(375) 555-8161", "(344) 555-9601", "(022) 555-4052", "(704) 555-5790")

*/

SELECT * FROM people
WHERE phone_number IN("(375) 555-8161", "(344) 555-9601",
"(022) 555-4052", "(704) 555-5790");

/*
315221 | Gregory | (022) 555-4052 | 3355598951 | V4C670D
652398 | Carl | (704) 555-5790 | 7771405611 | 81MZ921
864400 | Berthold | (375) 555-8161 |  | 4V16VO0
985497 | Deborah | (344) 555-9601 | 8714200946 | 10I5658
*/
-- it's not ernest i think it;s Russel he esqupe to
SELECT * FROM airports;
/*
1 | ORD | O'Hare International Airport | Chicago
2 | PEK | Beijing Capital International Airport | Beijing
3 | LAX | Los Angeles International Airport | Los Angeles
4 | LHR | Heathrow Airport | London
5 | DFS | Dallas/Fort Worth International Airport | Dallas
6 | BOS | Logan International Airport | Boston
7 | DXB | Dubai International Airport | Dubai
8 | CSF | Fiftyville Regional Airport | Fiftyville
9 | HND | Tokyo International Airport | Tokyo
10 | CDG | Charles de Gaulle Airport | Paris
11 | SFO | San Francisco International Airport | San Francisco
12 | DEL | Indira Gandhi International Airport | Delhi
BOSTON
*/

--find his helper

SELECT * FROM people
WHERE phone_number = "(725) 555-3243";
/*
id | name | phone_number | passport_number | license_plate
847116 | Philip | (725) 555-3243 | 3391710505 | GW362R6
sqlite> */
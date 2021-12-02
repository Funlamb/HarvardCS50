-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

tables :
--  To see what is in the DB
schema crime_scene_reports : To see what is in the crime_scene_reports

-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );

SELECT description FROM crime_scene_reports WHERE YEAR = 2020 AND month = 7 AND day = 28 AND street LIKE "Chamberlin Street";
--      Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
--      Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

schema interviews
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );

SELECT year, transcript FROM interviews;
-- Just wanted to see how many interviews there were in the DB

-- >.schema
-- Wanted to see how the DB was orginized

SELECT name FROM interviews WHERE day = 28 AND year = 2020 AND month = 7;
-- Forgot to add the transcript.

SELECT name, transcript FROM interviews WHERE day = 28 AND year = 2020 AND month = 7;

-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
--      If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized. 
--      Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. 
--      In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
--      The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT caller, receiver, duration FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020;
-- Too complicated to make an assumption on who it is. Need to figure out what the duration integer is in units.

SELECT license_plate, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;
-- Hoping to find our more about the vehicales that where near the scene of the crime

SELECT license_plate, hour, minute, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;
-- Trying to get a more detailed view with times

SELECT atm_location FROM atm_transactions;
-- Looked at what locations were in DB

SELECT transaction_type, amount FROM atm_transactions WHERE atm_location LIKE "Fifer Street" AND year = 2020 AND month = 7 AND day = 28;
-- Showed transactions but nothing of intrest yet

SELECT city FROM airports;
-- Want to see the airports

SELECT flights.origin_airport_id, flights.destination_airport_id, flights.hour, flights.minute FROM flights 
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE year = 2020 AND month = 7 AND day = 29
    ORDER BY flights.hour ASC;
-- Find out what flights were leaving the next day

-- Left parking lot within ten minutes, withdrew money from bank, called a friend for less than 1 minute
-- Join courthouse_security_logs with people by licence_plate, Join people to phone_calls
SELECT people.name, phone_calls.receiver,  FROM people 
    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    JOIN bank_accounts ON bank_accounts.person_id = people.id 
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 -- Shows right day
    AND phone_calls.duration <= 60 -- Shows right phone call duration
    
-- Join courthouse_security_logs with people by licence_plate, Join people to phone_calls, Join bank_accounts with people, 
SELECT people.name, phone_calls.receiver,  FROM people 
    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    JOIN bank_accounts ON bank_accounts.person_id = people.id 
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 -- Shows right day
    AND phone_calls.duration <= 60 -- Shows right phone call duration
    AND courthouse_security_logs.activity LIKE "exit" -- Shows correct direction of the car
    AND courthouse_security_logs.year = 2020 AND courthouse_security_logs.month = 7 AND courthouse_security_logs.day = 28 -- Shows right day at courthouse
    AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute <= 25 -- Shows the right time at courthouse
    AND atm_transactions.transaction_type LIKE "withdraw";

-- Join courthouse_security_logs with people by licence_plate, Join people to phone_calls, Join bank_accounts with people,  Join passangers to flights,
SELECT people.name, phone_calls.receiver, airports.city, flights.day FROM people 
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    JOIN bank_accounts ON bank_accounts.person_id = people.id 
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.destination_airport_id = airports.id
    WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 -- Shows right day
    AND phone_calls.duration <= 60 -- Shows right phone call duration
    AND courthouse_security_logs.activity LIKE "exit" -- Shows correct direction of the car
    AND courthouse_security_logs.year = 2020 AND courthouse_security_logs.month = 7 AND courthouse_security_logs.day = 28 -- Shows right day at courthouse
    AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute <= 25 -- Shows the right time at courthouse
    AND atm_transactions.transaction_type LIKE "withdraw";
-- Getting errors in my code. I think I need to try and find each piece individually 
-- Fixed the code but the view is too narrow. I think I need to find each piece individually
-- Ernest|(375) 555-8161|London|29
-- Ernest|(375) 555-8161|London|29
-- Russell|(725) 555-3243|Boston|29
-- Russell|(725) 555-3243|Fiftyville|30
-- Russell|(725) 555-3243|Dallas|30
-- I'm pretty sure its Ernest going to London calling whoever is at the 375 number

SELECT people.name FROM people
    WHERE people.phone_number LIKE "(375) 555-8161";
-- Berthold
    